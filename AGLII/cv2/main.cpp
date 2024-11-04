using namespace std;
#include <vector>
#include <iostream>

vector<double> SolveUpperTriangle(vector<vector<double>> A, vector<double> rhs){
    vector<double> result(A.size(), 0);
    double suma = 0;
    for (int i = A.size() - 1; i >= 0; i--)
    {
        suma = 0;
        for (int j = i; j < A.size(); j++)
        {
            suma += A[i][j] * result[j];
        }
        //   otocime na druhou stranu / nazenama
        result[i] = (rhs[i] - suma) / A[i][i];
    }
    return result;
}
vector<vector<double>> SolveWithGauss(vector<vector<double>> A, vector<double> rhs){
    int n = A.size();
    vector<vector<double>> M = A;
    vector<double> result = rhs;
    vector<vector<double>> L = vector<vector<double>>(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
    {
        L[i][i] = 1;
    }
    
    for (int i = 0; i < A.size(); i++)
    {
        int rowWithPivot = i;
        double pivotValue = M[i][i];

        for (int j = 0; j < n; j++)
        {
            if (abs(M[j][i]) > abs(pivotValue))
            {
                rowWithPivot = j;
                pivotValue = M[j][i];
            }
        }
        if (rowWithPivot != 1)
        {
            swap(M[i], M[rowWithPivot]);
            swap(rhs[i], rhs[rowWithPivot]);
        }
        
        
        for (int j = i + 1; j < A.size(); j++)
        {
            double factor = -M[i][j]/M[i][i];
            L[i][j] = factor;

            for (int k = i; k < A.size(); k++)
            {
                M[j][k] += factor*M[i][k];
            }
            result[j] += factor * result[i];
        }
    }
    return M;
}

vector<vector<double>> MatrixCal(vector<vector<double>> A, vector<vector<double>> B){
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            
        }
    }
    
}

int test(vector<double> input){
    vector<vector<double>> res(input.size(), vector<double>(input.size(), 0));
    for (int i = 0; i < input.size(); i++)
    {
        res[i][input[i]] = 1;
    }
    
}

int main(){
    vector<vector<double>> testup = {{2,-1,1}, {4,1,-1},{1,1,1}};
    vector<double> test2up = {1,5,0};

    vector<vector<double>> res = SolveWithGauss(testup, test2up);



    for (vector<double> a : res)
    {
        for (double i : a)
    {
        cout << i << ", ";
    }
    cout << endl;
    }
    cout << endl;
}