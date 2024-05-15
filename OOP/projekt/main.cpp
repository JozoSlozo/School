#include "game.h"
int main(){
    std::srand(std::time(nullptr));
    gameMaster *hra = new gameMaster("Pepa");
    while (!hra->makeMove())
    {
        
    }
    return 0;
}