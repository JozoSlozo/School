using namespace std;
#include <iostream>
#include <cmath>
#include <vector>

using point=pair<double, double>;

int Position(point A, point B, point C){
    int position = (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
    if (position > 0)
    {
        return 1;
    }
    else if (position < 0)
    {
        return -1;
    }
    return 0;
}
double Distance(point A, point B, point C){
    double a = A.first - B.first;
    double b = - (B.second - A.second);
    double c = - (a * A.first - b * A.second);
    double dist = abs(a * C.first + b * C.second + c) / sqrt(a*a + b*b);
    return dist;
}

point TheFarthestPoint(point A, point B, vector<point> input_set){
    double max_dist = -1;
    point max_point;
    for (point i : input_set)
    {
        double temp = Distance(A, B, i);
        if (temp > max_dist)
        {
            max_dist = temp;
            max_point = i; 
        }
        
    }
    return max_point;
}
pair<point, point> FindMinMax(vector<point> input_set){
    pair<point, point> fin;
    fin.first = input_set[0];
    fin.second = input_set[0];
    for (point i : input_set)
    {
        if (fin.first.first < i.first)
        {
            fin.first = i;
        }
        if (fin.second.first > i.first)
        {
            fin.second = i;
        }
    }
    return fin;   
}
vector<point> QuickHull(vector<point> input_set, point start, point end){
    if (input_set.size() < 4)
    {
        return input_set;
    }
    point max_dist = TheFarthestPoint(start, end, input_set);

    vector<point> upper_part_first;

    QuickHull(upper_part_first, start, max_dist);

    vector<point> upper_part_second;

    QuickHull(upper_part_second, max_dist, end);
}

int main(){

    return 0;
}