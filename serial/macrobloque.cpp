/**
 * Clase macrobloque
 * Encargada de guardar el arreglo de pixeles en un macrobloque y su posicion
 * con respecto a x y a y
 * */
#pragma once
#include <vector>

using namespace std;

class macrobloque
{
  public:
  int x,y;
  vector<int> pixeles;
  macrobloque(){}
  ~macrobloque(){}
  macrobloque(vector<int>pixeles,int x, int y){
    this->pixeles=pixeles;
    this->x=x;
    this->y=y;
  }

/*Toma un macrobloque y el macrobloque propio para encontrar el numero de diferencias
en los mismos, devuelve un entero que es igual al #de diferencias, si es 0 la imagen es igual*/

  int comparar(macrobloque MB){
      int diferencias=0;
      for(int i=0; i<pixeles.size();i++){
          if(pixeles[i]!=MB.pixeles[i]){
              diferencias++;
          }
      } 
      return diferencias;
  }
};