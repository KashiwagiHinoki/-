#include<iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int> > create_path(){
    //n -> ノード数, e -> エッジ数
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::vector<int> > ret(n);
    for(int i = 0;i < m; i++){
        int g[2];
        scanf("%d%d", g, g + 1);
        ret[g[0]].push_back(g[1]);
        ret[g[1]].push_back(g[0]);
    }
    return ret;
}

int _detect_articulation_point(const std::vector<std::vector<int> > &path, int *ord, int *low, int current, int before, int &_ord, std::vector<int> &ret){
    if(ord[current] != 0){
        return low[current];
    }
    ord[current] = _ord++;
    low[current] = ord[current];
    int cnt = 0;
    for(int i = 0;i < path[current].size(); i++){
        if(path[current][i] == before) continue;
        if(before == -1 && ord[path[current][i]] == 0) cnt++;
        low[current] = std::min(low[current], _detect_articulation_point(path, ord, low, path[current][i], current,_ord,  ret));
    }


    if(before == -1 && cnt > 1){
        ret.push_back(current);
    }
    if(before != -1){
        for(int i = 0;i < path[current].size(); i++){
            if(ord[current] <= low[path[current][i]]){
                ret.push_back(current);
                break;
            }
        }
    }
    return low[current];
}
std::vector<int> detect_articulation_point(std::vector<std::vector<int> > path){
    std::vector<int> ret;
    int n = path.size();
    int ord[n] = {0}, low[n] = {0};
    for(int i = 0;i < n; ++i){
        if(ord[i] == 0){
            int _ord = 1;
            _detect_articulation_point(path, ord, low, i, -1, _ord, ret);
        }
    }
    std::sort(ret.begin(), ret.end());
    ret.erase(std::unique(ret.begin(), ret.end()),ret.end());
    return ret;
}


int main(void){
    std::vector<std::vector<int> > path = create_path();
    std::vector<int> articulation_point = detect_articulation_point(path);
    for(auto i : articulation_point){
        printf("%d\n",i);
    }
    return 0;
}