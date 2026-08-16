"""
Windows 桌宠程序 — 使用 Python + Tkinter + Pillow
================================================
一只会在桌面上自动走动、发呆、坐下的透明背景宠物。

运行方法：
  1. pip install -r requirements.txt
  2. python main.py

交互：
  - 左键点击宠物 → 弹出随机气泡文字
  - 右键点击宠物 → 弹出菜单（退出）
"""

import tkinter as tk
from tkinter import Menu, Label
import random
import math
import sys
import os
from PIL import Image, ImageTk

# 兼容 Pillow 新旧版本的 LANCZOS 常量
try:
    _LANCZOS = Image.Resampling.LANCZOS   # Pillow >= 10.0.0
except AttributeError:
    _LANCZOS = _LANCZOS              # Pillow < 10.0.0

# ==================== 配置常量 ====================

# 图片路径（请按实际情况修改）
IMAGE_PATH = r"D:\Desktop\table pet\29f7f92eff77daca1e9a364bd0e2e9efae9980a51c2444-GCcgaA_fw658.webp"

PET_WIDTH = 128         # 宠物显示宽度（像素），高度按比例自动计算
WALK_SPEED = 2.5        # 行走速度（像素/帧）
TICK_MS = 50            # 动画帧间隔（毫秒），20 FPS
STATE_MIN = 5           # 状态切换最小间隔（秒）
STATE_MAX = 10          # 状态切换最大间隔（秒）
IDLE_DURATION = (3, 6)  # 发呆持续时长范围（秒）
SIT_DURATION = (2, 5)   # 坐下持续时长范围（秒）

# Tkinter 透明色（选一个极不可能出现在图片中的颜色）
TRANS_COLOR = "#010203"

# 气泡文字池
BUBBLE_TEXTS = [
    "你好～",
    "别卷啦！",
    "摸摸头～",
    "今天也要开心哦",
    "累了就休息吧",
    "加油！",
    "我在看着你哦",
    "嘿嘿～",
    "喝杯水吧",
    "起来走走～",
    "最喜欢你了！",
    "咕噜咕噜…",
    "不要戳我呀 >_<",
    "喵～（假装自己是猫）",
]

# ==================== 桌宠类 ====================


class DesktopPet:
    """桌面宠物主类，管理窗口、动画、状态和交互。"""

    def __init__(self):
        # ---- 根窗口 ----
        self.root = tk.Tk()

        # 屏幕尺寸
        self.scr_w = self.root.winfo_screenwidth()
        self.scr_h = self.root.winfo_screenheight()

        # 初始位置（随机，避开边缘）
        self.x = float(random.randint(150, max(150, self.scr_w - 300)))
        self.y = float(random.randint(100, max(100, self.scr_h - 400)))

        # 移动方向与速度
        if random.random() < 0.5:
            self.dx = WALK_SPEED
            self.flip = 1       # 1 = 正常（面朝右），-1 = 翻转（面朝左）
        else:
            self.dx = -WALK_SPEED
            self.flip = -1
        self.dy = random.uniform(-0.3, 0.3) * WALK_SPEED

        # 状态：walk / idle / sit
        self.state = "walk"
        self.state_timer = 0.0          # 当前状态已持续秒数

        # 发呆 / 坐下专用计时
        self.special_elapsed = 0.0      # 已流逝秒数
        self.special_duration = 0.0     # 本次持续目标秒数

        # 气泡窗口
        self.bubble_win = None
        self._bubble_job = None         # after job ID

        # 当前显示的 PhotoImage
        self.photo = None

        # ---- 加载图片 ----
        self.pet_h = 0                  # 缩放后的图片高度
        self._base_normal = None        # RGBA 正常朝向
        self._base_flipped = None       # RGBA 镜像朝向
        self._load_image()

        # ---- 搭建窗口 ----
        self._setup_window()

        # ---- 绑定事件 ----
        self._bind_events()

        # ---- 启动循环 ----
        self._tick()                    # 动画帧循环
        self._schedule_state()          # 状态切换定时器

    # ---------- 图片加载 ----------

    def _load_image(self):
        """加载图片，缩放并预生成正常/翻转两个 RGBA 版本。"""
        try:
            raw = Image.open(IMAGE_PATH)
        except FileNotFoundError:
            print(f"❌ 找不到图片文件：{IMAGE_PATH}")
            print("   请修改 main.py 顶部的 IMAGE_PATH 为正确的图片路径。")
            sys.exit(1)
        except Exception as e:
            print(f"❌ 图片加载失败：{e}")
            sys.exit(1)

        # 确保为 RGBA 模式（支持透明通道）
        if raw.mode != "RGBA":
            raw = raw.convert("RGBA")

        # 等比例缩放
        w, h = raw.size
        self.pet_h = int(h * PET_WIDTH / w)
        raw = raw.resize((PET_WIDTH, self.pet_h), _LANCZOS)

        # 保存 RGBA 原图与镜像图（后续每帧在此基础上缩放 + 合成）
        self._base_normal = raw
        self._base_flipped = raw.transpose(Image.FLIP_LEFT_RIGHT)

    # ---------- 窗口设置 ----------

    def _setup_window(self):
        """创建无边框、置顶、透明色窗口。"""
        self.root.overrideredirect(True)                        # 无标题栏/边框
        self.root.attributes("-topmost", True)                  # 始终置顶
        self.root.attributes("-transparentcolor", TRANS_COLOR)  # 指定色透明
        self.root.geometry(
            f"{PET_WIDTH}x{self.pet_h}+{int(self.x)}+{int(self.y)}"
        )

        # 画布（背景填透明色）
        self.canvas = tk.Canvas(
            self.root,
            width=PET_WIDTH,
            height=self.pet_h,
            bg=TRANS_COLOR,
            highlightthickness=0,
            bd=0,
        )
        self.canvas.pack()

        # 图片元素（后续通过 itemconfig 更新内容）
        self._img_id = self.canvas.create_image(
            PET_WIDTH // 2, self.pet_h // 2, anchor="center"
        )

    # ---------- 事件绑定 ----------

    def _bind_events(self):
        """绑定鼠标事件到画布和根窗口。"""
        # 左键单击 → 气泡
        self.canvas.bind("<Button-1>", self._on_left_click)
        self.root.bind("<Button-1>", self._on_left_click)
        # 右键单击 → 菜单
        self.canvas.bind("<Button-3>", self._on_right_click)
        self.root.bind("<Button-3>", self._on_right_click)

    def _on_left_click(self, event):
        """左键：弹出随机气泡文字。"""
        self._show_bubble()

    def _on_right_click(self, event):
        """右键：弹出退出菜单。"""
        menu = Menu(self.root, tearoff=0)
        menu.add_command(label="退出 (●'◡'●) 拜拜", command=self._quit)
        # 菜单显示在鼠标点击位置
        x = self.root.winfo_rootx() + event.x
        y = self.root.winfo_rooty() + event.y
        menu.post(x, y)

    def _show_bubble(self):
        """在宠物上方显示对话气泡，3 秒后自动消失。"""
        # 先消除已有气泡
        self._destroy_bubble()

        text = random.choice(BUBBLE_TEXTS)

        bw = tk.Toplevel(self.root)
        bw.overrideredirect(True)
        bw.attributes("-topmost", True)

        lbl = Label(
            bw,
            text=text,
            font=("Microsoft YaHei", 11, "bold"),
            bg="#FFECD2",       # 暖色气泡底
            fg="#5D4037",       # 深棕文字
            padx=14,
            pady=8,
        )
        lbl.pack()

        # 定位：宠物正上方居中
        bw.update_idletasks()
        bw_w = bw.winfo_width()
        bw_h = bw.winfo_height()
        bx = int(self.x + PET_WIDTH / 2 - bw_w / 2)
        by = int(self.y - bw_h - 10)
        # 防止超出屏幕上边缘
        if by < 0:
            by = int(self.y + self.pet_h + 5)
        bw.geometry(f"+{bx}+{by}")

        self.bubble_win = bw
        # 3 秒后自动消失
        self._bubble_job = self.root.after(3000, self._destroy_bubble)

    def _destroy_bubble(self):
        """销毁气泡窗口。"""
        if self._bubble_job is not None:
            self.root.after_cancel(self._bubble_job)
            self._bubble_job = None
        if self.bubble_win is not None:
            try:
                self.bubble_win.destroy()
            except tk.TclError:
                pass
            self.bubble_win = None

    def _quit(self):
        """退出程序。"""
        self._destroy_bubble()
        self.root.destroy()
        sys.exit(0)

    # ---------- 动画主循环 ----------

    def _tick(self):
        """每 TICK_MS 毫秒执行一帧。"""
        dt = TICK_MS / 1000.0       # 本帧时长（秒）
        self.state_timer += dt

        if self.state == "walk":
            self._update_walk(dt)
        elif self.state == "idle":
            self.special_elapsed += dt
            if self.special_elapsed >= self.special_duration:
                self._enter_walk()
            else:
                self._update_idle()
        elif self.state == "sit":
            self.special_elapsed += dt
            if self.special_elapsed >= self.special_duration:
                self._enter_walk()
            # 坐下时不移动，只需等计时结束

        self._check_bounds()
        self._redraw()
        self.root.after(TICK_MS, self._tick)

    def _update_walk(self, dt):
        """行走状态：按当前方向移动，偶尔随机微调。"""
        # 小概率随机改变纵向方向
        if random.random() < 0.015:
            self.dy += random.uniform(-0.4, 0.4) * WALK_SPEED
            # 限制纵向速度
            limit = WALK_SPEED * 0.7
            self.dy = max(-limit, min(limit, self.dy))

        self.x += self.dx
        self.y += self.dy

    def _update_idle(self):
        """发呆状态：微微原地晃动。"""
        t = self.special_elapsed
        self.x += math.sin(t * 2.0) * 0.7
        self.y += math.cos(t * 1.7) * 0.5

    def _check_bounds(self):
        """边界检测 + 碰到左右边缘水平翻转。"""
        margin = 3

        # 左边界 → 翻转，向右走
        if self.x < margin:
            self.x = margin
            self.dx = abs(self.dx) if self.state == "walk" else WALK_SPEED
            self.flip = 1

        # 右边界 → 翻转，向左走
        right_limit = self.scr_w - PET_WIDTH - margin
        if self.x > right_limit:
            self.x = right_limit
            self.dx = -abs(self.dx) if self.state == "walk" else -WALK_SPEED
            self.flip = -1

        # 上边界
        if self.y < margin:
            self.y = margin
            self.dy = abs(self.dy) if self.state == "walk" else WALK_SPEED * 0.3

        # 下边界（留出任务栏高度约 55px）
        bottom_limit = self.scr_h - self.pet_h - 55
        if self.y > bottom_limit:
            self.y = bottom_limit
            self.dy = -abs(self.dy) if self.state == "walk" else -WALK_SPEED * 0.3

    def _redraw(self):
        """根据当前 flip / state 生成显示图片并更新画布和窗口位置。"""
        # 1. 选择基础 RGBA 图像
        if self.flip == -1:
            src = self._base_flipped
        else:
            src = self._base_normal

        # 2. 按状态缩放
        if self.state == "sit":
            # 坐下：缩小到 80%
            w = int(PET_WIDTH * 0.80)
            h = int(self.pet_h * 0.80)
            src = src.resize((w, h), _LANCZOS)
        elif self.state == "idle":
            # 发呆：呼吸感缩放
            s = 1.0 + 0.04 * math.sin(self.special_elapsed * 3.5)
            w = int(PET_WIDTH * s)
            h = int(self.pet_h * s)
            src = src.resize((w, h), _LANCZOS)

        # 3. 合成到透明背景色上（让透明区域变成 TRANS_COLOR）
        bg = Image.new("RGBA", src.size, (1, 2, 3, 255))
        bg.paste(src, (0, 0), src)
        rgb = bg.convert("RGB")

        # 4. 转为 Tkinter PhotoImage 并更新画布
        self.photo = ImageTk.PhotoImage(rgb)
        self.canvas.itemconfig(self._img_id, image=self.photo)

        # 5. 移动窗口
        self.root.geometry(f"+{int(self.x)}+{int(self.y)}")

    # ---------- 状态切换 ----------

    def _schedule_state(self):
        """定时触发状态切换（仅在行走状态下可能切到其他状态）。"""
        delay = random.randint(STATE_MIN, STATE_MAX) * 1000
        self.root.after(delay, self._on_state_timer)

    def _on_state_timer(self):
        """状态定时器回调。"""
        if self.state == "walk":
            r = random.random()
            if r < 0.35:
                self._enter_idle()
            elif r < 0.60:
                self._enter_sit()
            # else: 继续保持行走
        self._schedule_state()  # 预约下一次切换

    def _enter_walk(self):
        """进入行走状态。"""
        self.state = "walk"
        self.state_timer = 0.0
        # 随机初始方向
        if random.random() < 0.5:
            self.dx = WALK_SPEED
            self.flip = 1
        else:
            self.dx = -WALK_SPEED
            self.flip = -1
        self.dy = random.uniform(-0.3, 0.3) * WALK_SPEED

    def _enter_idle(self):
        """进入发呆状态。"""
        self.state = "idle"
        self.state_timer = 0.0
        self.special_elapsed = 0.0
        self.special_duration = random.uniform(*IDLE_DURATION)
        self.dx = 0.0
        self.dy = 0.0

    def _enter_sit(self):
        """进入坐下状态。"""
        self.state = "sit"
        self.state_timer = 0.0
        self.special_elapsed = 0.0
        self.special_duration = random.uniform(*SIT_DURATION)
        self.dx = 0.0
        self.dy = 0.0

    # ---------- 入口 ----------

    def run(self):
        """启动 Tkinter 主循环。"""
        self.root.mainloop()


# ==================== 程序入口 ====================

if __name__ == "__main__":
    print("🐱 桌面宠物启动中…")
    print("   左键点击 → 气泡对话")
    print("   右键点击 → 退出菜单")
    print("   按 Ctrl+C 可强制退出（在终端中）")
    app = DesktopPet()
    app.run()
