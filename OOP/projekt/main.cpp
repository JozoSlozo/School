#include "game.h"

int main(){
    std::srand(std::time(nullptr));
    gameMaster *hra = new gameMaster("pepa", 2, 2);
    while (!hra->makeMove())
    {
        
    }
    return 0;
}