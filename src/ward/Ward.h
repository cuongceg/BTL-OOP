#ifndef WARD_H
#define WARD_H

#include <vector>
#include <string>

using std::vector;
using std::string;

struct Point
{
   double x,y;
};

class Ward{
private:
    string name;
    //ward can have 2 entrances and exit like ward A  
    vector<Point> entrance,exit;
    //4 corner coordinates
    vector<Point> wallCoordinates;

public:
    // Getter methods
    string getName() const { return name; }
    vector<Point> getEntrance() const { return entrance; }
    vector<Point> getExit() const { return this->exit; }
    vector<Point> getWallCoordinates() { return wallCoordinates; }

    // Setter methods
    void setName(std::string n) { name = n; }
    void setEntrance(vector<Point> entrance){this->entrance=entrance;}
    void setExit(vector<Point> exit) {this->exit=exit; }
    void setWallCoordinates(vector<Point> wall){ wallCoordinates=wall; }
};

vector<Ward> generateWard();
vector<Point> generateAroundWard();
#endif