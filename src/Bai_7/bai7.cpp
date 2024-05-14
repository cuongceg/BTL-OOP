#include "bai7.hpp"
#include "../../lib/nlohmann/json.hpp" 
#include "../utility/Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <unordered_set>

using namespace std;
using json = nlohmann::json;
using std::normal_distribution;

std::vector<std::vector<double>> getImpact(int numOfSamples, int numOfValues, double minValue, double maxValue) {
    // Create a 2D vector to hold the impacts for 6 emotions
    std::vector<std::vector<double>> impacts(6, std::vector<double>(numOfSamples));

    // Setup random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    double mean = (minValue + maxValue) / 2;
    double std = (maxValue - mean) / 3; // Standard deviation to keep most data within [minValue, maxValue]
    std::normal_distribution<> dist(mean, std);

    // Generate the random values
    for (auto& emotion : impacts) {
        std::generate(emotion.begin(), emotion.end(), [&]() {
            double value = dist(gen);
            return std::max(minValue, std::min(value, maxValue)); // Clamp values to range [minValue, maxValue]
        });
    }

    return impacts;
}

bool isChild(const Pedestrian& pedestrian) {
    return pedestrian.getAge() < 12;
}

int countYoungerThan12(const std::vector<Pedestrian>& allPedestrians) {
    return std::count_if(allPedestrians.begin(), allPedestrians.end(), [](const Pedestrian& p) {
        return isChild(p);
    });
}


bool isElder(const Pedestrian& pedestrian) {
    return pedestrian.getAge() > 60;
}

int countOlderThan60(const std::vector<Pedestrian>& allPedestrians) {
    return std::count_if(allPedestrians.begin(), allPedestrians.end(), [](const Pedestrian& p) {
        return isElder(p);
    });
}

std::unordered_set<std::string> alkwNames = {"A", "L", "K", "W"};
bool isALKW(const Pedestrian& pedestrian) {
    return alkwNames.count(pedestrian.getStart().getName()) > 0;
}

int countALKW(const std::vector<Pedestrian>& allPedestrians) {
    return std::count_if(allPedestrians.begin(), allPedestrians.end(), [](const Pedestrian& p) {
        return isALKW(p);
    });
}

std::unordered_set<std::string> bfgmenNames = {"B", "F", "G", "M", "E", "N"};
bool isBFGMEN(const Pedestrian& pedestrian) {
    return bfgmenNames.count(pedestrian.getStart().getName()) > 0;
}

int countBFGMEN(const std::vector<Pedestrian>& allPedestrians) {
    return std::count_if(allPedestrians.begin(), allPedestrians.end(), [](const Pedestrian& p) {
        return isBFGMEN(p);
    });
}

bool isBlinder(const Pedestrian& pedestrian) {
    return pedestrian.getWalkability() == Walkability::blind;
}

int countBlinder(const std::vector<Pedestrian>& allPedestrians) {
    return std::count_if(allPedestrians.begin(), allPedestrians.end(), [](const Pedestrian& p) {
        return isBlinder(p);
    });
}

std::vector<std::vector<int>> assignAGVImpacts(std::vector<Pedestrian>& allPedestrians) {
    json inputData;
    inputData = Utility::readInputData("data/input.json");
    json impactOfAGVData = inputData["impactOfAGV"]["distribution"];
    int nChildren = countYoungerThan12(allPedestrians);
    vector<vector<double>> impactToChildren = getImpact(nChildren, impactOfAGVData["children"]["numberOfValues"], impactOfAGVData["children"]["minValue"], impactOfAGVData["children"]["maxValue"]);

    int nElder = countOlderThan60(allPedestrians);
    vector<vector<double>> impactToElder = getImpact(nElder, impactOfAGVData["Elder"]["numberOfValues"], impactOfAGVData["Elder"]["minValue"], impactOfAGVData["Elder"]["maxValue"]);
    for (auto& row : impactToElder) {
        for (auto& val : row) val *= -1;
    }

    int nPersonnelOfALKW = countALKW(allPedestrians);
    vector<vector<double>> impactToALKW = getImpact(nPersonnelOfALKW, impactOfAGVData["ALKW"]["numberOfValues"], impactOfAGVData["ALKW"]["minValue"], impactOfAGVData["ALKW"]["maxValue"]);

    int nPersonnelOfBFGMEN = countBFGMEN(allPedestrians);
    vector<vector<double>> impactToBFGMEN = getImpact(nPersonnelOfBFGMEN, impactOfAGVData["BFGMEN"]["numberOfValues"], impactOfAGVData["BFGMEN"]["minValue"], impactOfAGVData["BFGMEN"]["maxValue"]);
    for (auto& row : impactToBFGMEN) {
        for (auto& val : row) val *= -1;
    }

    int nBlinder = countBlinder(allPedestrians);
    vector<vector<double>> impactToBlinder = getImpact(nBlinder, impactOfAGVData["Blinder"]["numberOfValues"], impactOfAGVData["Blinder"]["minValue"], impactOfAGVData["Blinder"]["maxValue"]);
    for (auto& row : impactToBlinder) {
        for (auto& val : row) val *= -1;
    }
    int nOthers = allPedestrians.size() - (nChildren + nPersonnelOfALKW + nPersonnelOfBFGMEN + nElder + nBlinder);
    vector<vector<double>> impactToOthers = getImpact(nOthers, impactOfAGVData["Other"]["numberOfValues"], impactOfAGVData["Other"]["minValue"], impactOfAGVData["Other"]["maxValue"]);


    // for (Pedestrian& person : allPedestrians) {
    //     // Adjust impactOfAGV based on the type of person
    //     vector<vector<int>> impactOfAGV;
    //     impactOfAGV.resize(6, vector<int>(1, 0));
    //     if (isChild(person)) {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToChildren[i][0];
    //         }
    //     } else if (isALKW(person)) {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToALKW[i][0];
    //         }
    //     } else if (isBFGMEN(person)) {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToBFGMEN[i][0];
    //         }
    //     } else if (isElder(person)) {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToElder[i][0];
    //         }
    //     } else if (isBlinder(person)) {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToBlinder[i][0];
    //         }
    //     } else {
    //         for (int i = 0; i < 6; ++i) {
    //             impactOfAGV[i][0] += impactToOthers[i][0];
    //         }
    //     }
    // }

    std::vector<std::vector<int>> impactOfAGV(allPedestrians.size(), std::vector<int>(6, 0));
    for (int i = 0; i < allPedestrians.size(); ++i) {
        const Pedestrian& person = allPedestrians[i];
        if (isChild(person)) {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToChildren[j][0];
            }
        } else if (isALKW(person)) {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToALKW[j][0];
            }
        } else if (isBFGMEN(person)) {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToBFGMEN[j][0];
            }
        } else if (isElder(person)) {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToElder[j][0];
            }
        } else if (isBlinder(person)) {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToBlinder[j][0];
            }
        } else {
            for (int j = 0; j < 6; ++j) {
                impactOfAGV[i][j] += impactToOthers[j][0];
            }
        }
    }
    return impactOfAGV;
}

vector<Ward> generateWard() {
    vector<Ward> wards;
    ifstream file("data/hospital.txt");
    string line;
    if (file.is_open()) {
        getline(file, line);
        for (int i = 2;i < 11;i++) {
            vector<Point>wall;
            Point midPoint1, midPoint2, point1, point2, point3, point4;
            double length;
            string name;
            if (!getline(file, line)) {
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
            wall.push_back(point1);
            wall.push_back(point2);
            wall.push_back(point3);
            wall.push_back(point4);
            Ward ward = Ward(midPoint1, midPoint2, name, wall);
            wards.push_back(ward);
            std::cout << wards.size() << endl;
        }
        file.close();
    }
    else {
        std::cout << "Cann't open" << endl;
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
            std::cout << endl;
            event.setIntensity(intensity);
            event.setTime(0);
            events.push_back(event);
        }
        file.close();
    } else {
        std::cout << "Cann't open"<< endl;
    }
    return events;
}
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
//bai 3
void generatePedestrian() {
    //47, 37, 37, 27, 25, 27 number of people
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    int ID = -1;
    //Example
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
    int numPedestrians[] = { 80,53,67 };
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    // 43 values likes 43 events
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 43);
    vector<double> allTimeDistances(43);
    for(int i=0;i<42;i++){
        allTimeDistances[i]=dis(gen);
    }
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < numPedestrians[i];j++) {
            //unique ID
            ID++;   
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
            switch (i) {
            case 0: {
                Personel personel;
                vector<Event>events;
                personel.setID(ID + 1);
                personel.setAge(ages[ID]);
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
    //Write result on file
    ofstream outFile("data/pedestrian.txt", ios::app);
    if (!outFile.is_open()) {
        cout << "Cann't open file" << endl;
        return ;
    }
    for (auto& pedestrian : pedestrians) {
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
        jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "Open" : "Neurotic";
        jsonObject["personality"]["lambda"] = pedestrian.getPersonality().getLambda();
        jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
        jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
        jsonObject["events"] = pedestrian.getEvents();
        outFile << jsonObject << std::endl;
    }
    outFile.close();

    cout << "Write Successfully!" << endl;
    return;
}
// bai 6
vector<vector<double>> eventsImpact(Pedestrian p,int timeHorizon){
    int lastTime=0,index=0;
    vector<double> temp(6, 0.0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(4, 10);
    vector<int> times(19);
    for (int i = 0; i < 19; ++i) {
        times[i] = dis(gen);
    }
    vector<vector<double>> events = p.getEvents();
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
            cout << "Su kien " << index << " xay ra luc " << i << endl;
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
