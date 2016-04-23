#include ".\exit.h"
#include "SDLCompo.h"



CExit::CExit()
{
  m_Type = CUnit::UT_EXIT;
}



CExit::~CExit()
{
}



void CExit::Display( CSDLApp& sdlApp )
{

  sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX, (int)m_fPosY, 200, 0, 56, 40 );

}



SDL_Rect CExit::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX;
  rcResult.y = (int)m_fPosY;
  rcResult.w = 56;
  rcResult.h = 40;

  return rcResult;

}