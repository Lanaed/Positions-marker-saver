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
    _base = (Marker*)malloc(_elementsCount*sizeof(Marker));
}

Marker MarkerArray::at(unsigned int position)
{
    return *(_base + sizeof(Marker)*position);
}

void MarkerArray::setValue(unsigned int position, Marker value)
{
    *(_base + sizeof(Marker)*position) = value;
}

void MarkerArray::resize(unsigned int size)
{
    _base = (Marker*)realloc(_base, size * sizeof(Marker));
    _elementsCount = size;
}
void MarkerArray::remove(unsigned int position)
{
    for (int i = position - 1; i < _elementsCount - 1; i++)
        _base[i] = _base[i + 1];

    _elementsCount -= 1;
    _base = (Marker*)realloc(_base, _elementsCount * sizeof(Marker));
}

void MarkerArray::append(Marker value)
{
    resize(_elementsCount + 1);
    _base[_elementsCount - 2] = value;
}

bool MarkerArray::isEmpty()
{
    return _elementsCount == 0;
}

void MarkerArray::getArray(string filepath)
{
    ifstream inputFile;
    inputFile.open(filepath, std::ios::in);
    inputFile >> _elementsCount;
    resize(_elementsCount);
    std::cout << "AMIGO " << _elementsCount << std::endl;
    for (int i = 0; i < _elementsCount; i++)
    {
        int id;
        int trackSize;
        inputFile >> id >> trackSize;
        std::cout << id << " " << trackSize << std::endl;

        vector<Position> track;
        for (int i = 0; i < trackSize; i++)
        {
            int x,y,z, time;
            inputFile >> x >> y >> z >> time;
            std::cout << x << " " << y << " " << z << " " << time << "\n";

            Position p;
            p.x = x;
            p.y = y;
            p.z = z;
            p.time = time;
            track.push_back(p);
        }
        setValue(i, Marker(id, track));
    }
}

void MarkerArray::toFile(string filepath)
{
    ofstream outFile;
    outFile.open(filepath, std::ios::out);
    outFile << _elementsCount << " ";
    for (int i = 0; i < _elementsCount; i++)
    {
        outFile << at(i).get_id() << " ";
        outFile << at(i).get_track().size() << " ";
        for (int j = 0; j < at(i).get_track().size(); j++)
            outFile << at(i).get_track()[j].x << " " << at(i).get_track()[j].y << " "
                    << at(i).get_track()[j].z << " " << at(i).get_track()[j].time << " ";
    }
}

unsigned int MarkerArray::size()
{
    return _elementsCount;
}
