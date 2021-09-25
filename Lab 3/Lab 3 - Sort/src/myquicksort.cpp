
#include <mysortfunctions.h>

// you only need to mantain the headers. You can create aux funcs, objects, or create 
// a generic quicksort that can work with different functions to select the pivot.

/// the most comon quicksort, with 2 recursive calls
void myquicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
    if(!v.empty()){
        // you need to set the counting of recursive recursive_calls
        stats.recursive_calls = 1;
        // you need to set the depth = the maximum height of the tree of recursion calls. 
        stats.depth_recursion_stack = stats.custom1 = 1;
        QuickSortM32R(v, 0, v.size()-1, stats);
    } else stats.recursive_calls = stats.depth_recursion_stack = stats.custom1 = 0;
}// function myquicksort_2recursion_medianOf3

/// quicksort with one recursive call
void myquicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
    if(!v.empty()){
        // you need to set the counting of recursive recursive_calls
        stats.recursive_calls = 1;
        // you need to set the depth = the maximum height of the tree of recursion calls. 
        stats.depth_recursion_stack = stats.custom1 = 1;
        QuickSortM31R(v, 0, v.size()-1, stats);
    } else stats.recursive_calls = stats.depth_recursion_stack = stats.custom1 = 0;
} // function myquicksort_1recursion_medianOf3

/// quicksort with fixed pivot and 2 recursive calls
void myquicksort_fixedPivot(std::vector<int> &v, SortStats &stats) {
    if(!v.empty()){
        // you need to set the counting of recursive recursive_calls
        stats.recursive_calls = 1;
        // you need to set the depth = the maximum height of the tree of recursion calls. 
        stats.depth_recursion_stack = stats.custom1 = 1;
        QuickSortFP2R(v, 0, v.size()-1, stats);
    } else stats.recursive_calls = stats.depth_recursion_stack = stats.custom1 = 0;
} // myquicksort_fixedPivot

/// inner functions with different headers
void QuickSortFP2R(std::vector<int> &v, int i, int f, SortStats &stats){
    if(i < f){
        // Partition:
        int p = Partition(v, i, f);
        //
        stats.custom1++;
        (stats.recursive_calls++, QuickSortFP2R(v, i, p-1, stats));
        (stats.recursive_calls++, QuickSortFP2R(v, p+1, f, stats));
        if(stats.custom1 > stats.depth_recursion_stack) 
            stats.depth_recursion_stack = stats.custom1;
        stats.custom1--;
    }
}

void QuickSortM32R(std::vector<int> &v, int i, int f, SortStats &stats){
    if(i < f){
        // Median of 3:
        MedianOf3(v, i, f);
        // Partition:
        int p = Partition(v, i, f);
        //
        stats.custom1++;
        (stats.recursive_calls++, QuickSortM32R(v, i, p-1, stats));
        (stats.recursive_calls++, QuickSortM32R(v, p+1, f, stats));
        if(stats.custom1 > stats.depth_recursion_stack) 
            stats.depth_recursion_stack = stats.custom1;
        stats.custom1--;
    }
}

void QuickSortM31R(std::vector<int> &v, int i, int f, SortStats &stats){
    while(i < f){
        // Median of 3:
        MedianOf3(v, i, f);
        // Partition:
        int p = Partition(v, i, f);
        //
        stats.custom1++;
        if(p-i < f-p) (stats.recursive_calls++, QuickSortM31R(v, i, p-1, stats), i = p+1);
        else          (stats.recursive_calls++, QuickSortM31R(v, p+1, f, stats), f = p-1);    
        if(stats.custom1 > stats.depth_recursion_stack) 
            stats.depth_recursion_stack = stats.custom1;
        stats.custom1--;
    }
}

/// auxiliary functions (could be implemented inline)
void MedianOf3(std::vector<int> &v, int i, int f){
    if(v[i] > std::max(v[(i+f)/2], v[f]))
        troca(v, i, (v[(i+f)/2] > v[f]) ? (i+f)/2 : f);
    if(v[i] < std::min(v[(i+f)/2], v[f]))
        troca(v, i, (v[(i+f)/2] < v[f]) ? (i+f)/2 : f);
}

int Partition(std::vector<int> &v, int left, int right){
    int pivot = v[left];
    int l = left+1, r = right;
    while(true){
        while (l < right && v[l] <  pivot) l++;
        while (r > left  && v[r] >= pivot) r--;
        if(l >= r) break; troca(v, l, r);
    }
    (v[left] = v[r], v[r] = pivot);
    return r;
}