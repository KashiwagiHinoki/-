#include<iostream>
#include<cstdio>
#include<algorithm>
#include <vector>

template<typename T>
std::vector<std::vector<T>> step_wise_vector(uint &n, T init){
    std::vector<std::vector<T>> ret(n);
    for(int i = 0;i < n; i++){
        ret[i] = std::vector<T>(i);
        for(int j = 0;j < i; j++){
            ret[i][j] = init;
        }
    }
    return ret;
}

int inc;
void _search_bridge(std::vector<std::vector<int>> &e, int *arrival_order, int *low, uint current, int before){
    if(arrival_order[current] != 0){
        return;
    }
    arrival_order[current] = inc++;
    low[current] = arrival_order[current];
    for(int i = 0;i < e[current].size(); ++i){
        if(e[current][i] == 1 && before != i) {
            _search_bridge(e, arrival_order, low, (uint)i, current);
            low[current] = std::min(low[current], low[i]);
        }
    }
    if(arrival_order[current] == low[current] && before != -1){
        printf("%d %d\n", std::min(current, (uint)before), std::max(current, (uint)before));
    }
    return;
}

void search_bridge(std::vector<std::vector<int>> &e){
    uint n = e.size();
    std::vector<std::vector<int>> bridge = step_wise_vector<int>(n, 0);
    int arrival_order[n] ={0};
    int low[n] = {0};
    for(int i = 0;i < n;i++){
        if(arrival_order[i] == 0){
            inc = 1;
            _search_bridge(e, arrival_order, low, i, -1);
        }
    }
}

int main(void){
    uint n, m;
    //n is used as a number of nodes and m is a number of edges
    scanf("%u%u", &n, &m);
    std::vector<std::vector<int>> e(n, std::vector<int>(n, 0));
    for(int i = 0;i < m;i++){
        uint _i, _j;
        scanf("%u%u", &_i, &_j);
        e[_i][_j] = e[_j][_i] = 1;
    }
    search_bridge(e);
    return 0;
}