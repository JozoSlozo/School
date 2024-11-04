#include <vector>
#include <iostream>
#include <queue>
#include "binary_tree.h"
using std::cout, std::vector, std::queue, std::endl;

Node *binarySearchTree::insert(Node *entryPoint, int value, int h){
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
void binarySearchTree::insert(int value){
    this->root = insert(root, value, 1);
}
binarySearchTree::binarySearchTree(){
    this->root = nullptr;
}
void binarySearchTree::inOrderToVec(const Node *entryPoint, vector<int> &data) const{
    if (entryPoint == nullptr)
    {
        return;
    }
    inOrderToVec(entryPoint->left, data);
    data.push_back(entryPoint->value);
    inOrderToVec(entryPoint->right, data);
}
void binarySearchTree::postOrderToVec(const Node *entryPoint, vector<int> &data) const{
    if (entryPoint == nullptr)
    {
        return;
    }
    postOrderToVec(entryPoint->left, data);
    postOrderToVec(entryPoint->right, data);
    data.push_back(entryPoint->value);
}
void binarySearchTree::preOrderToVec(const Node *entryPoint, vector<int> &data) const{
    if (entryPoint == nullptr)
    {
        return;
    }
    preOrderToVec(entryPoint->left, data);
    preOrderToVec(entryPoint->right, data);
    data.push_back(entryPoint->value);
}
vector<int> binarySearchTree::inOrderToVec() const{
    vector<int> fin;
    inOrderToVec(root, fin);
    return fin;
}
vector<int> binarySearchTree::postOrderToVec() const{
    vector<int> fin;
    postOrderToVec(root, fin);
    return fin;
}
vector<int> binarySearchTree::preOrderToVec() const{
    vector<int> fin;
    preOrderToVec(root, fin);
    return fin;
}
void binarySearchTree::deleteTree(Node* entryPoint){
    if (entryPoint == nullptr)
    {
        return;
    }
    deleteTree(entryPoint->left);
    deleteTree(entryPoint->right);
    delete entryPoint;
}
bool binarySearchTree::hasValue(const Node* entryPoint, int value) const{
    if (entryPoint == nullptr)
    {
        return false;
    }
    if (entryPoint->value == value)
    {
        return true;
    }
    if (entryPoint->value > value)
    {
        return hasValue(entryPoint->left, value);
    }
    if (entryPoint->value < value)
    {
        return hasValue(entryPoint->right, value);
    }
    return false;
}
void binarySearchTree::PP(){
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
binarySearchTree::~binarySearchTree(){
    deleteTree(root);
}