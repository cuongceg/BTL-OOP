#include "Pedestrian.hpp"
#include <iostream>
#include "../../lib/nlohmann/json.hpp" 
#include <fstream>
#include "../utility/Utility.h"

using namespace std;
using json = nlohmann::json;

void generatePedestrian(){
    //47, 37, 37, 27, 25, 27
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    int ID=-1;
    float deviationParam = 5;
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
    vector<Event> allEvents;
    vector<double> allTimeDistances;
    for(int i=0;i<1;i++){
        for(int j=0;j<numPedestrians[i];j++){
            ID++;
            double perNoDisabilityWithoutOvertaking =
                double(inputData1["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"]) * deviationParam;
            double perNoDisabilityWithOvertaking =
                double(inputData1["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"]) * deviationParam;
            // double perWalkingWithCrutches =
            //     double(inputData1["walkability"]["distribution"]["crutches"]["velocity"]) * deviationParam;
            // double perWalkingWithSticks = 
            //     double(inputData1["walkability"]["distribution"]["sticks"]["velocity"]) * deviationParam;
            // double perWheelchairs = 
            //     double(inputData1["walkability"]["distribution"]["wheelchairs"]["velocity"]) * deviationParam;
            // double perTheBlind =
            //     double(inputData1["walkability"]["distribution"]["blind"]["velocity"]) * deviationParam;
            switch (i)
            {
            case 0 :
                Personel personel;
                personel.setID(ID+1);
                personel.setAge(ages[ID]);
                personel.setVelocity(ID<47?perNoDisabilityWithoutOvertaking:perNoDisabilityWithOvertaking);
                pedestrians.push_back(personel);
                break;
        }
    }
    ofstream outFile("data/result.txt",ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Không thể mở file để ghi!" << std::endl;
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
        outFile << jsonObject << std::endl;
    }
    outFile.close();

    std::cout << "Dữ liệu đã được ghi vào file thành công!" << std::endl;
    return ;
}
}

