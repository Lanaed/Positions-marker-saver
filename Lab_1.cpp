//Лапшинова А.Э. БИВ165
//Программа фиксирует положение маркеров костюма во времени и пространстве.
//Информация: время, ID, положение в пространстве, видимость
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

//Константы для определения видимости
const double Mx = 1000, My = 1000, Mz = 1000;

//Структура для хранения позиции во времени
struct Position{
    double x, y, z;
    time_t time;
    bool vis;
};

class Marker{
public:
    Marker(unsigned int num, double x1, double y1, double z1);
    Marker();
    Marker(const Marker &obj);
    //~Marker ();
    vector<Position> get_track();
    void show();
    void show_track(vector<Position> track);
    //bool contain(unsigned int m_f_check);
private:
    unsigned int id;
    vector<Position> track;
    bool is_visible(double x, double y, double z);
};
//vector<unsigned int> Marker::ids = vector<unsigned int>();

//Конструктор
Marker::Marker(unsigned int num, double x1, double y1, double z1) {
    id = num;
    //ids.push_back(num);
    Position p;
    p.x = x1;
    p.y = y1;
    p.z = z1;
    p.vis = is_visible(x1, y1, z1);
    p.time = time(0);
    track.push_back(p);
}

//Конструктор по умолчанию
Marker::Marker(){
    id = 0;
    Position p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    p.vis = is_visible(0, 0, 0);
    p.time = time(0);
    track.push_back(p);
}

//Конструктор копирования
Marker::Marker(const Marker &obj){
    id = obj.id;
    track = obj.track;
}

vector<Position> Marker::get_track(){
    return track;
}

//Вывод трека
void Marker::show_track(vector<Position> track){
    for (int i = 0; i < track.size(); i++){
        cout <<"Position num. "<<i+1<<endl;
        if (!track[i].vis){
            cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
            cout<<"Marker is not visible"<<endl;
        }
        else {
            cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
            cout <<"X:"<< track[i].x << endl;
            cout <<"Y:"<< track[i].y << endl;
            cout <<"Z:"<< track[i].z << endl;

        }
        tm *ltm = localtime(&(track[i].time));
           cout << "Year: " << 1900 + ltm->tm_year<<endl;
           cout << "Month: "<< 1 + ltm->tm_mon<< endl;
           cout << "Day: "<< ltm->tm_mday << endl;
           cout << "Time: "<< ltm->tm_hour << ":";
           cout << ltm->tm_min << ":";
           cout << ltm->tm_sec << endl;
    }
}

/*
Marker::~Marker(){
    track.~vector<Position>();
}
*/
//Демонстарция маркера
void Marker::show(){
    cout <<"ID of marker: "<< id <<endl;
    for (int i = 0; i < track.size(); i++){
        cout <<"Position num. "<<i+1<<endl;
        if (!track[i].vis){
            cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
            cout<<"Marker is not visible"<<endl;
        }
        else {
            cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
            cout <<"X:"<< track[i].x << endl;
            cout <<"Y:"<< track[i].y << endl;
            cout <<"Z:"<< track[i].z << endl;

        }
        tm *ltm = localtime(&(track[i].time));
           cout << "Year: " << 1900 + ltm->tm_year<<endl;
           cout << "Month: "<< 1 + ltm->tm_mon<< endl;
           cout << "Day: "<< ltm->tm_mday << endl;
           cout << "Time: "<< ltm->tm_hour << ":";
           cout << ltm->tm_min << ":";
           cout << ltm->tm_sec << endl;
    }
}

//Определение видимости маркера
bool Marker::is_visible(double x, double y, double z) {
    return (x >=0 && x <= Mx && y >=0 && y<=My && z >=0 && z<=Mz);
}

//Ввод маркера
Marker input_info(){
    //input ID
    long int n_id;
    string str;
    cout<<"Input ID"<<endl;
    bool is_right = false;
    while (!is_right){
        cin>>str;
        try
        {
            n_id = std::stoi(str);
            if (n_id > 0)
                is_right = true;
        }
        catch(exception& e)
        {
            cout << "Invalid ID" <<endl;
        }
    }
    double n_x, n_y, n_z;
    //Input X
    cout<<"Input x"<<endl;
    is_right = false;
    while (!is_right){
        cin>>str;
        try
        {
            n_x = stod(str);
            if (n_x > 0)
                is_right = true;
        }
        catch(exception& e)
        {
            cout << "Invalid x" <<endl;
        }
    }
    //Input y
    cout<<"Input y"<<endl;
    is_right = false;
    while (!is_right){
        cin>>str;
        try
        {
            n_y = stod(str);
            if (n_y > 0)
                is_right = true;
        }
        catch(exception& e)
        {
            cout << "Invalid y" <<endl;
        }
    }
    //Input z
    cout<<"Input z"<<endl;
    is_right = false;
    while (!is_right){
        cin>>str;
        try
        {
            n_z = stod(str);
            if (n_z > 0)
                is_right = true;
        }
        catch(exception& e)
        {
            cout << "Invalid z" <<endl;
        }
    }
    return Marker(n_id, n_x, n_y, n_z);
}

int main()
{
    //Marker a(13, 10.5, 11.2, 12);
    //Вызов конструктора по умолчанию
    Marker a;
    a.show();
    //Вызов функции записи и конструктора
    a = input_info();
    a.show();
    cout<<endl;
    //Вызов копии маркера а
    cout<<"Copy of a in b:"<<endl;
    Marker b(a);
    b.show();
    //Вызов метода получения и демонстрации трека
    cout<<endl;
    cout<<"Track of b:"<<endl;
    b.show_track(b.get_track());
}
