 #include <iostream>
 #include <stack>
 #include <string>
 using namespace std;
 
 struct Node {
     char val;
     Node* left;
     Node* right;
     Node(char c) : val(c), left(nullptr), right(nullptr) {}
 };
 
 // 括号表示法建树
 // 格式: A(B(,C(D,)),E(F(G(H,K),),))
 Node* buildTree(const string& s) {
     stack<Node*> st;
     Node* root = nullptr;
     Node* cur = nullptr;
     int tag = 0; // 0=左孩子, 1=右孩子
 
     for (int i = 0; i < (int)s.size(); i++) {
         char c = s[i];
         if (c == '(') {
             // 当前节点要有孩子，压栈，准备读左孩子
             st.push(cur);
             tag = 0;
         } else if (c == ')') {
             // 回到父节点
             st.pop();
         } else if (c == ',') {
             // 切换到右孩子
             tag = 1;
         } else {
             // 字母，创建节点
             Node* node = new Node(c);
             if (st.empty()) {
                 // 根节点
                 root = node;
             } else {
                 if (tag == 0) {
                     st.top()->left = node;
                 } else {
                     st.top()->right = node;
                 }
             }
             cur = node;
         }
     }
     return root;
 }
 
 // 非递归先序遍历: 根-左-右
 void preOrder(Node* root) {
     if (!root) return;
     stack<Node*> st;
     st.push(root);
     while (!st.empty()) {
         Node* node = st.top(); st.pop();
         cout << node->val;
         // 先压右孩子，再压左孩子（保证左孩子先出栈）
         if (node->right) st.push(node->right);
         if (node->left)  st.push(node->left);
     }
     cout << "\n";
 }
 
 // 非递归中序遍历: 左-根-右
 void inOrder(Node* root) {
     stack<Node*> st;
     Node* cur = root;
     while (cur || !st.empty()) {
         // 一路向左压栈
         while (cur) {
             st.push(cur);
             cur = cur->left;
         }
         // 弹出并访问
         cur = st.top(); st.pop();
         cout << cur->val;
         // 转向右子树
         cur = cur->right;
     }
     cout << "\n";
 }
 
 // 非递归后序遍历: 左-右-根
 // 方法：先序变形(根-右-左)的逆序即为后序(左-右-根)
 // 使用两个栈：第一个栈做"根-右-左"，结果压入第二个栈，最后反向输出
 void postOrder(Node* root) {
     if (!root) return;
     stack<Node*> s1, s2;
     s1.push(root);
     while (!s1.empty()) {
         Node* node = s1.top(); s1.pop();
         s2.push(node);
         // 先压左孩子，再压右孩子（s1弹出顺序：根-右-左，s2收集后逆序：左-右-根）
         if (node->left)  s1.push(node->left);
         if (node->right) s1.push(node->right);
     }
     while (!s2.empty()) {
         cout << s2.top()->val;
         s2.pop();
     }
     cout << "\n";
 }
 
 int main() {
     string s;
     cin >> s;
     Node* root = buildTree(s);
     preOrder(root);
     inOrder(root);
     postOrder(root);
     return 0;
 }
