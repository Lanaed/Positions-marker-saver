#include "markerarray.h"
#include <cstring>
#include <fstream>

MarkerArray::MarkerArray()
{
    _elementsCount = 0;
    _base = NULL;
}

MarkerArray::MarkerArray(unsigned int elementsCount)
{
    _elementsCount = elementsCount;
    _base = new Marker[elementsCount];
}

Marker MarkerArray::at(unsigned int position)
{
    return _base[position];
}

void MarkerArray::setValue(unsigned int position, Marker value)
{
    _base[position] = value;
}

void MarkerArray::resize(unsigned int size)
{
    Marker* _old_base = _base;
    _base = new Marker[size];
    for (int i = 0; i < size - 1; i++)
        _base[i] = _old_base[i];
    _elementsCount = size;
}
void MarkerArray::remove(unsigned int position)
{
    std::copy(_base + position,
              _base + _elementsCount - 1,
              _base + position - 1);
    _elementsCount--;
}

void MarkerArray::append(Marker value)
{
    resize(_elementsCount + 1);
    std::cout << "Adding Value" << std::endl;
    _base[_elementsCount - 1] = value;
}

bool MarkerArray::isEmpty()
{
    return _elementsCount == 0;
}

void MarkerArray::getArray(string filepath)
{
    ifstream inputFile;
    _elementsCount = 0;
    inputFile.open(filepath, std::ios::in);
    //inputFile >> _elementsCount;
    //resize(_elementsCount);
    while (true)
    {
        int id;
        int trackSize;
        inputFile >> id >> trackSize;
        if (inputFile.eof())
            break;
        vector<Position> track;
        for (int i = 0; i < trackSize; i++)
        {
            int x,y,z, time;
            bool vis;
            inputFile >> x >> y >> z >> time;// >> vis;

            Position p;
            p.x = x;
            p.y = y;
            p.z = z;
            p.time = time;
            //p.vis = vis;
            track.push_back(p);
        }
        //std::cout << "Here with " << track[0].x << " " << track[0].y << " " << track[0].z << std::endl;
        append(Marker(id, track[0].x, track[0].y, track[0].z, track[0].time));
    }
}

void MarkerArray::toFile(string filepath)
{
    ofstream outFile;
    outFile.open(filepath, std::ios::out);
    //outFile << _elementsCount << " ";
    for (int i = 0; i < _elementsCount; i++)
    {
        outFile << at(i).get_id() << " ";
        outFile << at(i).get_track().size() << " ";
        for (int j = 0; j < at(i).get_track().size(); j++)
            outFile << at(i).get_track()[j].x << " " << at(i).get_track()[j].y << " "
                    << at(i).get_track()[j].z << " " << at(i).get_track()[j].time<<" ";
                    //<< " " << at(i).get_track()[j].vis << " ";
    }

}

unsigned int MarkerArray::size()
{
    return _elementsCount;
}
