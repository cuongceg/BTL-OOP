#include "Ward.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

vector<Ward> generateWard() {
    vector<Ward> wards;
    ifstream file("data/hospital.txt");
    string line;
    if (file.is_open()) {
        getline(file, line);
        for (int i = 2;i < 11;i++) {
            vector<Point>wall,entrance,exit;
            Point midPoint1, midPoint2, point1, point2, point3, point4;
            Ward ward;
            double length;
            string name;
            if (!getline(file, line)) {
                cout<<"Cann't read file";
                break;
            }
            istringstream iss(line);
            iss >> midPoint1.x >> midPoint1.y;
            iss >> midPoint2.x >> midPoint2.y;
            iss >> length;
            iss >> name;
            point1.x = midPoint1.x - length / 2;
            point2.x = midPoint1.x + length / 2;
            point1.y = midPoint1.y;
            point2.y = midPoint1.y;
            point3.x = midPoint2.x + length / 2;
            point4.x = midPoint2.x - length / 2;
            point3.y = midPoint2.y;
            point4.y = midPoint2.y;
            entrance.push_back(midPoint1);
            exit.push_back(midPoint2);
            wall.push_back(point1);
            wall.push_back(point2);
            wall.push_back(point3);
            wall.push_back(point4);
            ward.setEntrance(entrance);
            ward.setExit(exit);
            ward.setName(name);
            ward.setWallCoordinates(wall);
            wards.push_back(ward);
        }
        vector<Point>wall,entrance,exit;
        Ward ward;
        Point entrance1,entrance2,exit1,exit2, point1, point2, point3, point4;
        if (!getline(file, line)) {
            file.close();
            cout<<"Can't read ward A position";
            return wards;
        }
        istringstream iss(line);
        iss>> entrance1.x >> entrance1.y >> entrance2.x >> entrance2.y;
        iss>> exit1.x >> exit1.y >> exit2.x >> exit2.y;
        entrance.push_back(entrance1);
        entrance.push_back(entrance2);
        exit.push_back(exit1);
        exit.push_back(exit2);
        point1.x=point4.x=exit1.x;
        point1.y=point2.y=entrance1.y;
        point2.x=point3.x=exit2.x;
        point3.y=point4.y=entrance2.y;
        wall.push_back(point1);
        wall.push_back(point2);
        wall.push_back(point3);
        wall.push_back(point4);
        ward.setEntrance(entrance);
        ward.setExit(exit);
        ward.setName("A");
        ward.setWallCoordinates(wall);
        wards.push_back(ward);
        file.close();
    }
    else {
        cout << "Cann't open" << endl;
    }
    return wards;
}

vector<Point> generateAroundWard(){
    vector<Point> aroundWard;
    ifstream file("data/hospital.txt");
    string line;
    if(file.is_open()){
        for(int i=1;i<15;i++){
        getline(file, line);}
        istringstream iss(line);
        double x,y;
        for(int i=0;i<4;i++){
            iss>>x>>y;
            Point point;
            point.x=x;
            point.y=y;
            aroundWard.push_back(point);
        }
        file.close();
    }
    else{
        cout<<"Can't open file";
    }
    return aroundWard;
}