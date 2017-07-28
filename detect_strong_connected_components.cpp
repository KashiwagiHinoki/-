#include<iostream>
#include <vector>
#include <algorithm>

void __detect_strongly_connected_components(const std::vector<std::vector<int> > &rev_graph, int* is_reaching, int current, int before, std::vector<std::vector<int> > ret, const int &cls){
    if(is_reaching[current] == 2){
        return;
    }
    is_reaching[current] = 2;
    ret[cls].push_back(current);
    printf("%d ", current);
    for(int i = 0;i < rev_graph[current].size(); i++){
        if(rev_graph[current][i] == before) continue;
        __detect_strongly_connected_components(rev_graph, is_reaching, rev_graph[current][i], current, ret, cls);
    }
    return;
}
void _detect_strongly_connected_components(const std::vector<std::vector<int> > &graph, int *is_reaching, std::vector<int>& post_order, int current, int before){
    if(is_reaching[current] == 1){
        return;
    }
    is_reaching[current] = 1;
    for(int i = 0;i < graph[current].size(); i++){
        if(graph[current][i] == before) continue;
        _detect_strongly_connected_components(graph, is_reaching, post_order, graph[current][i], current);
    }
    post_order.push_back(current);
    return;
}
std::vector<std::vector<int> > detect_strongly_connected_components(const std::vector<std::vector<int> > &graph, const std::vector<std::vector<int> > &rev_graph){
    std::vector<std::vector<int> > ret;
    int is_reaching[graph.size()] = {0};
    for(int i = 0; i < graph.size(); i++){
        std::vector<int> post_order;
        if(is_reaching[i] == 0){
            _detect_strongly_connected_components(graph, is_reaching, post_order, i, -1);
            std::reverse(post_order.begin(), post_order.end());
            int cls = 0;
            for(int j = 0;j < post_order.size(); j++){
                if(is_reaching[post_order[j]] != 2) {
                    ret.push_back(std::vector<int>(0));
                    __detect_strongly_connected_components(rev_graph, is_reaching, post_order[j], -1, ret, cls);
                    puts("");
                    cls++;
                }
            }

        }
    }
}

std::vector<std::vector<int> > reverse_directed_graph(const std::vector<std::vector<int> > &_graph){
    std::vector<std::vector<int> > ret(_graph.size());
    for(int i = 0; i < _graph.size(); i++){
        for(auto j : _graph[i]){
            ret[j].push_back(i);
        }
    }
    return ret;
}
std::vector<std::vector<int> > create_directed_graph(){
    //n -> 頂点数, m -> 辺の数5
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::vector<int> > ret(n);
    for(int i = 0; i < m;i++){
        int domain, codomain;
        scanf("%d%d", &domain, &codomain);
        ret[domain].push_back(codomain);
    }
    return ret;
}
int main(void){
    std::vector<std::vector<int> > graph = create_directed_graph();
    std::vector<std::vector<int> > strongly_connected_components = detect_strongly_connected_components(graph, reverse_directed_graph(graph));

    return 0;
}