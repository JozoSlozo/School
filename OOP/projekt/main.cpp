//jeden hrac, hazi kostkou tim se pohybuje dopredu, kazde pole ma specialni efekt
//pouziva se override na defaultni classu pole, např specialni pole chest, nebo enemy
using namespace std;
#include <string>


#pragma region field
class field
{
private:
public:
    field();
    virtual int playerOnField(player* gamePlayer);
};
field::field(){

}
int field::playerOnField(player* gamePlayer){
    return 0;
}
#pragma endregion

#pragma region chest
class chest : public field
{
private:
    int rarity;//higher chest rarity = higher chance for better item
public:
    int playerOnField(player* gamePlayer);
};
int chest::playerOnField(player* gamePlayer){
    //add item to players inventory
    return 0;
}
#pragma endregion

#pragma region enemy
class enemy : public field
{
private:
public:
};
#pragma endregion

#pragma region gameField
class gameField
{
private:
    field** actualField;
    int actualCapacity;
public:
    gameField(/* args */);
    ~gameField();
};

gameField::gameField(/* args */)
{
}

gameField::~gameField()
{
}

#pragma endregion

#pragma region item
class item
{
private:
    string name;
    int damage;
    int defence;
    int hitPoints;
    int manaPoints;
public:
    item(string name, int damage);
    item(string name, int defence);
};
#pragma endregion

#pragma region player
class player
{
private:
    string name;
    int damage;
    int defence;
    int hitPoints;
    int manaPoints;
    double hpRegen;
    double mpRegen;
    item** items;
public:
    player(string name, int damage, int defence, int hp, int mp, double hpr, double mpr, int maxItems);
};
player::player(string name, int damage, int defence, int hp, int mp, double hpr, double mpr, int maxItems){
    this->name = name;
    this->damage = damage;
    this->defence = defence;
    this->hitPoints = hp;
    this->manaPoints = mp;
    this->hpRegen = hpr;
    this->mpRegen = mpr;
    this->items = new item*[maxItems];
}
#pragma endregion

#pragma region gameMaster
class gameMaster
{
private:
    player* playerGame;
    int playerPosition;
    gameField* playerField;
public:
    gameMaster(string pname, int pdamage, int pdefence);
    ~gameMaster();
};
gameMaster::gameMaster(string pname, int pdamage, int pdefence){
    this->playerGame = new player(pname, pdamage, pdefence, 20, 20, 1, 1, 4);
    this->playerPosition = 0;
    this->gameField = new gameField();
}
#pragma endregion