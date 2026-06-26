#include<stdio.h>
#include<stdlib.h>

//DFS：邻接矩阵版
#define MAXV 1000
int visited[MAXV]={0};
int G[MAXV][MAXV];
int n;
void DFS(int v){
	visited[v]=1;
	printf("%d",v);
	for(int i=0;i<=n;i++){
		if(G[v][i]==1&&!visited[i]){
			DFS(i);
		}
	}
} 


#include<stack>
using namespace std;

void DFS_NonRecursive(int start){
	stack<int> s;
	visited[start]=1;
	s.push(start);
	
	while(!s.empty()){
		int v=s.top();
		s.pop();
		printf("%d",v);
		
		for(int i=0;i<n;i++){
			if(G[v][i]==1&&!visited[i]){
				visited[i]=1;
				s.push(i);
			}
		}
	}
}

//BFS：
#include<queue>
using namespace std;
void BFS(int start){
	queue<int > q;
	visited[start]=1;
	q.push(start);
	
	while(!q.empty()){
		int v=q.front();
		q.pop();
		printf("%d",v);
		
		
		for(int i=0;i<n;i++){
			if(G[v][i]==1&&!visited[i]){
				visited[i]=1;
				q.push(i);
			}
		}
	}
} 










/*实际应用场景
DFS应用：
迷宫求解? - 寻找一条路径
连通分量? - 计算图的连通块
拓扑排序? - 有向无环图的排序
检测环? - 判断图中是否有环
回溯算法? - 如N皇后、全排列
BFS应用：
最短路径? - 在无权图中找到最短路径
社交网络? - 查找N度好友
扩散问题? - 如病毒传播、火灾蔓延模拟
层次遍历? - 二叉树的层序遍历
最小步数? - 如华容道、八数码问题
选择建议：
需要最短路径或最小步数? → 用BFS
需要检查所有可能或回溯? → 用DFS
图很大但目标较浅 → 用BFS
图很深但目标可能在深处 → 用DFS
需要拓扑排序或检测环? → 用DFS
理解这两种搜索的区别和适用场景，是算法学习的重要基础！
*/













 
