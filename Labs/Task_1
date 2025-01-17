#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <limits> // for input validation

// Define the Player class
class Player {
private:
    std::string name;
    int gold;
    std::vector<std::string_view> inventory;

public:
    Player(std::string_view m_name, int m_gold)
        : name{m_name}, gold{m_gold} {}

    int getGold() const {
        return gold;
    }

    std::string getName() const {
        return name;
    }

    void addPotion(std::string_view potion) {
        inventory.push_back(potion);
    }

    void spendGold(int amount) {
        gold -= amount;
    }

    void showInventory() const {
        std::cout << "\n" << name << "'s inventory:\n";
        if (inventory.empty()) {
            std::cout << "No potions purchased.\n";
        } else {
            for (const auto& item : inventory) {
                std::cout << "- " << item << '\n';
            }
        }
    }
};

// Define potions as a constant vector
const std::vector<std::pair<std::string_view, int>> potions {
    {"healing", 20},
    {"mana", 30},
    {"speed", 12},
    {"invisibility", 50}
};

// Function to display the shop
void shop() {
    std::cout << "Here is our selection for today:\n";

    for (std::size_t i = 0; i < potions.size(); ++i) {
        std::cout << i << ") " << potions[i].first << " costs " << potions[i].second << "\n";
    }
}

// Function to handle player purchases
void handlePurchase(Player& player) {
    while (true) {
        std::cout << "\nEnter the potion number to buy or -1 to exit: ";
        int choice;
        std::cin >> choice;

        // Input validation
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == -1) {
            break;
        }

        if (choice < 0 || static_cast<std::size_t>(choice) >= potions.size()) {
            std::cout << "Invalid potion number.\n";
        } else if (player.getGold() < potions[choice].second) {
            std::cout << "You don't have enough gold to buy a " << potions[choice].first << ".\n";
        } else {
            player.spendGold(potions[choice].second);
            player.addPotion(potions[choice].first);
            std::cout << "You bought a " << potions[choice].first << "!\n";
            std::cout << "Remaining gold: " << player.getGold() << "\n";
        }
    }
}

// Main function
int main() {
    std::string my_name;
    int my_gold{};

    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";
    std::cin >> my_name;

    std::cout << "Enter the amount of gold you want: ";
    std::cin >> my_gold;

    // Create a Player object
    Player me(my_name, my_gold);

    std::cout << "\nWelcome, " << me.getName() << "! You have " << me.getGold() << " gold.\n";

    shop();
    handlePurchase(me);
    me.showInventory();

    return 0;
}
