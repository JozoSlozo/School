//jeden hrac, hazi kostkou tim se pohybuje dopredu, kazde pole ma specialni efekt
//pouziva se override na defaultni classu pole, např specialni pole chest, nebo enemy
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include "game.h"

int gameMaster::position = 0;

//-------------------------------------------------UTIL-------------------------------------------------
#pragma region util
int weightedRandom(std::vector<int> vahy){
    int pole = rand()%100;
    for (int i = 0; i < vahy.size(); i++)
    {
        if (pole < vahy[i])
        {
            return i;
        }
        pole -= vahy[i];
    }
    return -1;
}
int randRange(int bottom, int top){
    return rand() % (top - bottom) + bottom; 
}
#pragma endregion
//-------------------------------------------------ITEM-------------------------------------------------
#pragma region item
item::item(std::string name, int damage, int defence, int hp){
    this->name = name;
    this->damage = damage;
    this->defence = defence;
    this->hitPoints = hp;
}
int item::getDamage(){
    return this->damage;
}
int item::getDefence(){
    return this->defence;
}
int item::getHP(){
    return this->hitPoints;
}
#pragma endregion
//-------------------------------------------------PLAYER-------------------------------------------------
#pragma region player
player::player(std::string name, int damage, int defence, int hp, double hpr){
    this->name = name;
    this->damage = damage;
    this->defence = defence;
    this->hitPoints = hp;
    this->hpRegen = hpr;
    this->maxHp = hp;
}
int player::addItem(item* predmet){
    this->items.push_back(predmet);
    this->maxHp += predmet->getHP();
    return 0;
}
int player::getDmg(){
    int temp = damage;
    for (item* i : this->items)
    {
        temp += i->getDamage();
    }
    return temp;
}
int player::recieveDmg(int dmg){
    int temp = dmg - this->defence;
    for (item* i : this->items)
    {
        temp -= i->getDefence();
    }
    if (temp > 0)
    {
        this->hitPoints -= temp;
        std::cout << this->name << " obdržel " << temp << " poškození a má " << this->hitPoints << " životů" << std::endl;
        if (this->hitPoints <= 0)
        {
            std::cout << this->name << " umírá" << std::endl;
            return 1;
        }
        return 0;
    }
    else{
        std::cout << this->name << " se ubráníl před požkozením" << std::endl;
        return 0;
    }
    
}
int player::getHp(){
    return this->hitPoints;
}
int player::regenHp(){
    if (!((this->hitPoints + this->hpRegen) > this->maxHp))
    {
        this->hitPoints += this->hpRegen;
    }
    return 0;
}
#pragma endregion
//-------------------------------------------------FIELD-------------------------------------------------
#pragma region field
field::field(std::string name){
    this->name = name;
}
int field::playerOnField(player* gamePlayer){
    return 0;
}
#pragma endregion
//-------------------------------------------------CHEST-------------------------------------------------
#pragma region chest
chest::chest(int ratiry) : field("truhla"){
    this->rarity = rarity;
}
int chest::playerOnField(player* gamePlayer){
    std::vector<std::string> nazvy = {"meč", "šťít", "brnění"};
    std::vector<std::vector<int>> staty {
        {1, 0, 0},
        {0, 1, 0},
        {0, 1, 1}
    };
    int predmet = randRange(0, 3);
    item* temp = new item(nazvy[predmet], staty[predmet][0] * randRange(rarity, rarity+5), staty[predmet][1] * randRange(rarity, rarity+5), staty[predmet][2] * randRange(rarity, rarity+5));
    std::cout << "Hráč otevřel truhlu s " << nazvy[predmet] << std::endl;
    gamePlayer->addItem(temp);
    return 0;
}
#pragma endregion
//-------------------------------------------------ENEMY-------------------------------------------------
#pragma region enemy
enemy::enemy(std::string enemyName, int damage, int hp, int defence) : field("enemy"){
    this->enemyName = enemyName;
    this->damage = damage;
    this->hitPoints = hp;
    this->defence = defence;
}
int enemy::playerOnField(player* gamePlayer){
    while (1)
    {   
        int dmg = randRange(1, gamePlayer->getDmg());
        this->hitPoints -= dmg;
        std::cout << this->enemyName << " obdržel " << dmg << " poškození a má " << this->hitPoints << " životů" << std::endl; 
        if (this->hitPoints <= 0)
        {
            std::cout << this->enemyName << " umírá" << std::endl;
            break;
        }
        else if (gamePlayer->recieveDmg(randRange(1, this->damage))){
            break;
        }
    }
    
    return 0;
}
int enemy::getDmg(){
    return this->damage;
}
#pragma endregion
//-------------------------------------------------GAMEFIELD-------------------------------------------------
#pragma region gameField
gameField::gameField()
{
}
int gameField::move(player* hrac){
    this->actualField.push_back(this->getRandomField());
    this->actualField[gameMaster::position]->playerOnField(hrac);
    gameMaster::position++;
    return 0;
}
field* gameField::getRandomField(){
    std::vector<int> vahy = {50, 25, 25};
    std::vector<std::string> enemyNames = {"zombie", "upír", "troll", "ghul", "drak"};
    int pole = weightedRandom(vahy);
    switch (pole)
    {
    case 0:
        std::cout << "Hráč stoupnul na prázdné pole" << std::endl;
        return new field("prazdne");
        break;
    case 1:
        std::cout << "Hráč stoupnul na pole s truhlou" << std::endl;
        return new chest(randRange(gameMaster::position, gameMaster::position + 10));
    case 2:
        std::cout << "Hráč stoupnul na pole s nepřítelem" << std::endl;
        return new enemy(enemyNames[randRange(0, enemyNames.size())], randRange(gameMaster::position, gameMaster::position + 10), randRange(gameMaster::position, gameMaster::position + 10), randRange(gameMaster::position, gameMaster::position + 10));
    default:
        return nullptr;
        break;
    }
    return nullptr;
}
#pragma endregion
//-------------------------------------------------GAMEMASTER-------------------------------------------------
#pragma region gameMaster
gameMaster::gameMaster(std::string pname, int pdamage, int pdefence){
    this->playerGame = new player(pname, pdamage, pdefence, 20, 1);
    this->playerField = new gameField();
}
gameMaster::~gameMaster(){
    delete this->playerField;
    delete this->playerGame;
}

int gameMaster::makeMove(){
    std::cout << "--------------------------------------------------------------------------------\nNové kolo, pozice hráče: " << gameMaster::position << "\n--------------------------------------------------------------------------------" << std::endl;
    this->playerField->move(this->playerGame);
    if (this->playerGame->getHp() <= 0)
    {   
        std::cout << "Konec hry" << std::endl;
        return 1;
    }
    this->playerGame->regenHp();
    return 0;
}
#pragma endregion