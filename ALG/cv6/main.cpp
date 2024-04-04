using namespace std;
#include <iostream>
#include <vector>

vector<int> selectionsort(vector<int> arr){
    size_t min;
    vector<int> temp = arr;
    for (size_t i = 0; i < temp.size()-1; i++)
    {
        min = i;
        for (size_t l = i; l < temp.size(); l++)
        {
            if (temp[min] > temp[l])
            {
                min = l;
            }   
        }
        std::swap(temp[i], temp[min]);
    }
    return temp;
}
vector<int> bubblesort(vector<int> arr){
    vector<int> temp = arr;
    for (size_t i = 0; i < temp.size(); i++)
    {
        for (size_t j = 0; j < temp.size()-(i+1); j++)
        {
            if (temp[j] > temp[j + 1])
            {
                std::swap(temp[j], temp[j + 1]);
            }
        }
    }
    return temp;
}
struct Point
{
    double x;
    double y;
};
bool IsUpFromLine(Point primka1, Point primka2, Point input){
    double a = primka2.y - primka1.x;
    double b = primka1.x - primka2.y;
    double c = primka1.y*primka2.x - primka2.y*primka1.x;
    if(a*input.x + b*input.y + c > 0){
        return 1;
    }
    return 0;
}

int main(){
    vector<int> array = {4,5,6,2,1,3,10,7,8,5};
    vector<int> arraySorted = bubblesort(array);
    for (int i = 0; i < array.size(); i++)
    {
        cout << arraySorted[i] << endl;
    }
    return 0;
}