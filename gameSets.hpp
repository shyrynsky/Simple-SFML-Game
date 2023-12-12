#pragma once

#include <string>

struct Item
{
    int id;
    std::string name;
    enum Type
    {
        tUndef,
        tWeapon,
        tPotion
    } type;
    union Prop
    {
        int damage;
        int health;
    } prop;
};

struct Enemy_Info
{
    int id;
    int health;
    int damage;
};

#define ITEM_SET_SIZE 18
#define ENEMY_SET_SIZE 4

extern Item item_set[ITEM_SET_SIZE];         // TODO заполнить
extern Enemy_Info enemy_set[ENEMY_SET_SIZE]; // TODO заполнить