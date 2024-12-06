#include <vector>
#include <iostream>
#include <functional>
#include <string>

using std::cout, std::endl, std::vector, std::string;

class cuckooHashTable
{
private:
    vector<string> table1;
    vector<string> table2;
    double maxOccupancy;
    double increaseFactor;
    int numberOfItems;
    int max_loops;
    int size1;
    int size2;

    size_t hashFunction(const string& key, size_t size){
        return size == 0 ? 0 : std::hash<string>{}(key) % size;
    }

public:
    cuckooHashTable(double inMaxOccupany, double inIncreaseFactor, int maxLoops, int insize1, int insize2){
        table1 = vector<string>(insize1, "");
        table2 = vector<string>(insize2, "");
        maxOccupancy = inMaxOccupany;
        increaseFactor = inIncreaseFactor;
        max_loops = maxLoops;
        numberOfItems = 0;
        size1 = insize1;
        size2 = insize2;
    }
    bool lookup(const string& key){
        if (table1[hashFunction(key, table1.size())] == key)
        {
            return true;
        }
        if (table2[hashFunction(key, table2.size())] == key)
        {
            return true;
        }
        return false;
    }
    void resize(){
        vector<string> temp1 = table1;
        vector<string> temp2 = table2;
        table1 = vector<string>(static_cast<double>(table1.size()) * increaseFactor, "");
        table2 = vector<string>(static_cast<double>(table2.size()) * increaseFactor, "");
        numberOfItems = 0;
        for (const auto& key : temp1) {
            if (!key.empty()) insert(key);
        }
        for (const auto& key : temp2) {
            if (!key.empty()) insert(key);
        }
    }
    bool needsresize(){
        return (static_cast<double>(numberOfItems) / (table1.size() + table2.size())) > maxOccupancy;
    }
    void insert(const string& key){
        if (lookup(key))
        {
            return;
        }
        if (needsresize())
        {
            cout << "pes" << endl;
            resize();
        }
        string keyCopy = key;
        for (int i = 0; i < max_loops; i++)
        {
            size_t index = hashFunction(keyCopy, table1.size());
            if (table1[index].empty())
            {
                numberOfItems++;
                table1[index] = std::move(keyCopy);
                return;
            }
            std::swap(keyCopy, table1[index]);
            index = hashFunction(keyCopy, table2.size());
            if (table2[index].empty())
            {
                numberOfItems++;
                table2[index] = std::move(keyCopy);
                return;
            }
            std::swap(keyCopy, table2[index]);
        }
        resize();
        insert(key);
    }
    void remove(const string key){
        if (table1[hashFunction(key, table1.size())] == key)
        {
            table1[hashFunction(key, table1.size())] = "";
            numberOfItems--;
        }
        else if (table2[hashFunction(key, table2.size())] == key)
        {
            table2[hashFunction(key, table2.size())] = "";
            numberOfItems--;
        }
        else
        {
            return;
        }
    }

    void ppTable(){
        cout << "Table" << 1 << "\n";
        for (size_t a = 0; a < table1.size(); a++)
        {
            if (!table1[a].empty())
            {
                cout << a << ": " << table1[a] << " ";
            }
        }
        cout << "\nTable" << 2 << "\n";
        for (size_t a = 0; a < table2.size(); a++)
        {
            if (!table2[a].empty())
            {
                cout << a << ": " << table2[a] << " ";
            }
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
    cuckooHashTable cuckoo = cuckooHashTable(0.5, 1.5, 5, 10, 11);
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