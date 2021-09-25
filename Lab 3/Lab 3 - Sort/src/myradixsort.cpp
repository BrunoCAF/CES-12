
#include <mysortfunctions.h>
#include <queue>

void myradixsort(std::vector<int> &v, SortStats &stats) {
    int n = v.size();
    std::queue<int> q[2];
    for(int d = 0, k = 0; n > 0; n >>= 1, d++, k = 0){
        for(auto it = v.begin(); it < v.end(); it++) q[(*it>>d)&1].push(*it);
        while(!q[0].empty()) (v[k++] = q[0].front(), q[0].pop());
        while(!q[1].empty()) (v[k++] = q[1].front(), q[1].pop());
    }
    stats.depth_recursion_stack = stats.recursive_calls = 0;
}
