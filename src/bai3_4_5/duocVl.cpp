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
    ofstream outFile(namefile,std::ios::trunc);
    
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
            outFile << "{ \"Type\": \"Patient\" , \"ID\": " << nguoiBenh[demPatient].getID() << "," << "\"Age\": " << nguoiBenh[demPatient].getAge() << ' ';
            outFile << "\"Journey\": ";
            vector<Ward> cacWard = nguoiBenh[demPatient].getJourney();
            for(auto a : cacWard)
            {
                outFile << a.getName() << ' ';
            }
            outFile << ',' << "\"Events\": ";

            vector<Event> sk = nguoiBenh[demPatient].getEvents();
            for(Event n : sk)
            {
                outFile << '(';
                vector<double> vt = n.getIntensity();
                for(int m = 0; m < vt.size();m++)
                {
                    outFile << vt[m] << ' ';
                }
                outFile << ") - " << "\"Time\": " << n.getTime() << ' ';
            }
            outFile << "}," << endl;

            demPatient++;
        }
        else if (nguoiTham[demVisitor].getID() == i)
        {
            outFile << "{ \"Type\": \"Visitor\" , \"ID\": " << nguoiTham[demVisitor].getID() << "," << "\"Age\": " << nguoiTham[demVisitor].getAge() << ' ';
            outFile << "\"Journey\": ";
            vector<Ward> cacWard = nguoiTham[demVisitor].getJourney();
            for(auto a : cacWard)
            {
                outFile << a.getName() << ' ';
            }
            outFile << ',' << "\"Events\": ";

            vector<Event> sk = nguoiTham[demVisitor].getEvents();
            for(Event n : sk)
            {
                outFile << '(';
                vector<double> vt = n.getIntensity();
                for(int m = 0; m < vt.size();m++)
                {
                    outFile << vt[m] << ' ';
                }
                outFile << ") - " << "\"Time\": " << n.getTime() << ' ';
            }
            outFile << "}," << endl;

            demVisitor++;
        }
        else
        {
            outFile << "{ \"Type\": \"Personel\" , \"ID\": " << bacSi[demPersonel].getID() << "," << "\"Age\": " << bacSi[demPersonel].getAge() << ' ';
            outFile << "\"Journey\": ";
            vector<Ward> cacWard = bacSi[demPersonel].getJourney();
            for(auto a : cacWard)
            {
                outFile << a.getName() << ' ';
            }
            outFile << ',' << "\"Events\": ";

            vector<Event> sk = bacSi[demPersonel].getEvents();
            for(Event n : sk)
            {
                outFile << '(';
                vector<double> vt = n.getIntensity();
                for(int m = 0; m < vt.size();m++)
                {
                    outFile << vt[m] << ' ';
                }
                outFile << ") - " << "\"Time\": " << n.getTime() << ' ';
            }
            outFile << "}," << endl;
            
            demPersonel++;
        }

    }
}