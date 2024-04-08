#ifndef PEDRESTRIAN_H
#define PEDRESTRIAN_H
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::pair;
using std::string;

struct Point
{
   double x,y;
};

class Ward{
private:
    string name;  
    Point entrance,exit;
    //4 corner coordinates
    vector<Point> wallCoordinates;

public:
    //constructor
    Ward(Point entr,Point exit,string name,vector<Point>wall){
        entrance=entr;
        this->exit=exit;
        this->name=name;
        wallCoordinates=wall;
    }
    // Getter methods
    string getName() const { return name; }
    Point getEntrance() const { return entrance; }
    Point getExit() const { return exit; }
    vector<Point> getWallCoordinates() { return wallCoordinates; }

    // Setter methods
    // void setName(std::string n) { name = n; }
    // void setEntrance(double x,double y) {entrance.x=x;entrance.y=y;}
    // void setExit(double x,double y) { exit.x=x;exit.y=y; }
    // void setWallCoordinates(vector<Point> wall){ wallCoordinates=wall; }
};

enum class Walkability {
    noDisability,
    crutches,
    sticks,
    wheelchairs,
    blind
};

class Emotion{
private:
    double pleasure;
    double surprise;
    double anger;
    double fear;
    double hate;
    double sad;

public:
    Emotion() : pleasure(0.0), surprise(0.0), anger(-0.2), fear(-0.2), hate(-0.4), sad(-0.4) {}
    // Getter methods
    double getPleasure() const { return pleasure; }
    double getSurprise() const { return surprise; }
    double getAnger() const { return anger; }
    double getFear() const { return fear; }
    double getHate() const { return hate; }
    double getSad() const { return sad; }  
};

class Event{
  private:    
    double time;
    vector<double>intensity;
  public:  
    //getter methods
    double getTime(){ return time; }
    vector<double> getIntensity(){ return intensity; }

    //setter methods
    void setTime(double time){this->time=time;}
    void setIntensity(vector<double> intensity){this->intensity=intensity;}
};

class AGVEvent:Event{};

class Personality {
private:
    double lambda;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;

public:
    // Setter methods
    void setLambda(double lambda){this->lambda=lambda;}
    void setPositiveEmotionThreshold(double pos){positiveEmotionThreshold=pos;}
    void setNegativeEmotionThreshold(double neg){negativeEmotionThreshold=neg;}
    // Getter methods
    double getLambda(){ return lambda; }
    double getPositiveEmotionThreshold(){ return positiveEmotionThreshold; }
    double getNegativeEmotionThreshold(){ return negativeEmotionThreshold; } 
};

class Pedestrian{
protected:
    int ID;
    //Ward start;
    //Ward end;
    //vector<Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion=Emotion();
    vector<Event> events;
    //double walkingTime;
    //double distance;
    double age;
    //AGVEvent impactOfAGV;
    //Point tempPoints;

public:
    // Setter methods
    void setID(int id){this->ID=id;}
    //void setStartWard(Ward start){this->start=start;}
    //void setEndWard(Ward end){this->end=end;}
    //void setDistance(double distance){this->distance=distance;}
    void setAge(double age){this->age=age;}
    //void setWalkingTime(double time){walkingTime=time;}
    void setVelocity(double velocity){this->velocity=velocity;}
    void setPersonality(Personality personality){this->personality=personality;}
    void setEvents(vector<Event>events){this->events=events;}
    // Getter methods
    int getID() const { return ID; }
    // //Ward getStart() const { return start; }
    // //Ward getEnd() const { return end; }
    // //std::vector<Ward> getJourney() const { return journey; }
    double getVelocity() const { return velocity; }
    Personality getPersonality() const { return personality; }
    Emotion getEmotion() const { return emotion; }
    vector<Event> getEvent(){return events;}
    vector<vector<double>> getEvents(vector<Event> events){
        vector<vector<double>> allEvents(6,vector<double>(20));
        for(int i=0;i<6;i++){
            for(int j=0;j<20;j++){
                allEvents[i][j]=events.at(j).getIntensity().at(i);
            }
        }
        return allEvents;
    }
    // double getWalkingTime() const { return walkingTime; }
    // double getDistance() const { return distance; }
    double getAge() const { return age; }
    // AGVEvent getImpactOfAGV() const { return impactOfAGV; }
    // Point getTempPoints() const { return tempPoints; }
};

class Patient: public Pedestrian{
    Walkability walkability;
};

class Visitor: public Pedestrian{
    Walkability walkability;
};

class Personel: public Pedestrian{};
vector<Event> generateEvents();
vector<Ward> generateWard();
void generatePedestrian();
#endif