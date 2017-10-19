#include <iostream>
#include "marker.h"
#include "markerarray.h"


Marker input_info(){
    //input ID
    long int n_id;
    string str;
    cout<<"Input ID"<<endl;
    bool is_right = false;
    while (!is_right){
        cin >> str;
        try
        {
            n_id = stoi(str);
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
    return Marker(n_id, n_x, n_y, n_z, 0);
}

#include <fstream>

int main()
{
    MarkerArray ar(3);

    for (int i = 0; i < ar.size(); i++)
        ar.setValue(i, Marker(i, (i+1)*2, 12*i, 21, 1));
    ar.toFile("out.txt");
    MarkerArray q;
    cout<< ar.size()<<endl;
    q.getArray("out.txt");
    cout<< q.size()<<endl;
    for (int i = 0; i < q.size(); i++)
        q.at(i).show();
    q.remove(2);
    cout<< q.size()<<endl;
    for (int i = 0; i < q.size(); i++)
        q.at(i).show();
}
