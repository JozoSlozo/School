#include <vector>
#include <iostream>
#include <functional>
#include <string>

using std::cout, std::endl, std::vector, std::string;

class hashTable
{
private:
    vector<string> table;

    size_t hashFunction(const string& key){
        return table.size() == 0 ? 0 : std::hash<string>{}(key) % table.size();
    }
public:
    hashTable(int size)
    {
        table = vector<string>(size, "");
    };

    bool insert(string& key){
        size_t index = hashFunction(key);
        if (table[index].empty())
        {
            table[index] = key;
            return true;
        }
        std::swap(table[index], key);
        return false;   
    }
    bool remove(const string& key){
        size_t index = hashFunction(key);
        if (table[index] != key)
        {
            return false;
        }
        table.erase(table.begin() + index-1);
        return true;           
    }
    void printTable(){
        int counter = 0;   
        for (const auto& item : table)
        {
            if (!item.empty())
            {
                cout << counter << ": " << item << " ";
            }
            counter++;    
        }
        cout << "\n";
    }
    bool lookup(const string& key){
        size_t index = hashFunction(key);
        return table[index] == key;
    }
    void resize(double inIncreaseFactor){
        vector<string> temp = table;
        table = vector<string>(static_cast<double>(table.size()) * inIncreaseFactor, "");
        for (const string& item : temp) {
            if (!item.empty()) {
                string temp = item;
                insert(temp);  // Re-insert using updated table size
            }
        }
    }
    int getSize(){
        return table.size();
    }
};
class cuckooHashTable
{
private:
    vector<hashTable*> tables;
    size_t max_loops;
    double maxOccupancy;
    double increaseFactor;
    int numberOfItems;
public:
    cuckooHashTable(double inMaxOccupany, double inIncreaseFactor, size_t maxLoops){
        maxOccupancy = inMaxOccupany;
        increaseFactor = inIncreaseFactor;
        max_loops = maxLoops;
        numberOfItems = 0;
    }
    ~cuckooHashTable(){
        for (hashTable* i : tables)
        {
            delete i;
        }
    }
    void createTable(int size){
        tables.push_back(new hashTable(size));
    }
    bool lookup(const string& key){
        for(hashTable* table : tables){
            if (table->lookup(key))
            {
                return true;
            }
        }
        return false;
    }
    bool insert(const string& key){
        if (tables.size() < 2)
        {
            cout << "not enough tables" << endl;
            return false;
        }
        resize();
        string keyCopy = key;
        for (size_t i = 0; i < max_loops; i++)
        {
            cout << "i: " << i << " keycopy: " << keyCopy << endl;
            if (tables[i % tables.size()]->insert(keyCopy))
            {
                numberOfItems++;
                return true;
            }
        }
        return false;
    }
    void ppTable(){
        for (size_t i = 0; i < tables.size(); i++)
        {
            cout << "Table" << i+1 << "\n";
            tables[i]->printTable();
        }
    }
    bool resize(){
        
        size_t temp = 0;
        for (hashTable* table : tables)
        {
            temp += table->getSize();
        }
        if (numberOfItems / static_cast<double>(temp) > maxOccupancy)
        {
            for (hashTable* table : tables)
            {
                table->resize(increaseFactor);
            }
            return true;
        }
        return false;
    }
};


int main(){
    vector<string> inputs = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", 
    "seventeen", "eighteen", "nineteen", "twenty", 
    "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five", 
    "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine", 
    };
    cuckooHashTable cuckoo = cuckooHashTable(0.5, 1.5, 5);
    cuckoo.createTable(10);
    cuckoo.createTable(11);
    for (auto input : inputs)
    {
        cuckoo.insert(input);
    }
    cuckoo.ppTable();
    return 0;
}