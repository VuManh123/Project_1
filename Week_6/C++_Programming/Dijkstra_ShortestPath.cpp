#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5; //nodes max 
int n, m, s, k; //nodes, arcs, source, dest 
vector<pair<int, int>> adj[MAX]; //Danh sach do thi ke 
const int INF = 1e9;

void dijkstra(int s, int k)
{
    vector<long long> d(n + 1, INF); //Khoang cach tu s den cac dinh con lai 
    d[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    while(q.size())
    {
        pair<int, int> t = q.top();
        q.pop();
        int kc = t.first;
        int u = t.second;
        if(kc > d[u]) continue;
        for(auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if(d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    
        if(d[k] == INF) cout << "-1";
        else cout << d[k];
    
}
int main()
{   
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
   
        cin >> n >> m;
        for(int i = 0; i <= n; i++)adj[i].clear();
        for(int i = 0; i < m; i++)
        {
            int x, y, w;
            cin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        cin >> s >> k;
        dijkstra(s, k);
        
    return 0;
}

