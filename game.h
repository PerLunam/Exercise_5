#ifndef EXERCISE_5_GAME_H
#define EXERCISE_5_GAME_H

#include <map>
#include <vector>
#include <memory>
#include <string>

//Forward-Declaration der Class "Character"
class Character;
class Item;

class Game {

private:

protected:
    std::map<std::string, std::shared_ptr<Character> > characters;
    std::vector<std::shared_ptr<Item>> nonAssignedItem;

public:
    void play();

    void addCharacter(std::shared_ptr<Character> character);

    /*
    //Verwendung eines Templates zur Initialisierung der Charaktere
    template<typename test_template, typename ...ARGS>
    std::shared_ptr<test_template> createCharacter(ARGS... args)
    {
        std::shared_ptr<test_template> retValue(new test_template(this, args...));
        characters.insert({retValue->getName(), retValue});
        return retValue;
    }
    */

    void removeCharacter(const std::string& char_name);

    void printCharacter();

    void addItem(std::shared_ptr<Item> item);
};


#endif //EXERCISE_5_GAME_H
