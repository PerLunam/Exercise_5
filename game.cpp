#include "game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cerrno>

#include "character.h"
#include "hero.h"
#include "npc.h"
#include "fighter.h"
#include "sorcerer.h"

void Game::play() {

    std::srand(time(nullptr));

    try
    {
        //Hero testing("Test", -100, 0, 15, 10);

        //Initialize Hero "Annina" und deren Items sowie Ausrüstung
        std::shared_ptr<Hero> annina(new Hero("Annina", 700, 200, 15, 10));
        addCharacter(annina);
        annina->addInventarItem(std::shared_ptr<Item>(new Item("Riesenschwert", 70)));
        annina->addInventarItem(std::shared_ptr<Item>(new Item("Diamantamulett", 90)));
        annina->addEquipmentItem(new Item("Rosenlanze", 300));
        annina->addEquipmentItem(new Item("Trank der Stärke", 25));

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;

        //Initialize Fighter "Matthias" und dessen Items
        std::shared_ptr<Fighter> matthias(new Fighter("Matthias", 50, 100, 10, 5, 25));
        addCharacter(matthias);
        matthias->addInventarItem(std::shared_ptr<Item>(new Item("Bernstein-Umhang", 250)));
        matthias->addInventarItem(std::shared_ptr<Item>(new Item("Silberaxt", 170)));
        matthias->addInventarItem(std::shared_ptr<Item>(new Item("Ahornstab", 150)));

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;

        //Initialize Sorcerer "Pascal" und dessen Items
        std::shared_ptr<Sorcerer> pascal(new Sorcerer("Pascal", 100, 300, 5, 10, 25));
        addCharacter(pascal);
        pascal->addInventarItem(std::shared_ptr<Item>(new Item("Zaubertrunk", 50)));
        pascal->addInventarItem(std::shared_ptr<Item>(new Item("Nachtschattenrüstung", 350)));
        pascal->addInventarItem(std::shared_ptr<Item>(new Item("Drachendolch", 100)));

        //Nach der Initialisierung der Charaktere sollen diesen im Terminal ausgegeben werden
        printCharacter();

        //Grafische Trennung der Inhalte
        std::cout << "------------------------------" << std::endl;

        //Ansatz mit einer nested if-Loop
        if(annina->fight(matthias.get()))
        {
            annina->retrieveRandomLoot(matthias.get());

            if(annina->fight(pascal.get()))
            {
                annina->retrieveRandomLoot(pascal.get());

                for(int k = 0; k < MAX_INVENTORY_SIZE; ++k)
                {
                    annina->sellItem(k);
                }

            }

            //TBD
            printCharacter();

        } else
        {
            //Falls die Heldin verliert...
            std::cout << annina->getName() << " fiel in Ohnmacht!" << std::endl;
        }
    } catch (std::exception &error) //alternativ: catch(...)
    {
        std::cerr << "Caught exception in main: " << error.what() << std::endl;
    }
}

void Game::addCharacter(std::shared_ptr<Character> character) {
    if(characters.find(character->getName()) == characters.end())
    {
        characters.insert({character->getName(), character});
    } else
    {
        throw NonUniqueNameException(std::string("Name ") + character->getName() +std::string(" ist bereits vorhanden."));
    }
}

void Game::removeCharacter(const std::string &char_name) {
    if(characters.find(char_name) != characters.end())
    {
        characters.erase(char_name);
    } else
    {
        throw NonExistingNameException(std::string("Name ") + char_name +std::string(" ist nicht vorhanden."));
    }
}

void Game::printCharacter() {

    //Grafische Trennung der Inhalte
    std::cout << "------------------------------" << std::endl;

    for(const auto &character: characters)
    {
        std::cout << "Key: " << character.first << " = " << "Lebenspunkte: " << character.second->getHealth() << " ; Gold: " << character.second->getGold()
        << " ; Rüstung: " << character.second->getArmor() << " ; Magieresistenz: " << character.second->getMR() <<  std::endl;
    }
}