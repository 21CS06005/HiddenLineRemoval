#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
    float startX;
    float endX;
    float height;
};
enum Position {start, endPoint};

struct Coordinates {
    float x;
    float y;
    Position position;
};

bool compareTwoStudents(Coordinates a, Coordinates b)
{
    if (a.x == b.x) {
        if(a.position == start && b.position == start) {
            return a.y > b.y;
        }
        else if(a.position == endPoint && b.position == endPoint) {
            return a.y < b.y;
        }
        else {
            if(a.position == start)
                return true;
            else
                return false;
        }
    }
    else if(a.x < b.x) {
        return true;
    }
    else {
        return false;
    }
}

vector<Coordinates> sweepLineAlgo(Rectangle r[], int size) {
    vector<Coordinates> result;
    Coordinates co;
    vector<Coordinates> coordinates;

    // Generate 2 co-ordinates for each tuple
    for (int i = 0; i < size; ++i) {
        co = {r[i].startX, r[i].height, start};
        coordinates.push_back(co);

        co = {r[i].endX, r[i].height, endPoint};
        coordinates.push_back(co);
    }
    // Sort the set of co-ordinates according to start-x
    sort(coordinates.begin(), coordinates.end(), compareTwoStudents);

    float prev_height = 0;
    vector<float> heap = {0};
    make_heap(heap.begin(),heap.end());
    vector<Coordinates> res;

    //Getting the border co-ordinates through heap
    for (auto i = coordinates.begin(); i != coordinates.end(); ++i) {
        Coordinates cur_coordinate = *i;

        if(i->position == start) {
            heap.push_back(cur_coordinate.y);
            push_heap(heap.begin(), heap.end());
        }
        else {
            auto cur_value = find(heap.begin(), heap.end(), cur_coordinate.y);
            heap.erase(cur_value);
            make_heap(heap.begin(), heap.end());
        }

        float cur_height = heap.front();

        if(cur_height != prev_height) {
            co = {cur_coordinate.x, cur_height, start};
            res.push_back(co);
            prev_height = cur_height;
        }
    }
    return res;
}

//Generating the random tuples of rectangles
Rectangle gen_random_rectangle(float prev) {
    float startX = float(rand() % 10 + prev);
    Rectangle random_rect = {startX,  startX + float(rand() % 7) + 1, float(rand() % 20)};
    return random_rect;
}


int main() {
    int size;
    cout<<"Enter the number of tuples to be generated:"<<endl;
    cin>>size;
    Rectangle r[size];
    srand(time(0));

    cout<<"Tuples Generated are:"<<endl;
    for (int i = 0; i < size; ++i) {
        if(i==0)
            r[i] = gen_random_rectangle(0);
        r[i] = gen_random_rectangle(r[i-1].startX);
        cout<<"("<<r[i].startX<<","<<r[i].endX<<","<<r[i].height<<")"<<endl;
    }

    vector<Coordinates> result = sweepLineAlgo(r, size);

    cout<<"Result:"<<endl;
    for (auto i = result.begin(); i != result.end(); ++i) {
        cout<<"("<<i->x<<","<<i->y<<")"<<endl;
    }
    return 1;
}