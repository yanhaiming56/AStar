#ifndef CPOINT_H
#define CPOINT_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

class CPoint
{
  public:
    CPoint ( int x, int y );

    ~CPoint();

    void calcF();

  public:
    int X;
    int Y;
    int G;
    int H;
    int F;
    CPoint* m_pParentPoint;
};
#endif // CPOINT_H
