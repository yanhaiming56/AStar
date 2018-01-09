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
    m_listOpen.push_back ( start ); //����ʼ��ŵ������б���

    while ( m_listOpen.size() )
    {
        CPoint* tempStart = getMinFPoint(); //��ȡFֵ��͵ĵ�

        removeFromOpenList ( tempStart ); //�������ӿ����б���ɾ��
        m_listClose.push_back ( tempStart ); //�������ŵ��ر��б���

        std::vector<CPoint*> surroundPoints = SurrroundPoints ( tempStart, IsIgnoreCorner ); //��ȡFֵ��͵����ڵĵ�

        tPointList::iterator _iter = surroundPoints.begin();

        //������Щ���ڵ�
        for ( ; _iter != surroundPoints.end(); ++_iter )
        {
            CPoint* point = *_iter;

            if ( inOpenList ( point->X, point->Y ) ) //���������ڿ����б���
                FoundPoint ( tempStart, point ); //���¼���Gֵ�����Gֵ��С������¸��ڵ㣬�������¼���Fֵ������ʲô������
            else
                NotFoundPoint ( tempStart, end, point ); //���ڿ����б��У�����뿪���б�����Gֵ,Fֵ���趨���ڵ�
        }

        if ( inOpenList ( end->X, end->Y ) ) //Ŀ�����Ѿ��ڿ����б���
        {
            //�����ڿ����б��еĸ��ڵ�
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
