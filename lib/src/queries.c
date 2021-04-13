/*
 * @autor Jazmin Santibañez
 * 
 * Este material esta bajo una Licencia Creative Commons 
 * Atribución-NoComercial-SinDerivadas 4.0 Internacional
 *  (CC BY-NC-ND 4.0)
 * 
 * Codigo implementado de los headers en queries.h
 * 
*/

#include "queries.h"

/* Funciones auxiliares*/
char* getName(Alumno *arrAl, int size, int id){
    for (int i = 0; i < size; i++){
         if (arrAl[i].id == id)
        {
            return arrAl[i].sName;
        }
    }
    return NULL;
}

int getIndexCalif(Grades *arrCalif, int size, int id)
{
    for (int i = 0; i < size; i++){
         if (arrCalif[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void help(){
    printf(" P1() \n\n");
    printf(" NOMBRE \n");
    printf(" \t p1 - Base de datos de una escuela. \n");
    printf("\n DESCRIPCION \n");
    printf(" \t Recibe dos archivos con informacion de los alumnos y sus calicaciones.\n");
    printf(" \t Permite al usuario desplegar toda la informacion almacenada o consultar.\n");
    printf(" \t cierta información a través de queries especificados.\n");
    printf("\n OPCIONES \n");
    printf(" \t -h \t\t Despliega toda la ayuda e información.\n");
    printf(" \t -v \t\t Verbose - Muestra detalles adicionales de la ejecución del programa.\n");
    printf(" \t -o <arg> \t Cambia el input a un archivo especificado. Requiere de un nombre de archivo despues de -o.\n");
    printf("\n QUERIES \n");
    printf(" \t Kardex <estudiante_id> \t\t\t Muestra las calificaciones de un alumno.\n");
    printf(" \t Fecha_estimada_graduacion <estudiante_id> \t Muestra la fecha aprox. de graduacion de un alumno.\n");
    printf(" \t Numero_alumnos <carrera> <ciudad_origen> \t Muestra el número de alumnos que hay en una carrera y ciudad dacos.\n");
    printf(" \t Numero_alumnos <carrera> \t\t\t Muestra el número de alumnos en una carrera.\n");
    printf(" \t Numero_alumnos * \t\t\t\t Muestra el número total de alumnos registrados.\n");
    printf(" \t Nombre_alumnos <carrera> <ciudad_origen> \t Muestra el nombre de alumnos que hay en una carrera y ciudad dacos.\n");
    printf(" \t Nombre_alumnos <carrera> \t\t\t Muestra el nombre de alumnos en una carrera.\n");
    printf(" \t Nombre_alumnos * \t\t\t\t Muestra el nombre de todos los alumnos registrados\n");
    printf(" \t Nombre_alumnos <operador> <numero> \t\t Muestra el nombre de los alumnos cuyo promedio cumple con la condicion nada.\n");
}

int menuQuery(char *qry[3], int numArg){
    if ( (strcmp(*(qry + 0), "Kardex") == 0 ) && (numArg == 2) ){
        return 1;
    }
    if ( (strcmp(*(qry + 0), "Fecha_estimada_graduacion") == 0 ) && (numArg == 2) ){
        return 2;
    }
    if ( (strcmp(*(qry + 0), "Numero_alumnos") == 0 ) ){
        if (numArg == 3)
            return 3;
        else if ( strcmp(*(qry + 1),"*") == 0 )
            return 4;
        else if (numArg == 2)
            return 5;
    }
    if ( (strcmp(*(qry + 0), "Nombre_alumnos") == 0 ) ){
        if ((strcmp(*(qry + 1), "<") == 0 ) || (strcmp(*(qry + 1), ">") == 0 ) || (strcmp(*(qry + 1), "==") == 0 ) || (strcmp(*(qry + 1), "!=") == 0 ) )
            return 6; 
        else if (numArg == 3)
            return 7;
        else if ( strcmp(*(qry + 1),"*") == 0 )
            return 8;
        else if (numArg == 2)
            return 9;
    }


    return -1;
}

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

