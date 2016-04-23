#pragma once

#include <list>
#include <map>

#include "resource.h"

#include "SDL.h"
#include "SDL_Mixer.h"

#include "World.h"



class CSDLApp
{

  public:

    std::map<char,SDL_Surface*> m_mapFont;

    std::list<SDL_Surface*>     m_listSurfaces;

    std::list<Mix_Chunk*>       m_listSounds;

    SDL_Surface*                m_pScreen;

    bool                        m_bRunning;

    bool                        m_bGameRunning,
                                m_bTitleMode,
                                m_bMouseButtonReleased,
                                m_bEscapeReleased,
                                m_bDoneMode;

    float                       m_fTitleAnim;

    SDL_Event                   m_Event;

    int                         m_iMouseX,
                                m_iMouseY,
                                m_iMouseButtons;

    Uint32                      m_dwLastTicks;

    Uint8*                      m_pKeyState;

    CWorld                      m_World;



    SDL_Surface*                m_pImageHero;
    SDL_Surface*                m_pImageUnits;
    SDL_Surface*                m_pImageGUI;
    SDL_Surface*                m_pImageWorld;
    SDL_Surface*                m_pImageTitle;

    Mix_Chunk*                  m_pSoundSwitch;
    Mix_Chunk*                  m_pSoundWellDone;
    Mix_Chunk*                  m_pSoundFailed;
    Mix_Chunk*                  m_pSoundHalleluja;
    Mix_Chunk*                  m_pSoundAreYouReady;
    Mix_Chunk*                  m_pSoundDie;


    bool                        InitInstance();
    void                        ExitInstance();
    void                        Run();
    void                        DisplayFrame();
    void                        UpdateLogic( const float fElapsedTime );


    SDL_Surface*                LoadImage( const char* szFileName, Uint32 ulColorKey = 0 );
    void                        DrawImage( SDL_Surface* pImage, int iX, int iY );
    void                        DrawImage( SDL_Surface* pImage, int iX, int iY, int iSourceX, int iSourceY, int iW, int iH );

    Mix_Chunk*                  LoadSound( const char* szFileName );
    void                        PlaySound( Mix_Chunk* pSound );

    void                        PrintCentered( int iY, const char* szText );
    void                        Print( int iX, int iY, const char* szText );

};


extern CSDLApp     theApp;