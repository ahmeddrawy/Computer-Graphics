#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <math.h>    /// added by Hanafy
#include <bits/stdc++.h> /// added by Hanafy
#include <tchar.h>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
int Round(double x){ /// utility function
    return (int)x+0.5;
}

void draw8points(HDC hdc,int xc , int yc , int x,  int y ,COLORREF c){
    SetPixel(hdc , x + xc  , y+yc , c);
    SetPixel(hdc , -x + xc  , y+yc , c);
    SetPixel(hdc , x + xc  , -y+yc , c);
    SetPixel(hdc , -x + xc  , -y+yc , c);

    SetPixel(hdc , y + xc  , x+yc , c);
    SetPixel(hdc , -y + xc  , x+yc , c);
    SetPixel(hdc , y + xc  , -x+yc , c);
    SetPixel(hdc , -y + xc  , -x+yc , c);

}
using namespace std;
void DrawCirclePolar(HDC hdc,int xc, int yc , int R ,COLORREF c ){
    int x = R , y = 0 ;
    double dtheta = 1.0/R;
    draw8points(hdc ,xc , yc , x,y,c);
    for(double theta = 0 ; theta < M_PI/4 ; theta +=dtheta ){
        x= Round(R * cos(theta));
        y= Round(R * sin(theta));
        draw8points(hdc ,xc , yc , x,y,c);

    }
}
/// exploiting the similarity in 8 points and solve it iteratively
void ImprovedCirclePolar(HDC hdc , int xc , int yc , int R , COLORREF c){
    int x = R , y = 0 ;
    double dtheta = 1.0/R ;
    double cosDeltaTheta = cos(dtheta);
    double sinDeltaTheta = sin(dtheta);
    while(x > y){

        int nx = Round(x*cosDeltaTheta - y * sinDeltaTheta);    ///trig
        int ny=  Round(x*sinDeltaTheta + y*cosDeltaTheta);
        draw8points(hdc , xc, yc,nx,ny,c);
        x = nx , y=ny;
    }
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc= GetDC(hwnd);
    DrawCirclePolar(hdc , 50 , 50 , 20 , RGB(0,0,0));
    DrawCirclePolar(hdc , 100 , 100 , 20 , RGB(0,0,0));

    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
