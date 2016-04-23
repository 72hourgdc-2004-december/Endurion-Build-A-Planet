#pragma once
#include "unit.h"

class CEyeStick : public CUnit
{

  public:

    enum eColor
    {
      COL_RED,
      COL_BLUE,
      COL_YELLOW,
    };

    eColor                  m_Color;

    float                   m_fStickHeight;


    CEyeStick();
    virtual ~CEyeStick();

    virtual void            Display( CSDLApp& sdlApp );
    virtual SDL_Rect        CollisionRect();

    virtual void            Update( const float fElapsedTime );

};
