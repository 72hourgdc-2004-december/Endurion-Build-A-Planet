#include ".\earth.h"
#include "SDLCompo.h"



CEarth::CEarth()
{
  m_Type = CUnit::UT_EARTH;
  iWidth = 40;
  iHeight = 40;
}

CEarth::~CEarth()
{
}



void CEarth::Display( CSDLApp& sdlApp )
{

  for ( int i = 1; i < iWidth / 20 - 1; ++i )
  {
    sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + i * 20, (int)m_fPosY, 20, 0, 20, 20 );

    sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + i * 20, (int)m_fPosY + iHeight - 20, 20, 40, 20, 20 );

    for ( int j = 1; j < iHeight / 20 - 1; ++j )
    {
      sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + i * 20, (int)m_fPosY + j * 20, 20, 20, 20, 20 );
    }
  }
  for ( int j = 1; j < iHeight / 20 - 1; ++j )
  {
    sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX, (int)m_fPosY + j * 20, 0, 20, 20, 20 );
    sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + iWidth - 20, (int)m_fPosY + j * 20, 40, 20, 20, 20 );
  }

  sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX, (int)m_fPosY, 0, 0, 20, 20 );
  sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + iWidth - 20, (int)m_fPosY, 40, 0, 20, 20 );

  sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX, (int)m_fPosY + iHeight - 20, 0, 40, 20, 20 );
  sdlApp.DrawImage( sdlApp.m_pImageWorld, (int)m_fPosX + iWidth - 20, (int)m_fPosY + iHeight - 20, 40, 40, 20, 20 );

}



SDL_Rect CEarth::CollisionRect()
{

  SDL_Rect    rcResult;

  rcResult.x = (int)m_fPosX + 5;
  rcResult.y = (int)m_fPosY + 5;
  rcResult.w = iWidth - 10;
  rcResult.h = iHeight - 10;

  return rcResult;

}