using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

struct numberArrow
{
    int number;
    int arrow;//-1 - arrow pointing left, 1 - arrow pointing right

    numberArrow(int n, int a){
        number = n;
        arrow = a;
    }
};

int PrintPermutation(vector<numberArrow> p){//pretty print of permutation
    for (numberArrow l : p)
    {
        if (l.arrow == -1)
        {
            cout << "← ";
        }
        else{
            cout << "→ ";
        }
    }
    cout << endl;
    for (numberArrow l : p)
    {
        cout << l.number << " ";
    }
    cout << endl;
    return 0;
}

bool ContainsMobile(vector<numberArrow> p){//returns true if permutation contains mobile number
    for (int i = 0; i < p.size(); i++)
    {
        bool boundsLogic = i + p[i].arrow >= 0 && i + p[i].arrow < p.size();
        if (p[i + p[i].arrow].number < p[i].number && boundsLogic)
        {
            return 1;
        }
    }
    return 0;
}

int GetMaxMobileIndex(vector<numberArrow> p){//find index of max mobile number
    int index = 0;
    int max = 0;
    for (int i = 0; i < p.size(); i++)
    {
        bool boundsLogic = i + p[i].arrow >= 0 && i + p[i].arrow < p.size();
        if (p[i + p[i].arrow].number < p[i].number && p[i].number > max && boundsLogic)
        {
            max = p[i].number;
            index = i;
        }
    }
    return index;
}

int FlipArrows(vector<numberArrow> &p, int max){//flips arrows of numbers greater than input
    for (numberArrow& i : p)
    {
        if (i.number > max)
        {
            i.arrow *= -1;
        }
    }
    return 0;
}

vector<vector<numberArrow>> GetPermutation(int n){

    vector<vector<numberArrow>>  permutations;
    vector<numberArrow>  actualPermutation;

    for (int i = 0; i < n; i++) actualPermutation.push_back(numberArrow(i+1, -1));

    permutations.push_back(actualPermutation);

    while (ContainsMobile(actualPermutation))
    {
        int maxMobileIndex = GetMaxMobileIndex(actualPermutation);
        int maxMobile = actualPermutation[maxMobileIndex].number;

        swap(actualPermutation[maxMobileIndex], actualPermutation[actualPermutation[maxMobileIndex].arrow + maxMobileIndex]);

        FlipArrows(actualPermutation, maxMobile);

        permutations.push_back(actualPermutation);
    }
    return permutations;
}

int main(){
    int n = 3;
    cout << fixed;//disables scientific notation of numbers

    auto start = chrono::high_resolution_clock::now();

    vector<vector<numberArrow>> myPermutations = GetPermutation(n);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time spent my permutations: " << duration.count() << " seconds" << endl;
    
    start = chrono::high_resolution_clock::now();

    vector<vector<int>>  cppPermutations;
    vector<int>  actualPermutation;
    for (int i = 0; i < n; i++) actualPermutation.push_back(i+1);
    do
    {
        cppPermutations.push_back(actualPermutation);
    } while (next_permutation(actualPermutation.begin(), actualPermutation.end()));

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time spent cpp permutations: " << duration.count() << " seconds" << endl;

    /*
    for (vector<numberArrow> i : myPermutations)
    {
        PrintPermutation(i);
    }
    */

    /*
    for (int i = 0; i < cppPermutations.size(); i++)
    {
        for (int l : cppPermutations[i])
        {
            cout << l << " ";
        }
        cout << "\t\t";
        for (numberArrow l : myPermutations[i])
        {
            cout << l.number << " ";
        }
        cout << endl;
    }
    */
    return 0;
}