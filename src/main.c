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
        printf(" !!! Error: El numero de alumnos en ambos archivos no coincide !!! ");
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
    int idUs = 0;
    scanf("%d", &idUs);
    kardex(arrCalif, numCalif, idUs, outF);
    fechaGrad(arrAl, numAlum, idUs, outF);

    /* Liberar memoria dinamica */
    free(arrAl);
    free(arrCalif);
    
    return 0;
}
