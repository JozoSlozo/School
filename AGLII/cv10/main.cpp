#include <iostream>
#include <vector>

using std::vector, std::cout, std::pair, std::endl;

class placeQueens
{
private:
    vector<vector<int>> matrix;
    int size;
public:
    placeQueens(int size){
        this->size = size;
        matrix = vector<vector<int>>(size, vector<int>(size, 0));
    }
    int PlaceQueen(vector<int> previous_pos, int current_row){
        if (current_row == size)
        {
            return 1;
        }
        for (int column_positions = 0; column_positions < size; column_positions++)
        {
            int is_valid = 1;
            for (int queenrow = 0; queenrow < current_row; queenrow++)
            {
                if (column_positions == previous_pos[queenrow])
                {
                    is_valid = 0;
                    break;
                }
                
            }
            if (is_valid)
            {
                previous_pos.push_back(column_positions);
                PlaceQueen(previous_pos, current_row+1);
            }
            
        }
        return 0;
    }
};





int main(){
    placeQueens pq = placeQueens(4);
    cout << pq.PlaceQueen(vector<int>(), 0) << endl;
}