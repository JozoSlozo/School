#include <vector>
#include <iostream>
#include <functional>
#include <string>

using std::cout, std::endl, std::vector, std::string;

class cuckooHashTable
{
private:
    vector<vector<string>> tables;
    double maxOccupancy;
    double increaseFactor;
    int numberOfItems;
    int max_loops;

    size_t hashFunction(const string& key, size_t size){
        return size == 0 ? 0 : std::hash<string>{}(key) % size;
    }

public:
    cuckooHashTable(double inMaxOccupany, double inIncreaseFactor, int maxLoops, vector<size_t> tablesizes){
        for (size_t i : tablesizes)
        {
            tables.push_back(vector<string>(i, ""));
        }
        maxOccupancy = inMaxOccupany;
        increaseFactor = inIncreaseFactor;
        max_loops = maxLoops;
        numberOfItems = 0;
    }
    bool lookup(const string& key){
        for (size_t i = 0; i < tables.size(); i++)
        {
            if (tables[i][hashFunction(key, tables[i].size())] == key)
            {
                return true;
            }
        }
        return false;
    }
    void resize(){
        vector<vector<string>> temp = tables;
        for (size_t i = 0; i < tables.size(); i++)
        {
            tables[i] = vector<string>(static_cast<double>(tables[i].size()) * increaseFactor, "");
        }
        numberOfItems = 0;
        for (size_t i = 0; i < tables.size(); i++)
        {
            for (const auto& key : temp[i]) {
                if (!key.empty()) 
                {
                    insert(key);
                }
            }
        }
    }
    bool needsresize(){
        size_t size = 0;
        for (size_t i = 0; i < tables.size(); i++)
        {
            size += tables[i].size();
        }
        return (static_cast<double>(numberOfItems) / size) > maxOccupancy;
    }
    void insert(const string& key){
        if (lookup(key))
        {
            return;
        }
        if (needsresize())
        {
            resize();
        }
        string keyCopy = key;
        for (int i = 0; i < max_loops; i++)
        {
            for (size_t a = 0; a < tables.size(); a++)
            {
                size_t index = hashFunction(keyCopy, tables[a].size());
                if (tables[a][index].empty())
                {
                    numberOfItems++;
                    tables[a][index] = std::move(keyCopy);
                    return;
                }
                std::swap(keyCopy, tables[a][index]);
            }
        }
        resize();
        insert(key);
    }
    void remove(const string& key){
        for (size_t i = 0; i < tables.size(); i++)
        {
            size_t index = hashFunction(key, tables[i].size());
            if (tables[i][index] == key)
            {
                tables[i][index] = "";
                numberOfItems--;
                return;
            }
        }
    }

    void ppTable(){
        int temp = 1;
        for (vector<string> i : tables)
        {
            cout << "Table" << temp << ":\n";
            temp++;
            for (size_t a = 0; a < i.size(); a++)
            {
                if (!i[a].empty())
                {
                    cout << a << ": " << i[a] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
};


int main(){
    const auto inputs = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",};
    const auto inputs2 = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
    "seventeen", "eighteen", "nineteen", "twenty", 
    "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five", 
    "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine",};
    const auto removals = { "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five", 
    "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine",
    "aardvark", "Bene Gesserit", "crane", "dog", "element"};
    vector<size_t> tablesizes = {10,11};
    cuckooHashTable cuckoo = cuckooHashTable(0.5, 1.5, 5, tablesizes);
    for (string i : inputs)
    {
        cuckoo.insert(i);
    }
    cuckoo.ppTable();
    for (string i : inputs2)
    {
        cuckoo.insert(i);
    }
    cuckoo.ppTable();
    for (string i : removals)
    {
        cuckoo.remove(i);
    }
    cuckoo.ppTable();
    return 0;
}