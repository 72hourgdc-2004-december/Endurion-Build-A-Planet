#include ".\hero.h"
#include "SDLCompo.h"



CHero::CHero()
{

  m_Type = CUnit::UT_HERO;

  m_bRelictCollected = false;

}



CHero::~CHero()
{
}



void CHero::Display( CSDLApp& sdlApp )
{

  sdlApp.DrawImage( sdlApp.m_pImageHero, (int)m_fPosX, (int)m_fPosY );

}



SDL_Rect CHero::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX + 7;
  rcResult.y = (int)m_fPosY + 5;
  rcResult.w = 26;
  rcResult.h = 74;

  return rcResult;

}