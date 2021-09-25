#ifndef YOURSORTFUNCTIONS_H
#define YOURSORTFUNCTIONS_H


#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <sortauxfuncs.h>

//////////////////////////////////// QuickSort ////////////////////////////////////////////
/// the most common quicksort, with 2 recursive calls
void myquicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats);
/// quicksort with one recursive call
void myquicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats);
/// quicksort with fixed pivot and two recursions
void myquicksort_fixedPivot(std::vector<int> &v, SortStats &stats);

/// Inner recursive functions with different headers
void QuickSortFP2R(std::vector<int> &v, int i, int f, SortStats &stats);
void QuickSortM32R(std::vector<int> &v, int i, int f, SortStats &stats);
void QuickSortM31R(std::vector<int> &v, int i, int f, SortStats &stats);

/// Median of 3
void MedianOf3(std::vector<int> &v, int i, int f);
/// Partition
int Partition(std::vector<int> &v, int i, int f);
///////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////// RadixSort ////////////////////////////////////////////
void myradixsort(std::vector<int> &v, SortStats &stats);
///////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// MergeSort ////////////////////////////////////////////
/// Recursive version
void mymergesort_recursive(std::vector<int> &v, SortStats &stats);
/// Iterative version
void mymergesort_iterative(std::vector<int> &v, SortStats &stats);
/// Inner recursive function with different header
void MergeSort(std::vector<int> &v, std::vector<int> &aux, int i, int f, SortStats &stats);
///////////////////////////////////////////////////////////////////////////////////////////

#endif
