#include <fstream>
#include <iostream>
#include <string>

#include ".\world.h"
#include "Hero.h"
#include "Weed.h"
#include "Earth.h"
#include "Exit.h"
#include "Sponge.h"
#include "Relict.h"
#include "EyeStick.h"
#include "SDLCompo.h"
#include "GameEnums.h"



CWorld::CWorld() :
  m_fWindSpeedX( 0.0f ),
  m_fWindSpeedY( 0.0f ),
  m_fGravity( 2.5f ),
  m_WindDir( DIR_NONE ),
  m_Atmosphere( ATM_AIR ),
  m_dwLight( 0x808030 ),
  m_dwCurrentLight( 0x808030 ),
  m_iCurrentLevel( 1 ),
  m_bDone( false ),
  m_bFailed( false ),
  m_bNReleased( true )
{
}

CWorld::~CWorld()
{

  ClearUnits();

}



void CWorld::Display( CSDLApp& sdlApp )
{

  SDL_FillRect( sdlApp.m_pScreen, NULL, SDL_MapRGB( sdlApp.m_pScreen->format, 
                                                    ( m_dwCurrentLight & 0xff0000 ) >> 16,
                                                    ( m_dwCurrentLight & 0x00ff00 ) >> 8,
                                                    ( m_dwCurrentLight & 0x0000ff ) ) );

  tListUnits::iterator    it( m_listUnits.begin() );
  while ( it != m_listUnits.end() )
  {
    CUnit*    pUnit = *it;

    // Collision boxes
    //SDL_FillRect( sdlApp.m_pScreen, &pUnit->CollisionRect(), SDL_MapRGB( sdlApp.m_pScreen->format, 0xff, 0xff, 0 ) );

    pUnit->Display( sdlApp );

    ++it;
  }

  theApp.DrawImage( sdlApp.m_pImageGUI, 640 -  80, 480 - 120, 0, 0, 40, 40 );
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 -  40, 480 -  80, 40, 0, 40, 40 );
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 -  80, 480 -  40, 80, 0, 40, 40 );
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 - 120, 480 -  80, 120, 0, 40, 40 );
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 -  80, 480 -  80, 160, 0, 40, 40 );

  // Gravity
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 - 120, 480 - 160, 0, 40, 120, 40 );
  // Light
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 - 120, 480 - 200, 120, 40, 120, 40 );
  // Restart
  theApp.DrawImage( sdlApp.m_pImageGUI, 640 - 120, 480 - 40, 200, 0, 40, 40 );

  if ( m_bDone )
  {
    theApp.PrintCentered( 220, "Well done, mortal!" );
    theApp.PrintCentered( 240, "Are you ready to continue thy quest?" );
  }
  else if ( m_bFailed )
  {
    theApp.PrintCentered( 220, "You failed me, mortal!" );
    theApp.PrintCentered( 240, "Are you ready to restart thy quest?" );
  }

}



void CWorld::Update( const float fElapsedTime )
{

  if ( m_bDone )
  {
    if ( ( theApp.m_iMouseButtons & SDL_BUTTON( 1 ) )
    &&   ( theApp.m_bMouseButtonReleased ) )
    {
      theApp.m_bMouseButtonReleased = false;
      m_iCurrentLevel++;
      if ( !Load() )
      {
        ClearUnits();
        theApp.m_bDoneMode = true;
        theApp.m_bGameRunning = false;
        theApp.m_bTitleMode = true;
      }
    }
    return;
  }
  else if ( m_bFailed )
  {
    if ( ( theApp.m_iMouseButtons & SDL_BUTTON( 1 ) )
    &&   ( theApp.m_bMouseButtonReleased ) )
    {
      theApp.m_bMouseButtonReleased = false;
      m_bFailed = false;
      if ( !Load() )
      {
        ClearUnits();
        theApp.m_bTitleMode = true;
      }
    }
    return;
  }

  tListUnits::iterator    it( m_listUnits.begin() );
  while ( it != m_listUnits.end() )
  {
    CUnit*    pUnit = *it;

    if ( pUnit->m_Type == CUnit::UT_HERO )
    {
      if ( pUnit->m_fSpeedX < m_fWindSpeedX )
      {
        pUnit->m_fSpeedX += 5.0f * fElapsedTime;
        if ( pUnit->m_fSpeedX > m_fWindSpeedX )
        {
          pUnit->m_fSpeedX = m_fWindSpeedX;
        }
      }
      else if ( pUnit->m_fSpeedX > m_fWindSpeedX )
      {
        pUnit->m_fSpeedX -= 5.0f * fElapsedTime;
        if ( pUnit->m_fSpeedX < m_fWindSpeedX )
        {
          pUnit->m_fSpeedX = m_fWindSpeedX;
        }
      }
      if ( pUnit->m_fSpeedY < m_fWindSpeedY )
      {
        pUnit->m_fSpeedY += 5.0f * fElapsedTime;
        if ( pUnit->m_fSpeedY > m_fWindSpeedY )
        {
          pUnit->m_fSpeedY = m_fWindSpeedY;
        }
      }
      else if ( pUnit->m_fSpeedY > m_fWindSpeedY )
      {
        pUnit->m_fSpeedY -= 5.0f * fElapsedTime;
        if ( pUnit->m_fSpeedY < m_fWindSpeedY )
        {
          pUnit->m_fSpeedY = m_fWindSpeedY;
        }
      }

      pUnit->m_fPosY += m_fGravity * fElapsedTime;
    }

    pUnit->Update( fElapsedTime );
    if ( pUnit->m_bRemoveMe )
    {
      delete pUnit;
      it = m_listUnits.erase( it );
      continue;
    }

    ++it;
  }

  tListUnits::iterator    it2( m_listUnits.begin() );
  while ( it2 != m_listUnits.end() )
  {
    CUnit*    pUnit = *it2;

    if ( pUnit->m_bRemoveMe )
    {
      ++it2;
      continue;
    }

    tListUnits::iterator    it3( m_listUnits.begin() );
    while ( it3 != m_listUnits.end() )
    {
      CUnit*    pOtherUnit = *it3;

      if ( pOtherUnit->m_bRemoveMe )
      {
        ++it3;
        continue;
      }

      if ( ( pUnit != pOtherUnit )
      &&   ( Intersect( pUnit->CollisionRect(), pOtherUnit->CollisionRect() ) ) )
      {
        if ( pUnit->m_Type > pOtherUnit->m_Type )
        {
          Collision( pOtherUnit, pUnit );
        }
        else
        {
          Collision( pUnit, pOtherUnit );
        }
      }

      if ( pUnit->m_bRemoveMe  )
      {
        break;
      }

      ++it3;
    }

    ++it2;
  }

  if ( ( theApp.m_iMouseButtons & SDL_BUTTON( 1 ) )
  &&   ( theApp.m_bMouseButtonReleased ) )
  {
    theApp.m_bMouseButtonReleased = false;

    if ( ( theApp.m_iMouseX >= 640 - 80 )
    &&   ( theApp.m_iMouseY >= 480 - 120 )
    &&   ( theApp.m_iMouseX < 640 - 80 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 120 + 40 ) )
    {
      m_fWindSpeedX = 0.0f;
      m_fWindSpeedY = -20.0f;

      m_WindDir = DIR_N;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 40 )
    &&   ( theApp.m_iMouseY >= 480 - 80 )
    &&   ( theApp.m_iMouseX < 640 - 40 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 80 + 40 ) )
    {
      m_fWindSpeedX = 20.0f;
      m_fWindSpeedY = 0.0f;

      m_WindDir = DIR_E;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 80 )
    &&   ( theApp.m_iMouseY >= 480 - 40 )
    &&   ( theApp.m_iMouseX < 640 - 80 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 40 + 40 ) )
    {
      m_fWindSpeedX = 0.0f;
      m_fWindSpeedY = 20.0f;

      m_WindDir = DIR_S;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 120 )
    &&   ( theApp.m_iMouseY >= 480 - 80 )
    &&   ( theApp.m_iMouseX < 640 - 120 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 80 + 40 ) )
    {
      m_fWindSpeedX = -20.0f;
      m_fWindSpeedY = 0.0f;

      m_WindDir = DIR_W;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 80 )
    &&   ( theApp.m_iMouseY >= 480 - 80 )
    &&   ( theApp.m_iMouseX < 640 - 80 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 80 + 40 ) )
    {
      m_fWindSpeedX = 0.0f;
      m_fWindSpeedY = 0.0f;

      m_WindDir = DIR_NONE;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 120 )
    &&   ( theApp.m_iMouseY >= 480 - 160 )
    &&   ( theApp.m_iMouseX < 640 - 120 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 160 + 40 ) )
    {
      m_fGravity = 1.0f;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 80 )
    &&   ( theApp.m_iMouseY >= 480 - 160 )
    &&   ( theApp.m_iMouseX < 640 - 80 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 160 + 40 ) )
    {
      m_fGravity = 2.5f;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 40 )
    &&   ( theApp.m_iMouseY >= 480 - 160 )
    &&   ( theApp.m_iMouseX < 640 - 40 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 160 + 40 ) )
    {
      m_fGravity = 10.0f;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 120 )
    &&   ( theApp.m_iMouseY >= 480 - 200 )
    &&   ( theApp.m_iMouseX < 640 - 120 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 200 + 40 ) )
    {
      m_dwLight = 0x303080;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 80 )
    &&   ( theApp.m_iMouseY >= 480 - 200 )
    &&   ( theApp.m_iMouseX < 640 - 80 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 200 + 40 ) )
    {
      m_dwLight = 0x808030;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 40 )
    &&   ( theApp.m_iMouseY >= 480 - 200 )
    &&   ( theApp.m_iMouseX < 640 - 40 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 200 + 40 ) )
    {
      m_dwLight = 0x803030;

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
    if ( ( theApp.m_iMouseX >= 640 - 120 )
    &&   ( theApp.m_iMouseY >= 480 - 40 )
    &&   ( theApp.m_iMouseX < 640 - 120 + 40 )
    &&   ( theApp.m_iMouseY < 480 - 40 + 40 ) )
    {
      // Restart
      Load();

      theApp.PlaySound( theApp.m_pSoundSwitch );
    }
  }

  if ( ( theApp.m_pKeyState[SDLK_n] )
  &&   ( m_bNReleased ) )
  {
    m_bNReleased = false;
    m_iCurrentLevel++;
    if ( !Load() )
    {
      ClearUnits();
      theApp.m_bDoneMode = true;
      theApp.m_bTitleMode = true;
      theApp.m_bGameRunning = false;
    }
  }
  if ( !theApp.m_pKeyState[SDLK_n] )
  {
    m_bNReleased = true;
  }

  if ( m_dwCurrentLight != m_dwLight )
  {
    int   iR = ( m_dwCurrentLight & 0xff0000 ) >> 16;
    int   iG = ( m_dwCurrentLight & 0x00ff00 ) >> 8;
    int   iB = ( m_dwCurrentLight & 0x0000ff );

    int   iR2 = ( m_dwLight & 0xff0000 ) >> 16;
    int   iG2 = ( m_dwLight & 0x00ff00 ) >> 8;
    int   iB2 = ( m_dwLight & 0x0000ff );

    if ( iR > iR2 )
    {
      iR--;
    }
    if ( iR < iR2 )
    {
      iR++;
    }
    if ( iG > iG2 )
    {
      iG--;
    }
    if ( iG < iG2 )
    {
      iG++;
    }
    if ( iB > iB2 )
    {
      iB--;
    }
    if ( iB < iB2 )
    {
      iB++;
    }
    m_dwCurrentLight = ( iR << 16 ) + ( iG << 8 ) + iB;
  }

}



bool CWorld::Load()
{

  ClearUnits();
  m_bDone = false;
  m_fWindSpeedX = 0.0f;
  m_fWindSpeedY = 0.0f;
  m_WindDir = DIR_NONE;
  m_fGravity = 2.5f;

  char    szFileName[256];
  sprintf( szFileName, "data\\world%d.dat", m_iCurrentLevel );

  std::ifstream   ifLevel( szFileName );

  if ( !ifLevel )
  {
    return false;
  }

  while( ( !ifLevel.eof() )
  &&     ( !ifLevel.fail() ) )
  {
    std::string     strUnit;

    ifLevel >> strUnit;

    if ( strUnit == "Hero" )
    {
      CHero* pHero = new CHero();

      ifLevel >> pHero->m_fPosX;
      ifLevel >> pHero->m_fPosY;

      m_listUnits.push_back( pHero );
    }
    else if ( strUnit == "Weed" )
    {
      CWeed* pUnit = new CWeed();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "Exit" )
    {
      CExit* pUnit = new CExit();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "Relict" )
    {
      CRelict* pUnit = new CRelict();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "EyeStick" )
    {
      CEyeStick* pUnit = new CEyeStick();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;

      std::string   strColor;
      ifLevel >> strColor;

      if ( strColor == "Red" )
      {
        pUnit->m_Color = CEyeStick::COL_RED;
      }
      if ( strColor == "Blue" )
      {
        pUnit->m_Color = CEyeStick::COL_BLUE;
      }
      if ( strColor == "Yellow" )
      {
        pUnit->m_Color = CEyeStick::COL_YELLOW;
      }

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "Sponge" )
    {
      CSponge* pUnit = new CSponge();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "Earth" )
    {
      CEarth* pUnit = new CEarth();

      ifLevel >> pUnit->m_fPosX;
      ifLevel >> pUnit->m_fPosY;
      ifLevel >> pUnit->iWidth;
      ifLevel >> pUnit->iHeight;

      m_listUnits.push_back( pUnit );
    }
    else if ( strUnit == "Wind" )
    {
      m_WindDir = DIR_NONE;

      ifLevel >> m_fWindSpeedX;
      ifLevel >> m_fWindSpeedY;

      if ( m_fWindSpeedX < 0.0f )
      {
        m_WindDir = DIR_W;
      }
      if ( m_fWindSpeedX > 0.0f )
      {
        m_WindDir = DIR_E;
      }
      if ( m_fWindSpeedY < 0.0f )
      {
        m_WindDir = DIR_N;
      }
      if ( m_fWindSpeedY > 0.0f )
      {
        m_WindDir = DIR_S;
      }
    }
  }

  theApp.PlaySound( theApp.m_pSoundAreYouReady );

  return true;

}



bool CWorld::Intersect( SDL_Rect& rc1, SDL_Rect& rc2 )
{

  if ( ( rc1.x > rc2.x + rc2.w )
  ||   ( rc1.x + rc1.w < rc2.x )
  ||   ( rc1.y > rc2.y + rc2.h )
  ||   ( rc1.y + rc1.h < rc2.y ) )
  {
    return false;
  }
  return true;

}



void CWorld::Collision( CUnit* pUnit1, CUnit* pUnit2 )
{

  if ( ( pUnit1->m_Type == CUnit::UT_HERO )
  &&   ( ( pUnit2->m_Type == CUnit::UT_WEED )
  ||     ( pUnit2->m_Type == CUnit::UT_SPONGE )
  ||     ( pUnit2->m_Type == CUnit::UT_EARTH ) ) )
  {
    pUnit1->m_bRemoveMe = true;
    theApp.PlaySound( theApp.m_pSoundDie );
    theApp.PlaySound( theApp.m_pSoundFailed );

    m_bFailed = true;
  }
  if ( ( pUnit1->m_Type == CUnit::UT_HERO )
  &&   ( pUnit2->m_Type == CUnit::UT_RELICT ) )
  {
    ( (CHero*)pUnit1 )->m_bRelictCollected = true;
    pUnit2->m_bRemoveMe = true;

    theApp.PlaySound( theApp.m_pSoundHalleluja );
  }
  if ( ( pUnit1->m_Type == CUnit::UT_HERO )
  &&   ( pUnit2->m_Type == CUnit::UT_EXIT ) )
  {
    // TODO done
    if ( ( (CHero*)pUnit1 )->m_bRelictCollected )
    {
      m_bDone = true;
      theApp.PlaySound( theApp.m_pSoundWellDone );
    }
  }

}



void CWorld::ClearUnits()
{

  tListUnits::iterator    it( m_listUnits.begin() );
  while ( it != m_listUnits.end() )
  {
    delete *it;

    ++it;
  }
  m_listUnits.clear();

}