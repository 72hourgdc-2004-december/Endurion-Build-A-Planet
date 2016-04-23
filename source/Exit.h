#pragma once
#include "unit.h"

class CExit : public CUnit
{

  public:


    CExit();
    virtual ~CExit();

    virtual void          Display( CSDLApp& sdlApp );
    virtual SDL_Rect      CollisionRect();


};
