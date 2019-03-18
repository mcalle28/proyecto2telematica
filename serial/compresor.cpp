/**
 * Clase compresor
 * Encargada de hacer el proceso de análisis entre macrobloques y enviarle
 * datos a otras clases tales como macrobloques
 * y vectormb
 * */

#pragma once
#include <iostream>
#include <vector>
#include "macrobloque.cpp"
#include "vectormb.cpp"

using namespace std;

class compresor
{
  private:
    vector<macrobloque>ArrImagen1;
    vector<macrobloque> ArrImagen2;
  public:
  compresor(){}
  ~compresor(){}
  compresor(vector<macrobloque>ArrImagen1, vector<macrobloque>ArrImagen2){
      this->ArrImagen1=ArrImagen1;
      this->ArrImagen2=ArrImagen2;
  }

    /*Toma los arreglos de macrobloques, los analiza y busca su coincidencia mas exacta en la clase
    macrobloque, genera con esta un vector que se imprime en su respectiva
    clase*/
    void compresionMPEG2(){
        for(int i=0;i<ArrImagen1.size();i++){
            int Dif=256;
            vectormb vector;
            for(int j=0;j<ArrImagen2.size();j++){
                int comparacion = ArrImagen1[i].comparar(ArrImagen2[j]);
                if(comparacion==0){
                    vector=vectormb(ArrImagen1[i].x, ArrImagen1[i].y, ArrImagen2[j].x, ArrImagen2[j].y);
                    break;
                }
                else if(comparacion<=Dif){
                    Dif=comparacion;
                    vector=vectormb(ArrImagen1[i].x, ArrImagen1[i].y, ArrImagen2[j].x, ArrImagen2[j].y);
                }

            }
            vector.imprimir();      
        }
    }
};