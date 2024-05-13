#include <string>
#include <ctime>
#include <vector>
#include <iostream>

//-------------------------------------------------UTIL-------------------------------------------------
int weightedRandom(std::vector<int> vahy);
int randRange(int bottom, int top);

//-------------------------------------------------ITEM-------------------------------------------------
class item
{
private:
    std::string name;
    int damage;
    int defence;
    int hitPoints;

public:
    item(std::string name, int damage, int defence, int hp);
    int getDamage();
    int getDefence();
};

//-------------------------------------------------PLAYER-------------------------------------------------
class player
{
private:
    std::string name;
    int damage;
    int defence;
    int hitPoints;
    double hpRegen;
    double mpRegen;
    std::vector<item*> items;

public:
    player(std::string name, int damage, int defence, int hp, double hpr);
    int addItem(item* predmet);
    int getDmg();
    int recieveDmg(int dmg);
    int recieveHit(class enemy* enem);
    int getHp();
};

//-------------------------------------------------FIELD-------------------------------------------------
class field
{
private:
    std::string name;

public:
    field(std::string name);
    virtual int playerOnField(class player* gamePlayer);
};

//-------------------------------------------------CHEST-------------------------------------------------
class chest : public field
{
private:
    int rarity;

public:
    chest(int rarity);
    int playerOnField(class player* gamePlayer);
};

//-------------------------------------------------ENEMY-------------------------------------------------
class enemy : public field
{
    std::string enemyName;
    int damage;
    int hitPoints;
    int defence;

public:
    enemy(std::string enemyName, int damage, int hp, int defence);
    int playerOnField(class player* gamePlayer);
    int getDmg();
};

//-------------------------------------------------GAMEFIELD-------------------------------------------------
class gameField
{
private:
    std::vector<field*> actualField;
    int position;

public:
    gameField();
    field* getRandomField();
    int move(class player* hrac);
    int getPos();
};

//-------------------------------------------------GAMEMASTER-------------------------------------------------
class gameMaster
{
private:
    player* playerGame;
    int position;
    gameField* playerField;

public:
    gameMaster(std::string pname, int pdamage, int pdefence);
    int makeMove();
    ~gameMaster();
};