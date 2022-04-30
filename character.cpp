#include "character.h"

//----------------------------- Objektfunktionen -----------------------------
bool Character::fight(Character *enemy)
{
    //Einleitungstext
    std::cout << enemy->getName() << " fordert " << this->getName() << " zu einem Kampf um Ruhm und Ehre heraus." << std::endl;

    //Lösung mithilfe einer Do-While-Loop
    do
    {
        this->attack(enemy);
        enemy->attack(this);
    } while(this->getHealth() > 0 && enemy->getHealth() > 0);

    //"Hero" gewinnt und schlägt "Enemy"
    if(this->getHealth() > 0)
    {
        std::cout << enemy->getName() << " fiel in Ohnmacht! " << this->getName() << " hat noch " << this->getHealth() << " Lebenspunkte." << std::endl;
        parent->removeCharacter(enemy->getName());
    }

    //Grafische Trennung der Inhalte
    std::cout << "------------------------------" << std::endl;

    //Falls Hero gewinnt, wird hier "true" zurückgegeben
    return this->getHealth() > 0;
}


void Character::addInventarItem(std::shared_ptr<Item> item)
{
    inventory.push_back(item);
}

std::shared_ptr<Item> Character::removeInventarItem(int slot)
{
    if(this->inventory[slot])
    {
        //Verweis eines shared Pointers "retValue" auf das Item an Position "slot",
        //welcher gleichzeitig als Rückgabewert dient
        //std::shared_ptr<Item> retValue = this->inventory[slot];
        auto retValue = this->inventory[slot];
        inventory.erase(inventory.begin()+slot);
        return retValue;
    } else
    {
        //Passende Exception, wenn der angegebene Indexwert auf "nullptr" zeigt
        throw InvalidItemException("Character::removeInventarItem(): Unter dem angegebenen Index ist kein gültiges Item gespeichert.");
    }
}

std::shared_ptr<Item> Character::retrieveRandomLoot(Character *enemy)
{
    //Initialisierung eines Counters, welcher als Zahlenbasis für die Zufallszahlgenerierung dient
    int counter = -1;

    //Für jedes korrekt initialisierte Item im Inventar des "enemy" wird "counter" um 1 erhöht
    for(int k = 0; k < enemy->inventory.size(); k++)
    {
        if(enemy->inventory[k])
        {
            counter++;
        }
    }

    /*
    //Für jedes korrekt initialisierte Item wird "counter" um 1 erhöht
    //Max. Wert = 9, da MAX_INVENTORY_SIZE als Array[10] also mit Index von 0 bis 9 definiert ist
    for(int i = 0; i < MAX_INVENTORY_SIZE; i++)
    {
        if(enemy->inventory[i])
        {
            counter++;
        }
    }
    */

    //Zufällige Zahl wird generiert und dient als Kriterium für die Auswahl des entsprechenden Item-Index
    int rndNumber = rand() % (counter);
    //std::cout << "Zufallszahl = " << rndNumber << std::endl;

    if(enemy->inventory[rndNumber])
    {
        //falls der Index korrekt initialisiert ist, soll das Item aus dem Inventar des Gegners entfernt ("removeInventarItem")
        //und dem Inventar des Helden/ der Heldin beigefügt werden ("addInventarItem")

        //Deklaration einer Variablen für das Item an Index "rndNumber"
        std::shared_ptr<Item> lootItem = enemy->inventory[rndNumber];

        //Item wird aus dem Inventar des Gegners entfernt
        enemy->removeInventarItem(rndNumber);

        //Das entsprechende Item wird dem Inventar des Helden/ der Heldin beigefügt
        this->addInventarItem(lootItem);

        std::cout << "Des einen Glück, des anderen Leid. " << this->getName() << " hat sich \"" << lootItem->getName() << "\" redlich verdient." << std::endl;

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;

        return lootItem;
    } else
    {
        //Exception, falls alle Plätze belegt sind
        std::cout << "Kein Platz vorhanden. Gegenstand \"" << enemy->getInventory(rndNumber)->getName() << "\" bleibt " << this->getName() << " leider verwehrt." << std::endl;

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;

        throw InventarFullException("Character::retrieveRandomLoot(): Inventar ist bereits komplett belegt.");
    }
}

int Character::countItems()
{
    int counter = this->inventory.size();
    return counter;
}

//----------------------------- Getter & Setter -----------------------------
const std::string& Character::getName() const
{
    return this->char_name;
}

void Character::setName(const std::string& newName)
{
    //Prüfung, ob die Eingabe überhaupt einen Wert enthält
    //Funktion wird nur ausgeführt, wenn "newName.empty()" == false aka "!newName.empty()"
    if(!newName.empty())
    {
        this->char_name = newName;
    }
}

int Character::getHealth() const
{
    return this->char_health;
}

void Character::setHealth(int newHealth)
{
    //Prüfung, ob die Eingabe einen korrekten Wert enthält, d. h. einen Wert größer 0
    //andernfalls wird "Health" mit 0 initialisiert
    if(newHealth > 0)
    {
        this->char_health = newHealth;
    } else
    {
        this->char_health = 0;
    }
}

int Character::getGold() const
{
    return this->char_gold;
}

void Character::setGold(int newGold)
{
    //Prüfung, ob die Eingabe einen korrekten Wert enthält, d. h. einen Wert größer oder gleich 0
    if(newGold >= 0)
    {
        this->char_gold = newGold;
    }
}

int Character::getArmor() const
{
    return this->char_armor;
}

void Character::setArmor(int newArmor)
{
    //Prüfung, ob die Eingabe einen korrekten Wert enthält, d. h. einen Wert größer oder gleich 0
    if(newArmor >= 0)
    {
        this->char_armor = newArmor;
    }
}

int Character::getMR() const
{
    return this->char_mr;
}

void Character::setMR(int newMR)
{
    if(newMR >= 0)
    {
        //Prüfung, ob die Eingabe einen korrekten Wert enthält, d. h. einen Wert größer oder gleich 0
        this->char_mr = newMR;
    }
}

std::shared_ptr<Item> Character::getInventory(int index)
{
    //std::shared_ptr<Item> item = this->inventory[index];
    auto item = this->inventory[index];
    return item;
}

void Character::setNullptrItemInventory(std::shared_ptr<Item> item)
{
    if(!item)
    {
        throw InvalidItemException("Character::setNullptrItem: Fehlerhaft initiertes Item.");
    } else
    {
        item = nullptr;
    }
}

//Operatorenüberladung des Operators "<<"
std::ostream& operator<<(std::ostream& out, const Character& character)
{
    out << "Hero " << character.getName() << " (mit " << character.getHealth() << " Lebenspunkten und " << character.getGold() << " Gold)";
    return out;
}
