
#ifdef WIN32 //Change me...
#include <windows.h>
#include <commctrl.h>
#include <process.h>
#else
#include <string.h>
#include "winlnxdefs.h"
#endif

#ifdef QT4_GUI
# include <QMessageBox>
#endif

#include <wes_gl.h>

#include "glN64.h"
#include "Debug.h"
#include "Zilmar GFX 1.3.h"
#include "OpenGL.h"
#include "N64.h"
#include "RSP.h"
#include "RDP.h"
#include "VI.h"
#include "Config.h"
#include "Textures.h"
#include "Combiner.h"

HWND        hWnd;
#ifndef __LINUX__
HWND        hStatusBar;
//HWND      hFullscreen;
HWND        hToolBar;
HINSTANCE   hInstance;
#endif // !__LINUX__

char        pluginName[] = "gles2N64 v0.0.2";
char        *screenDirectory;
u32 last_good_ucode = (u32) -1;
void        (*CheckInterrupts)( void );
char        configdir[PATH_MAX] = {0};
void        (*renderCallback)() = NULL;

#ifndef __LINUX__
LONG        windowedStyle;
LONG        windowedExStyle;
RECT        windowedRect;
HMENU       windowedMenu;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
    hInstance = hinstDLL;

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        Config_LoadConfig();
        OGL.hRC = NULL;
        OGL.hDC = NULL;
    }
    return TRUE;
}
#else
void
_init( void )
{
    Config_LoadConfig();
    OGL.hScreen = NULL;
# ifdef RSPTHREAD
    RSP.thread = NULL;
# endif
}
#endif // !__LINUX__

EXPORT void CALL CaptureScreen ( char * Directory )
{
    screenDirectory = Directory;
#ifdef RSPTHREAD
    if (RSP.thread)
    {
#ifdef WIN32
        SetEvent( RSP.threadMsg[RSPMSG_CAPTURESCREEN] );
        WaitForSingleObject( RSP.threadFinished, INFINITE );
#else
        RSP.threadIdle = 0;
        RSP.threadEvents.push(RSPMSG_CAPTURESCREEN);
        while(!RSP.threadIdle){SDL_Delay(1);};
#endif
    }
#else
    OGL_SaveScreenshot();
#endif
}

EXPORT void CALL ChangeWindow (void)
{
#ifdef __LINUX__
    SDL_WM_ToggleFullScreen( OGL.hScreen );
#else
#ifdef RSPTHREAD
    // Textures seem to get corrupted when changing video modes (at least on my Radeon), so destroy them
    SetEvent( RSP.threadMsg[RSPMSG_DESTROYTEXTURES] );
    WaitForSingleObject( RSP.threadFinished, INFINITE );

    if (!OGL.fullscreen)
    {
        DEVMODE fullscreenMode;
        memset( &fullscreenMode, 0, sizeof(DEVMODE) );
        fullscreenMode.dmSize = sizeof(DEVMODE);
        fullscreenMode.dmPelsWidth          = OGL.fullscreenWidth;
        fullscreenMode.dmPelsHeight         = OGL.fullscreenHeight;
        fullscreenMode.dmBitsPerPel         = OGL.fullscreenBits;
        fullscreenMode.dmDisplayFrequency   = OGL.fullscreenRefresh;
        fullscreenMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        if (ChangeDisplaySettings( &fullscreenMode, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL)
        {
            MessageBox( NULL, "Failed to change display mode", pluginName, MB_ICONERROR | MB_OK );
            return;
        }

        ShowCursor( FALSE );

        windowedMenu = GetMenu( hWnd );

        if (windowedMenu)
            SetMenu( hWnd, NULL );

        if (hStatusBar)
            ShowWindow( hStatusBar, SW_HIDE );

        windowedExStyle = GetWindowLong( hWnd, GWL_EXSTYLE );
        windowedStyle = GetWindowLong( hWnd, GWL_STYLE );

        SetWindowLong( hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST );
        SetWindowLong( hWnd, GWL_STYLE, WS_POPUP );

        GetWindowRect( hWnd, &windowedRect );

        OGL.fullscreen = TRUE;
        OGL_ResizeWindow();
    }
    else
    {
        ChangeDisplaySettings( NULL, 0 );

        ShowCursor( TRUE );

        if (windowedMenu)
            SetMenu( hWnd, windowedMenu );

        if (hStatusBar)
            ShowWindow( hStatusBar, SW_SHOW );

        SetWindowLong( hWnd, GWL_STYLE, windowedStyle );
        SetWindowLong( hWnd, GWL_EXSTYLE, windowedExStyle );
        SetWindowPos( hWnd, NULL, windowedRect.left, windowedRect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE );

        OGL.fullscreen = FALSE;
        OGL_ResizeWindow();
    }

    SetEvent( RSP.threadMsg[RSPMSG_INITTEXTURES] );
    WaitForSingleObject( RSP.threadFinished, INFINITE );
#endif // !RSPTHREAD
#endif // __LINUX__
}

EXPORT void CALL CloseDLL (void)
{
}

EXPORT void CALL DllAbout ( HWND hParent )
{
#ifndef __LINUX__
    MessageBox( hParent, "glN64 v0.4 by Orkin\n\nWebsite: http://gln64.emulation64.com/\n\nThanks to Clements, Rice, Gonetz, Malcolm, Dave2001, cryhlove, icepir8, zilmar, Azimer, and StrmnNrmn", pluginName, MB_OK | MB_ICONINFORMATION );
#else
# ifdef QT4_GUI
    QMessageBox::about(QWidget::find(hParent),
                        "About glN64",
                        "glN64 v0.4 by Orkin\nWebsite: http://gln64.emulation64.com/\n\nThanks to Clements, Rice, Gonetz, Malcolm, Dave2001, cryhlove, icepir8, zilmar, Azimer, and StrmnNrmn\nported by blight\nQt4 interface by slougi");
# else
    puts( "glN64 v0.4 by Orkin\nWebsite: http://gln64.emulation64.com/\n\nThanks to Clements, Rice, Gonetz, Malcolm, Dave2001, cryhlove, icepir8, zilmar, Azimer, and StrmnNrmn\nported by blight" );
# endif // QT4_GUI
#endif
}

EXPORT void CALL DllConfig ( HWND hParent )
{
    Config_DoConfig(hParent);
}

EXPORT void CALL DllTest ( HWND hParent )
{
#ifdef QT4_GUI
    QMessageBox::information(QWidget::find(hParent),
                              "glN64 Test",
                              "This plugin has nothing to test.");
#endif
}

EXPORT void CALL DrawScreen (void)
{
}

EXPORT void CALL GetDllInfo ( PLUGIN_INFO * PluginInfo )
{

    PluginInfo->Version = 0x101;
    PluginInfo->Type = PLUGIN_TYPE_GFX;
    strcpy( PluginInfo->Name, pluginName);
    PluginInfo->NormalMemory = FALSE;
    PluginInfo->MemoryBswaped = TRUE;
}

#ifndef __LINUX__
BOOL CALLBACK FindToolBarProc( HWND hWnd, LPARAM lParam )
{
    if (GetWindowLong( hWnd, GWL_STYLE ) & RBS_VARHEIGHT)
    {
        hToolBar = hWnd;
        return FALSE;
    }
    return TRUE;
}
#endif // !__LINUX__

EXPORT BOOL CALL InitiateGFX (GFX_INFO Gfx_Info)
{
    hWnd = Gfx_Info.hWnd;

#ifndef __LINUX__
    hStatusBar = Gfx_Info.hStatusBar;
    hToolBar = NULL;

    EnumChildWindows( hWnd, FindToolBarProc,0 );
    Config_LoadConfig();
    OGL.hScreen = NULL;
#else // !__LINUX__
    Config_LoadConfig();
    OGL.hScreen = NULL;
# ifdef RSPTHREAD
    RSP.thread = NULL;
# endif
#endif // __LINUX__
    DMEM = Gfx_Info.DMEM;
    IMEM = Gfx_Info.IMEM;
    RDRAM = Gfx_Info.RDRAM;

    REG.MI_INTR = (u32*) Gfx_Info.MI_INTR_REG;
    REG.DPC_START = (u32*) Gfx_Info.DPC_START_REG;
    REG.DPC_END = (u32*) Gfx_Info.DPC_END_REG;
    REG.DPC_CURRENT = (u32*) Gfx_Info.DPC_CURRENT_REG;
    REG.DPC_STATUS = (u32*) Gfx_Info.DPC_STATUS_REG;
    REG.DPC_CLOCK = (u32*) Gfx_Info.DPC_CLOCK_REG;
    REG.DPC_BUFBUSY = (u32*) Gfx_Info.DPC_BUFBUSY_REG;
    REG.DPC_PIPEBUSY = (u32*) Gfx_Info.DPC_PIPEBUSY_REG;
    REG.DPC_TMEM = (u32*) Gfx_Info.DPC_TMEM_REG;

    REG.VI_STATUS = (u32*) Gfx_Info.VI_STATUS_REG;
    REG.VI_ORIGIN = (u32*) Gfx_Info.VI_ORIGIN_REG;
    REG.VI_WIDTH = (u32*) Gfx_Info.VI_WIDTH_REG;
    REG.VI_INTR = (u32*) Gfx_Info.VI_INTR_REG;
    REG.VI_V_CURRENT_LINE = (u32*) Gfx_Info.VI_V_CURRENT_LINE_REG;
    REG.VI_TIMING = (u32*) Gfx_Info.VI_TIMING_REG;
    REG.VI_V_SYNC = (u32*) Gfx_Info.VI_V_SYNC_REG;
    REG.VI_H_SYNC = (u32*) Gfx_Info.VI_H_SYNC_REG;
    REG.VI_LEAP = (u32*) Gfx_Info.VI_LEAP_REG;
    REG.VI_H_START = (u32*) Gfx_Info.VI_H_START_REG;
    REG.VI_V_START = (u32*) Gfx_Info.VI_V_START_REG;
    REG.VI_V_BURST = (u32*) Gfx_Info.VI_V_BURST_REG;
    REG.VI_X_SCALE = (u32*) Gfx_Info.VI_X_SCALE_REG;
    REG.VI_Y_SCALE = (u32*) Gfx_Info.VI_Y_SCALE_REG;

    CheckInterrupts = Gfx_Info.CheckInterrupts;

    return TRUE;
}

EXPORT void CALL MoveScreen (int xpos, int ypos)
{
}

int Frame = 0;
EXPORT void CALL ProcessDList(void)
{
    Frame++;
    if ((Frame % OGL.frameSkip) == 0 || OGL.frameSkip == 0)
    {

    #ifdef RSPTHREAD
        if (RSP.thread)
        {
    #ifdef WIN32
            SetEvent( RSP.threadMsg[RSPMSG_PROCESSDLIST] );
            WaitForSingleObject( RSP.threadFinished, INFINITE );
    #else
            RSP.threadIdle = 0;
            RSP.threadEvents.push(RSPMSG_PROCESSDLIST);
            //while(!RSP.threadIdle){SDL_Delay(1);};
    #endif
        }
    #else
        RSP_ProcessDList();
    #endif
    } else {
        RSP.busy = FALSE;
        RSP.DList++;
    }
}

EXPORT void CALL ProcessRDPList(void)
{

}

EXPORT void CALL RomClosed (void)
{
#ifdef RSPTHREAD
    int i;

    if (RSP.thread)
    {
//      if (OGL.fullscreen)
//          ChangeWindow();

        if (RSP.busy)
        {
            RSP.halt = TRUE;
#ifdef WIN32
            WaitForSingleObject( RSP.threadFinished, INFINITE );
#else
            RSP.threadIdle = 0;
            while(!RSP.threadIdle){SDL_Delay(1);};
#endif
        }

#ifdef WIN32
        SetEvent( RSP.threadMsg[RSPMSG_CLOSE] );
        WaitForSingleObject( RSP.threadFinished, INFINITE );
        for (i = 0; i < 4; i++)
            if (RSP.threadMsg[i])
                CloseHandle( RSP.threadMsg[i] );
        CloseHandle( RSP.threadFinished );
        CloseHandle( RSP.thread );
#else
        RSP.threadIdle = 0;
        RSP.threadEvents.push(RSPMSG_CLOSE);
        while(!RSP.threadIdle){SDL_Delay(1);};
        SDL_KillThread(RSP.thread);
#endif
    }

    RSP.thread = NULL;
#else
    OGL_Stop();
#endif

#ifdef DEBUG
    CloseDebugDlg();
#endif
}

EXPORT void CALL RomOpen (void)
{
#ifdef RSPTHREAD
# ifdef WIN32
    DWORD threadID;
    int i;

    // Create RSP message events
    for (i = 0; i < 6; i++)
    {
        RSP.threadMsg[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
        if (RSP.threadMsg[i] == NULL)
        {
            MessageBox( hWnd, "Error creating video thread message events, closing video thread...", "glN64 Error", MB_OK | MB_ICONERROR );
            return;
        }
    }

    // Create RSP finished event
    RSP.threadFinished = CreateEvent( NULL, FALSE, FALSE, NULL );
    if (RSP.threadFinished == NULL)
    {
        MessageBox( hWnd, "Error creating video thread finished event, closing video thread...", "glN64 Error", MB_OK | MB_ICONERROR );
        return;
    }

    RSP.thread = CreateThread( NULL, 4096, RSP_ThreadProc, NULL, NULL, &threadID );
    WaitForSingleObject( RSP.threadFinished, INFINITE );
# else //
    RSP.threadIdle = 1;
    while(!RSP.threadEvents.empty()){RSP.threadEvents.pop();}
    RSP.thread = SDL_CreateThread(RSP_ThreadProc, NULL);
# endif //WIN32
#else


    RSP_Init();
#endif

    OGL_ResizeWindow();

#ifdef DEBUG
    OpenDebugDlg();
#endif
}

EXPORT void CALL ShowCFB (void)
{
}

EXPORT void CALL UpdateScreen (void)
{
#ifdef RSPTHREAD
    if (RSP.thread)
    {
#ifdef WIN32
        SetEvent( RSP.threadMsg[RSPMSG_UPDATESCREEN] );
        WaitForSingleObject( RSP.threadFinished, INFINITE );
#else
        RSP.threadIdle = 0;
        RSP.threadEvents.push(RSPMSG_UPDATESCREEN);
//        while(!RSP.threadIdle){SDL_Delay(1);};
#endif
    }
#else
    VI_UpdateScreen();
#endif
}

EXPORT void CALL ViStatusChanged (void)
{
}

EXPORT void CALL ViWidthChanged (void)
{
}


EXPORT void CALL ReadScreen (void **dest, int *width, int *height)
{
    OGL_ReadScreen( dest, width, height );
}

EXPORT void CALL SetConfigDir (char *configDir)
{
    strncpy(configdir, configDir, PATH_MAX);
}

EXPORT void CALL SetRenderingCallback(void (*callback)())
{
    renderCallback = callback;
}
