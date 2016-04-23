// SDLCompo.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "SDLCompo.h"

#include <math.h>


CSDLApp     theApp;



bool CSDLApp::InitInstance()
{

  m_fTitleAnim = 0.0f;
  m_bDoneMode = false;

  if ( SDL_Init( SDL_INIT_AUDIO | SDL_INIT_VIDEO ) < 0 ) 
  {
    return false;
  }
  atexit( SDL_Quit ); 

  if ( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 2048 ) < 0 )
  {
    return false;
  }

  m_pScreen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );

  if ( m_pScreen == NULL )
  {
    return false;
  }

  if ( ( !( m_pImageUnits = LoadImage( "images\\units.bmp", 0x00ff00ff ) ) )
  ||   ( !( m_pImageGUI = LoadImage( "images\\gui.bmp" ) ) )
  ||   ( !( m_pImageWorld = LoadImage( "images\\world.bmp", 0xffff00ff ) ) )
  ||   ( !( m_pImageTitle = LoadImage( "images\\title.bmp" ) ) )
  ||   ( !( m_pImageHero = LoadImage( "images\\hero.bmp", 0x00ff00ff ) ) ) )
  {
    return false;
  }

  if ( ( !( m_pSoundSwitch        = LoadSound( "sounds\\click.wav" ) ) )
  ||   ( !( m_pSoundWellDone      = LoadSound( "sounds\\welldone.wav" ) ) )
  ||   ( !( m_pSoundFailed        = LoadSound( "sounds\\youfailedme.wav" ) ) )
  ||   ( !( m_pSoundHalleluja     = LoadSound( "sounds\\halleluja.wav" ) ) )
  ||   ( !( m_pSoundAreYouReady   = LoadSound( "sounds\\areyouready.wav" ) ) )
  ||   ( !( m_pSoundDie           = LoadSound( "sounds\\die.wav" ) ) ) )
  {
    return false;
  }

  // load Font - fugly, i know
  m_mapFont['A'] = LoadImage( "images\\font-a.bmp", 0xff000000 );
  m_mapFont['B'] = LoadImage( "images\\font-b.bmp", 0xff000000 );
  m_mapFont['C'] = LoadImage( "images\\font-c.bmp", 0xff000000 );
  m_mapFont['D'] = LoadImage( "images\\font-d.bmp", 0xff000000 );
  m_mapFont['E'] = LoadImage( "images\\font-e.bmp", 0xff000000 );
  m_mapFont['F'] = LoadImage( "images\\font-f.bmp", 0xff000000 );
  m_mapFont['G'] = LoadImage( "images\\font-g.bmp", 0xff000000 );
  m_mapFont['H'] = LoadImage( "images\\font-h.bmp", 0xff000000 );
  m_mapFont['I'] = LoadImage( "images\\font-i.bmp", 0xff000000 );
  m_mapFont['J'] = LoadImage( "images\\font-j.bmp", 0xff000000 );
  m_mapFont['K'] = LoadImage( "images\\font-k.bmp", 0xff000000 );
  m_mapFont['L'] = LoadImage( "images\\font-l.bmp", 0xff000000 );
  m_mapFont['M'] = LoadImage( "images\\font-m.bmp", 0xff000000 );
  m_mapFont['N'] = LoadImage( "images\\font-n.bmp", 0xff000000 );
  m_mapFont['O'] = LoadImage( "images\\font-o.bmp", 0xff000000 );
  m_mapFont['P'] = LoadImage( "images\\font-p.bmp", 0xff000000 );
  m_mapFont['Q'] = LoadImage( "images\\font-q.bmp", 0xff000000 );
  m_mapFont['R'] = LoadImage( "images\\font-r.bmp", 0xff000000 );
  m_mapFont['S'] = LoadImage( "images\\font-s.bmp", 0xff000000 );
  m_mapFont['T'] = LoadImage( "images\\font-t.bmp", 0xff000000 );
  m_mapFont['U'] = LoadImage( "images\\font-u.bmp", 0xff000000 );
  m_mapFont['V'] = LoadImage( "images\\font-v.bmp", 0xff000000 );
  m_mapFont['W'] = LoadImage( "images\\font-w.bmp", 0xff000000 );
  m_mapFont['X'] = LoadImage( "images\\font-x.bmp", 0xff000000 );
  m_mapFont['Y'] = LoadImage( "images\\font-y.bmp", 0xff000000 );
  m_mapFont['Z'] = LoadImage( "images\\font-z.bmp", 0xff000000 );
  m_mapFont['a'] = LoadImage( "images\\font-a-sm.bmp", 0xff000000 );
  m_mapFont['b'] = LoadImage( "images\\font-b-sm.bmp", 0xff000000 );
  m_mapFont['c'] = LoadImage( "images\\font-c-sm.bmp", 0xff000000 );
  m_mapFont['d'] = LoadImage( "images\\font-d-sm.bmp", 0xff000000 );
  m_mapFont['e'] = LoadImage( "images\\font-e-sm.bmp", 0xff000000 );
  m_mapFont['f'] = LoadImage( "images\\font-f-sm.bmp", 0xff000000 );
  m_mapFont['g'] = LoadImage( "images\\font-g-sm.bmp", 0xff000000 );
  m_mapFont['h'] = LoadImage( "images\\font-h-sm.bmp", 0xff000000 );
  m_mapFont['i'] = LoadImage( "images\\font-i-sm.bmp", 0xff000000 );
  m_mapFont['j'] = LoadImage( "images\\font-j-sm.bmp", 0xff000000 );
  m_mapFont['k'] = LoadImage( "images\\font-k-sm.bmp", 0xff000000 );
  m_mapFont['l'] = LoadImage( "images\\font-l-sm.bmp", 0xff000000 );
  m_mapFont['m'] = LoadImage( "images\\font-m-sm.bmp", 0xff000000 );
  m_mapFont['n'] = LoadImage( "images\\font-n-sm.bmp", 0xff000000 );
  m_mapFont['o'] = LoadImage( "images\\font-o-sm.bmp", 0xff000000 );
  m_mapFont['p'] = LoadImage( "images\\font-p-sm.bmp", 0xff000000 );
  m_mapFont['q'] = LoadImage( "images\\font-q-sm.bmp", 0xff000000 );
  m_mapFont['r'] = LoadImage( "images\\font-r-sm.bmp", 0xff000000 );
  m_mapFont['s'] = LoadImage( "images\\font-s-sm.bmp", 0xff000000 );
  m_mapFont['t'] = LoadImage( "images\\font-t-sm.bmp", 0xff000000 );
  m_mapFont['u'] = LoadImage( "images\\font-u-sm.bmp", 0xff000000 );
  m_mapFont['v'] = LoadImage( "images\\font-v-sm.bmp", 0xff000000 );
  m_mapFont['w'] = LoadImage( "images\\font-w-sm.bmp", 0xff000000 );
  m_mapFont['x'] = LoadImage( "images\\font-x-sm.bmp", 0xff000000 );
  m_mapFont['y'] = LoadImage( "images\\font-y-sm.bmp", 0xff000000 );
  m_mapFont['z'] = LoadImage( "images\\font-z-sm.bmp", 0xff000000 );
  m_mapFont['"'] = LoadImage( "images\\font-apostrophe.bmp", 0xff000000 );
  m_mapFont['!'] = LoadImage( "images\\font-!.bmp", 0xff000000 );
  m_mapFont['.'] = LoadImage( "images\\font-dot.bmp", 0xff000000 );
  m_mapFont[':'] = LoadImage( "images\\font-ddot.bmp", 0xff000000 );
  m_mapFont['?'] = LoadImage( "images\\font-questionmark.bmp", 0xff000000 );
  m_mapFont['0'] = LoadImage( "images\\font-0.bmp", 0xff000000 );
  m_mapFont['1'] = LoadImage( "images\\font-1.bmp", 0xff000000 );
  m_mapFont['2'] = LoadImage( "images\\font-2.bmp", 0xff000000 );
  m_mapFont['3'] = LoadImage( "images\\font-3.bmp", 0xff000000 );
  m_mapFont['4'] = LoadImage( "images\\font-4.bmp", 0xff000000 );
  m_mapFont['5'] = LoadImage( "images\\font-5.bmp", 0xff000000 );
  m_mapFont['6'] = LoadImage( "images\\font-6.bmp", 0xff000000 );
  m_mapFont['7'] = LoadImage( "images\\font-7.bmp", 0xff000000 );
  m_mapFont['8'] = LoadImage( "images\\font-8.bmp", 0xff000000 );
  m_mapFont['9'] = LoadImage( "images\\font-9.bmp", 0xff000000 );

  m_dwLastTicks = SDL_GetTicks();

  m_bTitleMode = true;

  m_bGameRunning = false;
  m_bMouseButtonReleased = true;

  return true;

}


void CSDLApp::ExitInstance()
{

  std::list<SDL_Surface*>::iterator   itSurfaces( m_listSurfaces.begin() );
  while ( itSurfaces != m_listSurfaces.end() )
  {
    SDL_FreeSurface( *itSurfaces );

    ++itSurfaces;
  }
  m_listSurfaces.clear();

  Mix_HaltChannel( -1 );
  std::list<Mix_Chunk*>::iterator   itSounds( m_listSounds.begin() );
  while ( itSounds != m_listSounds.end() )
  {
    Mix_FreeChunk( *itSounds );

    ++itSounds;
  }
  m_listSounds.clear();

}



void CSDLApp::DrawImage( SDL_Surface* pImage, int iX, int iY )
{

  if ( pImage == NULL )
  {
    return;
  }

  SDL_Rect    rcTarget;

  rcTarget.x = iX;
  rcTarget.y = iY;

  SDL_BlitSurface( pImage, NULL, m_pScreen, &rcTarget );

}



void CSDLApp::DrawImage( SDL_Surface* pImage, int iX, int iY, int iSourceX, int iSourceY, int iW, int iH )
{

  if ( pImage == NULL )
  {
    return;
  }

  SDL_Rect    rcTarget;

  rcTarget.x = iX;
  rcTarget.y = iY;

  SDL_Rect    rcSource;
  
  rcSource.x = iSourceX;
  rcSource.y = iSourceY;
  rcSource.w = iW;
  rcSource.h = iH;

  SDL_BlitSurface( pImage, &rcSource, m_pScreen, &rcTarget );

}



Mix_Chunk* CSDLApp::LoadSound( const char* szFileName )
{

  Mix_Chunk*    pSound = Mix_LoadWAV( szFileName );
  if ( pSound )
  {
    m_listSounds.push_back( pSound );
  }

  return pSound;

}



void CSDLApp::PlaySound( Mix_Chunk* pSound )
{

  Mix_PlayChannel( -1, pSound, 0 );

}



SDL_Surface* CSDLApp::LoadImage( const char* szFileName, Uint32 ulColorKey )
{

  SDL_Surface*    pImageOld = NULL;

  pImageOld = SDL_LoadBMP( szFileName );
  if ( pImageOld == NULL )
  {
    return NULL;
  }

  // need to set color key?
  if ( ulColorKey )
  {
    SDL_SetColorKey( pImageOld, 
                     SDL_SRCCOLORKEY, 
                     SDL_MapRGB( pImageOld->format, 
                                 (Uint8)( ( ulColorKey & 0xff0000 ) >> 16 ), 
                                 (Uint8)( ( ulColorKey & 0x00ff00 ) >> 8 ),
                                 (Uint8)( ulColorKey & 0x0000ff ) ) );
  }

  // convert to screen format
  SDL_Surface*    pImage = SDL_DisplayFormat( pImageOld );

  SDL_FreeSurface( pImageOld );

  if ( pImage == NULL )
  {
    return NULL;
  }

  m_listSurfaces.push_back( pImage );

  return pImage;

}



void CSDLApp::DisplayFrame()
{

  if ( m_bDoneMode )
  {
    SDL_FillRect( m_pScreen, NULL, SDL_MapRGB( m_pScreen->format, 0, 0, 0 ) );

    PrintCentered(  50, "Well, you managed to let your avatar survive!" );
    PrintCentered(  70, "And he brought a whole load of new relicts for" );
    PrintCentered(  90, "your people to worship!" );
    PrintCentered( 130, "With all the new found worshippers your power" );
    PrintCentered( 150, "is growing beyond any borders. Nothing can stop" );
    PrintCentered( 170, "you now!" );
    PrintCentered( 250, "Well done!" );
    PrintCentered( 290, "(Insert cheesy outro music here)" );

    PrintCentered( 420, "Click the mouse button to replay if you dare!" );
    PrintCentered( 440, "or press Escape to return to your mortal deeds..." );
  }
  else if ( m_bTitleMode )
  {
    SDL_FillRect( m_pScreen, NULL, SDL_MapRGB( m_pScreen->format, 0, 0, 0 ) );

    DrawImage( m_pImageTitle, ( 640 - m_pImageTitle->w ) / 2, 50 );

    PrintCentered( 150, "Written by Georg \"Endurion\" Rottensteiner 2004" );
    PrintCentered( 190, "You've got your own planet, and your avatar is in" );
    PrintCentered( 210, "deep trouble! Help him retrieve the lost relicts" );
    PrintCentered( 230, "from the caves of despair." );
    PrintCentered( 250, "Customize the planet's gravity and atmosphere to" );
    PrintCentered( 270, "your own needs. Guide the hero's balloon safely" );
    PrintCentered( 290, "through all the obstacles." );

    PrintCentered( 420, "Click the mouse button to play if you dare!" );
    PrintCentered( 440, "or press Escape to return to your mortal deeds..." );

    float     fEyeStickHeight = 20.0f + 20.0f * cosf( m_fTitleAnim );

    DrawImage( m_pImageUnits, 40 - 9, 380 - 19 - (int)fEyeStickHeight, 0, 192, 20, (int)fEyeStickHeight );
    DrawImage( m_pImageUnits, 40 - 9, 380 - 19, 40, 172, 20, 20 );

    DrawImage( m_pImageUnits, 600 - 9, 380 - 19 - (int)( 40.0f - fEyeStickHeight ), 0, 192, 20, (int)( 40.0f - fEyeStickHeight ) );
    DrawImage( m_pImageUnits, 600 - 9, 380 - 19, 20, 172, 20, 20 );

    if ( fEyeStickHeight < 13.0f )
    {
      DrawImage( m_pImageUnits, 320 - 30, 380 - 59, 0, 80, 60, 60 );

      if ( fmodf( m_fTitleAnim, 0.5f ) > 0.25f )
      {
        DrawImage( m_pImageUnits, 200 - 65, 380 - 39, 160, 120, 80, 40 );

        DrawImage( m_pImageUnits, 440 - 65, 380 - 39, 160, 120, 80, 40 );
      }
      else
      {
        DrawImage( m_pImageUnits, 200 - 65, 380 - 39, 120, 0, 80, 40 );

        DrawImage( m_pImageUnits, 440 - 65, 380 - 39, 120, 0, 80, 40 );
      }
    }
    else if ( fEyeStickHeight < 27.0f )
    {
      DrawImage( m_pImageUnits, 320 - 20, 380 - 39, 0, 40, 40, 40 );

      DrawImage( m_pImageUnits, 200 - 20, 380 - 39, 0, 0, 40, 40 );
      DrawImage( m_pImageUnits, 440 - 20, 380 - 39, 0, 0, 40, 40 );
    }
    else
    {
      DrawImage( m_pImageUnits, 320 - 10, 380 - 19, 60, 80, 20, 20 );

      if ( fmodf( m_fTitleAnim, 0.5f ) > 0.25f )
      {
        DrawImage( m_pImageUnits, 200 - 15, 380 - 39, 160, 80, 80, 40 );

        DrawImage( m_pImageUnits, 440 - 15, 380 - 39, 160, 80, 80, 40 );
      }
      else
      {
        DrawImage( m_pImageUnits, 200 - 15, 380 - 39, 120, 40, 80, 40 );

        DrawImage( m_pImageUnits, 440 - 15, 380 - 39, 120, 40, 80, 40 );
      }
    }
  }
  else
  {
    m_World.Display( *this );

    if ( !m_bGameRunning )
    {
      PrintCentered( 220, "Save the Hero!" );
      PrintCentered( 240, "Guide him to the exit!" );
    }
  }

}



void CSDLApp::UpdateLogic( const float fElapsedTime )
{

  if ( m_bDoneMode )
  {
    if ( ( m_iMouseButtons & SDL_BUTTON( 1 ) )
    &&   ( m_bMouseButtonReleased ) )
    {
      m_bMouseButtonReleased = false;
      m_bTitleMode = true;
      m_bDoneMode = false;
    }
  }
  else if ( m_bTitleMode )
  {
    m_fTitleAnim += fElapsedTime;
    if ( ( m_iMouseButtons & SDL_BUTTON( 1 ) )
    &&   ( m_bMouseButtonReleased ) )
    {
      m_bMouseButtonReleased = false;
      m_bTitleMode = false;
      m_World.m_iCurrentLevel = 1;
      if ( !m_World.Load() )
      {
        m_bTitleMode = true;
      }
    }
    if ( ( theApp.m_pKeyState[SDLK_ESCAPE] )
    &&   ( m_bEscapeReleased ) )
    {
      m_bEscapeReleased = false;
      m_bRunning = false;
    }
  }
  else if ( m_bGameRunning )
  {
    m_World.Update( fElapsedTime );
    if ( ( theApp.m_pKeyState[SDLK_ESCAPE] )
    &&   ( m_bEscapeReleased ) )
    {
      m_bEscapeReleased = false;
      m_bTitleMode = true;
    }
  }
  else
  {
    if ( ( m_iMouseButtons & SDL_BUTTON( 1 ) )
    &&   ( m_bMouseButtonReleased ) )
    {
      m_bMouseButtonReleased = false;
      m_bGameRunning = true;
    }
    if ( ( theApp.m_pKeyState[SDLK_ESCAPE] )
    &&   ( m_bEscapeReleased ) )
    {
      m_bEscapeReleased = false;
      m_World.ClearUnits();
      m_bTitleMode = true;
    }
  }

  if ( !( m_iMouseButtons & SDL_BUTTON( 1 ) ) )
  {
    m_bMouseButtonReleased = true;
  }
  if ( !theApp.m_pKeyState[SDLK_ESCAPE] )
  {
    m_bEscapeReleased = true;
  }

}



void CSDLApp::PrintCentered( int iY, const char* szText )
{

  int   iWidth = 0;

  for ( size_t i = 0; i < strlen( szText ); ++i )
  {
    if ( szText[i] == ' ' )
    {
      iWidth += 14;
      continue;
    }
    std::map<char,SDL_Surface*>::iterator   it( m_mapFont.find( szText[i] ) );

    if ( it != m_mapFont.end() )
    {
      SDL_Surface*    pSurface = it->second;

      if ( pSurface )
      {
        iWidth += 1 + pSurface->w;
      }
    }
  }

  Print( ( 640 - iWidth ) / 2, iY, szText );

}



void CSDLApp::Print( int iX, int iY, const char* szText )
{

  for ( size_t i = 0; i < strlen( szText ); ++i )
  {
    if ( szText[i] == ' ' )
    {
      iX += 14;
      continue;
    }
    std::map<char,SDL_Surface*>::iterator   it( m_mapFont.find( szText[i] ) );

    if ( it != m_mapFont.end() )
    {
      SDL_Surface*    pSurface = it->second;

      if ( pSurface )
      {
        DrawImage( pSurface, iX, iY );
        iX += 1 + pSurface->w;
      }
    }
  }

}



void CSDLApp::Run()
{

  if ( !InitInstance() )
  {
    ExitInstance();
    return;
  }

  m_bRunning = true;

  while ( m_bRunning )
  {
    SDL_PumpEvents();
    while ( SDL_PollEvent( &m_Event ) )
    {
      switch ( m_Event.type )
      {
        case SDL_QUIT:
          m_bRunning = false;
          break;
      }
    }
    m_iMouseButtons = SDL_GetMouseState( &m_iMouseX, &m_iMouseY );
    Uint32      dwElapsedTicks = SDL_GetTicks() - m_dwLastTicks;

    m_pKeyState = SDL_GetKeyState( NULL );

    UpdateLogic( (float)dwElapsedTicks / 1000.0f );
    m_dwLastTicks = SDL_GetTicks();

    DisplayFrame();

    SDL_Flip( m_pScreen );
  }

  ExitInstance();

}



int main( int argc, char* argv[] )
{

  theApp.Run();
  return 0;

}

