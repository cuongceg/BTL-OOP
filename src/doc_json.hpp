#ifndef DOC_JSON
#define DOC_JSON
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
string name_file = "input.json";

int get_numOfAgents()
{
    //Mở file json
    ifstream file(name_file);
    if(!file.is_open())
    {
        cerr << "Failed to open JSON file." << std::endl;
        return -1;
    }
    //đọc dữ liệu
    json jsondata;
    file >> jsondata;
    file.close();


    int numOfAgents = jsondata["numOfAgents"]["value"];
    cout << "numOfAgents: " << numOfAgents << endl; 
    return numOfAgents;
}

#endif