#ifndef LOP
#define LOP

#include <vector>
using namespace std;

class Point
{
    private:
        double x;
        double y;
    public:
        Point(double x,double y)
        {
            this->x = x;
            this->y = y;
        }
        Point(){}

        double getX(){return this->x;}
        double getY(){return this->y;}

        void setX(double x){this->x = x;}
        void setY(double y){this->y = y;}   
};

class Ward
{
    protected:
        //Tên khoa viện
        string name;
        //Các cạnh viền của khoa/viện
        vector<pair<Point,Point>> wallCoordinates;
        //Chiều ngang khoa/viện
        double width;
    private:
        //ĐIểm đầu vào khoa viện
        Point entrance;
        //Điểm ra của khoa/viện
        Point exit;
    public:
        Ward(string name,Point entrance,Point exit,vector<pair<Point,Point>> wallCoordinates)
        {
            this->name = name;
            this->entrance = entrance;
            this->exit = exit;
            this->wallCoordinates = wallCoordinates;
        }
        Ward(){}

        string getName(){return this->name;}
        Point getEntrance(){return this->entrance;}
        Point getExit(){return this->exit;}
        double getWight(){return this->width;}
        vector<pair<Point,Point>> getWallCoordinates(){return this->wallCoordinates;}

        void setName(string name){this->name = name;}
        void setEntrance(Point entrance){this->entrance = entrance;}
        void setExit(Point exit){this->exit = exit;}
        void setWidth(double width){this->width = width;}
        void setWallCoordinates(vector<pair<Point,Point>>& wallCoordinates){this->wallCoordinates = wallCoordinates;}
};
class A : public Ward
{
    private:
        //Có 2 điểm đầu vào
        vector<Point> entrance;
        //Có 2 điểm đầu ra
        vector<Point> exit;
    public:
        void setEntrance(vector<Point>& entrance){this->entrance = entrance;}
        void setExit(vector<Point>& exit){this->exit = exit;}

};



// enum chứa các kiểu di chuyển của con người trên hành lang
enum Walkability
{
    
    noDisabilityNoOvertaking = 0,//Không khuyết tật,không vượt
    noDisabilityOvertaking = 1,//Không khuyết tật,vượt
    crutches = 2,//Di chuyển bằng nạng
    sticks = 3,//Di chuyển bằng gậy
    wheelchairs = 4,//Di chuyển bằng xe lăn
    blind = 5//Dị mù
};

//Lớp chứa 6 cảm xúc của con người
class Emotion
{
    private:
        
        double pleasure = 0.75;//vui
        double surprise = 0.5;//bất ngờ
        double anger = -0.2;//tức giận
        double fear = -0.2;//sợ
        double hate = -0.4;//ghét
        double sad = -0.4;//buồn
    public:
        Emotion(double pleasure,double surprise,double anger,double fear,double hate,double sad)
        {
            this->pleasure = pleasure;
            this->surprise = surprise;
            this->anger = anger;
            this->fear = fear;
            this->hate = hate;
            this->sad = sad;
        }
        Emotion(){}

        double getPleasure(){return this-> pleasure;}
        double getSurprise(){return this->surprise;}
        double getAnger(){return this->anger;}
        double getFear(){return this->fear;}
        double getHate(){return this->hate;}
        double getSad(){return this->sad;}

        void setPleasure(double pleasure){this-> pleasure = pleasure;}
        void settSurprise(double surprise){this->surprise = surprise;}
        void setAnger(double anger){this->anger = anger;}
        void setFear(double fear){this->fear = fear;}
        void setHate(double hate){this->hate = hate;}
        void setSad(double sad){this->sad= sad;}
};

class Event
{
    private:
        //dữ liệu sinh ra trong câu i) bài 2
        //mỗi sự kiện tác dộng 6 cảm xúc của con người
        vector<double> intensity;
        //Thời điểm bắt đầu xảy ra sự kiện đó
        double time;
    public:
        Event(vector<double> intensity,double time)
        {
            this->intensity = intensity;
            this->time = time;
        }
        Event(){}

        vector<double> getIntensity(){return this->intensity;}
        double getTime(){return this->time;}

        void setIntensity(vector<double> intensity){this->intensity = intensity;}
        void addIntensity(double events){this->intensity.push_back(events);}
        void setTime(double time){this->time = time;}
};

//sự kiện AGV tác động lên con người
class AGVEvent : public Event
{

};

//đọc từ đầu vào
class Personality
{
    private:
        double lambda;
        double positiveEmotionThreshold;//Ngưỡng cảm xúc tích cực
        double negativeEmotionThreshold;//Ngưỡng cảm xúc tiêu cực
    public:
        Personality(double lambda,double positiveEmotionThreshold,double negativeEmotionThreshold)
        {
            this->lambda = lambda;
            this->positiveEmotionThreshold = positiveEmotionThreshold;
            this->negativeEmotionThreshold = negativeEmotionThreshold;
        }
        Personality(){}

        double getLambda(){return this->lambda;}
        double getPositiveEmotionThreshold(){return this->positiveEmotionThreshold;}
        double getNegativeEmotionThreshold(){return this->negativeEmotionThreshold;}

        void setLambda(double lambda){this->lambda = lambda;}
        void setPositiveEmotionThreshold(double positiveEmotionThreshold){this->positiveEmotionThreshold = positiveEmotionThreshold;}
        void setNegativeEmotionThreshold(double negativeEmotionThreshold){this->negativeEmotionThreshold = negativeEmotionThreshold;}
};


class Pedestrian
{
    protected:
        int ID;//ID của người
        Ward start;//Khoa bắt đầu 
        Ward end;//Khoa kết thúc
        vector<Ward> journey;//Danh sách các khoa đi qua
        double velocity;//Vạn tốc
        Personality personality;//ngưỡng cảm xúc
        Emotion emotion;//dữ liệu từng loại cảm xúc
        vector<Event> events;//các sự kiện tác động
        double walkingTime;//Thời gian di chuyển
        int values;//Số lượng các khoa/viện cần đến;
        double distance;
        double age;//Tuổi
        AGVEvent impactOfAGV;
        Point tempPoints;
    public:
        Pedestrian(int ID,Ward start,Ward end,vector<Ward> journey,double velocity,Personality personality,Emotion emotion,
        vector<Event> events,double walkingTime,int values,double distance,double age,AGVEvent impactOfAGV,Point tempPoints)
        {
            this->ID = ID;
            this->start = start;
            this->end = end;
            this->journey = journey;
            this->velocity = velocity;
            this->personality = personality;
            this->emotion = emotion;
            this->events = events;
            this->walkingTime = walkingTime;
            this->values = values;
            this->distance = distance;
            this->age = age;
            this-> impactOfAGV = impactOfAGV;
            this->tempPoints = tempPoints;

        }
        Pedestrian(){}

        int getValues(){return this->values;}
        int getID() { return this->ID; }
        Ward getStart() { return this->start; }
        Ward getEnd() { return this->end; }
        std::vector<Ward> getJourney() { return this->journey; }
        double getVelocity() { return this->velocity; }
        Personality getPersonality() { return this->personality; }
        Emotion getEmotion() { return this->emotion; }
        std::vector<Event> getEvents() { return this->events; }
        double getWalkingTime() { return this->walkingTime; }
        double getDistance() { return this->distance; }
        double getAge() { return this->age; }
        AGVEvent getImpactOfAGV() { return this->impactOfAGV; }
        Point getTempPoints() { return this->tempPoints; }

        void setValues(int values){this->values = values;}
        void setID(int ID) { this->ID = ID; }
        void setStart(Ward start) { this->start = start; }
        void setEnd(Ward end) { this->end = end; }
        void setJourney(std::vector<Ward>& journey) { this->journey = journey; }
        void setVelocity(double velocity) { this->velocity = velocity; }
        void setPersonality(Personality Personality) { this->personality = personality; }
        void setEmotion(Emotion emotion) { this->emotion = emotion; }
        void setEvents(std::vector<Event>& events) { this->events = events; }
        void setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }
        void setDistance(double distance) { this->distance = distance; }
        void setAge(double age) { this->age = age; }
        void setImpactOfAGV(AGVEvent impactOfAGV) { this->impactOfAGV = impactOfAGV; }
        void setTempPoints(Point temPoints) { this->tempPoints = tempPoints; }
};


//Lớp bệnh nhân
class Patitent : public Pedestrian
{
    private:
        //Cho biết kiểu di chuyển của người bệnh
        enum Walkability walkability;
    public:
        Walkability getWalkability(){return this->walkability;}
        void setWalkability(Walkability walkability){this->walkability = walkability;}
        Patitent(){}
};

//Lớp người thăm
class Visitor : public Pedestrian
{
    private:
        //Kiểu di chuyển của người thăm
        enum Walkability walkability;
    public:
        Walkability getWalkability(){return this->walkability;}
        void setWalkability(Walkability walkability){this->walkability = walkability;}
};

//lớp bác sĩ
class Personel : public Pedestrian
{
};

class obJect
{
    private:
        vector<Patitent> nguoiBenh;
        vector<Visitor> nguoiTham;
        vector<Personel> bacSi;
    public:
        vector<Patitent> getPatitent(){return this->nguoiBenh;}
        vector<Visitor>  getVisitor(){return this->nguoiTham;}
        vector<Personel> getPersonel(){return this->bacSi;}

        void setPatient(vector<Patitent> nguoiBenh){this->nguoiBenh = nguoiBenh;}
        void setVisitor(vector<Visitor> nguoiTham){this->nguoiTham = nguoiTham;}
        void setPersonel(vector<Personel> bacSi){this->bacSi = bacSi;}
        

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


class speedWalkability
{
    public:
        //Mô tả loại di chuyển
        string description;
        //Tốc độ di chuyển
        float velocity;
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
                Ward start;//Khoa khởi hành
                Ward end;//Khoa đích
        };
        //Số khoa/viện bệnh nhân đến tham
        typeObject forPatient;
        //Số khoa/viện mà khách ghé thăm
        typeObject forVisitor;
        //Số khoa/viện bác sĩ ghé thăm
        typeObject forPesonel;
        
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