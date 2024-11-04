#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using std::vector, std::cout, std::size_t, std::endl, std::string;

class myHeap{
    private:
    vector<int> data;
    int n;

    void heapify(const int parent){
        int largest = parent;
        vector<int> children;

        for (int i = 1; i <= n; i++)
        {
            int childIndex = n * parent + i;
            if (childIndex < (int)data.size() && data.at(childIndex) > data.at(largest)) {
                largest = childIndex;
            }
        }
        if(parent != largest){
            std::swap(data.at(parent), data.at(largest));
            heapify(largest);
        }
    }

    void makeHeap(vector<int> input){
        for(int a : input){
            insert(a);
        }
    }

    public:

    myHeap(const vector<int>& input_data, int n){
        if (n < 2)
        {
            return;
        }
        this->n = n;
        makeHeap(input_data);        
    }


    bool isEmpty() const{
        return data.empty();
    }

    void makeEmpty(){
        data.resize(0);
    }

    void insert(const int value){
        data.push_back(value);
        size_t size = data.size();
        if( size == 1 ){
            return;
        }
        
        size_t current_index = size - 1;
        size_t parent_index = (current_index - 1)/n;
        
        while( current_index > 0 and data.at(parent_index) < data.at(current_index)){
            std::swap(data.at(parent_index), data.at(current_index));
            current_index = parent_index;
            parent_index = (current_index - 1)/n;
        }
    }
    
    int getMax(){
        int value = data[0];
        data[0] = data[data.size()-1];
        data.resize(data.size() - 1);

        // restore heap property
        heapify(0);

        return value;
    }

    void print() const {
        for(const auto& item : data){
            cout << item << " "; 
        }
        cout << "\n";
    };
};
vector<int> readIntegersFromFile(const string& filename, int &n) {
    std::ifstream file(filename);
    vector<int> numbersVec;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    string line;

    // change if to while to read the whole file

    if (std::getline(file, line))
    {
        n = std::stoi(line);
    }
    if (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        int num;
        while (lineAsStream >> num) {
            numbersVec.push_back(num);
        }
    }

    file.close();
    return numbersVec;
}
int main(int argc, char* argv[]) {
    string filename = argv[1];
    int n;
    vector<int> input = readIntegersFromFile(filename, n);

    myHeap heap(input, n);
    heap.print();
    heap.getMax();
    heap.print();
    heap.insert(42);
    heap.print();
    heap.insert(-5);
    heap.print();
    heap.getMax();
    heap.print();
    return 0;
}