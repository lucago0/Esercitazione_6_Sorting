#include <chrono>
#include <iostream>
#include <unistd.h>
#include <numeric>
#include <vector>
#include "SortingAlgorithm.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace SortLibrary;
using namespace std;

double mean(vector<double>& v){
    double s = 0;
    for(double v_i : v){
        s += v_i;
    }
    s /= v.size();
    return s;
}

int main(int argc, char** argv)
{
    unsigned int nIts = 15;
    vector<double> times1;
    vector<double> times2;

    times1.reserve(nIts);
    times2.reserve(nIts);

    vector<int> v;
    unsigned int n = argc;
    v.resize(n);

    // Test 1: vector already sorted
    iota(v.begin(),v.end(),n);
    vector<int> copy_of_v(n);
    copy_of_v = v;
    for (unsigned int i = 0; i < nIts; i++){
        chrono::steady_clock::time_point t_begin = chrono::steady_clock::now();
        BubbleSort(v);
        chrono::steady_clock::time_point t_end = chrono::steady_clock::now();
        times1.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
        t_begin = chrono::steady_clock::now();
        MergeSort(copy_of_v);
        t_end = chrono::steady_clock::now();
        times2.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
    }
    cout << "Sorted vector:" << endl << "> BubbleSort: \t" << mean(times1) << " microseconds" << endl << "> MergeSort: \t" << mean(times2) << " microseconds" << endl;
    times1.clear(); times2.clear();

    // Test 2: perturbed vectors
    iota(v.begin(),v.end(),n);
    for(unsigned int i = 0; i<(n/5); i++)
        v[i] = rand() % 10;
    copy_of_v = v;
    for (unsigned int i = 0; i < nIts; i++){
        chrono::steady_clock::time_point t_begin = chrono::steady_clock::now();
        BubbleSort(v);
        chrono::steady_clock::time_point t_end = chrono::steady_clock::now();
        times1.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
        t_begin = chrono::steady_clock::now();
        MergeSort(copy_of_v);
        t_end = chrono::steady_clock::now();
        times2.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
    }
    cout << "Perturbed vectors:" << endl << "> BubbleSort: \t" << mean(times1) << " microseconds" << endl << "> MergeSort: \t" << mean(times2) << " microseconds" << endl;
    times1.clear(); times2.clear();

    // Test 3: random vectors
    for(unsigned int i = 0; i<n; i++)
        v[i] = rand() % 10;
    copy_of_v = v;
    for (unsigned int i = 0; i < nIts; i++){
        chrono::steady_clock::time_point t_begin = chrono::steady_clock::now();
        BubbleSort(v);
        chrono::steady_clock::time_point t_end = chrono::steady_clock::now();
        times1.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
        t_begin = chrono::steady_clock::now();
        MergeSort(copy_of_v);
        t_end = chrono::steady_clock::now();
        times2.push_back(chrono::duration_cast<chrono::microseconds>(t_end-t_begin).count());
    }
    cout << "Random vectors:" << endl << "> BubbleSort: \t" << mean(times1) << " microseconds" << endl << "> MergeSort: \t" << mean(times2) << " microseconds" << endl;
    times1.clear(); times2.clear();

    cout << endl;
    return 0;
}
