#ifndef TICK_H
#define TICK_H
#include <vector>
#include <string>
#include <windows.h>
int tip(int a);

class Objek{

    public:
        Objek(int x,int y,int z);
        POINT getPoint(int bagian);
        void setBentuk(std::string jenis);
        static bool addBentuk(int mode,std::string info);
        static void jendela(int lebar,int panjang);
        static int pleb,ppan;
        std::vector<POINT> sudut;
    private:
        int px,py,pz;
        std::string pbag;
};
class player{
    public:
    static double x,y,z;
    static int rx,ry;
    
    static void rotasi(int rotx,int roty);
};
#endif 