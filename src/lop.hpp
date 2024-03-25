#ifndef LOP
#define LOP

#include <iostream>
#include <vector>
using namespace std;

class Point
{
    public:
        double x;
        double y;
};

class Ward
{
    public:
        //Tên khoa viện
        char name;

        //ĐIểm đầu vào khoa viện
        Point entrance;
        //Điểm ra của khoa/viện
        Point exit;

        //Các cạnh viền của khoa/viện
        vector<pair<Point,Point>> wallCoordinates;
};


// enum chứa các kiểu di chuyển của con người trên hành lang
enum Walkability
{
    noDisability,//Không khuyết tật
    crutches,//Di chuyển bằng nạng
    sticks,//Di chuyển bằng gậy
    wheelchairs,//Di chuyển bằng xe lăn
    blind//Dị mù
};

//Lớp chứa 6 cảm xúc của con người
class Emotion
{
    public:
        
        double pleasure = 0.75;//vui
        double surprise = 0.5;//bất ngờ
        double anger = -0.2;//tức giận
        double fear = -0.2;//sợ
        double hate = -0.4;//ghét
        double sad = -0.4;//buồn

};

class Event
{
    public:
        //dữ liệu sinh ra trong câu i) bài 2
        //mỗi sự kiện tác dộng 6 cảm xúc của con người
        vector<double> intensity;
        //Thời điểm bắt đầu xảy ra sự kiện đó
        double time;
};

//sự kiện AGV tác động lên con người
class AGVEvent : public Event
{

};

//đọc từ đầu vào
class Personality
{
    public:
        double lambda;
        double positiveEmotionThreshold;//Ngưỡng cảm xúc tích cực
        double negativeEmotionThreshold;//Ngưỡng cảm xúc tiêu cực
};


class Pedestrian
{
    public:
        int ID;//ID của người
        Ward start;//Khoa bắt đầu 
        Ward end;//Khoa kết thúc
        vector<Ward> journey;//Danh sách các khoa đi qua
        double velocity;//Vạn tốc
        Personality personality;//ngưỡng cảm xúc
        Emotion emotion;//dữ liệu từng loại cảm xúc
        vector<Event> events;//các sự kiện tác động 
        double walkingTime;//Thười gian di chuyển
        double distance;
        double age;//Tuổi
        AGVEvent impactOfAGV;
        Point tempPoints;
        
};



class Patitent : public Pedestrian
{
    public:
        //Cho biết kiểu di chuyển của người bệnh
        enum Walkability walkability;
};
class Visitor : public Pedestrian
{
    public:
        //Kiểu di chuyển của người thăm
        enum Walkability walkability;
};
class Personel : public Pedestrian
{
};







//Các lớp dữ liệu đọc

//Chế dộ chạy
class runMode
{
    public:
        int value;//giá trị đại diện ctr chấp nhận file hospital.txt
};

//Sinh ngẫu nhiên/nạp dữ liệu có sẵn
class randomness
{
    public:
        string description;
        //'1': Đại diện cho tạo ra giá trị ngẫu nhiên mới 
        //'0': chương trình nạp từ các dữ liệu có sẵn
        bool value;
};

//Độ tuổi của người di chuyển trên hành lang
class ageDistribution
{
    public:
        string description;
        int samples;//Đọc giá trị của numOfAgents
        int numberOfValues;
        int minValue;//Độ tuổi nhỏ nhất
        int maxValue;//Độ tuổi lớn nhất

        vector<float> ageInput;
};


class walkability
{
    public:
        
        //Lớp lưu trữ các dữ liệu của từng loại hình di chuyển
        class tyMove
        {
            public:
                //Mô tả loại di chuyển
                string description;
                //Tốc độ di chuyển
                float velocity;

        };
        class normal
        {
            public:
                string description ;//Mô tả
                int samples;//6 nhóm di chuyển
                int sumOfValues;//tổng số người trong 6 nhóm = numOfAgents
                int lowerBound;//Không có nhóm nào dưới
                int upperBound;//Không có nhóm nào vượt quá
        };

        //Miêu tả dữ liệu
        string description;

        // lưu trữ dữ liệu các loại di chuyển
        tyMove noDisabilityNoOvertaking;//Không khuyết tật và ko vượt
        tyMove noDisabilityOvertaking;//Không khuyết tật và có vượt
        tyMove crutches;//đi bằng nạng
        tyMove sticks;//Đi bằng gậy
        tyMove wheelchairs;//Di chuyển bằng xe lăn
        tyMove blind;//Người mù
        
        
        
        //Biến số người di chuyển theo loại hình này
         normal Normal;
};

//Số khoa/viện đến thăm theo loại đối tượng 
class journeyDistribution
{
    public:

        //Lớp lưu trữ thông tin về từng loại đối tượng di chuyển
        class typeObject
        {
            public:
                string description;
                int value;//số khoa/viện đi qua
                char start;//Khoa khởi hành
                char end;//Khoa đích
        };
        class personel : public typeObject
        {
            public:
                //Ngưỡng mà số nhân viên y tế phải bé hơn số người noDisability
                int threshold;
        };
        //Số khoa/viện bệnh nhân đến tham
        typeObject forPatient;
        //Số khoa/viện mà khách ghé thăm
        typeObject forVisitor;
        //Số khoa/viện 
        
};

//Phân chia khoa viện theo chức năng
class warDistribution
{
    public:
        string description;
        class department
        {
            public:
                //Mô tả chức năng của khoa
                string description;
        };
        class normal
        {
            public:
                string description;//mô tả
                int samples;
                int sumOfValues;
                int lowerBound;
                int upperBound;
        };
};


//Lớp lưu trữ đặc tính các loại cảm xúc
class personalityDistribution
{
    public:
        string description;//Mô tả
        class character
        {
            public:
                string description;//Mô tả tính cách

                //Ngưỡng cảm xúc tích cực
                float positiveEmotionThreshold;

                //Ngưỡng cảm xúc tiêu cực
                float negativeEmotionThreshold; 

                //phần trắm
                int percentage;
                int lambda;
        };
};

//Thời gian ở trong khoa/viện của mỗi người
class insideTimeDistribution
{
    public:
        //Mô tả
        string description;

        class uniform
        {
            public:
                string description;
                int value;
        };

        //Thời gian ở mỗi khoa/viện chung
        uniform uniform;
};

//

#endif