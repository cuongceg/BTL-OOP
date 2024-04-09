/*Bài 4 thực hiện nhiệm vụ
- nhận đầu vào là:
+ i) mảng các Ward.
+ ii) triple:Số lượng các mảng có 3 phần tử của Ward
+ iii) single: Số lượng các mảng có 1 phần tử của Ward
- Đầu ra 1 vector<pair<Ward,int>> sao cho
+ Tổng các giá trị int của pair bằng đúng triple*3 + single
+ Các int của pair tuân theo phân phối chuẩn
- Chú ý trả về lỗi nếu tổng triple và single không bằng numOfAgents
(tùy chọn bài 2)
*/
#ifndef BAI4_HPP
#define BAI4_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "doc_json.hpp"
#include "docfileTXT.hpp"
#include "lop.hpp"
using namespace std;

double rand_normal(double mean, double stddev)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(mean, stddev);
    double output = dist(gen);
    return output;
}
//triple - số đối tượng phải đi qua 3 khoa
//single - số đối tượng đi qua 1 khoa
vector<pair<Ward,int>> bai4(vector<Ward>& input,int triple,int single)
{
    
    vector<pair<Ward,int>> result;

    int numOfAgents = get_numOfAgents();//Tổng số người trong bệnh viện
    if(numOfAgents == -1)
    {
        cerr << "numOfAgents lỗi!\n" << endl;
        return result;
    }

    //Tổng số người đầu vào
    int sum = triple + single;
    //Kiểm tra dữ liệu
    if(sum != numOfAgents)
    {
        cout << "Lỗi!"<<'\n';
        return result;
    }

    //Số lượng khoa
    int sLuongWard = input.size();
    //Tổng số lượt đi qua các khoa/viện
    int total_value = triple*3 + single;
    int min_value = 0;//Giá trị nhỏ nhất có thể
    double mean = total_value/sLuongWard;//trung bình
    double std = 3;//độ lệch chuẩn
    
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

#endif