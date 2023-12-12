#include "gameSets.hpp"

Item item_set[ITEM_SET_SIZE] = {
    {0, "a common sword", Item::tWeapon, 10},

    {1, "a sharpened sword", Item::tWeapon, 15},
    {1, "a sharpened sword", Item::tWeapon, 15},
    {1, "a sharpened sword", Item::tWeapon, 15},

    {2, "an enchanted sword", Item::tWeapon, 20},
    {2, "an enchanted sword", Item::tWeapon, 20},

    {3, "the cursed sword", Item::tWeapon, 25},

    {4, "a small health potion", Item::tPotion, 25},
    {4, "a small health potion", Item::tPotion, 25},
    {4, "a small health potion", Item::tPotion, 25},
    {4, "a small health potion", Item::tPotion, 25},
    {4, "a small health potion", Item::tPotion, 25},

    {5, "health potion", Item::tPotion, 50},
    {5, "health potion", Item::tPotion, 50},
    {5, "health potion", Item::tPotion, 50},

    {6, "a large health potion", Item::tPotion, 100},
    {6, "a large health potion", Item::tPotion, 100},
    {7, "a special health potion", Item::tPotion, -100}};

Enemy_Info enemy_set[ENEMY_SET_SIZE] = {
    {0, 50, 5},

    {1, 30, 10},
    {1, 30, 10},

    {2, 15, 20}};