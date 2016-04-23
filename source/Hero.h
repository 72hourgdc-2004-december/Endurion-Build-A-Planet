#pragma once
#include "unit.h"

class CHero : public CUnit
{

  public:

    bool                  m_bRelictCollected;


    CHero();
    virtual ~CHero();

    virtual void          Display( CSDLApp& sdlApp );


    virtual SDL_Rect      CollisionRect();
    
};
