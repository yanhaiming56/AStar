#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "CAstar.h"
using namespace  std;

int main ( int argc, char* argv[] )
{

    int array[12][12] =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        { 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    CAstar* maze = new CAstar ( array );
    CPoint* start = new CPoint ( 1, 1 );
    CPoint* end = new CPoint ( 6, 10 );
    CPoint* parent = maze->FindPath ( start, end, false );


    while ( parent != NULL )
    {
        cout << parent->X << "," << parent->Y << endl;
        parent = parent->m_pParentPoint;
    }

    return 0;
}
