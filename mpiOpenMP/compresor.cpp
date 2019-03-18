/**
 * Clase compresor
 * Encargada de hacer el proceso de análisis entre macrobloques y enviarle
 * datos a otras clases tales como macrobloques
 * y vectormb
 * */

#pragma once
#include <iostream>
#include <vector>
#include <omp.h>
#include <mpi.h>
#include <cstddef>
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

        MPI_Init(NULL, NULL);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);    

        MPI_Datatype MBTYPE;
        MPI_Datatype type[3] = {MPI_INT, MPI_INT, MPI_INT};
        int blocklen[3] = {1, 1, 225};
        MPI_Aint disp[3];
	    disp[0] = (MPI_Aint)offsetof(class macrobloque, x);
	    disp[1] = (MPI_Aint)offsetof(class macrobloque, y);
	    disp[2] = (MPI_Aint)offsetof(class macrobloque, arr);

        MPI_Type_create_struct(3, blocklen, disp, type, &MBTYPE);
        MPI_Type_commit(&MBTYPE);

	    int size2=ArrImagen2.size();
	    int size1=ArrImagen1.size();
	    macrobloque mb2 [ArrImagen2.size()];
	    macrobloque mb1 [ArrImagen1.size()];
        int tamEnviar = size1 / world_size;

        if (world_rank == 0){
            mb2[ArrImagen2.size()];
            copy(ArrImagen2.begin(), ArrImagen2.end(), mb2);

            mb1[ArrImagen1.size()];
            copy(ArrImagen1.begin(), ArrImagen1.end(), mb1);
        }

	macrobloque mb1rec[tamEnviar];
	MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(mb2, size2, MBTYPE, 0, MPI_COMM_WORLD);
        MPI_Scatter(mb1, tamEnviar, MBTYPE, mb1rec, tamEnviar, MBTYPE, 0, MPI_COMM_WORLD);


    #pragma omp parallel for schedule(dynamic, 8)    
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