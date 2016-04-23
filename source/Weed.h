#pragma once
#include "unit.h"

class CWeed : public CUnit
{

  public:


    CWeed();
    virtual ~CWeed();


    virtual void                Display( CSDLApp& sdlApp );

    SDL_Rect                    CollisionRect();

};
