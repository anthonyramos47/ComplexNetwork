/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: zoso
 *
 * Created on 4 de abril de 2018, 17:17
 */
#include <stdbool.h>
#include "structs.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif
    
    //FuncionesRed.c
    void inicializarRed(Red*);
    void cableadoInicial(Red*, int);
    void imprimirRed(Red*, int);
    void recablearRed(Red*, int);
    void recablearNodo(int, int, int, int, Nodo*, Nodo*, Nodo*);
    
    
    //FuncionesRecableadoRed.c
    int  generarNodoAleatorio(int,int,int,int,Nodo);
    void sumarLink(int, Nodo*);
    int encontrarEnVecino(int,Nodo);
    void swapYQuitarLink(Nodo*, int);
    
    //FuncionesExtras.c
    float prob(void);
    
    
    //FuncionesSuperRed.c
    void recablearDosRedes(Red* , Red* , int , int ,float );
    bool Conectado(Nodo *,int , int );
    int EscogerNodoAleatorioEnRed(Red*, int);
    int EscogerVecino(Red*, Nodo* , int *, int);
    void AlterarConexiones(Nodo* , int , int );
    int BuscarIndiceEnConexiones(Nodo* , int );
    void GenerarNodosRandom(int *,int ,int );
    
//_----------------------------------    
    
    
    void liberarMemoria(void);
    void imprimir(int);
   
    float criticalProbAct(int, float, int);
    void inicializarMuestra(int, float);
    void actualizarRed(float, int);
    void actualizarEstadoNodo(int, float);
    bool algunVecinoActivo(int);
    float actividadRed(void);
   
    void inicializarEstadosRed();
    void correccionEstadosRed(void);
    float actividadMuestra(float, float);
    
#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H */

