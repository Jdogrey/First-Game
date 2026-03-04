#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "loader.h"
#include "Objects/room.h"
#include "Objects/item.h"
#include "json11/json11.hpp"

using namespace std;
using json = json11::Json;

vector<shared_ptr<Item>> LoadItems(const string& filename) {
    vector<shared_ptr<Item>> items;
    json jsonItems = read_json_file(filename);

    for (const auto& jsonItem : jsonItems.array_items()) {
        int id = jsonItem["id"].int_value();
        string name = jsonItem["name"].string_value();
        int value = jsonItem["value"].int_value();
        int level = jsonItem["level"].int_value();
        string type = jsonItem["type"].string_value();

        if (type == "Weapon") {
            int atk = jsonItem["atk"].int_value();
            items.push_back(make_shared<Weapon>(id, name, value, NORMAL, level, atk));
        } 
        else if (type == "Armor") {
            int def = jsonItem["def"].int_value();
            items.push_back(make_shared<Armor>(id, name, value, NORMAL, level, def));
        } 
        else if (type == "OffHandItem") {
            int block = jsonItem["block"].int_value();
            int special = jsonItem["special"].int_value();
            items.push_back(make_shared<OffHandItem>(id, name, value, NORMAL, level, block, special));
        } 
        else if (type == "HealingItem") {
            int healAmount = jsonItem["healAmount"].int_value();
            int maxHeld = jsonItem["maxHeld"].int_value();
            items.push_back(make_shared<HealingItem>(id, name, value, NORMAL, level, healAmount, maxHeld));
        } 
        else if (type == "BuffItem") {
            int buffAmount = jsonItem["buffAmount"].int_value();
            int duration = jsonItem["duration"].int_value();
            string buffType = jsonItem["buffType"].string_value();
            int maxHeld = jsonItem["maxHeld"].int_value();
            items.push_back(make_shared<BuffItem>(id, name, value, NORMAL, level, buffAmount, duration, buffType, maxHeld));
        }
        else if (type == "Scroll") {
            string spellName = jsonItem["spellName"].string_value();
            items.push_back(make_shared<Scroll>(id, name, value, NORMAL, level, spellName));
        }
        else if (type == "levelUpItem") {
            int maxHeld = jsonItem["maxHeld"].int_value();
            items.push_back(make_shared<LevelUpItem>(id, name, value, NORMAL, level, maxHeld));
        }
        else if (type == "playerLevelItem") {
            int maxHeld = jsonItem["maxHeld"].int_value();
            items.push_back(make_shared<PlayerLevelItem>(id, name, value, NORMAL, level, maxHeld));
        }
        else {
            cerr << "Unknown item type: " << type << endl;
        }
    }

}

json read_json_file(const string &file_path) {

    ifstream t(file_path);
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

    string err;
    const auto json = json::parse(str, err);
    return json;
}