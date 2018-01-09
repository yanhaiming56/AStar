#ifndef CASTAR_H
#define CASTAR_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "CPoint.h"
using namespace  std;

bool CompF(const CPoint* pl, const CPoint* pr);

class CAstar
{
  public:
    CAstar ( int textureMap[][12] );
    ~CAstar ();

    CPoint* FindPath ( CPoint* start, CPoint* end, bool IsIgnoreCorner );

    bool CanReach ( int x, int y );

    bool inCloseList ( int x, int y );

    bool inOpenList ( int x, int y );

    bool CanReach ( CPoint* start, int x, int y, bool IsIgnoreCorner );

    std::vector<CPoint*> SurrroundPoints ( CPoint* point, bool IsIgnoreCorner );



    CPoint* getMinFPoint();

    void removeFromOpenList ( CPoint* point );


    void FoundPoint ( CPoint* tempStart, CPoint* point );

    void NotFoundPoint ( CPoint* tempStart, CPoint* end, CPoint* point );

    int CalcG ( CPoint* start, CPoint* point );

    int CalcH ( CPoint* end, CPoint* point );

  private:
    static const int STEP = 10;
    static const int OBLIQUE = 14;

    typedef std::vector<CPoint*> tPointList;

    tPointList m_listOpen;
    tPointList m_listClose;


    int m_textureMap[100][100];


};

#endif // CASTAR_H
