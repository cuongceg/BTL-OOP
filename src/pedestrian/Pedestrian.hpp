#ifndef PEDRESTRIAN_H
#define PEDRESTRIAN_H
#include <vector>
#include <string>

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
    //topLeftCorner and bottomRightCorner
    vector<pair<Point,Point>> wallCoordinates;

public:
    // Getter methods
    string getName() const { return name; }
    Point getEntrance() const { return entrance; }
    Point getExit() const { return exit; }
    vector<pair<Point,Point>> getWallCoordinates() { return wallCoordinates; }

    // Setter methods
    void setName(std::string n) { name = n; }
    void setEntrance(double x,double y) {entrance.x=x;entrance.y=y;}
    void setExit(double x,double y) { exit.x=x;exit.y=y; }
    void setWallCoordinates(vector<pair<Point,Point>>& wall){ wallCoordinates=wall; }
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
    double time,intensity;
  public:  
    //contructor
    Event(double time,double intensity): time(time),intensity(intensity){}

    //getter methods
    double getTime(){ return time; }
    double getIntensity(){ return intensity; }

    //setter methods
    void setTime(double time){this->time=time;}
    void setIntensity(double intensity){this->intensity=intensity;}
};

class AGVEvent:Event{};

class Personality {
private:
    double lambda;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;

public:
    // Constructors
    Personality(double l, double p, double n)
        : lambda(l), positiveEmotionThreshold(p), negativeEmotionThreshold(n) {}

    // Getter methods
    double getLambda() const { return lambda; }
    double getPositiveEmotionThreshold() const { return positiveEmotionThreshold; }
    double getNegativeEmotionThreshold() const { return negativeEmotionThreshold; } 
};

class Pedestrian{
protected:
    int ID;
    //Ward start;
    //Ward end;
    //vector<Ward> journey;
    double velocity;
    //Personality personality;
    Emotion emotion=Emotion();
    //vector<Event> events;
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
    //void setPersonality(Personality personality){this->personality=personality;}
    // Getter methods
    int getID() const { return ID; }
    // //Ward getStart() const { return start; }
    // //Ward getEnd() const { return end; }
    // //std::vector<Ward> getJourney() const { return journey; }
    double getVelocity() const { return velocity; }
    // Personality getPersonality() const { return personality; }
    Emotion getEmotion() const { return emotion; }
    // std::vector<Event> getEvents() const { return events; }
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
void generatePedestrian();
#endif