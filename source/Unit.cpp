#include ".\unit.h"



CUnit::CUnit() :
  m_Type( UT_INVALID ),
  m_fPosX( 0.0f ),
  m_fPosY( 0.0f ),
  m_fSpeedX( 0.0f ),
  m_fSpeedY( 0.0f ),
  m_bRemoveMe( false ),
  m_fAnimTime( 0.0f )
{
}

CUnit::~CUnit()
{
}



void CUnit::Display( CSDLApp& sdlApp )
{
}



void CUnit::Update( const float fElapsedTime )
{

  m_fPosX += m_fSpeedX * fElapsedTime;
  m_fPosY += m_fSpeedY * fElapsedTime;

  m_fAnimTime += fElapsedTime;

}



SDL_Rect CUnit::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX;
  rcResult.y = (int)m_fPosY;
  rcResult.w = 40;
  rcResult.h = 40;

  return rcResult;

}