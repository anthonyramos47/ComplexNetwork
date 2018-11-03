

#include "structs.h"
#include <stdlib.h>
#include "functions.h"
#include <stdio.h>
#include <stdbool.h>

void recablearDosRedes(Red* red1, Red* red2, int numCnxs, int numReds,float probConexiones){

//    int rndNods[];
//    GenerarNodosRandom(rndNods,red1->N,numCnxs);

    //Parametros
    Nodo* nodosRed1 = red1 -> nodos; //invocamos al arreglo de nodos de la red
    Nodo* nodosRed2 = red2 -> nodos; //invocamos al arreglo de nodos de la red
    int clase1 = red1->id;
    int clase2 = red2->id;

    //Variables Auxiliares
    int idxActualRed1P, idxActualRed2P, idxVecinoEnActual1P,  idxVecinoEnActual2P;
    int idxVecinoRed1P, idxVecinoRed2P, idxActualEnVecino1P, idxActualEnVecino2P;
    //

    for (int i = 0; i < numCnxs; i++){

//        if(prob()<probConexiones){
            //Establezco los indices posicionales de los nodos elegido en Red1 y Red2 Aleatoriamente
            idxActualRed1P = EscogerNodoAleatorioEnRed(red1,numReds);
            idxActualRed2P = EscogerNodoAleatorioEnRed(red2,numReds);

            //Establezco los indices posicionales de los nodos vecinos elegido en Red1 y Red2
            //Establezco los indices poscionales de los vecinos en los nodos actuales
            idxVecinoEnActual1P = EscogerVecino(red1,&nodosRed1[idxActualRed1P],&idxVecinoRed1P,numReds);
            idxVecinoEnActual2P = EscogerVecino(red2,&nodosRed2[idxActualRed2P],&idxVecinoRed2P,numReds);

            //Establezco los indices poscionales de los actuales en los nodos vecinos
            idxActualEnVecino1P = BuscarIndiceEnConexiones(&nodosRed1[idxVecinoRed1P],idxActualRed1P*numReds+clase1);
            idxActualEnVecino2P = BuscarIndiceEnConexiones(&nodosRed2[idxVecinoRed2P],idxActualRed2P*numReds+clase2);

            //Imprimir Indices Involucrados
            printf("\nIndices involucadrados\n");
            printf("En Red 1\n");
            printf("Actual: %d \t Vecino: %d\n",idxActualRed1P*numReds+clase1,idxVecinoRed1P*numReds+clase1);
            printf("En Red 2\n");
            printf("Actual: %d \t Vecino: %d\n",idxActualRed2P*numReds+clase2,idxVecinoRed2P*numReds+clase2);
            printf("------------------------\n"); 



            // Creo enlace de nodo Red1 ----> nodo Red2
            AlterarConexiones(&nodosRed1[idxActualRed1P],idxActualRed2P*numReds+clase2,idxVecinoEnActual1P);

            // Creo enlace de nodo Red2 ----> nodo Red1
            AlterarConexiones(&nodosRed2[idxActualRed2P],idxActualRed1P*numReds+clase1,idxVecinoEnActual2P);

            // Creo enlace de nodo vecino Red1 ----> nodo vecino Red2
            AlterarConexiones(&nodosRed1[idxVecinoRed1P],idxVecinoRed2P*numReds+clase2,idxActualEnVecino1P);

            // Creo enlace de nodo vecino Red2 ----> nodo vecino Red1
            AlterarConexiones(&nodosRed2[idxVecinoRed2P],idxVecinoRed1P*numReds+clase1,idxActualEnVecino2P);

//        }
    }
}

//Compruebo si la ultima conexion de un nodo dado pertenece a la clase de su red
bool Conectado(Nodo * nodo,int numReds, int clase){
    bool conectado = true; //Si no pertenece quiere decir que esta conectado con la otra red
    int numVecino = nodo->k;
    int lastIdxModular = nodo->cnx[numVecino-1];
    if((lastIdxModular-clase)%numReds == 0){
        conectado = false; //Si pertenece a la no esta conectado y se puede usar
    }
}

int EscogerNodoAleatorioEnRed(Red* red,int numReds){ //Podria usar esta funcion para elegir los dos nodos de cada red que van a cambiar
    int numNodos = red->N;
    int clase = red->id;

    int idxAleatorioP = rand()%(numNodos);
    Nodo nodo = red->nodos[idxAleatorioP];

    //Si el nodo tiene conexiones ya con la otra red elijo otro aleatorio
    while(Conectado(&nodo,numReds,clase)){
        idxAleatorioP = rand()%(numNodos);
        nodo = red->nodos[idxAleatorioP];
    }
    //*/

  return idxAleatorioP ; //Regresa la posicion del nodo en el arreglo de nodos
}

//Tiene dos funciones
//1) Con el return. Elegir un nodo vecino de los conexiones de un nodo y regresar su indice posicional.
//2) Con un puntero. Regresar el indice posicional de tal todo en los nodos de la red
int EscogerVecino(Red* red, Nodo* nodoActual, int *idxPosicionEnNodos, int numReds){
    int numVecinos = nodoActual->k;
    int clase = red->id;

    int idxEnCnxP = rand()%(numVecinos);            //Eligo un vecino al azar
    int idxEnNodos = ((nodoActual->cnx[idxEnCnxP]- clase)/numReds); //Saco el indice para buscarlo en el array de nodos
    Nodo nodoAleatorioVecino = red->nodos[idxEnNodos];  //Tomo el nodo del array de nodos de la red dad

    //Si el nodo aleatorio que escojo de los vecinos tiene conexiones con la otra red escojo otro vecino
    while(Conectado(&nodoAleatorioVecino,numReds,clase)){
        int idxEnCnxP = rand()%(numVecinos);            //Eligo un vecino al azar
        int idxEnNodos = ((nodoActual->cnx[idxEnCnxP]- clase)/numReds); //Saco el indice para buscarlo en el array de nodos
        Nodo nodoAleatorioVecino = red->nodos[idxEnNodos];  //Tomo el nodo del array de nodos de la red dad
    }

    *idxPosicionEnNodos = idxEnNodos ; //El indice posicional pasado como puntero
    return idxEnCnxP ; //Regresa la posicion del nodo de en arreglo de conexiones
}

void AlterarConexiones(Nodo* nodo, int idxModular, int idPosicionalEnCnx){
    int numVec = nodo -> k;
    nodo -> cnx[idPosicionalEnCnx] = nodo -> cnx[numVec-1];
    nodo -> cnx[numVec-1]=idxModular;
}

// Con el indiceModular busco en que posicion del array de conexiones esta tal valor y regreso ese indice
int BuscarIndiceEnConexiones(Nodo* nodo, int idxModular){
    int numVec = nodo -> k;
    int *cnx = nodo -> cnx;
    int i;
    for(i = 0; i<numVec; i++){
        if(cnx[i]==idxModular){
        break;}
    }

    int idxPosicionalEnVec = i;
    return idxPosicionalEnVec;
}

//Genero nodos aleatorios de N/2 a N
void GenerarNodosRandom(int *rndNodos,int N,int numCnxs){
    rndNodos = malloc(numCnxs*sizeof(int));
    for(int i = 0; i<numCnxs;i++){
        rndNodos[i] = (rand()%(N/2))+(N/2);
    }
}
