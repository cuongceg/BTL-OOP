#include "Pedestrian.hpp"
#include "../../lib/nlohmann/json.hpp" 
#include "../utility/Utility.h"
#include "Distributions.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

//bai 3
// 1 is write to file, else is not write to file
vector<Pedestrian> generatePedestrian(int writeToFile) {
    //declare
    //47, 37, 37, 27, 25, 27 number of people
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    int ID = -1;
    int numOfPedes=inputData1["numOfAgents"]["value"];
    float deviationParam = randomFloat(1 - (float)inputData1["experimentalDeviation"]["value"] / 100, 1 + (float)inputData1["experimentalDeviation"]["value"] / 100);
    //number of types of Pedestrians
    //0 is noDisnoOvertaking, 1 is noDisOvertaking, 2 is crutches, 3 is sticks, 4 is wheelchairs, 5 is blind
    vector<int> numOfTypePedestrians = generateTypeOfPedes(6, numOfPedes,20, 47);
    int numOfStaff=numOfTypePedestrians[0]+numOfTypePedestrians[1]-randomNumber(1,20);
    int numOfVisitor=numOfTypePedestrians[0]+numOfTypePedestrians[1]-numOfStaff;
    int numOfPatient=numOfPedes-numOfStaff-numOfVisitor;
    int numPedestrians[]={numOfStaff,numOfVisitor,numOfPatient};
    //age distribution
    vector<double> agesStaff=generateAge(numOfStaff,23,61);
    vector<double> ages=generateAge(numOfPedes,5,104);
    
    // 43 elements likes 43 events
    vector<double> allTimeDistances(43);
    for(int i=0;i<42;i++){
        allTimeDistances[i]=randomNumber(1,19);
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
    double velocityList[numOfPedes];
    for (int i = 0;i < numOfPedes;i++) {
        if (i < numOfTypePedestrians[0]) {
            velocityList[i] = perNoDisabilityWithoutOvertaking;
        } else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1]) {
            velocityList[i] = perNoDisabilityWithOvertaking;
        } else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2]) {
            velocityList[i] = perWalkingWithCrutches;
        } else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2] + numOfTypePedestrians[3]) {
            velocityList[i] = perWalkingWithSticks;
        } else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2] + numOfTypePedestrians[3] + numOfTypePedestrians[4]) {
            velocityList[i] = perWheelchairs;
        } else {
            velocityList[i] = perTheBlind;
        }
    }

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
                personel.setID("s" + to_string(ID + 1));
                personel.setAge(agesStaff[ID]);
                personel.setStartWard(wards[ID%9]);
                personel.setEndWard(wards[ID%9]);
                personel.setPersonality(personalityOpen);
                personel.setVelocity(velocityList[ID]);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    i==0?event.setTime(allTimeDistances[x]):event.setTime(allTimeDistances[x]+events[i-1].getTime());
                    events.push_back(event);
                }
                personel.setEvents(events);
                pedestrians.push_back(personel);
                break;
            }
            case 1: {
                Visitor visitor;
                vector<Event>events;
                visitor.setID("v" + to_string(ID + 1));
                visitor.setAge(ages[ID]);
                visitor.setStartWard(wards[9]);//ward A
                visitor.setEndWard(wards[9]);//ward A
                visitor.setPersonality(ID > 100 ? personalityNeurotic : personalityOpen);
                visitor.setVelocity(velocityList[ID]);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    i==0?event.setTime(allTimeDistances[x]):event.setTime(allTimeDistances[x]+events[i-1].getTime());
                    events.push_back(event);
                }
                visitor.setEvents(events);
                pedestrians.push_back(visitor);
                break;
            }
            case 2: {
                Patient patient;
                vector<Event>events;
                patient.setID("p" + to_string(ID + 1));
                patient.setAge(ages[ID]);
                patient.setStartWard(wards[9]);//ward A
                patient.setEndWard(wards[9]);//ward A
                patient.setPersonality(personalityNeurotic);
                patient.setVelocity(velocityList[ID]);
                for (int i = 0;i < 20;i++) {
                    int x = randomNumber(0,42);
                    Event event = allEvents[x];
                    i==0?event.setTime(allTimeDistances[x]):event.setTime(allTimeDistances[x]+events[i-1].getTime());
                    events.push_back(event);
                }
                patient.setEvents(events);
                pedestrians.push_back(patient);
                break;
            }
            }
        }
    }
    if(writeToFile==1){
        //Write result on file
        ofstream outFile("result/pedestrian.txt", ios::app);
        if (!outFile.is_open()) {
            cout << "Cann't open file" << endl;
            return pedestrians;
        }
        for (auto& pedestrian : pedestrians) {
            json jsonObject;
            jsonObject["ID"] = pedestrian.getID();
            jsonObject["velocity"] = pedestrian.getVelocity();
            // jsonObject["emotion"]["pleasure"] = pedestrian.getEmotion().getPleasure();
            // jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
            // jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
            // jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
            // jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
            // jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
            jsonObject["age"] = pedestrian.getAge();
            jsonObject["start ward"] = pedestrian.getStart().getName();
            jsonObject["end ward"] = pedestrian.getEnd().getName();
            jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "Open" : "Neurotic";
            // jsonObject["personality"]["lambda"] = pedestrian.getPersonality().getLambda();
            // jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
            // jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
            jsonObject["events"] = pedestrian.getEventsIntensity();
            jsonObject["eventsTime"] = pedestrian.getEventsTime();
            outFile << jsonObject<<endl;
        }
        outFile.close();

        cout << "Write Successfully!" << endl;
    }
    return pedestrians;
}

//bai 4         
//triple - số đối tượng phải đi qua 3 khoa
//single - số đối tượng đi qua 1 khoa
vector<pair<Ward,int>> bai4(vector<Ward>& input,int triple,int single)
{
    
    vector<pair<Ward,int>> result;
    json inputData1;
    inputData1 = Utility::readInputData("data/input.json");

    int numOfAgents = inputData1["numOfAgents"]["value"];
   
    //Tổng số người đầu vào
    int sum = triple + single;
    //Kiểm tra dữ liệu
    if(sum != numOfAgents)
    {
        cout << "Error"<<'\n';
        return result;
    }

    //Số lượng khoa
    int sLuongWard = input.size();
    //Tổng số lượt đi qua các khoa/viện
    int total_value = triple*3 + single;    
    double mean = total_value/sLuongWard;//average
    double std = 3;//standard deviation
    
    //Số lượt đi qua của từng khoa/viện
    vector<int> number;
    bool test = true;//Trạng thái lặp
    while(test)
    {
        //Xóa hết các giá trị không t/m
        number.clear();
        for(int i = 0; i < sLuongWard;i++)
        {
            //Tạo ngẫu nhiên số lần đi qua khoa
            int a = static_cast<int>(rand_normal(mean,std));
            number.push_back(a);
        }

        //Tính tổng số lượt đi qua các khoa
        int sum = 0;
        for(int num : number)
        {
            sum = sum + num;
        }
        //Thỏa mãn tổng các int bằng tổng số lượt
        if(sum == total_value)
        {
            test = false;
        }    
    }

    //Thiết lập khoa tương ứng số lượt đi qua   
    for(int i = 0; i < sLuongWard;i++)
    {
        pair<Ward,int> pr;
        pr.first = input[i];
        pr.second = number[i];
        result.push_back(pr);
    }
    return result;
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
    
    vector<Pedestrian>pedestrians=generatePedestrian(0);
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


