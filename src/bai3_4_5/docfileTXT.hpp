#ifndef DOCFILETXT
#define DOCFILETXT
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "lop.hpp"
#include "doc_json.hpp"

std::vector<int> layDulieumoiLoaiDichuyen()
{
    std::string filename = "outputMoiLoaiDiChuyen.txt";
    std::ifstream file(filename);
    std::vector<int> soLuong;

    //Kiểm tra có mở tệp thành công hay không
    if(!file.is_open())
    {
        std::cerr << "Mở file không thành công" << std::endl;
        return soLuong;
    }

    //Tổng số lượng các Pedestrian
    int sum;
    std::string line;
    std::getline(file,line);
    std::stringstream ss(line);
    ss >> sum;  
    // std::cout << "numOfAgents: " << sum << endl;
    //Kiểm tra tổng các giá trị sinh ra có thỏa mãn đầu vào không
    if(sum != get_numOfAgents())
    {
        std::cout << "Du lieu chua thoa man numOfAgents.\nTạo lại dữ liệu." << endl;
        return soLuong;
    }

    //Lấy số lượng từng loại di chuyển
    while(std::getline(file,line))
    {
        std::stringstream ss(line);
        int num;
        while(ss >> num)
        {
            soLuong.push_back(num);
        }
    }
    file.close();
    cout << "Gọi thành công layDulieumoiLoaiDichuyen()!" << endl;
    return soLuong;
}
std::vector<double> layTuoi()
{
    std::vector<double> tuoi;
    std::string filename = "outputTuoi.txt";
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Không mở được file!" << endl;
    }
    std::string line;
    while(std::getline(file,line))
    {
        //Chyển dữ liệu
        double num = stod(line);
        tuoi.push_back(num);
    }
    file.close();
    cout << "Gọi thành công layTuoi()!" << endl;
    return tuoi;
}

std::vector<Event> eventTacDong()
{
    std::vector<Event> sukien;
    std::string filename = "outputTacDongSuKien.txt";
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Không mở được file!" << endl;
    }
    std::string line;
    while(std::getline(file,line))
    {
        std::stringstream ss(line);
        std::vector<double> thongso;
        double num;
        while(ss >> num)
        {
            thongso.push_back(num);
        }
        Event ev;
        ev.setIntensity(thongso);
        sukien.push_back(ev);
    }
    cout << "Gọi thành công eventTacDong()!" << endl;
    return sukien;
}

std::vector<std::vector<int>> timeEvents()
{
    std::vector<std::vector<int>> timeAllObject;
    std::string filename = "outputTimeEvents.txt";
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Không mở thành công file!" <<'\n';
        return timeAllObject;
    }
    std::string line;
    while(std::getline(file,line))
    {
        std::stringstream ss(line);
        std::vector<int> timeOneObject;
        double num;
        while (ss >> num)
        {
            timeOneObject.push_back(num);
        }
        timeAllObject.push_back(timeOneObject);
    }
    cout << "Gọi thành công timeEvents()!" << endl;
    return timeAllObject;
}

std::pair<vector<Ward>,A> mapWard()
{
    pair<vector<Ward>,A> input;
    vector<Ward> khacA;
    std::string filename = "hospital.txt";
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Mở file không thành công!" << std::endl;
        return input;
    }
    std::string line;
    int soKhoa;
    std::getline(file,line);
    std::istringstream ss(line);
    ss >> soKhoa;
    for(int i = 0; i < soKhoa;i++)
    {
        std::getline(file,line);
        std::istringstream iss(line);
        Point entrance;
        Point exit;
        double x1,y1;
        double x2,y2;
        double num;
        double width;
        string name;
        iss >> x1 >> y1 >> x2 >> y2 >> width >> name;
        entrance.setX(x1);
        entrance.setY(y1);
        exit.setX(x2);
        exit.setY(y2);
        Ward khoa;
        khoa.setWidth(width);
        khoa.setEntrance(entrance);
        khoa.setExit(exit);
        khoa.setName(name);
        khacA.push_back(khoa);
    }
    std::getline(file,line);
    std::istringstream aa(line);
    std::string name = "A";
    vector<Point> entrance;
    vector<Point> exit;
    double x1,y1,x2,y2;
    aa >> x1 >> y1 >> x2 >> y2;
    Point diem1(x1,y1);
    Point diem2(x2,y2);
    entrance.push_back(diem1);
    entrance.push_back(diem2);
    aa >> x1 >> y1 >> x2 >> y2;
    Point diem3(x1,y1);
    Point diem4(x2,y2);
    exit.push_back(diem3);
    exit.push_back(diem4);
    A a;
    a.setEntrance(entrance);
    a.setExit(exit);
    input.first = khacA;
    input.second = a;
    cout << "Gọi thành công mapWard()!" << endl;
    return input;
}
#endif 