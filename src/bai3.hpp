/*Đọc file dữ liệu tạo mảng M phần tử là số người đi bộ
trong hành lang.

M = 'value'

số nhân viên y tế(đối tượng lớp Personel) < số lượng noDisability

Không có đối tượng lớp Personel thuộc nhóm crutches,sticks
wheeelchairs,blind(nhóm người bệnh)

các đối tượng có số khoa viện cần đến(ko tính khoa đầu tiên
cuối cùng) =  số khoa trong tùy chọn journeyDistribution

tất cả các khoa viện xuất hiện ít nhất 1 lần trong các 
khoa cần đến của người đi bộ

tie lệ người có tính cách open/neurotic = 50% (sai số 5%)

ko có người nào dưới 11 tuổi có tính cách neutoric

ko có nhân viên y tế nào có 23 <= tuổi >= 61

cảm xúc ban đầu :
pleasure = 0.75,surprise = 0.5,anger=fear= -0.2
hate = sad = -0.4
*/

#ifndef BAI3_H
#define BAI3_H
#include <iostream>
#include <vector>
#include <random>
#include "lop.hpp"
using namespace std;
void bai3(vector<Pedestrian> dulieu)
{
    //lấy từ dữ liệu đầu vào có 43 sự kiện
    vector<Event> allEvents;
    vector<double> allTimeDistances;

    //Khởi tạo generator ngẫu nhiên
    random_device rd; 
    mt19937 generator(rd());
    //Phạm vi số ngẫu nhiên
    int min_value = 0;
    int max_value = allEvents.size() - 1;
    //Tạo distribution để sinh số ngẫu nhiên trong phạm vi trên
    uniform_int_distribution<int> distribution(min_value,max_value);

    for(auto i : dulieu)
    {
        for(int k = 0; k < 20;k++)
        {
            //Sinh số ngẫu nhiên
             int X = distribution(generator);
             //Lấy sự kiện ngẫu nhiên từ giá trị ngẫu nhiên X
             Event event = allEvents[X];
             event.time = allTimeDistances[X];
             i.events.push_back(event);
        }
    }
}
#endif
