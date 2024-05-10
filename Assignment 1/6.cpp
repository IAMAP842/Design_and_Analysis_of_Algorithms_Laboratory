#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

void bucketSort(vector<float> &arr)
{
    int size = arr.size();
    vector<vector<float>> b(size);
    for (int i = 0; i < size; i++)
    {
        int bi = size * arr[i];
        b[bi].push_back(arr[i]);
    }
    for (int i = 0; i < size; i++)
    {
        sort(b[i].begin(), b[i].end());
    }
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            arr[index++] = b[i][j];
        }
    }
}

int main()
{
    random_device rd;
    default_random_engine generator(rd());
    int arraySize, iterations;
    cout << "Enter the size of the array: ";
    cin >> arraySize;
    cout << "Enter the number of iterations: ";
    cin >> iterations;
    uniform_real_distribution<float> unidist(0.0, 1.0);  // Object for Uniform Distribution Generation //
    normal_distribution<float> normdist(0.5, 0.2);       // Object for Normal Distribution Generation //
    vector<chrono::duration<double>> time_complexity_ud; // Vector to store the different time intervals of uniform distribution //
    vector<chrono::duration<double>> time_complexity_nd; // Vector to store the different time intervals of normal distribution //

    // Uniform Distribution
    for (int i = 0; i < iterations; i++)
    {
        vector<float> uniformArray(arraySize);
        for (int j = 0; j < arraySize; j++)
        {
            uniformArray[j] = unidist(generator);
        }
        auto bucket_sort_ud_start = chrono::high_resolution_clock::now();
        bucketSort(uniformArray);
        auto bucket_sort_ud_stop = chrono::high_resolution_clock::now();
        auto time_taken_ud = (bucket_sort_ud_stop - bucket_sort_ud_start);
        time_complexity_ud.push_back(time_taken_ud);
        cout << " Time complexity for Uniform Distribution at iteration " << i + 1 << ": " << time_taken_ud.count() << " seconds\n";
    }

    // Normal Distribution
    for (int i = 0; i < iterations; i++)
    {
        vector<float> normalArray(arraySize);
        for (int j = 0; j < arraySize; j++)
        {
            normalArray[j] = normdist(generator);
        }
        auto bucket_sort_nd_start = chrono::high_resolution_clock::now();
        bucketSort(normalArray);
        auto bucket_sort_nd_stop = chrono::high_resolution_clock::now();
        auto time_taken_nd = (bucket_sort_nd_stop - bucket_sort_nd_start);
        time_complexity_nd.push_back(time_taken_nd);
        cout << " Time complexity for Normal Distribution at iteration " << i + 1 << ": " << time_taken_nd.count() << " seconds\n";
    }

    // Calculate average time complexities
    chrono::duration<double> time_sum_ud(0);
    for (const auto &time : time_complexity_ud)
    {
        time_sum_ud += time;
    }
    time_sum_ud /= iterations;
    cout << "Average time complexity for Uniform Distribution: " << time_sum_ud.count() << " seconds\n";

    chrono::duration<double> time_sum_nd(0);
    for (const auto &time : time_complexity_nd)
    {
        time_sum_nd += time;
    }
    time_sum_nd /= iterations;
    cout << "Average time complexity for Normal Distribution: " << time_sum_nd.count() << " seconds\n";

    return 0;
}