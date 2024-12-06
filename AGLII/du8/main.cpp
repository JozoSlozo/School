#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using std::string, std::ifstream, std::istreambuf_iterator, std::cerr, std::endl, std::unordered_map, std::cout, std::vector, std::pair;

struct SimplePairHash {
    size_t operator()(const pair<int, int> &inPair) const {
        return inPair.first + 10000 * inPair.second; // we expect and promise less than 10000 keys in stringToCode
    }
};
string readTextFromFile(const string &fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Unable to open file " << fileName << endl;
        exit(1);
    }
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return text;
}
string escapeSpecialChars(const string &s) {
    string result;
    for (char c : s) {
        if (c == '\n') {
            result += "\\n";
        } else if (c == '\t') {
            result += "\\t";
        } else {
            result += c;
        }
    }
    return result;
}

class bytePair
{
private:
    unordered_map<string, int> stringToCode;
    int stringCode;
    int n;
    string text;

    void addCharacterCode(string s);
    pair<int, int> getMaxPair();
    void updateTextAsNumbers(pair<int, int> max);
    void solve();
public:
    unordered_map<int, string> codeToString;
    vector<int> textAsNumbers;
    bytePair(string text, int n);
};
bytePair::bytePair(string text, int n)
{
    stringCode = 0;
    this->n = n;
    this->text = text;
    for (char character : text)
    {
        string s(1, character);
        if (stringToCode.find(s) == stringToCode.end())
        {
            addCharacterCode(s);
        }
        textAsNumbers.push_back(stringToCode[s]);
    }
    solve();
}
void bytePair::addCharacterCode(string s){
    stringToCode[s] = stringCode;
    codeToString[stringCode] = s;
    stringCode++;
}
pair<int, int> bytePair::getMaxPair(){
    pair<int, int> maxPair = {0,0};
    int maxValue = 0;
    unordered_map<pair<int, int>, int, SimplePairHash> pairFrequency;
    for (size_t i = 1; i < textAsNumbers.size(); i++)
    {
        pair<int, int> currPair = {textAsNumbers[i-1], textAsNumbers[i]};
        pairFrequency[currPair] += 1;
        if (pairFrequency[currPair] == maxValue)
        {
            maxPair = maxPair > currPair ? maxPair : currPair;
        }
        else if (pairFrequency[currPair] > maxValue)
        {
            maxValue = pairFrequency[currPair];
            maxPair = currPair;
        }
    }
    return maxPair;
}
void bytePair::updateTextAsNumbers(pair<int, int> max){
    vector<int> charAsIntCopy = textAsNumbers;
    textAsNumbers.clear();
    for (size_t i = 0; i < charAsIntCopy.size(); i++)
    {
        if (i == charAsIntCopy.size()-1)
        {
            textAsNumbers.push_back(textAsNumbers[i]);
        }
        else if (pair<int, int>{charAsIntCopy[i], charAsIntCopy[i+1]} == max)
        {
            textAsNumbers.push_back(stringCode-1);
            i++;
        }
        else
        {
            textAsNumbers.push_back(textAsNumbers[i]);
        }
    }
}
void bytePair::solve(){
    int numOfStartingCharacters = stringToCode.size();
    for (int j = 0; j < n-numOfStartingCharacters; j++)
    {
        pair<int, int> maxPair = getMaxPair();

        string s;
        s += codeToString[maxPair.first] + codeToString[maxPair.second];
        addCharacterCode(s);

        updateTextAsNumbers(maxPair);
    }
}

int main(int argc, char* argv[]){
    (void)argc;

    bytePair bp = bytePair(readTextFromFile(argv[1]), std::stoi(argv[2]));

    for (size_t i = 0; i < bp.codeToString.size(); i++)
    {
        cout << i << " -> '" << escapeSpecialChars(bp.codeToString[i]) << "'" << endl;
    }
}