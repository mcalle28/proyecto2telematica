#include <iostream>
#include <vector>
#include "lector.cpp"
#include "macrobloque.cpp"
#include "compresor.cpp"

using namespace std;

int main(int argc, char* argv[]){

    if(argc!=3){
        printf("uso: ./main.exe imagen1.bmp imagen2.bmp");
    }
    else{

        lector l = lector(argv[1],argv[2]);
        vector<vector<macrobloque> > datos=l.leer();
        compresor c= compresor(datos[0],datos[1]);
        c.compresionMPEG2();
    }

    return 0;
}