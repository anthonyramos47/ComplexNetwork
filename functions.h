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
#define N 10 // numero de nodos

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void inicializarRed(int);
    void cableadoInicial(int);
    void sumarLink(int, int);
    void recableadoRed(float, int);
    int nuevoNodo(int);
    void liberarMemoria(void);
    void imprimir(int);
    float prob(void);
    int encontrarVecino(int, int );
    float critialProbAct(int, float, int);
    void inicializarMuestra(int, float);
    void actualizarRed(float, int);
    void actualizarEstadoNodo(int, float);
    bool algunVecinoActivo(int);
    float actividadRed(void);
    void swap(int, int);
    void quitarLink(int);
    void inicializarEstadosRed();
    void correccionEstadosRed(void);
    float actividadMuestra(float, float);
    void imprimirRed();

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H */

