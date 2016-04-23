#pragma once
#include "unit.h"

class CSponge : public CUnit
{

  public:


    CSponge();
    virtual ~CSponge();

    virtual void              Display( CSDLApp& sdlApp );
    virtual SDL_Rect          CollisionRect();

};
