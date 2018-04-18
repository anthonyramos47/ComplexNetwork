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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
    
     //FuncionesDinamicaRed.c
    void actualizarEstadoNodo(Red*, int, int, float);
    void actualizarEstadoNodoRedes(Red*, Red*, int, int, float);
    bool algunVecinoActivo(Red*, int, int);
    bool algunVecinoActivoRedes(Red*, Red*, int, int);
    void actualizarRed(Red*, int, int);
    void correccionEstadosRed(Red*);
    void inicializarMuestra(Red*, int);
    float actividadRed(Red*);
    void inicializarEstadosRed(Red*);
    float actividadMuestra(Red*, int, float);
    void liberarMemoria(Red*);
    void imprimir(Red*, int);
    void actualizarRedPaso(Red*, Red*, int, FILE*, FILE*);
    void actividadRedes(Red*, Red*, int, float);
    void colorearNodo(Red*, int, FILE*, FILE*);
    void generarEImprimirMatrizAdyacente(Red*, int);
    
    
    
//_----------------------------------    
    

    
#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H */

