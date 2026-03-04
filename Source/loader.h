#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Objects/room.h"
#include "Objects/item.h"
#include "json11/json11.hpp"

using namespace std;
using json = json11::Json;

vector<shared_ptr<Item>> LoadItems(const string& filename);
json read_json_file(const string &file_path);

#endif // LOADER_H