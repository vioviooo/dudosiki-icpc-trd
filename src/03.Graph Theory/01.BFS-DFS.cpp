using graph = vector<vector<int>>;//список смежности
double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

//Поиск в ширину, для нахождения кратчайшего пути, O(n + m)
void bfs(int start, const graph& g, vector<int>& d, vector<int>& p) {
    queue<int> q;
    d[start] = 0;
    p[start] = start;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();//достаем верхний из очереди
        q.pop();
        for (int v : g[u]) {//если у него не помечены ребра, то помечаем
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                p[v] = u;
                q.push(v);//и суем в очередь вершины из этих ребер
            }
        }
    }
}

//Поиск в глубину, для нахождения всего, что связано с циклами в графе O(n + m)
int cnt_cycles = 0;
bool dfs(int u, const graph& g, vector<int>& color, vector<int>& path, vector<int>& cycle) {
    if (color[u] == 2) {
        return false;
    }
    path.push_back(u);
    color[u] = 1;
    for (int v : g[u]) {
        if (color[v] == 1) {
            cycle.push_back(v);
            int ind = path.size() - 1;
            while (path[ind] != v) {
                cycle.push_back(path[ind]);
                ind--;
            }
            reverse(cycle.begin(), cycle.end());
            return true;
        }
        if(dfs(v, g, color, path, cycle)) {
            return true;
        }
    }
    color[u] = 2;
    path.pop_back();
    return false;
}

//Посчитаем число циклов? :-)
void count_cycles(int u, const graph& g, vector<int>& color) {
    if (color[u] == 2) {
        return;
    }
    color[u] = 1;
    for (int v : g[u]) {
        if (color[v] == 1) {
            cnt_cycles++;
        }
        else{
            count_cycles(v, g, color);
        }
    }
    color[u] = 2;
}

void solve_dfs_AND_cntcycles(){
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
    }
    vector<int> color(n, 0);
    vector<int> path;
    vector<int> cycle;
    bool has_cycle = dfs(0, g, color, path, cycle);
    for (int i = 0; i < cycle.size(); i++) {
        cout << cycle[i] + 1 << ' ';
    }

    color.assign(n, 0);
    path.resize(0);
    count_cycles(0, g, color);
    cout << endl;
    cout << cnt_cycles << endl;
}

void solve_bfs(){
    int n = 0, m = 0;//кол-во вершин и ребер
    cin >> n >> m;
    //характеристики вершин
    int start = 0;
    int finish = 0;
    cin >> start >> finish;
    start--;
    finish--;
    graph g(n);
    for (int i = 0; i < m; i++) {
        //Перечисление ребер
        int u, v;//откуда и куда
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        //В список вершины добавляем ребро
        //Если хотим неор. граф, то
        //g[v].push_back(u);
    }

    vector<int> distance(n, -1);//длина
    vector<int> parent(n, -1);
    bfs(start, g, distance, parent);
    vector<int> path;
    //----------------------------------
    //Поиск по предкам
    int cur = finish;
    while (parent[cur] != cur) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(cur);
    reverse(path.begin(), path.end());
    //----------------------------------
    //path - путь из вершин;
    //cout << path.size() << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] + 1 << ' ';
    }


}