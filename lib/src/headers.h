/*
 * @autor Jazmin Santibañez
 * 
 * Este material esta bajo una Licencia Creative Commons 
 * Atribución-NoComercial-SinDerivadas 4.0 Internacional
 *  (CC BY-NC-ND 4.0)
 * 
 * Headers de las funciones que formaran la biblioteca dinamica para main.c
 * 
*/

#ifndef QUERIES_H
#define QUERIES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Alumno
{
    int id;
    char sName[40];
    char sCarrera[4];
    char sCiudad[25];
    char sFecha[10];
} Alumno;

typedef struct Grades
{
    int id;
    float mA;
    float mB;
    float mC;
    float mD;
} Grades;

/* Funciones de apoyo */

char *getName(Alumno *arrAl, int size, int id);

int getIndexCalif(Grades *arrCalif, int size, int id);

void help();

int menuQuery(char *qry[3], int numArg);

/* Queries */

void kardex(Grades *arrCalif, Alumno *arrAl, int size, int id, FILE *salida);

void fechaGrad(Alumno *arrAl, int size, int id, FILE *salida);

void numAlumT(int numAlum, FILE *salida);

void numAlum1(Alumno *arrAl, int size, char *carr, FILE *salida);

void numAlum2(Alumno *arrAl, int size, char *carr, char *cd, FILE *salida);

void nombAlumT(Alumno *arrAl, int size, FILE *salida);

void nombAlum1(Alumno *arrAl, int size, char *carr, FILE *salida);

void nombAlum2(Alumno *arrAl, int size, char *carr, char *cd, FILE *salida);

void nombAlumOp(Grades *arrCalif, Alumno *arrAl, int size, char *op, float target, FILE *salida);

#endif