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

int menuQuery(char *qry[3], int numArg){
    if ( strcmp(*(qry + 0), "Kardex\n") && (numArg == 2) ){
        return 1;
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
    
    /* Logica principal del programa */
    FILE *outF;
    outF = stdout;
    int iOpc;
    do {
        iOpc = -1;
        printf("\n ---- Menu ---- \n");
        printf("1 - Mostrar estudiantes \n2 - Hacer consulta \n0 - Terminar el programa\n");
        printf("Que opción le gustaria ejecutar?: ");
        scanf("%d", &iOpc);

        switch (iOpc){
        case 1:{
            printf("  ID \t  Nombre \tCarrera \t Ciudad \t Graduacion \t Calificaciones\n");
            for (int i = 0; i < numAlum; i++){
                printf(" %d) %d  -  %s\t%s   %s     \t%s", i+1, arrAl[i].id, arrAl[i].sName, arrAl[i].sCarrera, arrAl[i].sCiudad, arrAl[i].sFecha);
                ind = getIndexCalif(arrCalif, numCalif, arrAl[i].id);
                printf("\t Notas: - %.1f %.1f %.1f %.1f\n", arrCalif[ind].mA, arrCalif[ind].mB, arrCalif[ind].mC, arrCalif[ind].mD);
            }
            break;
        }
        
        case 2:{
            printf(" ** Da enter sin escribir nada para salir **\n");
               while (1){
                    char str[35];
                    str[0] = '\0';
                    char *qry[3];
                    int arg = 0, bFlag = 0, iMenu;
                    iMenu = - 1;
                    getchar();

                    printf(" Query >");
                    scanf("%[^\n]", str);
                    
                    
                    qry[0] = strtok(str, " \n");
                    qry[1] = strtok(NULL, " \n");
                    qry[2] = strtok(NULL, " \n");

                    if (qry[0] == NULL){
                        break;
                    }
                    else if ( qry[2] != NULL){
                        arg = 3;
                        bFlag = 1;
                    }
                    else if (qry[1] == NULL ){
                        printf(" !!! Error: Los queries deben tener al menos un argumento. !!! ");
                        bFlag = 0;
                    }
                    else if (qry[2] == NULL){
                        arg = 2;
                        bFlag = 1;
                    }

                    if (bFlag == 1) {
                        //Llamar a menu
                        iMenu = menuQuery(qry, arg);
                        switch(iMenu){
                            case 1:
                            {
                                //printf("%d\n", atoi(qry[1]));
                                kardex(arrCalif, numCalif, atoi(qry[1]), outF); 
                                break;
                            }
                        }
                    }

                }
                break;
            }
        
        case 0:
            break;
        
        default:{
            printf(" !!! Error: Opción no reconocida. Ingresa uno de los numeros del menu !!!\n");
            break;
        }
        }
    } while (iOpc != -0);

    //// Pruebas manuales /////
    
    outF = stdout;
    

    /* Liberar memoria dinamica */
    free(arrAl);
    free(arrCalif);
    
    return 0;
}
