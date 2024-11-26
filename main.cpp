#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <d2d1.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include "include/tick.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define radian (M_PI/180.0)
#pragma comment(lib,"d2d1")
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void painting(HWND hwnd,PAINTSTRUCT &ps);
class Gbr{
    private:
        //HWND mhwnd;
        PAINTSTRUCT &mps;
        HDC mhd;
        COLORREF mcb=RGB(0,0,0);
        COLORREF mcp=RGB(0,0,0);
    public:
        Gbr(PAINTSTRUCT &ps,HDC hd):mps(ps),mhd(hd){
        }
        Gbr brush(int r,int g,int b){
            mcb =RGB(r,g,b);
            return *this;
        }
        Gbr pen(int r,int g,int b){
            mcp = RGB(r,g,b);
            return *this;
        }
        void poli(const std::vector<POINT>& vec){
           // std::size_t uk = vec.size();
            //int* arr = new int[uk];
            //std::copy(vec.begin(),vec.end(),arr);
            SetDCPenColor(mhd,mcp);
            SetDCBrushColor(mhd,mcb);
            SelectObject(mhd,GetStockObject(DC_BRUSH));
            SelectObject(mhd,GetStockObject(DC_PEN));
            Polygon(mhd,vec.data(),vec.size());
        }
        void line(POINT a,POINT b){
            HPEN hpen=CreatePen(PS_SOLID,1,mcp);
            HPEN hold=(HPEN) SelectObject(mhd,hpen);
            MoveToEx(mhd,a.x,a.y,NULL);
            LineTo(mhd,b.x,b.y);
            SelectObject(mhd,hold);
            DeleteObject(hpen);
        }
        void rect(int x,int y,int px,int py)
        {
            px =x+px;
            py =y+py;
            SetDCPenColor(mhd,mcp);
            SetDCBrushColor(mhd,mcb);
            SelectObject(mhd,GetStockObject(DC_BRUSH));
            SelectObject(mhd,GetStockObject(DC_PEN));
            Rectangle(mhd,x,y,px,py);
        }
        void text(int x,int y,const wchar_t* te){
            SetDCPenColor(mhd,mcp);
            SetDCBrushColor(mhd,mcb);
            SelectObject(mhd,GetStockObject(DC_BRUSH));
            SelectObject(mhd,GetStockObject(DC_PEN));
            TextOut(mhd,x,y,te,wcslen(te));
        }
        //void poli(){}
};
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"for a god sake",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
bool cursor = true;
HBITMAP bitmapbuff =NULL;
unsigned char wasd= 0b0000;
bool upsize=false;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_SIZE:{
        upsize = true;
        break;
        }
        case WM_MOUSEMOVE:
        if(!cursor){
            RECT raf;
            if(GetWindowRect(hwnd,&raf)){
                int with=(raf.right+raf.left)/2;
                int hedh=(raf.bottom+raf.top)/2;
                POINT pp ;
                GetCursorPos(&pp);
                int dx = pp.x-with;
                int dy = pp.y-hedh;
                player::rotasi(player::rx+(dx/1.5),player::ry+(dy/1.5));
                SetCursorPos(with,hedh);

            }
        }
        break;
        case WM_KEYUP:
            switch (wParam)
            {
                case 'P':
                    cursor =!cursor;
                    ShowCursor(cursor);
                break;
            case 'W':
                wasd &= ~0b1000;
                //player::z+=4;
                break;
            case 'A':
                wasd &= ~0b0100;
               // player::x-=4;
                break;
            case 'S':
                wasd &= ~0b0010;
               // player::z-=4;
                break;
            case 'D':
                wasd &= ~0b0001;
               // player::x+=4;
                break;
            
            default:
                break;
            }
           // InvalidateRect(hwnd,NULL,true);
        break;
        case WM_KEYDOWN:
            switch (wParam)
            {
            case 'W':
                wasd |= 0b1000;
                //player::z+=4;
                break;
            case 'A':
                wasd |= 0b0100;
               // player::x-=4;
                break;
            case 'S':
                wasd |= 0b0010;
               // player::z-=4;
                break;
            case 'D':
                wasd |= 0b0001;
               // player::x+=4;
                break;
            
            default:
                break;
            }
            //InvalidateRect(hwnd,NULL,true);
            break;
        case WM_CREATE:{
            SetTimer(hwnd,1,20,NULL);
            return 0;
        }
        case WM_TIMER:{
            InvalidateRect(hwnd,NULL,false);
            return 0;

        }
    case WM_SETCURSOR: {
            // Mengatur kursor menjadi panah saat berada dalam jendela
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            return TRUE;  // Memberitahu Windows bahwa kita telah menangani pesan ini
        }
    case WM_DESTROY:
        KillTimer(hwnd,1);
        if (bitmapbuff) {
                DeleteObject(bitmapbuff);
            }
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
         PAINTSTRUCT ps;   

            // All painting occurs here, between BeginPaint and EndPaint.
            painting(hwnd,ps);

            
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
std::vector<POINT> as = {{56,90},{70,88},{100,100}};

void kubus(Gbr g,Objek h){
    g.line(h.getPoint(0),h.getPoint(1));
    g.line(h.getPoint(0),h.getPoint(2));
    g.line(h.getPoint(0),h.getPoint(4));
    g.line(h.getPoint(1),h.getPoint(3));
    g.line(h.getPoint(1),h.getPoint(5));
    g.line(h.getPoint(2),h.getPoint(3));
    g.line(h.getPoint(2),h.getPoint(6));
    g.line(h.getPoint(3),h.getPoint(7));
    g.line(h.getPoint(4),h.getPoint(5));
    g.line(h.getPoint(4),h.getPoint(6));
    g.line(h.getPoint(5),h.getPoint(7));
    g.line(h.getPoint(6),h.getPoint(7));
}
std::vector<Objek> tent;
void painting(HWND hwnd,PAINTSTRUCT &ps){
    
            HDC hdc = BeginPaint(hwnd, &ps);
            double angleInRadians = player::rx*radian;
            if (wasd & 0b1000) {  
    player::x += (round((4.0 * sin(angleInRadians))*100))/100;
    player::z += (round((4.0 * cos(angleInRadians))*100))/100;
}

// Mundur (S)
if (wasd & 0b0010) {
    player::x -= (round((4.0 * sin(angleInRadians))*100))/100;
    player::z -= (round((4.0 * cos(angleInRadians))*100))/100;
}

// Ke kiri (A)
if (wasd & 0b0100) {
    player::x -= (round((4.0 * cos(angleInRadians))*100))/100;
    player::z += (round((4.0 * sin(angleInRadians))*100))/100;
}

// Ke kanan (D)
if (wasd & 0b0001) {
    player::x += (round((4.0 * cos(angleInRadians))*100))/100;
    player::z -= (round((4.0 * sin(angleInRadians))*100))/100;
}
            RECT fet;
            // All painting occurs here, between BeginPaint and EndPaint.
            GetClientRect(hwnd,&fet);
            if ((!bitmapbuff)||upsize) {
        HDC hdcScreen = GetDC(hwnd);
        bitmapbuff = CreateCompatibleBitmap(hdcScreen, fet.right, fet.bottom);
        ReleaseDC(hwnd, hdcScreen);
    }
        
            HDC chdc = CreateCompatibleDC(hdc);
            HBITMAP hOldBitmap = (HBITMAP)SelectObject(chdc, bitmapbuff);
            Gbr gambar(ps,chdc);
            Gbr warna =gambar.brush(34,67,255);
            //Objek::jendela(GetSystemMetrics(SM_CYSCREEN),GetSystemMetrics(SM_CXSCREEN));
            RECT raf;
            if(GetClientRect(hwnd,&raf)){
                int wit=raf.right-raf.left;
                int hed=raf.bottom-raf.top;
                
                Objek::jendela(hed,wit);
            }

            //Objek::jendela(1500,700);
            for(int i=-10;i<=10;i++){
            for(int j=-10;j<=10;j++){
                
                Objek test(i,0,j);
                test.setBentuk("kubus");
                tent.push_back(test);
            
            }
            }
            FillRect(chdc,&fet,CreateSolidBrush(RGB(255,255,255)));
            for(int i=0;i<tent.size();i++){
                kubus(warna,tent[i]);

            }
            tent.clear();
            
           /* Objek test2(-20,20,25);
            test2.setBentuk("kubus");
            
            kubus(warna,test2);*/

           // warna.rect(50,50,50,50);
          // if(as[1].x<=500&&as[1].y <=300){
          //  as[1].x+=15;
           // as[1].y+=10;
           //}else{
           // as[1].x = -300;
           // as[1].y = -100;
          // }
            warna.poli(as);
            //warna.poli(test.sudut);
            BitBlt(hdc, 0, 0, fet.right, fet.bottom, chdc, 0, 0, SRCCOPY);
            SelectObject(chdc, hOldBitmap);
            DeleteDC(chdc);
            EndPaint(hwnd, &ps);
        
}