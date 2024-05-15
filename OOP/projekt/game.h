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
    int getHP();
};

//-------------------------------------------------PLAYER-------------------------------------------------
class player
{
private:
    std::string name;
    int damage;
    int defence;
    int hitPoints;
    int maxHp;
    double hpRegen;
    std::vector<item*> items;

public:
    player(std::string name, int damage, int defence, int hp, double hpr);
    player(std::string name);
    int addItem(item* predmet);
    int getDmg();
    int recieveDmg(int dmg);
    int recieveHit(class enemy* enem);
    int getHp();
    int regenHp();
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

public:
    gameField();
    field* getRandomField();
    int move(class player* hrac);
};

//-------------------------------------------------GAMEMASTER-------------------------------------------------
class gameMaster
{
private:
    player* playerGame;
    gameField* playerField;

public:
    static int position;
    gameMaster(std::string pname);
    int makeMove();
    ~gameMaster();
};