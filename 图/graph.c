#include"graph.h"

// 建立邻接矩阵（带权有向图，输入格式：起点、终点、权值）
void CreateMat(MGraph *G){
	int i,j,k;
	int u,v,w;
	printf("请输入带权有向图的顶点数n和边数e:\n");
	scanf("%d,%d", &G->n, &G->e);
	// 初始化边权为无穷大（32767表示无穷大）
	for(i=0;i<G->n;i++){
		for(j=0;j<G->n;j++){
			G->edgs[i][j]=32767;
		}
	}
	printf("请输入%d条边的信息（起点、终点、权值）：\n", G->e);
	for(k=0;k<G->e;k++){
		 scanf("%d,%d,%d", &u, &v, &w);
		 G->edgs[u][v] = w;
		 
		 
	}
}

// 建立邻接表
void CreateAdj(ALGraph *G){
	int i,j,k;
	int u,v,w;
	ArcNode *p;
	
	printf("请输入带权有向图的顶点数n和边数e:\n");
	scanf("%d,%d", &G->n, &G->e);
	
	// 初始化顶点
	for(int i=0;i<G->n;i++){
		G->vertices[i].data=i;
		G->vertices[i].firstarc=NULL;
		
	}
	
	 printf("请输入%d条边的信息（起点、终点、权值）：\n", G->e);
	for(int k=0;k<G->e;k++){
		scanf("%d,%d,%d", &u, &v, &w);
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=v;
		p->weight=w;
		p->nextarc=G->vertices[u].firstarc;
		G->vertices[u].firstarc=p;
	}
}

// 输出邻接矩阵
void DispMat(MGraph G){
	int i,j;
	printf("邻接矩阵:\n");
	for(int i=0;i<G.n;i++){
		for(int j=0;j<G.n;j++){
			if(G.edgs[i][j]==32767){
			printf("∞\t");	
			}else{
				 printf("%d\t", G.edgs[i][j]);
			}
		}
		printf("\n");
		
	}
}

// 输出邻接表
void DispAdj(ALGraph G){
	int i;
	ArcNode *p;
	printf("邻接表:\n");
	for(int i=0;i<G.n;i++){
		printf("顶点%d: ", i);
		p=G.vertices[i].firstarc;
		while(p){
			printf("-> [%d](%d) ", p->adjvex, p->weight);
			p=p->nextarc;
		}
		printf("\n");
	}
}


// 递归DFS
void DFS(ALGraph G,int v,int visited[]){
	int stack[MAXV],top=-1;
	ArcNode *p;
	int x,w;
	
	stack[++top]=v;
	visited[v]=1;
	printf("%d",v);
	
	while(top!=-1){
		x=stack[top];
		p=G.vertices[x].firstarc;
		while(p){
			w=p->adjvex;
			if(!visited[w]){
				visited[w]=-1;
			printf("%d ", w);
			stack[++top] = w;
			break;  // 找到一个就进栈，继续处理新栈顶	
			}
			p=p->nextarc;
		}
		if(p==NULL){
			top--;// 没有未访问邻接点，退栈
			
		}
	}
}

// BFS（用队列）
void BFS(ALGraph G, int v, int visited[]) {
    int queue[MAXV], front = 0, rear = 0;
    ArcNode *p;
    int x;

    queue[rear++] = v;
    visited[v] = 1;
    printf("%d ", v);

    while (front != rear) {
        x = queue[front++];
        p = G.vertices[x].firstarc;
        while (p) {
            if (!visited[p->adjvex]) {
                visited[p->adjvex] = 1;
                printf("%d ", p->adjvex);
                queue[rear++] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
}

// 深度优先生成树（记录父节点）
void DFSTree(ALGraph G, int v, int parent[]) {
    ArcNode *p;
    int w;
    parent[v] = -1;  // 根节点父节点为-1
    printf("DFSTree 边: ");
    p = G.vertices[v].firstarc;
    while (p) {
        w = p->adjvex;
        if (parent[w] == -1) {  // 未访问过
            parent[w] = v;
            printf("(%d,%d) ", v, w);
            DFSTree(G, w, parent);
        }
        p = p->nextarc;
    }
}

// 广度优先生成树（记录父节点）
void BFSTree(ALGraph G, int v, int parent[]) {
    int queue[MAXV], front = 0, rear = 0;
    ArcNode *p;
    int x, w;

    parent[v] = -1;
    queue[rear++] = v;

    while (front != rear) {
        x = queue[front++];
        p = G.vertices[x].firstarc;
        while (p) {
            w = p->adjvex;
            if (parent[w] == -1) {
                parent[w] = x;
                printf("(%d,%d) ", x, w);
                queue[rear++] = w;
            }
            p = p->nextarc;
        }
    }
}

// 销毁邻接矩阵（其实不需要，因为是静态数组）
void DestroyMat(MGraph *G) {
    G->n = G->e = 0;
}

// 销毁邻接表（释放所有节点）
void DestroyAdj(ALGraph *G) {
    int i;
    ArcNode *p, *q;
    for (i = 0; i < G->n; i++) {
        p = G->vertices[i].firstarc;
        while (p) {
            q = p;
            p = p->nextarc;
            free(q);
        }
        G->vertices[i].firstarc = NULL;
    }
    G->n = G->e = 0;
}
 
 









