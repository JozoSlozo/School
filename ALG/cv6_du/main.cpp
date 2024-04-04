#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<double>> MatrixMultiply(vector<vector<double>> A,vector<vector<double>> B, int size){//slozitost je n^3
    vector<vector<double>> temp(size, vector<double>(size, 0));
    for (int rows = 0; rows < size; ++rows) {
        for (int columns = 0; columns < size; columns++) {
            for (int multiply = 0; multiply < size; multiply++) {
                temp[rows][columns] += A[rows][multiply] * B[multiply][columns];
            }
        }
    }
    return temp;
}
vector<vector<double>> MatrixExponential(vector<vector<double>> baseMatrix, int matrixSize, int accuracyNumber){//slozitost je n^2 * accuracyNumber
    vector<vector<double>> matrix(matrixSize, vector<double>(matrixSize, 0));
    vector<vector<double>> powerMatrix(matrixSize, vector<double>(matrixSize, 0));
    double fact = 1;
    for (int i = 0; i < matrixSize; i++)//init power matrix to 1 matrix
    {
        powerMatrix[i][i] = 1;
        matrix[i][i] = i;
    }
    
    for (int exponential = 1; exponential < accuracyNumber; exponential++)
    {
        powerMatrix = MatrixMultiply(powerMatrix, baseMatrix, matrixSize);//calculate power of i of matrix
        fact *= exponential; //factorial i
        for (int row = 0; row < matrixSize; row++)
        {
            for (int column = 0; column < matrixSize; column++)
            {
                matrix[row][column] += powerMatrix[row][column] / fact;
            }
        }
    }
    return matrix;
}

vector<vector<double>> MatrixSine(vector<vector<double>> baseMatrix, int matrixSize, int accuracyNumber){//slozitost je n^2 * accuracyNumber
    vector<vector<double>> matrix = baseMatrix;//starting matrix set to A
    vector<vector<double>> powerMatrix = baseMatrix;//starting power matrix set to ^1
    double fact = 1;
    int number = 1;// -/+ number
    for (int exponential = 1; exponential < accuracyNumber; exponential++)
    {
        for (int i = 0; i < 2; i++)//2n
        {
            fact*=exponential*2 + i;
            powerMatrix = MatrixMultiply(powerMatrix, baseMatrix, matrixSize);
        }
        number *= -1;

        for (int row = 0; row < matrixSize; row++)
        {
            for (int column = 0; column < matrixSize; column++)
            {
                matrix[row][column] += number * (powerMatrix[row][column] / fact);
            }
        }
    }
    return matrix;
}

vector<vector<double>> MatrixCosine(vector<vector<double>> baseMatrix, int matrixSize, int accuracyNumber){//slozitost je n^2 * accuracyNumber
    vector<vector<double>> matrix(matrixSize, vector<double>(matrixSize, 0));
    vector<vector<double>> powerMatrix(matrixSize, vector<double>(matrixSize, 0));
    double fact = 1;
    for (int i = 0; i < matrixSize; i++)//matrix set to 1
    {
        powerMatrix[i][i] = 1;
        matrix[i][i] = i;
    }
    int number = 1;// -/+ number
    int factnum = 1;//number for factorial calculation
    for (int exponential = 1; exponential < accuracyNumber; exponential++)
    {
        for (int i = 0; i < 2; i++)//2n
        {
            fact *= factnum;
            powerMatrix = MatrixMultiply(powerMatrix, baseMatrix, matrixSize);
            factnum ++;
        }
        number *= -1;
        for (int row = 0; row < matrixSize; row++)
        {
            for (int column = 0; column < matrixSize; column++)
            {
                matrix[row][column] += number * (powerMatrix[row][column] / fact);
                
            }
        }
    }
    return matrix;
}

double power(double num, int n){
    switch (n)
    {
    case 2:
        return num * num;
        break;
    case 1:
        return num;
    case 0:
        return 1;
    default:
        break;
    }
    if (n % 2 == 0)
    {
        double temp = power(num, n/2);
        return temp * temp;
    }
    else{
        return power(num, n-1) * num;
    }
    return 0;
}

double power2(double num, int n) {
    double result = 1.0;
    if (n == 0) {
        return 1.0;
    }
    if (n == 1) {
        return num;
    }
    while (n > 0) {
        if (n % 2 == 1) {
            result *= num;
        }       
        num *= num;
        n /= 2;
    }
    return result;
}

int main() {
    vector<vector<double>> pes = {{1,2},{3,4}};
    vector<vector<double>> exp = MatrixExponential(pes, 2, 20);
    vector<vector<double>> sin = MatrixSine(pes, 2, 20);
    vector<vector<double>> cos = MatrixCosine(pes, 2, 20);
    cout << "exp: " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << exp[i][j];
            cout << ", ";
        }
        cout << endl;
    }
    cout << "sin: " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << sin[i][j];
            cout << ", ";
        }
        cout << endl;
    }
    cout << "cos: " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << cos[i][j];
            cout << ", ";
        }
        cout << endl;
    }
    cout << power(2, 12) << endl;
    cout << power2(2, 12) << endl;
}