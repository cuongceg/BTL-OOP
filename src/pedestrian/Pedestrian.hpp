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
    Emotion() : pleasure(0.75), surprise(0.5), anger(-0.2), fear(-0.2), hate(-0.4), sad(-0.4) {}
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

class AGVEvent:public Event{};

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
    Ward start;
    Ward end;
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
    void setStartWard(Ward start){this->start=start;}
    void setEndWard(Ward end){this->end=end;}
    //void setDistance(double distance){this->distance=distance;}
    void setAge(double age){this->age=age;}
    //void setWalkingTime(double time){walkingTime=time;}
    void setVelocity(double velocity){this->velocity=velocity;}
    void setPersonality(Personality personality){this->personality=personality;}
    void setEvents(vector<Event>events){this->events=events;}
    // Getter methods
    int getID() const { return ID; }
    Ward getStart() const { return start; }
    Ward getEnd() const { return end; }
    // //std::vector<Ward> getJourney() const { return journey; }
    double getVelocity() const { return velocity; }
    Personality getPersonality() const { return personality; }
    Emotion getEmotion() const { return emotion; }
    vector<vector<double>> getEventsIntensity(){
        vector<vector<double>> allEvents(6,vector<double>(20));
        for(int i=0;i<6;i++){
            for(int j=0;j<20;j++){
                allEvents[i][j]=events.at(j).getIntensity().at(i);
            }
        }
        return allEvents;
    }
    vector<int> getEventsTime(){
        vector<int> time;
        for(int i=0;i<19;i++){
            time.push_back(events.at(i).getTime());
        }
        return time;
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
vector<Ward> generateWard();
//Pedestrian generatePedestrian(); test eventsImpact
vector<Pedestrian> generatePedestrian();
vector<vector<double>> eventsImpact(Pedestrian p,int timeHorizon);
void leavingDistribution(string name);
#endif