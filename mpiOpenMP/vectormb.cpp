/**
 * Clase vectormb
 * Encargada de imprimir el vector que es enviado en la clase compresor
 * */
#pragma once
#include <iostream>

using namespace std;


class vectormb
{
  private:
  int x1,y1,x2,y2;

  public:
  vectormb(){}
  ~vectormb(){}
  vectormb(int x1, int y1, int x2,int y2){
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
  }

  /*Imprime el vector enviado en el formato indicado por el documento*/
  void imprimir(){
      cout<<"| MB("<<this->x1<<","<<this->y1<<")=(x"<<this->x2<<",y"<<this->y2<<") |"<<endl;
  }
};