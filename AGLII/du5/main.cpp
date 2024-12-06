#include <iostream>
#include <vector>
#include <algorithm>

using std::vector, std::cout, std::endl, std::max;

class CoinCollectRobot
{
private:
    vector<vector<int>> C;
    vector<vector<int>> F;
    size_t n;
    size_t m;

public:

    CoinCollectRobot(const vector<vector<int>> mat)
    {
        this->C = mat;
        this->m = mat[0].size();
        this->n = mat.size();
        F = vector<vector<int>>(n, vector<int>(m, 0));
    }

    int solveCoinCollectProblem(){
        F[0][0] = C[0][0];
        for (size_t i = 1; i < n; ++i) {
            F[i][0] = F[i-1][0] + C[i][0];
            for (size_t j = 1; j < m; ++j) {
                F[0][j] = F[0][j - 1] + C[0][j];
                F[i][j] = max(F[i - 1][j], F[i][j - 1]) + C[i][j];
            }

        }
        return F[n-1][m-1];
    }

    void PPMatrix(vector<vector<int>> mat){
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                cout << mat[i][j] << (j == m-1 ? "" : ", ");
            }
            cout << endl;
        }
    }
};
int main(){
    vector<vector<int>> board1 = {
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0}
    };
    CoinCollectRobot ccr1 = CoinCollectRobot(board1);
    cout << "Board 1: " << ccr1.solveCoinCollectProblem() << " coins." << endl;


    vector<vector<int>> board2 = {
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 1}
    };
    CoinCollectRobot ccr2 = CoinCollectRobot(board2);
    cout << "Board 2: " << ccr2.solveCoinCollectProblem() << " coins." << endl;
}