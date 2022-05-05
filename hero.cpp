#include "hero.h"

void Hero::attack(Character *enemy)
{
    //Berechnung einer zufälligen Zahl zwischen 15 und 25
    int rndNumber = 15 + std::rand() % (25 - 15 + 1);

    //Berechnung des Schadens
    //Bei Hero ist die Vorgabe "damage = rand(15,25) - armor"
    //Wert von "armor" bezieht sich auf den Gegner
    int damage = rndNumber - enemy->getArmor();
    enemy->setHealth(enemy->getHealth() - damage);

    std::cout << this->getName() << " trifft " << enemy->getName() << " für " << damage << " Lebenspunkte." << std::endl;
}

int Hero::addEquipmentItem(std::shared_ptr<Item> item)
{
    for(int i = 0; i < MAX_EQUIPMENT_SIZE; ++i)
    {
        //Prüfung, ob Index auf "nullptr" zeigt oder auf eine gültige Speicheradresse
        //bei "false" zeigt der Index auf "nullptr" und wird nun korrekt initialisiert
        if(!this->hero_gear[i])
        {
            this->hero_gear[i] = item;
            //this->inventory[i]->setName(item->getName());
            //this->inventory[i]->setValue(item->getValue());

            //Bei erfolgreicher Platzierung soll der Index des Items ausgegeben werden
            return i;
        }
    }
    //Exception, falls alle Plätze belegt sind
    throw InventarFullException("Character::addInventarItem(): Inventar ist bereits komplett belegt.");
}

std::shared_ptr<Item> Hero::removeEquipmentItem(int slot)
{
    if (slot < 0 || slot > MAX_EQUIPMENT_SIZE)
    //if (slot >= 0 && slot < MAX_EQUIPMENT_SIZE)
    {
        //Passende Exception, wenn der eingegebene Indexwert außerhalb des Wertebereichs liegt
        throw InvalidIndexException("Hero::removeEquipmentItem(): Der angegebene Indexwert liegt außerhalb des gültigen Wertebereichs.");
    } else if(this->hero_gear[slot])
    {
        //Überschreiben des Slots mit "nullptr" mithilfe einer zusätzlichen Variablen "retValue"
        auto retValue = this->hero_gear[slot];
        //std::shared_ptr<Item> retValue = this->hero_gear[slot];
        hero_gear[slot].reset();

        //std::cout << "Das Item " << this->hero_gear[slot]->getName() << " wurde aus dem Equipment von " << this->getName() << " entfernt." << std::endl;

        return retValue;
    } else
    {
        //Passende Exception, wenn der angegebene Indexwert auf "nullptr" zeigt
        throw InvalidItemException("Hero::removeEquipmentItem(): Unter dem angegebenen Index ist kein gültiges Item gespeichert.");
    }
}

void Hero::setNullptrItemEquipment(std::shared_ptr<Item> item)
{
    if(!item)
    {
        throw InvalidItemException("Character::setNullptrItem: Fehlerhaft initiertes Item.");
    } else
    {
        item = nullptr;
    }
}

void Hero::sellItem(int index)
{
    //Verkauf der Items aus "inventory" und "hero_gear"

    //Erster Schritt - Prüfung, ob Wert von "index" innerhalb der Array-Größe von "hero_gear" liegt
    if (index >= 0 && index < MAX_EQUIPMENT_SIZE)
    {
        if (this->hero_gear[index])
        {
            this->setGold(this->getGold() + this->getEquipment(index)->getValue());
            //this->setGold(this->getEquipment(index)->getValue());

            this->setNullptrItemEquipment(this->getEquipment(index));

            //Ausgabe einer Bestätigung über das Terminal
            std::cout << "Der Gegenstand " << this->getEquipment(index)->getName() << " wurde für "
                      << this->getEquipment(index)->getValue() << " Gold verkauft. "
                      << this->getName() << " besitzt nun " << this->getGold() << " Gold." << std::endl;
        } else
        {
            //Passende Exception, wenn der angegebene Indexwert auf "nullptr" zeigt
            throw InvalidItemException(
                    "Hero::sellItem(): line141_Unter dem angegebenen Index ist kein gültiges Item in \"hero_gear\" gespeichert.");
        }
    } else
    {
        //Passende Exception, wenn der eingegebene Indexwert außerhalb des Wertebereichs liegt
        throw InvalidIndexException(
                "Hero::sellItem(): Der angegebene Indexwert liegt außerhalb des gültigen Wertebereichs.");
    }

    //Zweiter Schritt - Prüfen, ob am Platz von "index" ein gültiges Item (bzw. "nicht-Nullptr") vorhanden ist
    if (this->getInventory(index))
    {
        this->setGold(this->getGold() + this->getInventory(index)->getValue());
        //char_gold += this->getInventory(index)->getValue();

        parent->addItem(this->getInventory(index));

        this->removeInventarItem(index);

        //Ausgabe einer Bestätigung über das Terminal
        std::cout << "Der Gegenstand " << this->getInventory(index)->getName() << " wurde für "
                  << this->getInventory(index)->getValue() << " Gold verkauft. "
                  << this->getName() << " besitzt nun " << this->getGold() << " Gold." << std::endl;
    } else
    {
        //Passende Exception, wenn der angegebene Indexwert auf "nullptr" zeigt
        throw InvalidItemException(
                "Hero::sellItem(): line158_Unter dem angegebenen Index ist kein gültiges Item in \"inventory\" gespeichert.");
    }
}

std::shared_ptr<Item> Hero::getEquipment(int index)
{
    if(index >= 0 && index < MAX_EQUIPMENT_SIZE)
    {
        std::shared_ptr<Item> equipment = this->hero_gear[index];
        return equipment;
    } else
    {
        //Passende Exception, wenn der eingegebene Indexwert außerhalb des Wertebereichs liegt
        throw InvalidIndexException("Hero::getEquipment(): Der angegebene Indexwert liegt außerhalb des gültigen Wertebereichs.");
    }
}

enumType& Hero::getType()
{
    return this->typ;
}