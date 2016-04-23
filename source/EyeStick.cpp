#include ".\eyestick.h"
#include "SDLCompo.h"



CEyeStick::CEyeStick()
{
  m_Type = CUnit::UT_EYESTICK;
  m_Color = COL_RED;
  m_fStickHeight = 0.0f;
}

CEyeStick::~CEyeStick()
{
}



void CEyeStick::Display( CSDLApp& sdlApp )
{

  if ( m_fStickHeight > 0.0f )
  {
    sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 10, (int)m_fPosY - 19 - (int)m_fStickHeight, 0, 192, 20, (int)m_fStickHeight );
  }
  switch ( m_Color )
  {
    case COL_RED:
      sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 10, (int)m_fPosY - 19, 40, 172, 20, 20 );
      break;
    case COL_BLUE:
      sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 10, (int)m_fPosY - 19, 0, 172, 20, 20 );
      break;
    case COL_YELLOW:
      sdlApp.DrawImage( sdlApp.m_pImageUnits, (int)m_fPosX - 10, (int)m_fPosY - 19, 20, 172, 20, 20 );
      break;
  }

}



SDL_Rect CEyeStick::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX - 10;
  rcResult.y = (int)m_fPosY - 19 - (int)m_fStickHeight;
  rcResult.w = 20;
  rcResult.h = (int)m_fStickHeight + 20;

  return rcResult;

}



void CEyeStick::Update( const float fElapsedTime )
{

  CUnit::Update( fElapsedTime );

  if ( ( ( theApp.m_World.m_dwLight == 0x808030 )
  &&     ( m_Color != COL_YELLOW ) )
  ||   ( ( theApp.m_World.m_dwLight == 0x303080 )
  &&     ( m_Color != COL_BLUE ) )
  ||   ( ( theApp.m_World.m_dwLight == 0x803030 )
  &&     ( m_Color != COL_RED ) ) )
  {
    if ( m_fStickHeight < 40.0f )
    {
      m_fStickHeight += 30.0f * fElapsedTime;
      if ( m_fStickHeight > 40.0f )
      {
        m_fStickHeight = 40.0f;
      }
    }
  }
  else
  {
    if ( m_fStickHeight > 0.0f )
    {
      m_fStickHeight -= 30.0f * fElapsedTime;
      if ( m_fStickHeight < 0.0f )
      {
        m_fStickHeight = 0.0f;
      }
    }
  }

}