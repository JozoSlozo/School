#include <iostream>
#include "binary_tree.h"
using std::cout;

int main(){
    binarySearchTree* bin = new binarySearchTree();
    const int inputs[] = {5,1,0,6,8,9,7,4};
    for (int i : inputs)
    {
        bin->insert(i);
    }
    vector<int> temp;
    temp = bin->inOrderToVec();
    for (int i : temp)
    {
        std::cout << i << std::endl;
    }
    return 0;
}