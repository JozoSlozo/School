#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> secti_2(vector<int> &input){
    vector<int> ret(2, 0);
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] % 2 == 0)
        {
            ret[0]++;
        }
        else{
            ret[1]++;
        }
        
    }
    return ret;
}

vector<int> InsertionSort(vector<int> vec){
    int v;
    int j;
    for (int i = 1; i < vec.size(); i++)
    {
        v = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > v)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = v;
    }
    return vec;
}

int checkEU(vector<int> in){
    in = InsertionSort(in);
    for (int i = 0; i < in.size(); i++)
    {
        if (in[i] == in[i+1])
        {
            return 0;
        }
    }
    return 1;
}

int checkEU2(vector<int> in){
    unordered_map<int, int> dict;
    for (int item : in)
    {
        if (dict.count(item) == 1)
        {
            return 0;
        }
        dict[item] = 1;    
    }
    return 1;
}

int checkModus(vector<int> in){
    in = InsertionSort(in);
    int maxIndex = 0;
    int max = 0;
    int index = -1;
    while (index != in.size()+1)
    {
        int curr = 1;
        index++;
        while(in[index] == in[index + 1])
        {
            index++;
            curr++;
        }
        if (curr > max)
        {
            max = curr;
            maxIndex = in[index];
        }
    }
    return maxIndex;
}

vector<int> leviatin(vector<int> input, int s){
    vector<int> pes;
    input = InsertionSort(input);
    int leftIndex = 0;
    int rightIndex = input.size()-1;
    while (true)
    {
        int sum = input[leftIndex] + input[rightIndex];
        if (sum > s)
        {
            rightIndex -= 1;
        }
        if (sum < s)
        {
            leftIndex++;
        }
        else {
            pes.push_back(input[leftIndex]);
            pes.push_back(input[rightIndex]);
            break;
        }
    }
    return pes;
}

int main(){
    vector<int> pes = {1,3,5,9};
    vector<int> les(2,0);
    les = secti_2(pes);
    cout << les[0] << ", "<< les[1] << endl;
    cout << checkEU(pes) << endl;
    cout << checkEU2(pes) << endl;
    cout << checkModus(pes) << endl;
    vector<int> keks;
    keks = leviatin(pes, 6);
    for(int i : keks){
        cout << i << ", ";
    }
    cout << endl;
}