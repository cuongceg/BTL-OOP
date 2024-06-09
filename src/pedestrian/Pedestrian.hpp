#ifndef PEDRESTRIAN_H
#define PEDRESTRIAN_H

#include <vector>
#include <string>
#include <iostream>

#include "../ward/Ward.h"
#include "../event/Event.h"

using std::vector;
using std::pair;
using std::string;

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
    string ID;
    Ward start;
    Ward end;
    vector<Ward> journey;
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
    void setID(string id){this->ID=id;}
    void setStartWard(Ward start){this->start=start;}
    void setEndWard(Ward end){this->end=end;}
    //void setDistance(double distance){this->distance=distance;}
    void setAge(double age){this->age=age;}
    //void setWalkingTime(double time){walkingTime=time;}
    void setVelocity(double velocity){this->velocity=velocity;}
    void setPersonality(Personality personality){this->personality=personality;}
    void setEvents(vector<Event>events){this->events=events;}
    void setJourney(vector<Ward> journey){this->journey=journey;}
    // Getter methods
    string getID() const { return ID; }
    Ward getStart() const { return start; }
    Ward getEnd() const { return end; }
    vector<Ward> getJourney() const { return journey; }
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
vector<Pedestrian> generatePedestrian(int writeToFile);
vector<vector<double>> eventsImpact(Pedestrian p,int timeHorizon);
void leavingDistribution(string name);
#endif