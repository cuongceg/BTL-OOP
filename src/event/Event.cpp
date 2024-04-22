#include "Event.h"
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

vector<Event> generateEvents(){
    vector<Event>events;
    ifstream file("data/event_distrubution.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            Event event;
            istringstream iss(line);
            double value;
            vector<double> intensity;

            while (iss >> value) {
                intensity.push_back(value);
            }
            cout << endl;
            event.setIntensity(intensity);
            event.setTime(0);
            events.push_back(event);
        }
        file.close();
    } else {
        cout << "Cann't open"<< endl;
    }
    return events;
}