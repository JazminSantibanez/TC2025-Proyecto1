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

/* Queries para pasar a biblioteca */
void kardex(Grades *arrCalif, int size, int id, FILE *salida){
    for (int i = 0; i < size; i++){
        if (arrCalif[i].id == id)
        {
            fprintf(salida, " -- Alumno: %d --\n", arrCalif[i].id);
            fprintf(salida, "Materia 1: %.2f\n", arrCalif[i].mA);
            fprintf(salida, "Materia 2: %.2f\n", arrCalif[i].mB);
            fprintf(salida, "Materia 3: %.2f\n", arrCalif[i].mC);
            fprintf(salida, "Materia 4: %.2f\n", arrCalif[i].mD);
            return;
        }
    }
}

void fechaGrad(Alumno *arrAl, int size, int id, FILE *salida){
    for (int i = 0; i < size; i++){
        if (arrAl[i].id == id){
            fprintf(salida, "Alumno: %d \t Fecha estimada de graduación: %s\n", arrAl[i].id, arrAl[i].sFecha);
            return;
        }
    }
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

char* getName(Alumno *arrAl, int size, int id){
    for (int i = 0; i < size; i++){
         if (arrAl[i].id == id)
        {
            return arrAl[i].sName;
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



int main(int argc, char *argv[])
{
    FILE *archAlumnos, *archCalif;
    char line[100];
    int numAlum = -1, ind = 0, numCalif = -1;
    Alumno *arrAl;
    Grades *arrCalif;

    /* Contar numero de alumnos en arch1 */
    archAlumnos = fopen(argv[1], "r");
    while (!feof(archAlumnos))
    {
        fgets(line, 100, archAlumnos);
        numAlum++;
    }
    rewind(archAlumnos);
    arrAl = malloc(numAlum * sizeof(Alumno));

    /* Guardar informacion de alumnos */
    fgets(line, 100, archAlumnos); //Ignorar headers
    while (ind < numAlum)
    {	
        fscanf(archAlumnos, "%d %[^\t] %s %[^\t] %s\n", &arrAl[ind].id, arrAl[ind].sName, arrAl[ind].sCarrera, arrAl[ind].sCiudad, arrAl[ind].sFecha);
        //printf(">%d %s %s %s %s\n", arrAl[ind].id, arrAl[ind].sName, arrAl[ind].sCarrera, arrAl[ind].sCiudad, arrAl[ind].sFecha);
        ind++;
    }
    fclose(archAlumnos);

    /* Contar numero de alumnos en arch2 */
    archCalif = fopen(argv[2], "r");
    while (!feof(archCalif))
    {
        fgets(line, 100, archCalif);
        numCalif++;
    }
    rewind(archCalif);
    arrCalif = malloc(numCalif * sizeof(Grades));
    
    /* Guardar informacion de calificaciones */
    if ( numAlum == numCalif) /* Guardar informacion */
    {
        ind = 0;
        fgets(line, 100, archCalif);

        while (ind < numCalif)
        {
            fscanf(archCalif, "%d %f %f %f %f", &arrCalif[ind].id, &arrCalif[ind].mA, &arrCalif[ind].mB, &arrCalif[ind].mC, &arrCalif[ind].mD);
            ind++;
        }
    }
    else {
        printf(" !!! Error: El numero de alumnos en ambos archivos no coincide !!!\n");
    }
    fclose(archCalif);

    /* Print de datos */
    /* printf("--------\n");
    for (int i = 0; i < numAlum; i++)
    {
        //printf(">%d %lu %lu %lu %lu\n", arrAl[i].id, strlen(arrAl[i].sName), strlen(arrAl[i].sCarrera), strlen(arrAl[i].sCiudad), strlen(arrAl[i].sFecha));
        printf(">%d %s %s %s %s\n", arrAl[i].id, arrAl[i].sName, arrAl[i].sCarrera, arrAl[i].sCiudad, arrAl[i].sFecha);
    } 
    printf("\n--------\n");
    for (int i = 0; i < numAlum; i++)
    {
        printf("%d %f %f %f %f\n", arrCalif[i].id, arrCalif[i].mA, arrCalif[i].mB, arrCalif[i].mC, arrCalif[i].mD);
    }  */

    //// Pruebas manuales /////
    FILE *outF;
    outF = stdout;
    
    /*
    int idUs = 0;
    scanf("%d", &idUs);
    kardex(arrCalif, numCalif, idUs, outF);
    fechaGrad(arrAl, numAlum, idUs, outF); 
    
    char str[4], str2[25];
    nombAlumT(arrAl, numAlum, outF);
    printf("Carrera: ");
    scanf("%s", str);
    nombAlum1(arrAl, numAlum, str, outF);
    printf("Ciudad: ");
    scanf("%s", str2);
    nombAlum2(arrAl, numAlum, str, str2, outF);
    */
    char str[4];
    float prom = 0.0;
    printf("Operador: ");
    scanf("%s", str);
    printf("Promedio: ");
    scanf("%f", &prom);
    nombAlumOp(arrCalif, arrAl, numAlum, str, prom, outF);

    /* Liberar memoria dinamica */
    free(arrAl);
    free(arrCalif);
    
    return 0;
}
