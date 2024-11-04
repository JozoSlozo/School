#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
using std::cout; using std::vector; using std::endl; using std::queue; using std::string;

struct Node {
    int value;
    Node *left;
    Node *right;
    int depth;
    explicit Node(int val, int d) : value(val), left(nullptr), right(nullptr), depth(d) {}
};

class binarySearchTree {
private:
    Node *root;

    Node *insert(Node *entryPoint, int value, int h){
        if (entryPoint == nullptr)
        {
            return new Node(value, h);
        }
        if (value == entryPoint->value)
        {
            std::cerr << "duplicaties are not allowed" << std::endl;
            return entryPoint;
        }

        if (value > entryPoint->value)
        {
            entryPoint->right = insert(entryPoint->right, value, h+1);
        }
        else if (value < entryPoint->value){
            entryPoint->left = insert(entryPoint->left, value, h+1);
        }
        return entryPoint;
    }

    void deleteTree(Node *entryPoint){
        if (entryPoint == nullptr)
        {
            return;
        }
        deleteTree(entryPoint->left);
        deleteTree(entryPoint->right);
        delete entryPoint;
    }

    void inOrderToVec(const Node *entryPoint, vector<int> &data) const{
        if (entryPoint == nullptr)
        {
            return;
        }
        inOrderToVec(entryPoint->left, data);
        data.push_back(entryPoint->value);
        inOrderToVec(entryPoint->right, data);
    }

    void postOrderToVec(const Node *entryPoint, vector<int> &data) const{
        if (entryPoint == nullptr)
        {
            return;
        }
        postOrderToVec(entryPoint->left, data);
        postOrderToVec(entryPoint->right, data);
        data.push_back(entryPoint->value);
    }

    void preOrderToVec(const Node *entryPoint, vector<int> &data) const{
        if (entryPoint == nullptr)
        {
            return;
        }
        data.push_back(entryPoint->value);
        preOrderToVec(entryPoint->left, data);
        preOrderToVec(entryPoint->right, data);
    }

    Node *hasValue(Node *entryPoint, int value) const{
        if (entryPoint == nullptr)
        {
            return nullptr;
        }
        if (entryPoint->value == value)
        {
            return entryPoint;
        }
        if (entryPoint->value > value)
        {
            return hasValue(entryPoint->left, value);
        }
        if (entryPoint->value < value)
        {
            return hasValue(entryPoint->right, value);
        }
        return nullptr;
    }
    Node* nextInOrder(Node* entryPoint) {
        if (entryPoint == nullptr)
        {
            return nullptr;
        }
        entryPoint = entryPoint->right;
        while (entryPoint != nullptr && entryPoint->left != nullptr) {
            entryPoint = entryPoint->left;
        }
        return entryPoint;
    }
    Node *deleteNode(Node *entryPoint, int value){
        if (entryPoint == nullptr)
        {
            return entryPoint;
        }
        
        if (entryPoint->value > value)
        {
            entryPoint->left = deleteNode(entryPoint->left, value);
        }
        else if (entryPoint->value < value)
        {
            entryPoint->right = deleteNode(entryPoint->right, value);
        }
        else {
            if (entryPoint->left == nullptr) {
                Node* temp = entryPoint->right;
                delete entryPoint;
                return temp;
            }
            else if (entryPoint->right == nullptr) {
                Node* temp = entryPoint->left;
                delete entryPoint;
                return temp;
            }

            Node* temp = nextInOrder(entryPoint);
            entryPoint->value = temp->value;
            entryPoint->right = deleteNode(entryPoint->right, temp->value);
        }
        return entryPoint;
    }

public:
    
    binarySearchTree(){
        this->root = nullptr;
    }
    binarySearchTree(vector<int> vec){
        this->root = nullptr;
        for (int i : vec)
        {
            this->root = insert(this->root, i, 1);
        }
    }

    void insert(int value){
        this->root = insert(this->root, value, 1);
    }

    [[nodiscard]] vector<int> inOrderToVec() const{
        vector<int> fin;
        inOrderToVec(root, fin);
        return fin;
    }

    [[nodiscard]] vector<int> postOrderToVec() const{
        vector<int> fin;
        postOrderToVec(root, fin);
        return fin;
    }

    [[nodiscard]] vector<int> preOrderToVec() const{
        vector<int> fin;
        preOrderToVec(root, fin);
        return fin;
    }

    bool hasValue(int value) const{
        return hasValue(this->root, value);
    }
    void deleteNode(int value){
        deleteNode(this->root, value);
    }

    int height() const;

    ~binarySearchTree(){
        deleteTree(root);
    }
    void PP(){
        if (root == nullptr)
        {
            return;
        }
        queue<Node*> queue;
        queue.push(root);
        cout << root->value << " " << endl;
        int d = root->depth;
        while (!queue.empty())
        {
            Node* temp = queue.front();
            queue.pop();

            if (temp->depth != d)
            {
                cout << endl;
            }
            d = temp->depth;

            if (temp->left != nullptr)
            {   
                cout << temp->left->value << " ";
                queue.push(temp->left);
            }
            else 
            {
                cout << "X ";
            }

            if (temp->right != nullptr)
            {
                cout << temp->right->value << " ";
                queue.push(temp->right);
            }
            else 
            {
                cout << "X ";
            }
        }
        cout << endl;
    }
};

vector<int> readIntegersFromFile(const string& filename) {
    std::ifstream file(filename);
    vector<int> numbersVec;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    string line;

    // change if to while to read the whole file
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

void PPVector(vector<int> vec){
    for (int i : vec)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    string filename = argv[1];
    
    vector<int> input = readIntegersFromFile(filename);

    binarySearchTree* bin = new binarySearchTree(input);

    PPVector(bin->postOrderToVec());
    PPVector(bin->preOrderToVec());
    PPVector(bin->inOrderToVec());
    bin->PP();
    delete bin;
    return 0;
}