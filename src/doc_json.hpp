#ifndef DOC_JSON
#define DOC_JSON
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
#include "lop.hpp"

using namespace std;
using json = nlohmann::json;
string name_file = "input.json";

int get_numOfAgents()
{
    //Mở file json
    ifstream file(name_file);
    if(!file.is_open())
    {
        cerr << "Mở file json không thành công." << std::endl;
        return -1;
    }
    //đọc dữ liệu
    json jsondata;
    file >> jsondata;
    file.close();

    int numOfAgents = jsondata["numOfAgents"]["value"];
    cout << "numOfAgents: " << numOfAgents << ".\n"; 

    return numOfAgents;
}

//Số lượng khoa/viện di chuyển qua của bệnh nhân,bác sĩ,người thăm
// journeyDistribution soLuongKhoaVien()
// {
//     pair<vector<Ward>,A> map;
//     map = mapWard();
//     journeyDistribution x;
//     //Mở file json
//     ifstream file(name_file);
//     if(!file.is_open())
//     {
//         cerr << "Failed to open JSON file." << std::endl;
//         return x;
//     }
//     //đọc dữ liệu
//     json jsondata;
//     file >> jsondata;
//     file.close();
//     x.forPatient.description = jsondata["journeyDistribution"]["distribution"]["forPatient"]["description"];
//     x.forPatient.value = jsondata["journeyDistribution"]["distribution"]["forPatient"]["value"];
    
//     x.forPatient.end.setName(jsondata["journeyDistribution"]["distribution"]["forPatient"]["end"]);

//     x.forVisitor.description = jsondata["journeyDistribution"]["distribution"]["forVisitor"]["description"];
//     x.forVisitor.value = jsondata["journeyDistribution"]["distribution"]["forVisitor"]["value"];
//     x.forVisitor.start.setName(jsondata["journeyDistribution"]["distribution"]["forVisitor"]["start"]);
//     x.forVisitor.end.setName(jsondata["journeyDistribution"]["distribution"]["forVisitor"]["end"]);

//     x.forPesonel.description = jsondata["journeyDistribution"]["distribution"]["forPersonel"]["description"];
//     x.forPesonel.value = jsondata["journeyDistribution"]["distribution"]["forPersonel"]["value"];
//     x.forPesonel.start.setName(jsondata["journeyDistribution"]["distribution"]["forPersonel"]["start"]);
//     x.forPesonel.end.setName(jsondata["journeyDistribution"]["distribution"]["forPersonel"]["end"]);
// }

vector<Personality> nguongCamxuc()
{
    vector<Personality> input;
    //Mở file json
    ifstream file(name_file);
    if(!file.is_open())
    {
        cerr << "Mở file json không thành công." << std::endl;
        return input;
    }
    //đọc dữ liệu
    json jsondata;
    file >> jsondata;
    file.close();

    //Kiểu tích cách open
    Personality open;
    //open.description = jsondata["personalityDistribution"]["distribution"]["open"]["description"];
    open.setPositiveEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]);
    open.setNegativeEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]);
    open.setLambda(jsondata["personalityDistribution"]["distribution"]["open"]["lambda"]);
    input.push_back(open);
   //Kiểu tích cách nẻuotic
    Personality neurotic;
    //open.description = jsondata["personalityDistribution"]["distribution"]["open"]["description"];
    neurotic.setPositiveEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]);
    neurotic.setNegativeEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]);
    //neurotic.setLambda(jsondata["personalityDistribution"]["distribution"]["neurotic"]["lambda"]);
    input.push_back(neurotic);
//     Personality heuristic;
//     heuristic.setPositiveEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["heuristic"]["positiveEmotionThreshold"]);
//     heuristic.setNegativeEmotionThreshold(jsondata["personalityDistribution"]["distribution"]["heuristic"]["negativeEmotionThreshold"]);
//     input.push_back(heuristic);
    cout << "Gọi thành công ngưỡng cảm xúc!\n";
    return input;
}

vector<speedWalkability> getSpeedWalkability()
{
    vector<speedWalkability> inputSpeed;
    //Mở file json
    ifstream file(name_file);
    if(!file.is_open())
    {
        cerr << "Failed to open JSON file." << std::endl;
        return inputSpeed;
    }
    //đọc dữ liệu
    json jsondata;
    file >> jsondata;
    file.close();
    speedWalkability noDisabilityNoOvertaking ;
    noDisabilityNoOvertaking.description = jsondata["walkability"]["distribution"]["noDisabilityNoOvertaking"]["description"];
    noDisabilityNoOvertaking.velocity = jsondata["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"];
    inputSpeed.push_back(noDisabilityNoOvertaking);

    speedWalkability noDisabilityOvertaking;
    noDisabilityOvertaking.description = jsondata["walkability"]["distribution"]["noDisabilityOvertaking"]["description"];
    noDisabilityOvertaking.velocity = jsondata["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"];
    inputSpeed.push_back(noDisabilityOvertaking);

    speedWalkability crutches;
    crutches.description = jsondata["walkability"]["distribution"]["crutches"]["description"];
    crutches.velocity = jsondata["walkability"]["distribution"]["crutches"]["velocity"];
    inputSpeed.push_back(crutches);

    speedWalkability sticks;
    sticks.description = jsondata["walkability"]["distribution"]["sticks"]["description"];
    sticks.velocity = jsondata["walkability"]["distribution"]["sticks"]["velocity"];
    inputSpeed.push_back(sticks);

    speedWalkability wheelchairs;
    wheelchairs.description = jsondata["walkability"]["distribution"]["wheelchairs"]["description"];
    wheelchairs.velocity = jsondata["walkability"]["distribution"]["wheelchairs"]["velocity"];
    inputSpeed.push_back(wheelchairs);

    speedWalkability blind;
    blind.description = jsondata["walkability"]["distribution"]["blind"]["description"];
    blind.velocity = jsondata["walkability"]["distribution"]["blind"]["velocity"];
    inputSpeed.push_back(blind);

    cout << "Gọi thành công getSpeedWalkability().\n";

    return inputSpeed;
}
// int main()
// {
//     // vector<Personality> inputNguongCamXuc = nguongCamxuc();
//     // for(int i = 0; i < 2;i++)
//     // {
//     //     cout << "PositiveEmotionThreshold: " << inputNguongCamXuc[i].getPositiveEmotionThreshold() << '\n';
//     //     cout << "NegativeEmotionThreshold: " << inputNguongCamXuc[i].getNegativeEmotionThreshold() << '\n';  
//     //     cout << "Lambda: " << inputNguongCamXuc[i].getLambda() << '\n';
//     // }
//     vector<speedWalkability> inputspeed = getSpeedWalkability();
//     for(speedWalkability i : inputspeed)
//     {
//         cout << "description" << i.description <<'\n';
//         cout << "velocity: " <<i.velocity << '\n';
//         cout << '\n'; 
//     }
// }
#endif