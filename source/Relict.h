#pragma once
#include "unit.h"

class CRelict : public CUnit
{

  public:


    CRelict();
    virtual ~CRelict();


    virtual void            Display( CSDLApp& sdlApp );
    virtual SDL_Rect        CollisionRect();

};
