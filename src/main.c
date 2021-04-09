#include <stdlib>
#indluce <stdio.h>

typedef struct Alumno
{
    int id;
    char *sName; //Cambiar a dinamico ??? Buscar como hacer free dsps
    char sCarrera[3];
    char sCiudad[20];
    char sFecha[10];
} Alumno;

typedef struct Grades
{
    int id;
    double mA;
    double mB;
    double mC;
    double mD;
} Grades;

int maint(int argc, char *argv[])
{
    FILE *archAlumnos, *archCalif;
    archAlumnos = fopen(argv[1], "r");
    archCalif = fopen(argv[2], "r");
}