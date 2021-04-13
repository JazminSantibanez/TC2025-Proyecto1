/*
 * @autor Jazmin Santibañez
 * 
 * Este material esta bajo una Licencia Creative Commons 
 * Atribución-NoComercial-SinDerivadas 4.0 Internacional
 *  (CC BY-NC-ND 4.0)
 * 
 * Codigo implementado de los queries a ejecutar en main.c
 * 
*/

#include "headers.h"


/* Queries para pasar a biblioteca */
void kardex(Grades *arrCalif, Alumno *arrAl, int size, int id, FILE *salida){
    for (int i = 0; i < size; i++){
        if (arrCalif[i].id == id)
        {
            fprintf(salida, " -- Alumno: %d %s --\n", arrCalif[i].id, getName(arrAl, size, arrCalif[i].id) );
            fprintf(salida, "Materia 1: %.2f\n", arrCalif[i].mA);
            fprintf(salida, "Materia 2: %.2f\n", arrCalif[i].mB);
            fprintf(salida, "Materia 3: %.2f\n", arrCalif[i].mC);
            fprintf(salida, "Materia 4: %.2f\n", arrCalif[i].mD);
            return;
        }
    }
    printf(" -- El alumno %d no se encuentra en los datos -- \n", id);
}

void fechaGrad(Alumno *arrAl, int size, int id, FILE *salida){
    for (int i = 0; i < size; i++){
        if (arrAl[i].id == id){
            fprintf(salida, "Alumno: %d \t Fecha estimada de graduación: %s\n", arrAl[i].id, arrAl[i].sFecha);
            return;
        }
    }
    printf(" -- El alumno %d no se encuentra en los datos -- \n", id);
}

void numAlumT(int numAlum, FILE *salida){
    fprintf(salida, "%d\n", numAlum);
}

void numAlum1(Alumno *arrAl, int size, char *carr, FILE *salida){
    int contador = 0;
    for (int i = 0; i < size; i++){
        if( strcmp(arrAl[i].sCarrera, carr) == 0)
            contador++;
    }
    fprintf(salida, "%d\n", contador);
}

void numAlum2(Alumno *arrAl, int size, char *carr ,char *cd, FILE *salida){
    int contador = 0;
    for (int i = 0; i < size; i++){
        if( (strcmp(arrAl[i].sCarrera, carr) == 0) && (strcmp(arrAl[i].sCiudad, cd) == 0) )
            contador++;
    }
    fprintf(salida, "%d\n", contador);
}

void nombAlumT(Alumno *arrAl, int size, FILE *salida){
    for (int i = 0; i < size; i++){
        fprintf(salida, "%s\n", arrAl[i].sName);
    }
}

void nombAlum1(Alumno *arrAl, int size, char *carr, FILE *salida){
    for(int i = 0; i < size; i++){
        if ( strcmp(arrAl[i].sCarrera, carr) == 0){
            fprintf(salida, "%s\n", arrAl[i].sName);
        }
    }
}

void nombAlum2(Alumno *arrAl, int size, char *carr, char *cd, FILE *salida){
    for(int i = 0; i < size; i++){
        if( (strcmp(arrAl[i].sCarrera, carr) == 0) && (strcmp(arrAl[i].sCiudad, cd) == 0) ){
            fprintf(salida, "%s\n", arrAl[i].sName);
        }
    }
}

void nombAlumOp(Grades *arrCalif, Alumno *arrAl, int size, char *op, float target, FILE *salida){
    int opc = 0;
    if (strcmp(op,"<") == 0)
        opc = 1;
    else if (strcmp(op,">") == 0)
        opc = 2;
    else if (strcmp(op,"==") == 0)
        opc = 3;
    else if (strcmp(op,"!=") == 0)
        opc = 4;

    for(int i= 0; i < size; i++){
        switch (opc)
        {
        case 1:
            if ( ((arrCalif[i].mA + arrCalif[i].mB + arrCalif[i].mC + arrCalif[i].mD) / 4.0) < target ){
                fprintf(salida, "%s\n", getName(arrAl, size, arrCalif[i].id));
            }
            break;
        case 2:
            if ( ((arrCalif[i].mA + arrCalif[i].mB + arrCalif[i].mC + arrCalif[i].mD) / 4.0) > target ){
                fprintf(salida, "%s\n", getName(arrAl, size, arrCalif[i].id));
            }
            break;
        
        case 3:
            if ( ((arrCalif[i].mA + arrCalif[i].mB + arrCalif[i].mC + arrCalif[i].mD) / 4.0) == target ){
                fprintf(salida, "%s\n", getName(arrAl, size, arrCalif[i].id));
            }
            break;
        
        case 4:
            if ( ((arrCalif[i].mA + arrCalif[i].mB + arrCalif[i].mC + arrCalif[i].mD) / 4.0) != target ){
                fprintf(salida, "%s\n", getName(arrAl, size, arrCalif[i].id));
            }
            break; 

        default:
            fprintf(salida, " !!! Error: El operador ingresado no es valido !!!\n");
            return;
        }
    }
}

