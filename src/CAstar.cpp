#include "CAstar.h"
bool CompF ( const CPoint* pl, const CPoint* pr )
{
    return pl->F < pr->F;
}

CAstar::CAstar ( int textureMap[][12] )
{
    for ( int i = 0; i < 100; i++ )
    {
        for ( int j = 0; j < 100; j++ )
        {
            m_textureMap[i][j] = 0;
        }
    }

    for ( int i = 0; i < 12; i++ )
    {
        for ( int j = 0; j < 12; j++ )
        {
            m_textureMap[i][j] = textureMap[i][j];
        }
    }
}

CAstar::~CAstar()
{
    //dtor
}

CPoint* CAstar::FindPath ( CPoint* start, CPoint* end, bool IsIgnoreCorner )
{
    m_listOpen.push_back ( start ); //将起始点放到开启列表中

    while ( m_listOpen.size() )
    {
        CPoint* tempStart = getMinFPoint(); //获取F值最低的点

        removeFromOpenList ( tempStart ); //将这个点从开启列表中删除
        m_listClose.push_back ( tempStart ); //将这个点放到关闭列表中

        std::vector<CPoint*> surroundPoints = SurrroundPoints ( tempStart, IsIgnoreCorner ); //获取F值最低点相邻的点

        tPointList::iterator _iter = surroundPoints.begin();

        //遍历这些相邻点
        for ( ; _iter != surroundPoints.end(); ++_iter )
        {
            CPoint* point = *_iter;

            if ( inOpenList ( point->X, point->Y ) ) //如果这个点在开启列表中
                FoundPoint ( tempStart, point ); //重新计算G值，如果G值更小，则更新父节点，并且重新计算F值，否则什么都不做
            else
                NotFoundPoint ( tempStart, end, point ); //不在开启列表中，则加入开启列表，计算G值,F值，设定父节点
        }

        if ( inOpenList ( end->X, end->Y ) ) //目标结点已经在开启列表中
        {
            //返回在开启列表中的父节点
            for ( int i = 0; i < m_listOpen.size(); i++ )
            {
                if ( m_listOpen[i]->X == end->X && m_listOpen[i]->Y == end->Y )
                {
                    return m_listOpen[i];
                }
            }
        }
    }

    return end;
}

bool CAstar::CanReach ( int x, int y )
{
    return m_textureMap[x][y] == 0;
}

bool CAstar::inCloseList ( int x, int y )
{
    CPoint* p = new CPoint ( x, y );

    tPointList::iterator _iter = m_listClose.begin();

    for ( ; _iter != m_listClose.end(); ++_iter )
    {
        CPoint* temp = *_iter;

        if ( temp->X == p->X && temp->Y == p->Y )
            return true;
    }

    if ( p )
    {
        delete p;
        p = NULL;
    }

    return false;
}

bool CAstar::inOpenList ( int x, int y )
{
    CPoint* p = new CPoint ( x, y );

    tPointList::iterator _iter = m_listOpen.begin();

    for ( ; _iter != m_listOpen.end(); ++_iter )
    {
        CPoint* temp = *_iter;

        if ( temp->X == p->X && temp->Y == p->Y )
            return true;
    }

    if ( p )
    {
        delete p;
        p = NULL;
    }

    return false;
}

bool CAstar::CanReach ( CPoint* start, int x, int y, bool IsIgnoreCorner )
{
    if ( !CanReach ( x, y ) || inCloseList ( x, y ) )
        return false;
    else
    {
        if ( ( abs ( x - start->X ) + abs ( y - start->Y ) ) == 1 )
            return true;
        else
        {
            if ( CanReach ( abs ( x - 1 ), y ) && CanReach ( x, abs ( y - 1 ) ) )
                return true;
            else
                return IsIgnoreCorner;
        }
    }
}

std::vector<CPoint*> CAstar::SurrroundPoints ( CPoint* point, bool IsIgnoreCorner )
{
    tPointList surroundPoints ;

    for ( int x = point->X - 1; x <= point->X + 1; x++ )
        for ( int y = point->Y - 1; y <= point->Y + 1; y++ )
        {

            if ( CanReach ( point, x, y, IsIgnoreCorner ) )
            {

                CPoint* p = new CPoint ( x, y );

                surroundPoints.push_back ( p );
            }
            else
            {

            }
        }

    return surroundPoints;
}

CPoint* CAstar::getMinFPoint()
{

    tPointList tempList;

    for ( int i = 0; i < ( int ) m_listOpen.size(); i++ )
    {
        tempList.push_back ( m_listOpen[i] );
    }

    sort ( tempList.begin(), tempList.end(), CompF );


    if ( tempList.size() )
    {
        return tempList[0];
    }

}

void CAstar::removeFromOpenList ( CPoint* point )
{
    tPointList::iterator _iter = m_listOpen.begin();

    for ( ; _iter != m_listOpen.end(); ++_iter )
    {
        m_listOpen.erase ( _iter );
        break;
    }
}

void CAstar::FoundPoint ( CPoint* tempStart, CPoint* point )
{
    int G = CalcG ( tempStart, point );

    if ( G < point->G )
    {
        point->m_pParentPoint = tempStart;
        point->G = G;
        point->calcF();
    }
}

void CAstar::NotFoundPoint ( CPoint* tempStart, CPoint* end, CPoint* point )
{
    point->m_pParentPoint = tempStart;


    point->G = CalcG ( tempStart, point );
    point->H = CalcH ( end, point );
    point->calcF();
    m_listOpen.push_back ( point );
}

int CAstar::CalcG ( CPoint* start, CPoint* point )
{
    int G = ( abs ( point->X - start->X ) + abs ( point->Y - start->Y ) ) == 2 ? STEP : OBLIQUE;
    int parentG = point->m_pParentPoint != NULL ? point->m_pParentPoint->G : 0;
    return G + parentG;
}

int CAstar::CalcH ( CPoint* end, CPoint* point )
{
    int step = abs ( point->X - end->X ) + abs ( point->Y - end->Y );
    return step * STEP;
}
