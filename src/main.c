/*
 * @autor Jazmin Santibañez
 * 
 * Este material esta bajo una Licencia Creative Commons 
 * Atribución-NoComercial-SinDerivadas 4.0 Internacional
 *  (CC BY-NC-ND 4.0)
 * 
 * Este programa funciona como base de datos
 * de una escuela y recibe como parametro dos archivos.
 *      - arch1.txt - Informacion general de los alumnos
 *      - arch2.txt - Calificaciones de los alumnos en 4 materias.
 * 
 * Cuenta con un menu donde se pueden realizar 2 actividades.
 * 1) Mostrar toda la informacion de todos los alumnos.
 * 2) Permitir ingresar queries por el usuario.

 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "../lib/src/headers.h"

int main(int argc, char *argv[])
{
    /* Opciones */
    int opt;
    int bVerbose = 0, bOutput = 0; //Bandera de verbose y output
    char *outName, *arch1, *arch2;
    FILE *archAlumnos, *archCalif, *outF;
    arch1 = argv[1];
    arch2 = argv[2];

    archAlumnos = fopen(arch1, "r");
    archCalif = fopen(arch2, "r");

     if (argc < 3)
    {
        printf("\n !!! Error: El programa debe recibir como parametro 2 archivos !!! \n");
        return 0;
    }

    if ( archAlumnos == NULL || archCalif == NULL )
    {
        printf("\n !!! Error: Los archivos de entrada no pudieron ser abiertos. Revisa su sintaxis. !!! \n");
        return 0;
    }

    while ((opt = getopt(argc, argv, "hvo:")) != -1) { 
        switch(opt) {
            case 'h':
                help();
                return 1;
            case 'o':
                outName = optarg;
                bOutput = 1;
                break;
            case 'v':
                bVerbose = 1;
                break;
            default:
                break;
        }
    }

    if (bOutput == 1)
    {
        outF = fopen(outName, "w");
    } 
    else {
        outF = stdout;
    }

   

    /* Inicializacion de archivos*/
    if (bVerbose == 1)
        fprintf(outF, " ~ Abriendo archivo1\n");
   
    char line[100];
    int numAlum = -1, ind = 0, numCalif = -1;
    Alumno *arrAl;
    Grades *arrCalif;

    if (bVerbose == 1)
        fprintf(outF, " ~ Contando numero de alumnos\n");
    /* Contar numero de alumnos en arch1 */
    while (!feof(archAlumnos))
    {
        fgets(line, 100, archAlumnos);
        numAlum++;
    }
    rewind(archAlumnos);
    arrAl = malloc(numAlum * sizeof(Alumno));
    
    /* Guardar informacion de alumnos */
    if (bVerbose == 1)
        fprintf(outF, " ~ Guardando datos de alumnos de archivo1\n");
    fgets(line, 100, archAlumnos); //Ignorar headers
    while (ind < numAlum)
    {	
        fscanf(archAlumnos, "%d %[^\t] %s %[^\t] %s\n", &arrAl[ind].id, arrAl[ind].sName, arrAl[ind].sCarrera, arrAl[ind].sCiudad, arrAl[ind].sFecha);
        //printf(">%d %s %s %s %s\n", arrAl[ind].id, arrAl[ind].sName, arrAl[ind].sCarrera, arrAl[ind].sCiudad, arrAl[ind].sFecha);
        ind++;
    }
    fclose(archAlumnos);

    /* Contar numero de alumnos en arch2 */
    if (bVerbose == 1)
        fprintf(outF, " ~ Abriendo archivo2 \n");
    
    while (!feof(archCalif))
    {
        fgets(line, 100, archCalif);
        numCalif++;
    }
    rewind(archCalif);
    arrCalif = malloc(numCalif * sizeof(Grades));
    
    /* Guardar informacion de calificaciones */
    if (bVerbose == 1)
        fprintf(outF, " ~ Guardando calificaciones de archivo2 \n");
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
        return 0;
    }
    fclose(archCalif);
    
    /* Logica principal del programa */
    if (bVerbose == 1)
        fprintf(outF, " ~ Abriendo menu principal\n");
    int iOpc;
    do {
        iOpc = -1;
        printf("\n ---- Menu ---- \n");
        printf("1 - Mostrar estudiantes \n2 - Hacer consulta \n0 - Terminar el programa\n");
        printf("Que opción le gustaria ejecutar?: ");
        scanf("%d", &iOpc);

        switch (iOpc){
        case 1:{
            if (bVerbose == 1)
                fprintf(outF, " ~ Mostrando toda la informacion de todos los alumnos \n");
            fprintf(outF, "  ID \t  Nombre \tCarrera \t Ciudad \t Graduacion \t Calificaciones\n");
            for (int i = 0; i < numAlum; i++){
                fprintf(outF," %d) %d  -  %s\t%s   %s     \t%s", i+1, arrAl[i].id, arrAl[i].sName, arrAl[i].sCarrera, arrAl[i].sCiudad, arrAl[i].sFecha);
                ind = getIndexCalif(arrCalif, numCalif, arrAl[i].id);
                fprintf(outF,"\t Notas: - %.1f %.1f %.1f %.1f\n", arrCalif[ind].mA, arrCalif[ind].mB, arrCalif[ind].mC, arrCalif[ind].mD);
                
            }
            if (bOutput == 1)
                fprintf(outF, "\n");
            break;
        }
        
        case 2:{
            printf(" ** Da enter sin escribir nada para salir **\n");
               while (1){
                    char str[35];
                    str[0] = '\0';
                    char *qry[3];
                    int arg = 0, bFlag = 0;
                    getchar();

                    printf("\n Query >");
                    scanf("%[^\n]", str);

                    if (bOutput == 1 && str != NULL)
                    {
                        fprintf(outF, " Query >%s\n", str);
                    }
                    
                    if (bVerbose == 1)
                        fprintf(outF, " ~ Separando query en substrings \n");
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
                        printf(" !!! Error: Query inválido. Revisa la documentación si necesitas ayuda !!! \n");
                        bFlag = 0;
                    }
                    else if (qry[2] == NULL){
                        arg = 2;
                        bFlag = 1;
                    }

                    if (bFlag == 1) {
                        if (bVerbose == 1)
                            fprintf(outF, " ~ Ejecutando query \n");
                        //Llamar a menu
                        int iMenu = -1;
                        iMenu = menuQuery(qry, arg);
                        switch(iMenu){
                            case 1: //Caso Kardex
                            {
                                kardex(arrCalif, arrAl, numCalif, atoi(qry[1]), outF); 
                                break;
                            }
                            case 2: //Caso fecha de Graduacion
                            {
                                fechaGrad(arrAl, numAlum, atoi(qry[1]), outF);
                                break;
                            }
                            case 3: //Numero de alumnos. Filtro: Carrera y ciudad
                            {
                                numAlum2(arrAl, numAlum, qry[1], qry[2], outF);
                                break;
                            }
                            case 4: //Numero de alumnos en total.
                            {
                                numAlumT(numAlum, outF);
                                break;
                            }
                            case 5:  //Numero de alumnos. Filtro: Carrera 
                            {
                                numAlum1(arrAl, numAlum, qry[1], outF);
                                break;
                            }
                            case 6: //Nombre de alumnos con operador
                            {
                                nombAlumOp(arrCalif, arrAl, numAlum, qry[1], atof(qry[2]), outF);
                                break;
                            }
                            case 7: //Nombre de alumno.  Filtro: Carrera y ciudad
                            {
                                nombAlum2(arrAl, numAlum, qry[1], qry[2], outF);
                                break; 
                            }
                            case 8: //Nombre de todos los alumnos
                            {
                                nombAlumT(arrAl, numAlum, outF);
                                break;
                            }
                            case 9: //Nombre de los alumnos. Filtro: Carrera
                            {
                                nombAlum1(arrAl, numAlum, qry[1], outF);
                                break;
                            }

                            default:
                                printf(" !!! Error: Query inválido. Revisa la documentación si necesitas ayuda !!! \n");
                        }
                    }
                    fprintf(outF, "\n");
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

    /* Liberar memoria dinamica */
    if (bVerbose == 1)
        fprintf(outF, " ~ Liberando memoria dinamica\n");
    free(arrAl);
    free(arrCalif);
    
    return 0;
}
