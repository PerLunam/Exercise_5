#ifndef EXERCISE_5_CHARACTER_H
#define EXERCISE_5_CHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "game.h"
#include "item.h"
#include "type.h"
#include "exception.h"

class Character
{
private:

protected:
    Game* parent;
    std::string char_name;
    int char_health;
    int char_gold;
    int char_armor;
    int char_mr;
    std::vector<std::shared_ptr<Item>> inventory;
    /*
    std::map<int, std::shared_ptr<Item>> inventory;
    int nextInventoryID = 0;
    */

public:
    //Konstruktor der Class "Character"

    //Individueller Konstruktor
    Character(Game* parent, const std::string &name, int health, int gold, int armor, int mr)
            : parent(parent), char_name(name), char_health(health), char_gold(gold), char_armor(armor), char_mr(mr), inventory()
    {
        //Exception, falls kein Name bei der Initialisierung angegeben wurde
        if(name.empty())
        {
            throw InvalidArgumentException("Character:Character: Bitte gib einen Namen ein.");
        }

        //Exception, falls ein negativer Wert bei der Initialisierung angegeben wurde
        if(health < 0 || gold < 0 || armor < 0 || mr < 0)
        {
            throw InvalidArgumentException("Character::Character: Bitte gib einen Wert größer oder gleich 0 ein.");
        }

        //std::cout << "Character::Constructor: " << char_name << std::endl;
    }

    //Destruktor
    virtual ~Character()
    {
        //std::cout << "Character::Destructor: " << char_name << std::endl;
        inventory.clear();

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;
    }

    //----------------------------- Objektfunktionen -----------------------------
    virtual void attack(Character *enemy) = 0;

    bool fight(Character *enemy);

    void addInventarItem(std::shared_ptr<Item> item);
    //int addInventarItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeInventarItem(int slot);

    virtual enumType &getType() = 0;

    std::shared_ptr<Item> retrieveRandomLoot(Character *enemy);

    int countItems();

    //----------------------------- Getter & Setter -----------------------------
    const std::string& getName() const;
    void setName(const std::string& newName);

    int getHealth() const;
    void setHealth(int newHealth);

    int getGold() const;
    void setGold(int newGold);

    int getArmor() const;
    void setArmor(int newArmor);

    int getMR() const;
    void setMR(int newMR);

    std::shared_ptr<Item> getInventory(int index);
    void setNullptrItemInventory(std::shared_ptr<Item> item);
};

//Operatorenüberladung des Operators "<<"
std::ostream& operator<<(std::ostream& out, const Character& character);

#endif //EXERCISE_5_CHARACTER_H
