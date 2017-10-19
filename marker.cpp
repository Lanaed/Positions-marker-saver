#include "marker.h"

Marker::Marker(){
    id = 0;
    Position p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    p.vis = is_visible(0, 0, 0);
    p.time = 0;
    track.push_back(p);
}

Marker::Marker(unsigned int num, double x1, double y1, double z1, unsigned int time) {
    id = num;
    Position p;
    p.x = x1;
    p.y = y1;
    p.z = z1;
    p.vis = is_visible(x1, y1, z1);
    p.time = time;
    track.push_back(p);
}
Marker::Marker(unsigned int num, vector<Position> tr)
{
    id = num;
    track = tr;
}


Marker::Marker(const Marker &obj){
    id = obj.id;
    track = obj.track;
}

vector<Position> Marker::get_track(){
    return track;
}

void Marker::show(){
    cout <<"ID of marker: "<< id <<endl;
    for (int i = 0; i < track.size(); i++)
    {
        cout <<"Position num. "<<i+1<<endl;
        cout <<"Visibillity: "<<boolalpha <<track[i].vis<<endl;
        if (track[i].vis){
            cout <<"X:"<< track[i].x << endl;
            cout <<"Y:"<< track[i].y << endl;
            cout <<"Z:"<< track[i].z << endl;
        }
    }
}
unsigned int Marker::get_id()
{
    return id;
}

bool Marker::is_visible(double x, double y, double z) {
    return (x >=0 && x <= Mx && y >=0 && y<=My && z >=0 && z<=Mz);
}
