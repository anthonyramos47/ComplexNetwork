/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structs.h
 * Author: zoso
 *
 * Created on 4 de abril de 2018, 17:37
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  int estadoActual;
  int estadoAntiguo;
  int k; // número de elementos en cnx
  int *cnx; // conexiones
  int nulos;
} nodo;


#ifdef __cplusplus
}
#endif

#endif /* STRUCTS_H */

