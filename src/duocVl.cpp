#include <fstream>

#include "khoiTaoPedestrian.hpp"
#include "bai3.hpp"
#include "bai4.hpp"
#include "bai5.hpp"

int main()
{
    //Khoiqr tạo các thông số cơ bản cho Pedestrian
    obJect doituong = khoitaodoituong();
    //Thiết lập danh sách các Event tác động đến doi tuong
    bai3(doituong);
    int M = get_numOfAgents();
    //Bài 5
    //Thiết lập danh sách các khoa/viện đi qua cho đối tượng
    bai5(doituong);

    string namefile = "doituong.txt";
    ofstream outFile(namefile,std::ios::app);
    
    //In các giá trị
    vector<Patitent> nguoiBenh = doituong.getPatitent();
    vector<Visitor> nguoiTham = doituong.getVisitor();
    vector<Personel> bacSi = doituong.getPersonel();

    int demPatient = 0;
    int demVisitor = 0;
    int demPersonel = 0;


    for(int i = 0; i < M;i++)
    {
        if(nguoiBenh[demPatient].getID() == i)
        {
            cout <<"ID: " << nguoiBenh[demPatient].getID() << " Age: " << nguoiBenh[demPatient].getAge() <<'\n';
            vector<Event> events = nguoiBenh[demPatient].getEvents();
            cout << "Time Events: ";
            for(Event a: events)
            {
                cout << a.getTime() << ' '; 
            }
            cout <<'\n';
            vector<Ward> cacKhoa = nguoiBenh[demPatient].getJourney();
            cout << "Các Khoa: ";
            for(auto k : cacKhoa)
            {
                cout << k.getName() << ' ';
            }
            cout << '\n';
            outFile << "{ID:" << nguoiBenh[demPatient].getID() << ";" << "Age:" << nguoiBenh[demPatient].getAge() << ' ';
            
            demPatient++;
        }
        else if (nguoiTham[demVisitor].getID() == i)
        {
            cout <<"ID: " << nguoiTham[demVisitor].getID() << " Age: " << nguoiTham[demVisitor].getAge() <<'\n';
            vector<Event> events = nguoiTham[demVisitor].getEvents();
            cout << "Time Events: ";
            for(auto& a: events)
            {
                cout << a.getTime() << ' '; 
            }
            cout << '\n';
            vector<Ward> cacKhoa = nguoiTham[demVisitor].getJourney();
            cout << "Các Khoa: ";
            for(auto k : cacKhoa)
            {
                cout << k.getName() << ' ';
            }
            cout << '\n';
            outFile << "{ID:" << nguoiTham[demVisitor].getID() << "," << "Age:" << nguoiTham[demVisitor].getAge() <<"}"<< endl;
            demVisitor++;
        }
        else
        {
            cout <<"ID: " << bacSi[demPersonel].getID() << " Age: " << bacSi[demPersonel].getAge() <<'\n';
            vector<Event> events = bacSi[demPersonel].getEvents();
            cout << "Time Events: ";
            for(auto& a: events)
            {
                cout << a.getTime() << ' '; 
            }
            cout << '\n';
            vector<Ward> cacKhoa = bacSi[demPersonel].getJourney();
            cout << "Các Khoa: ";
            for(auto k : cacKhoa)
            {
                cout << k.getName() << ' ';
            }
            cout << '\n';
            outFile << "{ID:" << bacSi[demPersonel].getID() << "," << "Age:" << bacSi[demPersonel].getAge() <<"}"<< endl;
            demPersonel++;
        }

    }
}