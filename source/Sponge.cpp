#include ".\sponge.h"
#include "SDLCompo.h"



CSponge::CSponge()
{
  m_Type = CUnit::UT_SPONGE;
}



CSponge::~CSponge()
{
}



void CSponge::Display( CSDLApp& sdlApp )
{

  if ( sdlApp.m_World.m_fGravity == 1.0f )
  {
    sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 30, (int)m_fPosY - 59, 0, 80, 60, 60 );
  }
  else if ( sdlApp.m_World.m_fGravity == 2.5f )
  {
    sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 39, 0, 40, 40, 40 );
  }
  else if ( sdlApp.m_World.m_fGravity == 10.0f )
  {
    sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 10, (int)m_fPosY - 19, 60, 80, 20, 20 );
  }
 
}



SDL_Rect CSponge::CollisionRect()
{

  SDL_Rect    rcResult;

  if ( theApp.m_World.m_fGravity == 1.0f )
  {
    rcResult.x = (int)m_fPosX - 30 + 10;
    rcResult.y = (int)m_fPosY - 59 + 10;
    rcResult.w = 40;
    rcResult.h = 50;
  }
  else if ( theApp.m_World.m_fGravity == 2.5f )
  {
    rcResult.x = (int)m_fPosX - 20 + 14;
    rcResult.y = (int)m_fPosY - 39 + 10;
    rcResult.w = 16;
    rcResult.h = 30;
  }
  else if ( theApp.m_World.m_fGravity == 10.0f )
  {
    rcResult.x = (int)m_fPosX - 10 + 6;
    rcResult.y = (int)m_fPosY - 19 + 10;
    rcResult.w = 12;
    rcResult.h = 10;
  }
  return rcResult;

}