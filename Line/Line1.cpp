#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <math.h>    /// added by Hanafy
#include <bits/stdc++.h> /// added by Hanafy
#include <tchar.h>
#include <windows.h>
using namespace std;
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
/// drawing line in the 1st quadrant using the line equation
void drawLine(HDC hdc,int x1 , int y1 , int x2 , int y2 , COLORREF c){
    int dx = x1 - x2, dy = y1 - y2;
    if(abs(dx) >abs(dy)){ /// change in x
        if(x1>x2){
            swap(x1, x2);
            swap(y1,y2);
        }
        SetPixel(hdc , x1, y1,c);
        for(int x = x1+1; x<=x2 ; ++x){
            double y = (1.0*dy/dx)*(x-x1) + y1;
            SetPixel(hdc, x , Round(y) , c);

        }
    }
    else {  /// change in y
        if(y1>y2){
            swap(x1, x2);
            swap(y1,y2);
        }
        SetPixel(hdc , x1, y1,c);
        for(int y = y1+1; y<=y2 ; ++y){
            double x = (1.0*dx/dy)*(y-y1) + x1;
            SetPixel(hdc, Round(x) ,y , c);

        }
    }

}
/// based on first difference draw
void drawLine2(HDC hdc,int x1 , int y1 , int x2 , int y2 , COLORREF c){
    int dx = x1 - x2 , dy = y1- y2;
    if(abs(dx) > abs(dy)){
        if(x1>x2){
            swap(x1, x2);
            swap(y1,y2);
        }
        double y = y1 ;
        SetPixel(hdc,  x1 , y1,c);
        double m = dy*1.0/dx;
        for(int x = x1+1 ; x<=x2 ; ++x){
            y+=m;
            SetPixel(hdc, x, Round(y),c);
        }


    }
    else {
        if(y1>y2){
            swap(x1, x2);
            swap(y1,y2);
        }
        double x = x1 ;
        SetPixel(hdc,  x1 , y1,c);
        double m_inv = dx*1.0/dy;
        for(int y = y1+1 ; y<=y2 ; ++y){
            x+=m_inv;
            SetPixel(hdc, Round(x), y,c);
        }

    }


}
/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc= GetDC(hwnd);
    //drawLine(hdc,0,0,100,50,RGB(0,0,0));
    drawLine2(hdc,0,200,200,0,RGB(0,0,0));
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
