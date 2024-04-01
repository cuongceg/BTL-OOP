#include "Pedestrian.hpp"
#include <iostream>
#include "../../lib/nlohmann/json.hpp" 
#include <fstream>
#include <sstream>
#include <random>
#include "../utility/Utility.h"

using namespace std;
using json = nlohmann::json;

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
            for (const auto& value : intensity) {
                cout << value << " ";
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

int randomNumber(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 42); 

    int random_number = dis(gen);
    return random_number;
}
void generatePedestrian(){
    //47, 37, 37, 27, 25, 27
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    int ID=-1;
    //Example
    float deviationParam = 5;
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
    int numPedestrians[] = {80,53,67};
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents=generateEvents();
    // 43 values likes 43 events
    vector<double> allTimeDistances={2675, 860, 1399, 1909, 810, 2402, 1046, 3036, 1113, 1049, 1550, 1711,
        1537, 3313, 1397, 1051, 2408, 798, 1210, 1975, 2148, 1220, 1884, 1427,
        1207, 1604, 902, 1868, 2092, 3312, 814, 2368, 2029, 3028, 1539, 1802,
        1321, 1530, 2025, 2308, 2808, 2037, 1982};
    for(int i=0;i<3;i++){
        for(int j=0;j<numPedestrians[i];j++){
            //unique ID
            ID++;
            //personality
            Personality personalityOpen,personalityNeurotic;
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
            switch (i) {
            case 0: {
                Personel personel;
                vector<Event>events;
                personel.setID(ID + 1);
                personel.setAge(ages[ID]);
                personel.setPersonality(personalityOpen);
                personel.setVelocity(ID < 47 ? perNoDisabilityWithoutOvertaking : perNoDisabilityWithOvertaking);
                for(int i=0;i<20;i++){
                    int x = randomNumber();
                    Event event=allEvents[x];
                    event.setTime(allTimeDistances[x]);
                    events.push_back(event);
                }
                personel.setEvents(events);
                pedestrians.push_back(personel);
                break;
            }
            case 1: {
                Visitor visitor;
                visitor.setID(ID + 1);
                visitor.setAge(ages[ID]);
                visitor.setPersonality(ID>100?personalityNeurotic:personalityOpen);
                visitor.setVelocity(ID < 122 ? (ID < 85 ? perNoDisabilityWithOvertaking : perWalkingWithCrutches) : perWalkingWithSticks);
                pedestrians.push_back(visitor);
                break;
            }
            case 2: {
                Patient patient;
                patient.setID(ID + 1);
                patient.setAge(ages[ID]);
                patient.setPersonality(personalityNeurotic);
                patient.setVelocity(ID > 148 ? (ID > 173 ? perTheBlind : perWheelchairs) : perWalkingWithSticks);
                pedestrians.push_back(patient);
                break;
            }
        }       
        }
    }
    vector<Event>test=pedestrians[0].getEvents();
    cout<<test.size();
    ofstream outFile("data/result.txt",ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Cann't open file" << std::endl;
        return ;
    }
    for(auto &pedestrian:pedestrians){
        json jsonObject;
        jsonObject["ID"] = pedestrian.getID();
        jsonObject["velocity"] = pedestrian.getVelocity();
        jsonObject["emotion"]["pleasure"] = pedestrian.getEmotion().getPleasure();
        jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
        jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
        jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
        jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
        jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
        jsonObject["age"] = pedestrian.getAge();
        jsonObject["personality"]["name"]=pedestrian.getPersonality().getLambda()==1?"Open":"Neurotic";
        jsonObject["personality"]["lambda"]=pedestrian.getPersonality().getLambda();
        jsonObject["personality"]["positiveEmotionThreshold"]=pedestrian.getPersonality().getPositiveEmotionThreshold();
        jsonObject["personality"]["negativeEmotionThreshold"]=pedestrian.getPersonality().getNegativeEmotionThreshold();
        jsonObject["events"]["pleasure"]=pedestrian.getEvents().at(0).getIntensity();
        outFile << jsonObject << std::endl;
    }
    outFile.close();

    cout << "Write Successfully!" << endl;
    return ;
}

