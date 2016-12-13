int V;
bool adj[MAXN][MAXN];
int w[MAXN][MAXN];
int p[MAXN];
int m[MAXN];
int d[MAXN];
int c1[MAXN], c2[MAXN];
int q[MAXN], *qf, *qb;
int pp[MAXN];
int f(int x) {return x == pp[x] ? x : (pp[x] = f(pp[x]));}
void u(int x, int y) {pp[x] = y;}
int v[MAXN];
void path(int r, int x){
    if (r == x) return;
    if (d[x] == 0){
        path(r, p[p[x]]);
        int i = p[x], j = p[p[x]];
        m[i] = j; m[j] = i;
    }
    else if (d[x] == 1){
        path(m[x], c1[x]);
        path(r, c2[x]);
        int i = c1[x], j = c2[x];
        m[i] = j; m[j] = i;
    }
}
int lca(int x, int y, int r){
    int i = f(x), j = f(y);
    while (i != j && v[i] != 2 && v[j] != 1){
        v[i] = 1; v[j] = 2;
        if (i != r) i = f(p[i]);
        if (j != r) j = f(p[j]);
    }
    int b = i, z = j; if (v[j] == 1) swap(b, z);
    for (i = b; i != z; i = f(p[i])) v[i] = -1;
    v[z] = -1;
    return b;
}
void contract_one_side(int x, int y, int b){
    for (int i = f(x); i != b; i = f(p[i])){
        u(i, b);
        if (d[i] == 1) c1[i] = x, c2[i] = y, *qb++ = i;
    }
}
bool BFS(int r){
    for (int i=0; i<V; ++i) pp[i] = i;
    memset(v, -1, sizeof(v));
    memset(d, -1, sizeof(d));
    d[r] = 0;
    qf = qb = q;
    *qb++ = r;
    while (qf < qb)
        for (int x=*qf++, y=0; y<V; ++y)
            if (adj[x][y] && m[y] != y && f(x) != f(y))
                if (d[y] == -1)
                    if (m[y] == -1){
                        path(r, x);
                        m[x] = y; m[y] = x;
                        return true;
                    }
                    else{
                        p[y] = x; p[m[y]] = y;
                        d[y] = 1; d[m[y]] = 0;
                        *qb++ = m[y];
                    }
                else
                    if (d[f(y)] == 0) {
                        int b = lca(x, y, r);
                        contract_one_side(x, y, b);
                        contract_one_side(y, x, b);
                    }
    return false;
}
int match_result(){
    int res=0;
    memset(m,-1,sizeof(m));
    for(int i=0;i<V;i++){
        if(m[i]==-1){
            if(BFS(i))res++;
            else m[i]=i;
        }
    }
    return res;
}
int num[10000 + 10],top;
int main(){
    int T,Case=0,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        V=(1<<n);
        top=0;
        for(int i=0;i<V;i++){
            for(int j=i+1;j<V;j++){
                scanf("%d",&w[i][j]);
                num[top++]=w[i][j];
            }
        }
        sort(num,num+top);
        top = (unique(num,num+top)-num);
        int l=0,r=top-1,mid;
        while(r>l){
            mid=(l+r+1)/2;
            memset(adj,false,sizeof(adj));
            for(int i=0;i<V;i++){
                for(int j=i+1;j<V;j++){
                    if(w[i][j]>=num[mid])adj[i][j]=adj[j][i]=true;
                }
            }
            int res=match_result();
            if(res==V/2)l=mid;
            else r=mid-1;
        }
        printf("Case %d: %d\n",++Case,num[l]);
    }
}
