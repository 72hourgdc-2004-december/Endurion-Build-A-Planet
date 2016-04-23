#include <math.h>

#include ".\weed.h"
#include "SDLCompo.h"



CWeed::CWeed()
{
  m_Type = CUnit::UT_WEED;
}

CWeed::~CWeed()
{
}



void CWeed::Display( CSDLApp& sdlApp )
{

  switch ( sdlApp.m_World.m_WindDir )
  {
    case DIR_NONE:
      sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 39, 0, 0, 40, 40 );
      break;
    case DIR_N:
      if ( fmodf( m_fAnimTime, 0.5f ) > 0.25f )
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 79, 40, 0, 40, 80 );
      }
      else
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 79, 80, 80, 40, 80 );
      }
      break;
    case DIR_S:
      if ( fmodf( m_fAnimTime, 0.5f ) > 0.25f )
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 8, 120, 80, 40, 80 );
      }
      else
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 20, (int)m_fPosY - 8, 80, 0, 40, 80 );
      }
      break;
    case DIR_W:
      if ( fmodf( m_fAnimTime, 0.5f ) > 0.25f )
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 65, (int)m_fPosY - 39, 160, 120, 80, 40 );
      }
      else
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 65, (int)m_fPosY - 39, 120, 0, 80, 40 );
      }
      break;
    case DIR_E:
      if ( fmodf( m_fAnimTime, 0.5f ) > 0.25f )
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 15, (int)m_fPosY - 39, 160, 80, 80, 40 );
      }
      else
      {
        sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 15, (int)m_fPosY - 39, 120, 40, 80, 40 );
      }
      break;
  }
 
}



SDL_Rect CWeed::CollisionRect()
{

  SDL_Rect    rcResult;

  switch ( theApp.m_World.m_WindDir )
  {
    case DIR_NONE:
      rcResult.x = (int)m_fPosX - 20 + 8;
      rcResult.y = (int)m_fPosY - 39 + 16;
      rcResult.w = 24;
      rcResult.h = 24;
      break;
    case DIR_N:
      rcResult.x = (int)m_fPosX - 20 + 4;
      rcResult.y = (int)m_fPosY - 79 + 2;
      rcResult.w = 32;
      rcResult.h = 78;
      break;
    case DIR_S:
      rcResult.x = (int)m_fPosX - 20 + 4;
      rcResult.y = (int)m_fPosY - 8 + 5;
      rcResult.w = 32;
      rcResult.h = 75;
      break;
    case DIR_W:
      rcResult.x = (int)m_fPosX - 65 + 4;
      rcResult.y = (int)m_fPosY - 39 + 15;
      rcResult.w = 72;
      rcResult.h = 25;
      break;
    case DIR_E:
      rcResult.x = (int)m_fPosX - 15 + 4;
      rcResult.y = (int)m_fPosY - 39 + 15;
      rcResult.w = 72;
      rcResult.h = 25;
      break;
  }

  return rcResult;

}