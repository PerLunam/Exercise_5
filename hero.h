#ifndef EXERCISE_5_HERO_H
#define EXERCISE_5_HERO_H

#include <string>

#include "character.h"

#define MAX_EQUIPMENT_SIZE 2

//Forward-Declaration der Class "NPC"
class NPC;

class Hero : public Character
{
private:
    std::shared_ptr<Item> hero_gear[MAX_EQUIPMENT_SIZE];
    enumType typ;

protected:

public:
    //Konstruktor der Class "Hero"

    //Individueller Konstruktor
    Hero(Game* parent, const std::string &char_name, int char_health, int char_gold, int char_armor, int char_mr)
            : Character(parent, char_name, char_health, char_gold, char_armor, char_mr), hero_gear(), typ(typeHero)
    {
        std::cout << "Hero::Constructor: " << char_name << std::endl;
    }

    //Destruktor
    virtual ~Hero()
    {
        //Grafische Trennung der Inhalte
        //std::cout << "------------------------------" << std::endl;

        //TODO - Erklärung zur Funktionsweise ergänzen
        std::cout << *this << " verabschiedet sich und geht voller Stolz der untergehenden Sonne entgegen." << std::endl;
    }

    //----------------------------- Objektfunktionen -----------------------------
    virtual void attack(Character *enemy) override;

    int addEquipmentItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeEquipmentItem(int slot);

    void setNullptrItemEquipment(std::shared_ptr<Item> item);

    void sellItem(int index);

    virtual enumType& getType() override;

    //----------------------------- Getter & Setter -----------------------------
    //Werden von der Elternklasse "Character" übernommen
    std::shared_ptr<Item> getEquipment(int index);
};

#endif //EXERCISE_5_HERO_H
