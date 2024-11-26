#include "tick.h"
#include <string>
#include <windows.h>
#include <cmath>
//int tip(int a){
 //   return a;
//}
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define radian (M_PI/180.0)
int skala =10;
#pragma comment(lib,"user32.lib")
Objek::Objek(int x,int y,int z):px(x*skala),py(y*skala),pz(z*skala){};
/*int ztox(int xoy,int z){
    int slayary = (Objek::pleb)/2;
    int slayarx = (Objek::ppan)/2;
    int dx;
    if(xoy>slayarx){
        dx=xoy-slayarx;
        return xoy-(z/(dx/8));
    }
        dx=slayarx-xoy;
        return xoy+(z/(dx/8));
    
}*/
float asep=1.0f;
/*void rotate3D(double& x, double& y, double& z, double angleX, double angleY) {
    // Konversi sudut ke radian
    double radX = angleX * M_PI / 180.0;
    double radY = angleY * M_PI / 180.0;

    // Rotasi terhadap sumbu X
    double newY = y * cos(radX) - z * sin(radX);
    double newZ = y * sin(radX) + z * cos(radX);
    y = newY;  // Update nilai y
    z = newZ;  // Update nilai z

    // Rotasi terhadap sumbu Y
    double newX = x * cos(radY) + z * sin(radY);
    newZ = -x * sin(radY) + z * cos(radY);
    x = newX;  // Update nilai x
    z = newZ;  // Update nilai z
}*/
double rotasi(double nkoor,double zkoor,bool sumbisy,bool koorisz){
    if(sumbisy){
        if(koorisz){
            return nkoor*sin(player::ry*(M_PI/180.0))+zkoor*cos(player::ry*radian);
        }
            return nkoor*cos((player::ry)*(M_PI/180.0))-zkoor*sin(player::ry*radian);
    }
    if(koorisz){
            return (-1*(nkoor*sin((-1*player::rx)*(M_PI/180.0))))+zkoor*cos((-1*player::rx)*radian);

    }
            return ((nkoor*cos((-1*player::rx)*(M_PI/180.0))))+zkoor*sin((-1*player::rx)*radian);
    
}
POINT pointing(int x,int y,int z){
    double relx = x-player::x;
    double rely = y-player::y;
    double relz = (z-player::z);
    //rotate3D(lokx,loky,lokz,player::rx,player::ry);
    /**/
   double lokx= rotasi(relx,relz,false,false);
    double loky=rotasi(rely,rotasi(relx,relz,false,true),true,false);
    double lokz=rotasi(rely,rotasi(relx,relz,false,true),true,true);

    if(lokz<0){
        lokz = -0.0;
    }
    asep+=1.0f;
    float scale = 1000.0f/(lokz);
    
    POINT p;
    if(scale>0){p.x=Objek::ppan/2+static_cast<int>(lokx*scale);}else{
        if(relx >0)p.x=Objek::ppan+1;
       if(relx <0)p.x=-1;
        if(relx ==0)p.x=Objek::ppan/2;
    }
    if(scale>0){p.y=Objek::pleb/2+static_cast<int>(loky*scale);}else{
        if(rely >0)p.y=Objek::pleb+1;
        if(rely <0)p.y=-1;
        if(rely ==0)p.y=Objek::pleb/2;

    }
    
    return p;
}
/*int ztoy(int xoy,int z){
    int slayarx = (Objek::pleb)/2;
    //int slayarx = (Objek::ppan)/2;
    int dx;
    if(xoy>slayarx){
        dx=xoy-slayarx;
        return xoy-(z/(dx/10));
    }
        dx=slayarx-xoy;
        return xoy+(z/(dx/10));
}*/
bool kanan=false,depan=false,atas=false;
int player::ry = 0;

void player::rotasi(int rotx,int roty){
    if(rotx<0){rotx=360+rotx;}
    if(roty<0){roty=360+roty;}
    player::rx=rotx%360;
    player::ry=roty%360;
}
int player::rx =0;
double player::x =0;
double player::y=-10;
double player::z =0;
void Objek::setBentuk(std::string jenis){
    if (jenis =="kubus"){
        int srusuk=5 ;
        int coorpl[3]={1,1,-7};
        int fov=2;
        for(int i =0;i<8;i++){
        int tmpx=px,tmpy=py,tmpz=pz;
        atas = (i&1)!=0;
        kanan = (i&2)!=0;
        depan = (i&4)!=0;
        if(depan){
            tmpz+=srusuk;
        }else{
            tmpz-=srusuk;
        }
        if(atas){
            tmpy+=srusuk;
            
        }else{
            tmpy-=srusuk;
           
        }
        if(kanan){
            tmpx+=srusuk;
            
        }else{
            tmpx-=srusuk;

        }
        //sudut.push_back({ztox(tmpx-player::x,(tmpz-player::z)),ztoy(tmpy-player::y,(tmpz-player::z))});
        sudut.push_back(pointing(tmpx,tmpy,tmpz));
        
        }
    }
    pbag = jenis;
}
void Objek::jendela(int lebar,int panjang){
    Objek::pleb = lebar;
    Objek::ppan = panjang;
}
POINT Objek::getPoint(int bagian){
    if(pbag=="kubus"){
        if(bagian <8||bagian >=0&&!(sudut.size()<8)){
            
            return sudut[bagian];
        }else{
            return {NULL,NULL};
        }
    }else{
        return {NULL,NULL};
    }
}
bool Objek::addBentuk(int mode,std::string info){
    return false;
}
int Objek::pleb = 0;
int Objek::ppan = 0;
