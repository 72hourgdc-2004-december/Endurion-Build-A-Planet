#pragma once

#include <sdl.h>



class CSDLApp;


class CUnit
{

  public:

    enum eUnitType
    {
      UT_INVALID = 0,
      UT_HERO,
      UT_EARTH,
      UT_WEED,
      UT_SPONGE,
      UT_EXIT,
      UT_RELICT,
      UT_EYESTICK,
    };


    eUnitType             m_Type;

    float                 m_fPosX,
                          m_fPosY,
                          m_fSpeedX,
                          m_fSpeedY,
                          m_fAnimTime;

    bool                  m_bRemoveMe;


    CUnit();
    virtual ~CUnit();

    virtual void          Display( CSDLApp& sdlApp );
    virtual void          Update( const float fElapsedTime );

    virtual SDL_Rect      CollisionRect();

};
