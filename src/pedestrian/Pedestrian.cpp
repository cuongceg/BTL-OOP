#include "Pedestrian.hpp"
#include "../../lib/nlohmann/json.hpp" 
#include "../utility/Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>

using namespace std;
using json = nlohmann::json;

float randomFloat(float lowerBound, float upperBound)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}

int randomNumber(int lowerBound,int upperBound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lowerBound,upperBound);

    int random_number = dis(gen);
    return random_number;
}
//standard distribution
double normalDistribution(int x, double mean, double stdDev) {
    double exponent = -(pow(x - mean, 2) / (2 * pow(stdDev, 2)));
    return (1 / (sqrt(2 * M_PI) * stdDev)) * exp(exponent);
}

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
        entrance.push_back(entrance1);
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
        // for(Ward ward : wards){
        //     cout<<ward.getName()<<endl;
        // }
        file.close();
    }
    else {
        cout << "Cann't open" << endl;
    }
    return wards;
}

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
//bai 3
vector<Pedestrian> generatePedestrian() {
    //declare
    //47, 37, 37, 27, 25, 27 number of people
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    int ID = -1;
    float deviationParam = randomFloat(1 - (float)inputData1["experimentalDeviation"]["value"] / 100, 1 + (float)inputData1["experimentalDeviation"]["value"] / 100);
    //age distribution
    double ages[] = {
        40.8, 49.6, 42.8, 46.5, 40.6, 48.7, 48.9, 32.4, 40.1, 35.3, 45.1, 35.8, 42.3, 49.4, 33.6, 44.7,
        38.9, 37.8, 44.1, 44.2, 39.0, 27.9, 38.2, 46.0, 46.3, 54.9, 59.5, 44.7, 45.9, 41.1, 41.0, 32.7,
        31.3, 37.8, 33.2, 49.3, 33.6, 38.2, 36.7, 39.5, 42.4, 46.4, 45.8, 41.6, 31.5, 42.8, 35.5, 40.4,
        52.1, 45.2, 50.8, 40.9, 44.3, 55.8, 49.4, 45.8, 45.9, 36.1, 31.9, 49.1, 40.7, 44.5, 39.4, 42.7,
        36.5, 41.1, 39.0, 35.9, 39.7, 48.9, 43.4, 31.9, 44.9, 42.6, 38.8, 41.8, 31.9, 40.2, 25.9, 41.7,
        34.7, 39.5, 79.9, 89.7, 54.3, 93.4, 55.9, 50.0, 54.6, 69.9, 52.4, 55.8, 36.8, 46.9, 50.1, 60.9,
        70.1, 56.0, 53.6, 51.0, 37.1, 38.2, 58.5, 34.7, 38.4, 71.1, 62.1, 47.7, 64.8, 57.7, 63.2, 67.5,
        58.0, 60.4, 41.1, 40.1, 31.1, 85.7, 13.2, 54.6, 42.7, 57.1, 39.5, 57.3, 97.0, 63.0, 76.5, 41.2,
        66.5, 38.5, 64.7, 85.3, 27.1, 19.6, 87.7, 74.3, 40.7, 48.4, 58.5, 53.0, 64.9, 66.7, 68.0, 27.9,
        47.4, 79.6, 59.2, 58.5, 76.2, 65.2, 55.8, 49.9, 53.9, 59.8, 59.8, 41.6, 80.4, 55.8, 26.7, 45.2,
        74.3, 48.2, 69.1, 55.7, 69.3, 55.3, 77.4, 60.8, 85.2, 47.9, 63.7, 84.2, 56.1, 68.1, 32.3, 32.1,
        46.9, 56.7, 57.8, 80.2, 33.8, 75.2, 67.2, 74.0, 60.2, 62.6, 43.9, 61.3, 46.1, 72.0, 41.1, 37.2,
        69.1, 42.0, 55.8, 56.3, 58.8, 44.6, 62.9, 41.2
    };
    //number of types of Pedestrians
    int numPedestrians[] = { 80,53,67 };
    // 43 elements likes 43 events
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 43);
    vector<double> allTimeDistances(43);
    for(int i=0;i<42;i++){
        allTimeDistances[i]=dis(gen);
    }
    //personality
    Personality personalityOpen, personalityNeurotic;
    personalityOpen.setLambda(double(inputData1["personalityDistribution"]["distribution"]["open"]["lambda"]));
    personalityOpen.setPositiveEmotionThreshold(double(inputData1["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]));
    personalityOpen.setNegativeEmotionThreshold(double(inputData1["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]));
    personalityNeurotic.setLambda(double(inputData1["personalityDistribution"]["distribution"]["neurotic"]["lambda"]));
    personalityNeurotic.setPositiveEmotionThreshold(double(inputData1["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]));
    personalityNeurotic.setNegativeEmotionThreshold(double(inputData1["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]));
    //velocity
    double perNoDisabilityWithoutOvertaking =
        double(inputData1["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"]) * deviationParam;
    double perNoDisabilityWithOvertaking =
        double(inputData1["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"]) * deviationParam;
    double perWalkingWithCrutches =
        double(inputData1["walkability"]["distribution"]["crutches"]["velocity"]) * deviationParam;
    double perWalkingWithSticks =
        double(inputData1["walkability"]["distribution"]["sticks"]["velocity"]) * deviationParam;
    double perWheelchairs =
        double(inputData1["walkability"]["distribution"]["wheelchairs"]["velocity"]) * deviationParam;
    double perTheBlind =
        double(inputData1["walkability"]["distribution"]["blind"]["velocity"]) * deviationParam;
    //ward
    vector<Ward> wards= generateWard();   
    //generate
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < numPedestrians[i];j++) {
            //unique ID
            ID++;   
            switch (i) {
            case 0: {
                Personel personel;
                vector<Event>events;
                personel.setID(ID + 1);
                personel.setAge(ages[ID]);
                personel.setStartWard(wards[ID%9]);
                personel.setEndWard(wards[ID%9]);
                personel.setPersonality(personalityOpen);
                personel.setVelocity(ID < 47 ? perNoDisabilityWithoutOvertaking : perNoDisabilityWithOvertaking);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    event.setTime(allTimeDistances[x]);
                    events.push_back(event);
                }
                personel.setEvents(events);
                pedestrians.push_back(personel);
                break;
            }
            case 1: {
                Visitor visitor;
                vector<Event>events;
                visitor.setID(ID + 1);
                visitor.setAge(ages[ID]);
                visitor.setStartWard(wards[9]);//ward A
                visitor.setEndWard(wards[9]);//ward A
                visitor.setPersonality(ID > 100 ? personalityNeurotic : personalityOpen);
                visitor.setVelocity(ID < 122 ? (ID < 85 ? perNoDisabilityWithOvertaking : perWalkingWithCrutches) : perWalkingWithSticks);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    event.setTime(allTimeDistances[x]);
                    events.push_back(event);
                }
                visitor.setEvents(events);
                pedestrians.push_back(visitor);
                break;
            }
            case 2: {
                Patient patient;
                vector<Event>events;
                patient.setID(ID + 1);
                patient.setAge(ages[ID]);
                patient.setStartWard(wards[9]);//ward A
                patient.setEndWard(wards[9]);//ward A
                patient.setPersonality(personalityNeurotic);
                patient.setVelocity(ID > 148 ? (ID > 173 ? perTheBlind : perWheelchairs) : perWalkingWithSticks);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    event.setTime(allTimeDistances[x]);
                    events.push_back(event);
                }
                patient.setEvents(events);
                pedestrians.push_back(patient);
                break;
            }
            }
        }
    }
    return pedestrians;
    //Write result on file
    // ofstream outFile("data/pedestrian.txt", ios::app);
    // if (!outFile.is_open()) {
    //     cout << "Cann't open file" << endl;
    //     return pedestrians;
    // }
    // for (auto& pedestrian : pedestrians) {
    //     json jsonObject;
    //     jsonObject["ID"] = pedestrian.getID();
    //     jsonObject["velocity"] = pedestrian.getVelocity();
    //     // jsonObject["emotion"]["pleasure"] = pedestrian.getEmotion().getPleasure();
    //     // jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
    //     // jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
    //     // jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
    //     // jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
    //     // jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
    //     jsonObject["age"] = pedestrian.getAge();
    //     jsonObject["start ward"] = pedestrian.getStart().getName();
    //     jsonObject["end ward"] = pedestrian.getEnd().getName();
    //     jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "Open" : "Neurotic";
    //     // jsonObject["personality"]["lambda"] = pedestrian.getPersonality().getLambda();
    //     // jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
    //     // jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
    //     jsonObject["events"] = pedestrian.getEventsIntensity();
    //     outFile << jsonObject << std::endl;
    // }
    // outFile.close();

    // cout << "Write Successfully!" << endl;
    // return pedestrians;
}

// bai 6
vector<vector<double>> eventsImpact(Pedestrian p,int timeHorizon){
    int lastTime=0,index=0;
    vector<double> temp(6, 0.0);
    vector<int> times=p.getEventsTime();
    vector<vector<double>> events = p.getEventsIntensity();
    double lambda = p.getPersonality().getLambda();
    vector<vector<double>> allEmotions={
        {p.getEmotion().getPleasure()},
        {p.getEmotion().getSurprise()},
        {p.getEmotion().getAnger()},
        {p.getEmotion().getFear()},
        {p.getEmotion().getHate()},
        {p.getEmotion().getSad()}
        };
    for(int i=0;i<6;i++){
        allEmotions[i].push_back(allEmotions[i][0]+events[i][0]+allEmotions[i][0]*exp(lambda));
        cout<<"allEmotions["<<i<<"][1]="<<allEmotions[i][1]<<", events[" << i << "][0]=" << events[i][0] <<", allEmotions["<<i<<"][0]="<<allEmotions[i][0]<<endl;
    }
    for(int time : times){
        cout<<time<<" ";
    }
    cout<<endl;
    for (int i = 2; i < 20; i++) {
        for (int j = 0; j < 6; j++) {
            temp[j] = allEmotions[j][i - 1];
        }
        if (i - lastTime == times[index]) {
            index++;
            lastTime = i;
            cout << "Event " << index << " occurs at " << i << endl;
            for (int j = 0; j < 6; j++) {
                temp[j] += allEmotions[j][i - 1] * exp(-lambda) + events[j][index];
                cout << "temp[" << j << "]=" << temp[j] << ", events[" << j << "][" << index << "]=" << events[j][index] << ", allEmotions[" << j << "][" << i - 1 << "]=" << allEmotions[j][i - 1] << endl;
            }
        }
        for (int j = 0; j < 6; j++) {
            allEmotions[j].push_back(temp[j]);
        }
    }

    return allEmotions;
}

//bai8
void leavingDistribution(string name){
    int totalValue=0;
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    string start = inputData1["leavingDistribution"]["distribution"][name]["normal"]["start"];
    string end = inputData1["leavingDistribution"]["distribution"][name]["normal"]["end"];
    string timeSte = inputData1["leavingDistribution"]["distribution"][name]["normal"]["timeStep"];
    int stdDev = inputData1["leavingDistribution"]["distribution"][name]["normal"]["std_dev"];
    int startTime=stoi(start);
    int endTime=stoi(end);
    int timeStep=stoi(timeSte);
    double numberOfValue = (double)(endTime-startTime+1)/timeStep;
    
    vector<Pedestrian>pedestrians=generatePedestrian();
    for(Pedestrian pedestrian : pedestrians){
        if(pedestrian.getEnd().getName().compare(name)==0){
            totalValue++;
        }
    }
    double meanValue= (double)totalValue/numberOfValue;
    for (int i = startTime; i <= 10; i += 2) {
        double numLeavers = normalDistribution(i, meanValue, stdDev) * totalValue;
        cout << "Time " << i << ": " << numLeavers << " people leaving from ward "<<name << endl;
    }
}


