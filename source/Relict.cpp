#include ".\relict.h"
#include "SDLCompo.h"



CRelict::CRelict()
{
  m_Type = CUnit::UT_RELICT;
}



CRelict::~CRelict()
{
}



void CRelict::Display( CSDLApp& sdlApp )
{

  sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX, (int)m_fPosY, 0, 140, 32, 32 );

}



SDL_Rect CRelict::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX;
  rcResult.y = (int)m_fPosY;
  rcResult.w = 32;
  rcResult.h = 32;

  return rcResult;

}