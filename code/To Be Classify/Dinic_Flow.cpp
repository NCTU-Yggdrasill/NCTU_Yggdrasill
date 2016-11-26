#define maxnode (200+10) 
#define maxedge (400+10)
#define INF 1023456789
#include<bits/stdc++.h>
using namespace std;
int node, src, dest, nedge; 
int head[maxnode], point[maxedge], nxt[maxedge], flow[maxedge], capa[maxedge]; 
int dist[maxnode], Q[maxnode], work[maxnode]; 
//set number of node, source, and destination (one base)
void init(int _node, int _src, int _dest) { 
    node = _node; 
    src = _src; 
    dest = _dest; 
    nedge = 0; 
    memset(point, -1, sizeof(point)); 
    for (int i = 1; i <= node; i++) head[i] = -1; 
    nedge = 0; 
} 
void add_edge(int u, int v, int c1, int c2) { 
    point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0, nxt[nedge] = head[u], head[u] = (nedge++); 
    point[nedge] = u, capa[nedge] = c2, flow[nedge] = 0, nxt[nedge] = head[v], head[v] = (nedge++); 
} 
bool dinic_bfs() { 
    memset(dist, 255, sizeof (dist)); 
    dist[src] = 0; 
    int sizeQ = 0; 
    Q[sizeQ++] = src; 
    for (int cl = 0; cl < sizeQ; cl++) 
        for (int k = Q[cl], i = head[k]; i >= 0; i = nxt[i]) 
            if (flow[i] < capa[i] && dist[point[i]] < 0) { 
                dist[point[i]] = dist[k] + 1; 
                Q[sizeQ++] = point[i]; 
            } 
    return dist[dest] >= 0; 
} 
int dinic_dfs(int x, int exp) { 
    if (x == dest) return exp; 
    for (int &i = work[x]; i >= 0; i = nxt[i]) { 
        int v = point[i], tmp; 
        if (flow[i] < capa[i] && dist[v] == dist[x] + 1 && (tmp = dinic_dfs(v, min(exp, capa[i] - flow[i]))) > 0) { 
            flow[i] += tmp; 
            flow[i^1] -= tmp; 
            return tmp; 
        } 
    } 
    return 0; 
} 
int dinic_flow() { 
    int result = 0; 
    while (dinic_bfs()) { 
        for (int i = 0; i < node; i++) work[i] = head[i]; 
        while (1) { 
            int delta = dinic_dfs(src, INF); 
            if (delta == 0) break; 
            result += delta; 
        } 
    } 
    return result; 
} 
int main(){
	int n,m,x,y,z;
	while(scanf("%d%d",&n,&m)==2){
		init(m,1,m);
		for(int i=0;i<n;i++){
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,z,0);
		}
		printf("%d\n",dinic_flow());
	}
	return 0;
}
