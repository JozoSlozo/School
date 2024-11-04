#include "compute_modus.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

string getModusWord(vector<string> words){
    sort(words.begin(), words.end());

    int index = 1;
    int max = 0;
    int curr = 0;
    string word = "";

    while (index < words.size()-1)
    {
        curr = 1;
        while (words[index] == words[index-1])
        {   
            index++;
            curr++;
        }
        index++;
        
        if (curr > max)
        {
            max = curr;
            word =  words[index-2];
        }
    }
    return word;
}

int getModusMap(vector<string> words){
    unordered_map<string, int> wordsMap;
    for (string i : words)
    {
        wordsMap[i] = 0;
    }
    for (string i : words)
    {
        wordsMap[i] += 1;
    }
    vector<string> finword;
    for (int j = 0; j < 10; j++)
    {
        int max = 0;
        string top = "";
        for (string i : words)
        {
            int curr = wordsMap[i];
            if (curr > max)
            {
                max = curr;
                top = i;
            }
        }
        finword.push_back(top);
        auto temp = wordsMap.find(top);
        wordsMap.erase(temp);
    }
    for (string i : finword)
    {
        cout << i << endl;
    }
    
    return 0;
}

int main() {

    const std::string file_path = "words.txt";
    string txt;
    ifstream MyReadFile(file_path);
    vector<string> words;

    while (getline (MyReadFile, txt)) {
        words.push_back(txt);
    }

    getModusMap(words);

    return 0;
}

