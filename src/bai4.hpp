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
#include "lop.hpp"
using namespace std;

vector<pair<Ward,int>> bai4(vector<Ward> input,int triple,int single)
{
    //triple số lượng người phải di chuyển đến 3 Ward
    //single số lượng người chỉ cần đến 1 khoa/viện Ward
    vector<pair<Ward,int>> result;

    //Tổng số người trong bệnh viện
    int numOfAgents = get_numOfAgents();
    if(numOfAgents == -1)
    {
        cerr << "numOfAgents value could not be obtained" << endl;
        return result;
    }

    //Tổng số người đầu vào
    int sum = triple +single;
    if(sum != numOfAgents)
    {
        cout << "Lỗi!"<<'\n';
        return result;
    }

    //Tổng số lượt đi qua các khoa/viện
    int total_value = triple*3 + single;
    //Khởi tạo số ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());
    //Các tham số của phân phối chuẩn
    int min_value = 0;//Giá trị nhỏ nhất có thể
    float mean = (min_value + total_value)/2;
    float std = (total_value - min_value)/6;
    //Cài đặt phân phối chuẩn
    normal_distribution<float> dist(std,mean);

    //Tổng của các giá trị đã sinh ngẫu nhiên
    int current_sum = 0;
    for(int i = 0; i < input.size();i++)
    {
        if(total_value > 0)
        {
            int x = 0;
            do
            {
                //Sinh ngẫu nhiên giá trị x
                x = dist(gen);
            } while (x < 0 && x + current_sum > total_value);
            x = static_cast<int>(round(x));
            current_sum += x;
            result.push_back(pair(input[i],x));
            continue;
        }
        else if(i = input.size() -1  && current_sum != total_value)
        {
            result.push_back(pair(input[i],total_value - current_sum));
        }
        else
        {
            //Tổng các giá trị đã bằng tổng
            result.push_back(pair(input[i],0));
        }
    }
    return result;
}


 #endif