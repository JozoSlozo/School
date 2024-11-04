#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

vector<int> closestNum(vector<int> input){
    std::sort(input.begin(), input.end());
    vector<int> ret;
    for (size_t i = 0; i < input.size()-1; i++)
    {
        ret.push_back(abs(input[i]-input[i+1]));
    }
    return ret; 
}
vector<int> intersectionBrute(vector<int> inputA, vector<int> inputB){
    vector<int> ret;
    for (int i : inputA)
    {
        for (int l : inputB)
        {
            if (i == l)
            {
                ret.push_back(i);
            }
        }
    }
    return ret;
}
vector<int> intersectionSort(vector<int> inputA, vector<int> inputB){
    inputA.insert(inputA.end(), inputB.begin(), inputB.end());
    std::sort(inputA.begin(), inputA.end());
    vector<int> ret;
    for (int i = 0; i < inputA.size()-1; i++)
    {
        if (inputA[i] == inputA[i+1])
        {
            ret.push_back(inputA[i]);
            i++;
        }
    }
    return ret;
}

vector<int> generateRandomVector(int len, int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);

    vector<int> result;
    result.reserve(len);

    while (result.size() < len)
    {
        int temp = distribution(gen);
        if (find(result.begin(), result.end(), temp) == result.end())
        {
            result.push_back(temp);
        }
    }
    return result;
}

int main(){
    int len = 100;
    vector<int> intArr1 = generateRandomVector(len, 1, 1000);
    vector<int> intArr2 = generateRandomVector(len, 1, 1000);
    cout << fixed;

    auto start = chrono::high_resolution_clock::now();
    vector<int> testDone = intersectionBrute(intArr1, intArr2);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    for (int i : testDone)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    cout << "Time spent: " << duration.count() << " seconds\n" << endl;

    start = chrono::high_resolution_clock::now();
    testDone = intersectionSort(intArr1, intArr2);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    for (int i : testDone)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    cout << "Time spent: " << duration.count() << " seconds\n" << endl;
}