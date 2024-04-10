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
#include "docfileTXT.hpp"
#include "khoiTaoPedestrian.hpp"
#include "lop.hpp"
using namespace std;
void bai3(obJect &doituong)
{
    vector<Patitent> nguoiBenh = doituong.getPatitent();
    vector<Visitor> nguoiTham = doituong.getVisitor();
    vector<Personel> bacSi = doituong.getPersonel();

    //lấy từ dữ liệu đầu vào có 43 sự kiện
    vector<Event> allEvents = eventTacDong();
    //Lấy thời gian sự kiện tác động của tất cả các dối tượng
    vector<vector<int>> allTimeDistances = timeEvents();
    //Khởi tạo generator ngẫu nhiên
    random_device rd; 
    mt19937 generator(rd());
    //Phạm vi số ngẫu nhiên
    int min_value = 0;
    int max_value = allEvents.size() - 1;
    //Tạo distribution để sinh số ngẫu nhiên trong phạm vi trên
    uniform_int_distribution<int> distribution(min_value,max_value);

    //Thiết lập danh sách các Events tác động lên Patient
    for(int i = 0; i < nguoiBenh.size();i++)
    {
        int id = nguoiBenh[i].getID();
        vector<Event> events;
        for(int j = 0; j < 20;j++)
        {
            int X = distribution(rd);
            Event sk;
            sk = allEvents[X];
            sk.setTime(allTimeDistances[id][j]);
            events.push_back(sk);
        }
        nguoiBenh[i].setEvents(events);
    }
    //Thiết lặp danh sách tác động lên Visitor
    for(int i = 0; i < nguoiTham.size();i++)
    {
        int id = nguoiTham[i].getID();
        vector<Event> events;
        for(int j = 0; j < 20;j++)
        {
            int X = distribution(rd);
            Event sk;
            sk = allEvents[X];
            sk.setTime(allTimeDistances[id][j]);
            events.push_back(sk);
        }
        nguoiTham[i].setEvents(events);
    }
    //Thiết lập danh sách các Event tác động lên Personel
    for(int i = 0; i < bacSi.size();i++)
    {
        int id = bacSi[i].getID();
        vector<Event> events;
        for(int j = 0; j < 20;j++)
        {
            int X = distribution(rd);
            Event sk;
            sk = allEvents[X];
            sk.setTime(allTimeDistances[id][j]);
            events.push_back(sk);
        }
        bacSi[i].setEvents(events);
    }
    //Cập nhật thông số cho đối tượng
    doituong.setPatient(nguoiBenh);
    doituong.setVisitor(nguoiTham);
    doituong.setPersonel(bacSi);
}
#endif
