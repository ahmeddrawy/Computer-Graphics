#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <math.h>    /// added by Hanafy
#include <bits/stdc++.h> /// added by Hanafy
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
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

void drawLine(HDC hdc,int x1 , int y1 , int x2 , int y2 , COLORREF c){
    int dx = x1 - x2, dy = y1 - y2;
    if(abs(dx) >abs(dy)){ /// change in x
        if(x1>x2){
            std::swap(x1, x2);
            std::swap(y1,y2);
        }
        SetPixel(hdc , x1, y1,c);
        for(int x = x1+1; x<=x2 ; ++x){
            double y = (1.0*dy/dx)*(x-x1) + y1;
            SetPixel(hdc, x , Round(y) , c);

        }
    }
    else {  /// change in y
        if(y1>y2){
            std::swap(x1, x2);
            std::swap(y1,y2);
        }
        SetPixel(hdc , x1, y1,c);
        for(int y = y1+1; y<=y2 ; ++y){
            double x = (1.0*dx/dy)*(y-y1) + x1;
            SetPixel(hdc, Round(x) ,y , c);

        }
    }

}
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


/*  This function is called by the Windows function DispatchMessage()  */
int xx1 = -1 , yy1 = -1 , xx2 = 0 , yy2 = 0 , xx3 = 0 , yy3 = 0 ;
int cnt = 0 ;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc= GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:

            if(cnt%2 ==0  ){

                cnt++;
                xx1 = GET_X_LPARAM(lParam);
                yy1 = GET_Y_LPARAM(lParam);
                cout << "p1\n";
            }
            else {
                cnt++;
                xx2 = GET_X_LPARAM(lParam);
                yy2 = GET_Y_LPARAM(lParam);
                cout << "p2\n";

                //DrawCirclePolar(hdc , xx2,yy2,50 ,RGB(0,0,0) );
            }
            break;
        case WM_RBUTTONDOWN:
            cout <<"Right"<< cnt << endl;
            if((cnt>0) && (cnt%2==0) ){
                xx3 = GET_X_LPARAM(lParam);
                yy3 = GET_Y_LPARAM(lParam);
               // xx1 = 129 , yy1 = 58 , xx2 = 300 , yy2 = 57 , xx3 = 224;


                int dx = xx1 - xx2 ;
                int dy = yy1 - yy2 ;
                cout <<"dx = " << dx <<endl;
                cout <<"dy = " << dy <<endl;
                if(dx == 0){
                    xx3 = xx2;

                }
                else if(dy==0){
                    yy3 = yy2;
                }
                else {
                   // cout << 1.0*dy/dx
                    yy3 = Round(((1.0*dy)/dx) *(xx3 -xx2) + yy2);
                }
                cout << "p3\n";
                cout <<xx1 <<" " << yy1 << endl;
                cout <<xx2 <<" " << yy2 << endl;
                cout <<xx3 <<" " << yy3 << endl;

                int r1 = Round(sqrt((xx1-xx3)*(xx1-xx3) + (yy1-yy3)*(yy1-yy3)));
                int r2 = Round(sqrt((xx2-xx3)*(xx2-xx3) + (yy2-yy3)*(yy2-yy3)));
                cout <<r1 << " "<< r2 <<"\n";
                DrawCirclePolar(hdc , xx1,yy1,r1 ,RGB(0,0,0) );
                DrawCirclePolar(hdc, xx2 , yy2 ,r2 , RGB(0,0,0) );

            }
            break;



        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
