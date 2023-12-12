#include "gameSets.hpp"

Item item_set[ITEM_SET_SIZE] = {
    {0, "обычный меч", Item::tWeapon, 10},

    {1, "заточенный меч", Item::tWeapon, 15},
    {1, "заточенный меч", Item::tWeapon, 15},
    {1, "заточенный меч", Item::tWeapon, 15},

    {2, "зачарованный меч", Item::tWeapon, 20},
    {2, "зачарованный меч", Item::tWeapon, 20},

    {3, "проклятый меч", Item::tWeapon, 25},

    {4, "малое зелье здоровья", Item::tPotion, 25},
    {4, "малое зелье здоровья", Item::tPotion, 25},
    {4, "малое зелье здоровья", Item::tPotion, 25},
    {4, "малое зелье здоровья", Item::tPotion, 25},
    {4, "малое зелье здоровья", Item::tPotion, 25},

    {5, "зелье здоровья", Item::tPotion, 50},
    {5, "зелье здоровья", Item::tPotion, 50},
    {5, "зелье здоровья", Item::tPotion, 50},

    {6, "большое зелье здоровья", Item::tPotion, 100},
    {6, "большое зелье здоровья", Item::tPotion, 100},
    {7, "особое зелье здоровья", Item::tPotion, -100}};

Enemy_Info enemy_set[ENEMY_SET_SIZE] = {
    {0, 50, 5},

    {1, 30, 10},
    {1, 30, 10},

    {2, 15, 20}};