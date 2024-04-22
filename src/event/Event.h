#ifndef EVENT_H
#define EVENT_H

#include <vector>
using std::vector;

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

vector<Event> generateEvents();
#endif
