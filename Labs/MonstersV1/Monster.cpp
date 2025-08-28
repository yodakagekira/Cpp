#pragma once
#include <iostream>
#include <string>
#include <array>
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Creature.cpp"
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Player.cpp"
#include "random.h"

class Monster : public Creature
{
public:
    enum Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

private:
    inline static std::array<Creature, max_types> monsterData{
        Creature{"dragon", 'D', 20, 4, 100},
        Creature{"orc",    'o',  4, 2, 25},
        Creature{"slime",  's',  1, 1, 10}
    };

public:
    Monster(Type type)
        : Creature(monsterData[type])
    {
    }

    static Monster getRandomMonster()
    {
        int num{ Random::get(0, max_types - 1) };
        return Monster{ static_cast<Type>(num) };
    }

    // Player attacks monster
    static void attackMonster(Player& player, Monster& monster)
    {
        if (player.isDead()) return;

        std::cout << "You hit the " << monster.getName()
                  << " for " << player.getDmg() << " damage.\n";

        monster.reduceHealth(player.getDmg());

        if (monster.isDead())
        {
            std::cout << "You killed the " << monster.getName() << ".\n";
            player.levelUp();
            std::cout << "You are now level " << player.getLevel() << ".\n";
            std::cout << "You found " << monster.getGold() << " gold.\n";
            player.addGold(monster.getGold());
        }
    }

    // Monster attacks player
    static void attackPlayer(const Monster& monster, Player& player)
    {
        if (monster.isDead()) return;

        player.reduceHealth(monster.getDmg());
        std::cout << "The " << monster.getName()
                  << " hit you for " << monster.getDmg() << " damage.\n";
    }

    // Handles the entire fight
    static void fightMonster(Player& player)
    {
        Monster monster{ getRandomMonster() };
        std::cout << "You have encountered a " << monster.getName()
                  << " (" << monster.getSymbol() << ").\n";

        while (!monster.isDead() && !player.isDead())
        {
            std::cout << "(R)un or (F)ight: ";
            char input{};
            std::cin >> input;

            if (input == 'R' || input == 'r')
            {
                if (Random::get(1, 2) == 1)
                {
                    std::cout << "You successfully fled.\n";
                    return;
                }
                else
                {
                    std::cout << "You failed to flee.\n";
                    attackPlayer(monster, player);
                    continue;
                }
            }

            if (input == 'F' || input == 'f')
            {
                attackMonster(player, monster);
                attackPlayer(monster, player);
            }
        }
    }
};
