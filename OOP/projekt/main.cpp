#include "game.h"

int main(){
    std::srand(std::time(nullptr));
    gameMaster *hra = new gameMaster("pepa", 5, 5);
    while (!hra->makeMove())
    {
        
    }
    return 0;
}