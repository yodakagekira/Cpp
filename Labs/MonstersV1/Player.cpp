#include<iostream>
#include <string>
#include "C:\Users\Ahmad_2\Documents\Computer Science\C++\Test2\Creature.cpp"


class Player : public Creature {
private:
    int m_level{1};  // Player starts at level 1

public:
    Player(const std::string& name)
        : Creature(name, '@', 10, 1, 0) // name, symbol, health=10, damage=1, gold=0
    {}

    void levelUp() { ++m_level; }
    int getLevel() const { return m_level; }
    bool hasWon() const { return m_level >= 20; }
};
