#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#define idTimer 25
#define time_stamp 25
#define idTimer54 25

LPSTR NazwaKlasy = "Klasa Okienna";
MSG Komunikat;
bool Przyc = false;
std::vector<double> roll, pitch;
int n;
double x=1;
double y=2500;
static int timeV = 0;

UINT nIdEvent;



LRESULT CALLBACK OkiennaProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );


HWND hPLUSXPrzycisk;
HWND hPLUSYPrzycisk;
HWND hMINUSXPrzycisk;
HWND hMINUSYPrzycisk;
HFONT hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );

void readRollAndPitch(std::vector<double> &a, std::vector<double> &b, std::string fileName)
{
    std::fstream myFile;
    myFile.open(fileName,std::ios::in);
    if (!myFile)
    {
        throw "Could not open file";
    }
    std::string line;
    double rollValue, pitchValue;
    while (std::getline(myFile, line))
    {
        myFile>>rollValue>>pitchValue;
        a.push_back(rollValue);
        b.push_back(pitchValue);
    }
}

double convertToRadians(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

double calculate_value(double roll, double pitch)
{
    double bigger=std::max(abs(roll),abs(pitch));
    double length=0.5;
    double biggerRadians=convertToRadians(bigger);
    double result=length*(1-cos(biggerRadians));
    return result;
}

void Draw(double xx, double yy, HDC hdc, HPEN PenR, HPEN PenB, HPEN PenG, HPEN PenW, HPEN PenVoid)
{
    for(int a=0; a<pitch.size()-1; a++)
    {
        if(a<timeV)
        {
            SelectObject( hdc, PenR );
        }
        else
        {
            SelectObject( hdc, PenVoid );
        }
        MoveToEx(hdc,101+a*xx,640-calculate_value(roll[a],pitch[a])*yy,0);
        LineTo(hdc,101+(1+a)*xx,640-calculate_value(roll[a+1],pitch[a+1])*yy);
        if(a<timeV)
        {
            SelectObject( hdc, PenB );
        }
        else
        {
            SelectObject( hdc, PenVoid );
        }
        MoveToEx(hdc,101+a*xx,640-convertToRadians(roll[a])*yy/25,0);
        LineTo(hdc,101+(1+a)*xx,640-convertToRadians(roll[a+1])*yy/25);
        if(a<timeV)
        {
            SelectObject( hdc, PenG );
        }
        else
        {
            SelectObject( hdc, PenVoid );
        }
        MoveToEx(hdc,101+a*xx,640-convertToRadians(pitch[a])*yy/25,0);
        LineTo(hdc,101+(1+a)*xx,640-convertToRadians(pitch[a+1])*yy/25);
    }
    SelectObject( hdc, PenW );
    MoveToEx(hdc,100,640,0);
    LineTo(hdc,1200,640);
}

void CALLBACK timer(HWND hwnd, UINT message, UINT timer_id, DWORD dwTime)
{

    HDC hdcWin = GetDC(hwnd);
    HPEN PenRed, PenWhite, PenBlack, PenBlue, PenGreen;
    PenRed = CreatePen( PS_SOLID, 2, 0x0000FF );
    PenBlue = CreatePen( PS_SOLID, 2, 0xFF0000 );
    PenGreen = CreatePen( PS_SOLID, 2, 0x00FF00 );
    PenWhite = CreatePen( PS_SOLID, 1, 0xFFFFFF );
    PenBlack = CreatePen( PS_SOLID, 2, 0x000000 );
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = GetDC(hwnd);

    switch(timer_id)
    {
    case (idTimer54):

        timeV++;

        Draw(x, y, hdc, PenRed, PenBlue, PenGreen, PenWhite, PenBlack);
        if(timeV>pitch.size())
        {
            KillTimer(hwnd, idTimer54);
        }
        break;
    }
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    WNDCLASSEX okno;
    okno.cbSize = sizeof( WNDCLASSEX );
    okno.style = 0;
    okno.lpfnWndProc = OkiennaProc;
    okno.cbClsExtra = 0;
    okno.cbWndExtra = 0;
    okno.hInstance = hInstance;
    okno.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    okno.hCursor = LoadCursor( NULL, IDC_ARROW );
    okno.hbrBackground =( HBRUSH )( COLOR_WINDOW + 5 );
    okno.lpszMenuName = NULL;
    okno.lpszClassName = NazwaKlasy;
    okno.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    readRollAndPitch(roll,pitch,"outputPendulum01.log");
    std::cout<<"How many rows should we delete?"<<std::endl;
    std::cin>>n;
    roll.erase(roll.begin(), roll.begin() + n);
    pitch.erase(pitch.begin(), pitch.begin() + n);
    if( !RegisterClassEx( & okno ) )
    {
        MessageBox( NULL, "error!", "brrrr",
                    MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }
    HWND hwnd;
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "swing", WS_OVERLAPPEDWINDOW | WS_VISIBLE,CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, NULL, NULL, hInstance, NULL );
    HWND h1Static = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_CENTER, 10, 10, 100, 20, hwnd, NULL, hInstance, NULL );
    SetWindowText( h1Static, "wysokosc" );
    HWND h2Static = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_CENTER, 10, 35, 100, 20, hwnd, NULL, hInstance, NULL );
    SetWindowText( h2Static, "kat pitch" );
    HWND h3Static = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_CENTER, 10, 60, 100, 20, hwnd, NULL, hInstance, NULL );
    SetWindowText( h3Static, "kat roll" );
    hPLUSYPrzycisk = CreateWindowEx( 0, "BUTTON", "+", WS_CHILD | WS_VISIBLE,10, 100, 50, 30, hwnd, NULL, hInstance, NULL );
    hMINUSYPrzycisk = CreateWindowEx( 0, "BUTTON", "-", WS_CHILD | WS_VISIBLE,10, 130, 50, 30, hwnd, NULL, hInstance, NULL );
    hPLUSXPrzycisk = CreateWindowEx( 0, "BUTTON", "+", WS_CHILD | WS_VISIBLE,50, 650, 50, 30, hwnd, NULL, hInstance, NULL );
    hMINUSXPrzycisk = CreateWindowEx( 0, "BUTTON", "-", WS_CHILD | WS_VISIBLE,0, 650, 50, 30, hwnd, NULL, hInstance, NULL );
    if( hwnd == NULL )
    {
        MessageBox( NULL, "error", "brrrr", MB_ICONEXCLAMATION );
        return 1;
    }
    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

LRESULT CALLBACK OkiennaProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam  )
{
    SetTimer(hwnd, idTimer, time_stamp, (TIMERPROC) timer);
    HDC hdc;
    hdc = GetDC( hwnd );
    PAINTSTRUCT ps;
    HPEN PenRed, PenWhite, PenBlack, PenBlue, PenGreen;
    PenRed = CreatePen( PS_SOLID, 2, 0x0000FF );
    PenBlue = CreatePen( PS_SOLID, 2, 0xFF0000 );
    PenGreen = CreatePen( PS_SOLID, 2, 0x00FF00 );
    PenWhite = CreatePen( PS_SOLID, 1, 0xFFFFFF );
    PenBlack = CreatePen( PS_SOLID, 2, 0x000000 );
    switch( msg )
    {
    case WM_TIMER:
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        SelectObject( hdc, PenWhite );
        MoveToEx(hdc,100,640,0);
        LineTo(hdc,1200,640);
        MoveToEx(hdc,100,640,0);
        LineTo(hdc,100,100);


        SelectObject( hdc, PenRed );
        MoveToEx(hdc,120,20,0);
        LineTo(hdc,150,20);
        SelectObject( hdc, PenGreen );
        MoveToEx(hdc,120,45,0);
        LineTo(hdc,150,45);
        SelectObject( hdc, PenBlue );
        MoveToEx(hdc,120,70,0);
        LineTo(hdc,150,70);
        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    case WM_COMMAND:

        if(( HWND ) lParam == hPLUSYPrzycisk )
        {
            Draw(x, y, hdc, PenBlack, PenBlack, PenBlack, PenWhite, PenBlack);
            y=y*1.5;
        }
        if(( HWND ) lParam == hMINUSYPrzycisk )
        {
            Draw(x, y, hdc, PenBlack, PenBlack, PenBlack, PenWhite, PenBlack);
            y=y/1.5;
        }
        if(( HWND ) lParam == hPLUSXPrzycisk )
        {
            Draw(x, y, hdc, PenBlack, PenBlack, PenBlack, PenWhite, PenBlack);
            x=x*1.5;
        }
        if(( HWND ) lParam == hMINUSXPrzycisk )
        {
            Draw(x, y, hdc, PenBlack, PenBlack, PenBlack, PenWhite, PenBlack);
            x=x/1.5;
        }
        break;
    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    return 0;
}
