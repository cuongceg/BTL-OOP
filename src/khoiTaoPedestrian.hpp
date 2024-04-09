#ifndef KHOITAOPEDESTRIAN
#define KHOITAOPEDESTRIAN
#include <iostream>
#include <random>
#include "lop.hpp"
#include "doc_json.hpp"
#include "docfileTXT.hpp"
using namespace std;

int randomnumber(int min,int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min,max);
    int random_number = dis(gen);
    return random_number;
}

Personality xacDinhNguongCamXuc(int numLoaiCamXuc[2],const vector<Personality>& inputNguongCamXuc,const int numOfAgents)
{
    if(numLoaiCamXuc[0] == numOfAgents/2)
    {
        numLoaiCamXuc[1]++;
        return inputNguongCamXuc[1];
    }
    else if (numLoaiCamXuc[1] == numOfAgents/2)
    {
        /* code */
        numLoaiCamXuc[0]++;
        return inputNguongCamXuc[0];
    }
    else
    {
         //Random kiểu tính cách với 0-open, 1-Neurotic
        int x = randomnumber(0,1);
        numLoaiCamXuc[x]++;
        return inputNguongCamXuc[x];
    } 
}

obJect khoitaodoituong()
{
    /*Số lượng của mỗi kiểu di chuyển của đối tượng 
    noDisabilityNoOvertaking = 0,//Không khuyết tật,không vượt
    noDisabilityOvertaking = 1,//Không khuyết tật,vượt
    crutches = 2,//Di chuyển bằng nạng
    sticks = 3,//Di chuyển bằng gậy
    wheelchairs = 4,//Di chuyển bằng xe lăn
    blind = 5//Dị mù
    */
    vector<int> soLudiChuyen = layDulieumoiLoaiDichuyen();
    //Tuổi của các Object
    vector<double> ageObject = layTuoi();
    // // //Thời gian sự kiện tác dộng của sự kiện dối với từng Object
    // vector<vector<int>> timeAllObject = timeEvents();
     //Các thông số của khoa/viện
    std::pair<vector<Ward>,A> inputWard = mapWard();

    //Số lượng đối tượng
    int M = get_numOfAgents();
    cout << "M:" << M <<'\n'; 
    // //Ngưỡng cảm xúc tính cưc/tiêu cực 0-open, 1-neurotic,2-heuristic
    vector<Personality> inputNguongCamXuc = nguongCamxuc();
    // //tốc độ của từng kiểu di chuyển 
    vector<speedWalkability> inputSpeed = getSpeedWalkability(); 

    // //Tổng noDisability
    int sumNoDisability = soLudiChuyen[0] + soLudiChuyen[1];
    
    //Lưu trữ tất cả dối tượng
    vector<Patitent>  nguoibenh;
    vector<Visitor> nguoiTham;
    vector<Personel> bacSi;

    int numPatient = 0;//Số người bệnh nhân
    int numVisitor = 0;//Số người đến thăm
    int numPersonel = 0;//Số người bác sĩ   

    // //Lưu trữ số lượng đối tượng thuộc từng loại cảm xúc
    int numLoaiCamXuc[2] = {0,0};
    //đối tượng tuổi < 11
    vector<int> age11;
    for(int i = 0; i < ageObject.size();i++)
    {
        if(ageObject[i] < 11.0)
        {
            age11.push_back(i);
            cout << i << ' ';
        }
    }
    cout << '\n';
    // //Khởi tạo các đối tượng có tuổi < 11
    for(int i = 0; i < age11.size();i++)
    {
        //0 - Patient,1-Visitor
        int x = randomnumber(0,1);
        switch (x)
        {
            case 0:
            {
                Patitent object;
                object.setID(age11[i]);//Thiết lặp ID
                object.setAge(ageObject[age11[i]]);//Thiết lặp tuổi
                object.setValues(3);//Số lượng khóa/viện cần đi qua
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                //Nhỏ hơn 11 tuổi chỉ có cảm xúc open
                if(numLoaiCamXuc[0] < (M/2))
                {
                    object.setPersonality(inputNguongCamXuc[0]);
                    numLoaiCamXuc[0]++;
                }    
                else
                {
                    cout << "Đầu vào vô lí!\n";
                }        

                //Thiết lặp tốc độ di chuyển  
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numPatient++;
                nguoibenh.push_back(object);
                break;
            }
            case 1:
            {
                Visitor object;
                object.setID(age11[i]);//Thiết lặp ID
                object.setAge(ageObject[age11[i]]);//Thiết lặp tuổi
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                if(numLoaiCamXuc[0] < (M/2))
                {
                    //Xác định ngưỡng cảm xúc open cho đối tượng < 11 tuổi
                    object.setPersonality(inputNguongCamXuc[0]);
                    numLoaiCamXuc[0]++;
                }
                else
                {
                    cout << "Đầu vào vô lí!\n";
                }
                //Xác định kiểu di chuyển và vận tốc
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numVisitor++;
                nguoiTham.push_back(object);
                break;
            }
            default:
            {
                std::cerr << "Lỗi random!" << endl;
            }

        }
    }
    for(int k = 0;k < M;k++)
    {
        //Kiểu đối tượng
        int rd = 0;
        if(ageObject[k] < 11)
        {
            continue;
        }
        //Personel- bác sĩ không thể có tuổi < 23 hoặc > 63
        else if(ageObject[k] < 23.0 || ageObject[k] > 63.0)
        {
            rd = randomnumber(0,1);
        }
        //Đảm bảo điều kiện số Personel bé hơn noDisability
        else if(sumNoDisability == numPersonel + 1)
        {
            rd = randomnumber(0,1);
        }
        else
        {
            rd = randomnumber(0,2);
        }
        switch (rd)
        {
            //Xử lí dữ liệu với Patient- bệnh nhân
            case 0:
            {
                Patitent object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(3);//Số lượng khóa/viện cần đi qua
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numPatient++;
                nguoibenh.push_back(object);
                break;
            }
            //Xử lí với Visitol
            case 1:
            {
                Visitor object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(1);//Số lượng khoa/viện cần đi qua
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                //Xác định ngưỡng cảm xúc
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                bool speedTest = false;
                while(!speedTest)
                {
                    int speed = randomnumber(0,5);
                    if(soLudiChuyen[speed] > 0)
                    {
                        Walkability typeWalk{static_cast<Walkability>(speed)};
                        object.setWalkability(typeWalk);
                        object.setVelocity(inputSpeed[speed].velocity);
                        soLudiChuyen[speed]--;
                        speedTest = true;
                    }
                }
                numVisitor++;
                nguoiTham.push_back(object);
                break;
            }
        //Khởi tạo bác sĩ - Personel
            case 2:
            {
                Personel object;
                object.setID(k);//Thiết lặp ID
                object.setAge(ageObject[k]);//Thiết lặp tuổi
                object.setValues(3);
                //Khởi tạo Ward start
                object.setStart(inputWard.second);
                //Khởi tạo điểm kết thúc
                object.setEnd(inputWard.second);
                //Xác định ngưỡng cảm xúc
                object.setPersonality(xacDinhNguongCamXuc(numLoaiCamXuc,inputNguongCamXuc,M));
                //Kiểu di chuyển 
                numVisitor++;
                bacSi.push_back(object);
                break;
            }
            default:
            {
                cout << "Lỗi random.\n";
                break;
            }
        }
    }
    //lưu giữ các đối tượng theo từng loại
    obJect doiTuong;
    doiTuong.setPatient(nguoibenh);
    doiTuong.setVisitor(nguoiTham);
    doiTuong.setPersonel(bacSi);
    return doiTuong;
}

#endif