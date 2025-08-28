#include <iostream>
#include <string>

class Creature {
private:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_dmg{};
    int m_gold{};

public:
    // Constructor
    Creature(const std::string& name, char symbol, int health, int dmg, int gold)
        : m_name(name), m_symbol(symbol), m_health(health), m_dmg(dmg), m_gold(gold)
    {}

    // Getters
    std::string getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDmg() const { return m_dmg; }
    int getGold() const { return m_gold; }

    // Other functions
    void reduceHealth(int amount) {
        m_health -= amount;
    }

    bool isDead() const {
        return m_health <= 0;
    }

    void addGold(int amount) {
        m_gold += amount;
    }
};

// Test program
int main()
{
    Creature o{ "orc", 'o', 4, 2, 10 };
    o.addGold(5);
    o.reduceHealth(1);
    std::cout << "The " << o.getName() << " has "
              << o.getHealth() << " health and is carrying "
              << o.getGold() << " gold.\n";

    return 0;
}
