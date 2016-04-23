#pragma once
#include "unit.h"

class CEarth : public CUnit
{

  public:

    int               iWidth,
                      iHeight;


    CEarth();
    virtual ~CEarth();


    virtual void              Display( CSDLApp& sdlApp );
    virtual SDL_Rect          CollisionRect();

};
