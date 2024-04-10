/*Bài 5
Thiết lập danh sách các khoa đi qua cho các đối tượng
*/

#ifndef BAI5
#define BAI5

#include "khoiTaoPedestrian.hpp"
#include "bai4.hpp"
#include <map>
#include <algorithm>

//Tìm kiếm khoa có name
Ward timWardMax(string name,vector<Ward>& cackhoa)
{
    Ward a;
    for(int i = 0; i < cackhoa.size();i++)
    {
        if(cackhoa[i].getName() == name)
        {
            a = cackhoa[i];
            return a;
        }
    }
    return a;
}

void bai5(obJect& doituong)
{
    vector<Patitent> nguoiBenh = doituong.getPatitent();
    vector<Visitor> nguoiTham = doituong.getVisitor();
    vector<Personel> bacSi = doituong.getPersonel();
    
    //Số lượng đối tượng
    int M = get_numOfAgents();
    //số lượng đối tượng lớp Visitor
    int single = nguoiTham.size();
    //Số lượng đối tượng Pedestrian-single
    int triple = M - single;

    //Bản dồ bệnh viện đầu vào
    pair<vector<Ward>,A> map = mapWard();
    vector<Ward> cackhoa = map.first;

    //true - gọi lại bài 4
    bool test = false;
    do
    {
        //Thiết lập số lượt đi qua tương ứng các khoa
        vector<pair<Ward,int>>  numKhoa = bai4(map.first,triple,single);

        // map lưu trữ số lần xuất hiện của các khoa
        std::map<string,int> numWard;
        for(pair<Ward,int> a : numKhoa)
        {
            string name = a.first.getName();
            int num = a.second;
            numWard[name] += num;
        }

        vector<pair<string,int>> sapXep(numWard.begin(),numWard.end());
        int sizeWard = sapXep.size();
        //Duyệt vector Patient
        int demPatient = 0;
        //Duyệt vector Visitor
        int demVisitor = 0;
        //Duyệt vector Personel
        int demPersonel = 0;

        for(int i = 0;i < M;i++)
        {
            if(demVisitor < nguoiTham.size() && nguoiTham[demVisitor].getID() == i)
            {
                //Sắp xếp theo thứ tự giảm dần
                sort(sapXep.begin(),sapXep.end(),[](const auto& a, const auto& b) {
                                                return a.second > b.second;});
                
                //Khoa có số lượt di chuyển qua còn lại nhiều nhất
                pair<string,int> m = sapXep[0];
                string nameMax = m.first;
                //Khoa đi qua của Visitor
                Ward max = timWardMax(nameMax,cackhoa);
                vector<Ward> journey;
                journey.push_back(max);
                //Thiết lập khoa đi qua
                nguoiTham[demVisitor].setJourney(journey);

                //Giảm/tăng các giá trị
                numWard[nameMax]--;
                sapXep[0].second--;
                demVisitor++;
            }

            else if(demPatient < nguoiBenh.size() && nguoiBenh[demPatient].getID() == i)
            {
                //Sắp xếp số lầm tăng dần
                sort(sapXep.begin(),sapXep.end(),[](const auto& a, const auto& b) {
                                                    return a.second > b.second;
                                                    });

                pair<string,int> max1 = sapXep[0];
                pair<string,int> max2 = sapXep[1];
                pair<string,int> max3 = sapXep[2];
                //3 khoa có số xuất hiện nhiều nhất
                Ward maxWard1 = timWardMax(max1.first,cackhoa);
                Ward maxWard2 = timWardMax(max2.first,cackhoa);
                Ward maxWard3 = timWardMax(max3.first,cackhoa);

                vector<Ward> journey{maxWard1,maxWard2,maxWard3};
                //Thiết lập các khoa đi qua cho dối tượng
                nguoiBenh[demPatient].setJourney(journey);

                //Giảm số lượt qua các khoa
                numWard[max1.first]--;
                numWard[max2.first]--;
                numWard[max3.first]--;

                //Giảm số lượt qua các khoa
                sapXep[0].second--;
                sapXep[1].second--;
                sapXep[2].second--;
                demPatient++;
            }
            else if(demPersonel < bacSi.size() && bacSi[demPersonel].getID() == i)
            {
                //Sắp xếp số lầm tăng dần
                sort(sapXep.begin(),sapXep.end(),[](const auto& a, const auto& b) {
                                                    return a.second > b.second;
                                                    });

                pair<string,int> max1 = sapXep[0];
                pair<string,int> max2 = sapXep[1];
                pair<string,int> max3 = sapXep[2];
                //3 khoa có số xuất hiện nhiều nhất
                Ward maxWard1 = timWardMax(max1.first,cackhoa);
                Ward maxWard2 = timWardMax(max2.first,cackhoa);
                Ward maxWard3 = timWardMax(max3.first,cackhoa);

                vector<Ward> journey{maxWard1,maxWard2,maxWard3};
                //Thiết lập các khoa đi qua cho dối tượng
                bacSi[demPersonel].setJourney(journey);
                
                //Giảm số lượt qua các khoa
                numWard[max1.first]--;
                numWard[max2.first]--;
                numWard[max3.first]--;
                //Giảm số lượt qua các khoa
                sapXep[0].second--;
                sapXep[1].second--;
                sapXep[2].second--;
                demPersonel++;
            }
        }
        //Kiểm tra xem còn khoa nào còn lượt đi qua hay không
        for(auto& k : numWard)
        {
            if(k.second != 0)
            {
                //Chưa sử dụng hết
                test = true;
            }
        }
    } while (test);

    //Cập nhật các thông số của các đối tượng
    doituong.setPatient(nguoiBenh);
    doituong.setVisitor(nguoiTham);
    doituong.setPersonel(bacSi);
}

#endif