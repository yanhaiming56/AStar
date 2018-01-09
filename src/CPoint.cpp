#include "CPoint.h"

CPoint::CPoint ( int x, int y )
    : X ( x ), Y ( y ), G ( 0 ), H ( 0 ),  F ( 0 ), m_pParentPoint ( NULL )
{
    //ctor
}

CPoint::~CPoint()
{
    //dtor
}

void CPoint::calcF()
{
    this->F = this->H + this->G;
}
