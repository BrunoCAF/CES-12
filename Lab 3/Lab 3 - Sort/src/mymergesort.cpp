
#include <mysortfunctions.h>

void mymergesort_recursive(std::vector<int> &v, SortStats &stats) {
    std::vector<int> aux;
    aux.resize(v.size());
    
    if (!v.empty()){
        // you need to set the counting of recursive recursive_calls
        stats.recursive_calls = 1;
        // you need to set the depth = the maximum height of the tree of recursion calls. 
        stats.depth_recursion_stack = stats.custom1 = 1;
        MergeSort(v, aux, 0, v.size()-1, stats);
    } else stats.recursive_calls = stats.depth_recursion_stack = stats.custom1 = 0;
    
    aux.clear();
}

/// Recursive top-down version of MergeSort
void MergeSort(std::vector<int> &v, std::vector<int> &aux, int i, int f, SortStats &stats){
    if(i < f){
        int m = (i+f)/2;
        stats.custom1++;
        (stats.recursive_calls++, MergeSort(v, aux,  i , m, stats));
        (stats.recursive_calls++, MergeSort(v, aux, m+1, f, stats));
        if(stats.custom1 > stats.depth_recursion_stack) 
            stats.depth_recursion_stack = stats.custom1;
        stats.custom1--;
        // Merge
        int lh = i, rh = m+1, auxit = i;
        while (lh <= m && rh <= f) aux[auxit++] = (v[lh] < v[rh]) ? v[lh++] : v[rh++];
        while (lh <= m) aux[auxit++] = v[lh++];
        while (rh <= f) aux[auxit++] = v[rh++];

        for (int j = i; j <= f; j++) v[j] = aux[j];
    }
}

/// Iterative bottom-up version of MergeSort
void mymergesort_iterative(std::vector<int> &v, SortStats &stats) {
    std::vector<int> aux;
    aux.resize(v.size());
    
    if (!v.empty()){
        int block_size = 1, i = 0, f = v.size()-1;
        int p, r, m;
        while (block_size < f){
            p = i;
            while (p+block_size <= f){
                r = std::min(f, p-1+2*block_size);
                m = p+block_size-1;
                // Merge (p, m, r)
                int lh = p, rh = m+1, auxit = p;
                while (lh <= m && rh <= r) aux[auxit++] = (v[lh] < v[rh]) ? v[lh++] : v[rh++];
                while (lh <= m) aux[auxit++] = v[lh++];while (rh <= r) aux[auxit++] = v[rh++];
                for (int j = p; j <= r; j++) v[j] = aux[j];
                // 
                p += (block_size<<1);
            }
            block_size <<= 1;
        }
    }
    stats.recursive_calls = stats.depth_recursion_stack = stats.custom1 = 0;
    aux.clear();
}
    
