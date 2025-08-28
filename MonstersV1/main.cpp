#include <iostream>
#include <string>
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Creature.cpp"
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Player.cpp"
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Monster.cpp"
#include "random.h"

int main()
{
    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;

    Player player{ playerName };
    std::cout << "Welcome, " << player.getName() << '\n';

    // If the player isn't dead and hasn't won yet, the game continues
    while (!player.isDead() && !player.hasWon())
        Monster::fightMonster(player);   // ✅ FIXED

    // At this point, the player is either dead or has won
    if (player.isDead())
    {
        std::cout << "You died at level " << player.getLevel()
                  << " and with " << player.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }
    else
    {
        std::cout << "You won the game with "
                  << player.getGold() << " gold!\n";
    }

    return 0;
}
