using namespace std;
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

int T(int n){
    if(n == 0) return 1;
    return 5 * T(n-1);
}

vector<int> ShakerSort(vector<int> numbers, int& iterations){
    vector<int> temp = numbers;
    bool swapped = 0;
    for (int i = 0; i < temp.size() / 2; i++)
    {
        swapped = 0;
        for (int l = i; l < temp.size() - i - 1; l++)
        {
            if (temp[l] < temp[l+1])
            {
                swap(temp[l], temp[l+1]);
                swapped = 1;
            }
            iterations++;
        }
        for (int l = temp.size() - i - 2; l > i; l--)
        {
            if (temp[l] > temp[l-1])
            {
                swap(temp[l], temp[l-1]);
                swapped = 1;
            }
            iterations++;
        }
        if (!swapped)
        {
            break;
        }
        
    }
    return temp;
}

vector<int> bubblesort(vector<int> arr, int &iterations){
    vector<int> temp = arr;
    for (size_t i = 0; i < temp.size(); i++)
    {
        for (size_t j = 0; j < temp.size()-(i+1); j++)
        {
            if (temp[j] > temp[j + 1])
            {
                std::swap(temp[j], temp[j + 1]);
            }
            iterations++;
        }
    }
    return temp;
}

vector<int> selectionsort(vector<int> arr, int &iterations){
    size_t min;
    vector<int> temp = arr;
    for (size_t i = 0; i < temp.size()-1; i++)
    {
        min = i;
        for (size_t l = i; l < temp.size(); l++)
        {
            if (temp[min] > temp[l])
            {
                min = l;
            }
            iterations++;   
        }
        std::swap(temp[i], temp[min]);
    }
    return temp;
}

vector<int> generateRandomVector(int len, int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);

    vector<int> result;
    result.reserve(len);

    for (int i = 0; i < len; i++)
    {
        result.push_back(distribution(gen));
    }
    return result;
}

int main(){

    cout << "Test T: " << T(2) << endl;

    int len = 100;
    vector<int> intArr = generateRandomVector(len, 1, 10000);
    int iter = 0;
    vector<int> intArrSorted = ShakerSort(intArr, iter);
    cout << fixed;

    auto start = chrono::high_resolution_clock::now();
    ShakerSort(intArr, iter);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    cout << "Shaker sort for vector length " << len << endl;
    cout << "Number of iterations: " << iter << endl;
    cout << "Time spent: " << duration.count() << " seconds\n" << endl;

    iter = 0;
    start = chrono::high_resolution_clock::now();
    bubblesort(intArr, iter);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    cout << "Bubble sort for vector length " << len << endl;
    cout << "Number of iterations: " << iter << endl;
    cout << "Time spent: " << duration.count() << " seconds\n" << endl;

    iter = 0;
    start = chrono::high_resolution_clock::now();
    selectionsort(intArr, iter);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    cout << "Bubble sort for vector length " << len << endl;
    cout << "Number of iterations: " << iter << endl;
    cout << "Time spent: " << duration.count() << " seconds" << endl;

    return 0;
}