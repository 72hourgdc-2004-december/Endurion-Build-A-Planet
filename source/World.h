#pragma once

#include <list>

#include "Unit.h"
#include "GameEnums.h"



class CWorld
{

  public:

    typedef std::list<CUnit*>   tListUnits;


    tListUnits                  m_listUnits;

    eWindDir                    m_WindDir;

    float                       m_fWindSpeedX;
    float                       m_fWindSpeedY;

    float                       m_fGravity;

    int                         m_iCurrentLevel;

    bool                        m_bDone,
                                m_bFailed,
                                m_bNReleased;

    eAtmosphere                 m_Atmosphere;

    Uint32                      m_dwLight,
                                m_dwCurrentLight;


    CWorld();
    ~CWorld();


    void                        Display( CSDLApp& sdlApp );
    void                        Update( const float fElapsedTime );

    void                        ClearUnits();
    bool                        Load();

    bool                        Intersect( SDL_Rect& rc1, SDL_Rect& rc2 );
    void                        Collision( CUnit* pUnit1, CUnit* pUnit2 );

};
