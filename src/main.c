#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Alumno
{
    int id;
    char *sName;
    char *sCarrera;
    char *sCiudad;
    char *sFecha;
} Alumno;

typedef struct Grades
{
    int id;
    double mA;
    double mB;
    double mC;
    double mD;
} Grades;

int main(int argc, char *argv[])
{
    FILE *archAlumnos, *archCalif;
    char line[100];
    int numAlum = -1, ind = 0;
    Alumno *arrAl;

    archAlumnos = fopen(argv[1], "r");
    //archCalif = fopen(argv[2], "r");

    //Contar numero de alumnos
    while (!feof(archAlumnos))
    {
        fgets(line, 100, archAlumnos);
        numAlum++;
    }
    rewind(archAlumnos);
    arrAl = malloc(numAlum * sizeof(Alumno));

    fgets(line, 100, archAlumnos);

    while (ind < numAlum)
    {	
        fscanf(archAlumnos, "%d %[^\n]", &arrAl[ind].id, line);
        char* token = strtok(line, "\t");
        char *temp[4];
        int j = 0;
        
        //Separar los elementos de line
        while (token != NULL) {
            temp[j] = token;
            token = strtok(NULL, "\t");
            j++;
        }
        arrAl[ind].sName = temp[0];
        arrAl[ind].sCarrera = temp[1];
        arrAl[ind].sCiudad = temp[2];
        arrAl[ind].sFecha = temp[3];

        //printf(">%d %s  %s  %s %s\n", arrAl[ind].id,arrAl[ind].sName, arrAl[ind].sCarrera, arrAl[ind].sCiudad, arrAl[ind].sFecha);
        ind++;
    }
    //Liberar memoria dinamica
    free(arrAl);

    //Cerrar archivos
    fclose(archAlumnos);
    //fclose(archCalif);
    return 0;
}
