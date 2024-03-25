#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;

class Pedestrian{
    private:
    int ID;
    Ward start;
    Ward end;
    vector<Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    vector<Event> events;
    double walkingTime;
    double distance;
    double age;
    AGVEvent impactOfAGV;
    Point tempPoints;

public:
    // Constructors
    Pedestrian(int id, Ward& start,Ward& end,vector<Ward>& j,
               double v,Personality& p,Emotion& e, vector<Event>& ev,
               double w, double d, double a,AGVEvent& i,Point& tp)
        : ID(id), start(start), end(end), journey(j), velocity(v), personality(p), emotion(e), events(ev),
          walkingTime(w), distance(d), age(a), impactOfAGV(i), tempPoints(tp) {}

    // Getter methods
    int getID() const { return ID; }
    Ward getStart() const { return start; }
    Ward getEnd() const { return end; }
    std::vector<Ward> getJourney() const { return journey; }
    double getVelocity() const { return velocity; }
    Personality getPersonality() const { return personality; }
    Emotion getEmotion() const { return emotion; }
    std::vector<Event> getEvents() const { return events; }
    double getWalkingTime() const { return walkingTime; }
    double getDistance() const { return distance; }
    double getAge() const { return age; }
    AGVEvent getImpactOfAGV() const { return impactOfAGV; }
    Point getTempPoints() const { return tempPoints; }
};

class Patient:Pedestrian{
    Walkability walkability;
};

class Visitor:Pedestrian{
    Walkability walkability;
};

class Personel{};

class Ward{
private:
    string name;  
    Point entrance,exit;
    //topLeftCorner and bottomRightCorner
    vector<pair<Point,Point>> wallCoordinates;

public:
    // Constructors
    Ward(string n, Point en, Point ex, vector<pair<Point,Point>>& wall) 
        : name(n), entrance(en), exit(ex),wallCoordinates(wall){}

    // Getter methods
    string getName() const { return name; }
    Point getEntrance() const { return entrance; }
    Point getExit() const { return exit; }
    vector<pair<Point,Point>> getWallCoordinates() const { return wallCoordinates; }

    // Setter methods
    void setName(std::string n) { name = n; }
    void setEntrance(Point en) { entrance = en; }
    void setExit(Point ex) { exit = ex; }
    void setWallCoordinates(vector<pair<Point,Point>>& wall){ wallCoordinates=wall; }
};

enum class Walkability {
    noDisability,
    crutches,
    sticks,
    wheelchairs,
    blind
};

struct Point
{
    double x,y;
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
    double setTime(double time){this->time=time;}
    double setIntensity(double intensity){this->intensity=intensity;}
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