#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./lib/clase_ag.cpp"   //incluyo la libreria que estÃ¡ en carpeta contigua
#include "./Actvidad2-master/extra_ag2.cpp"  //incluyo libreria

#define N_BYTES         400  // longitud mÃ¡xima del string (cromosoma). se utiliza a efectos de reserva de espacio
#define N_INDIVIDUOS    1 //cantidad de individuos que forman a la poblaciÃ³n
#define N_PASOS        400      //cantidad de pasos maximos que hara el algoritmo
#define N_CASILLAS        22      //longitud de un lado del mapa que es de forma de cuadrada


typedef unsigned char uchar;
typedef unsigned long ulong;

// variables
int mapa[N_CASILLAS][N_CASILLAS]; //El valor de cada caja


CLASECromosoma a, b, c, d; //varios cromosomas auxiliares
CLASEAGenetico ag;  //poblaciÃ³n de cromosomas a ser cruzadas en el AG (ag=poblaciÃ³n)
FILE *archivo;      //archivo de salida donde se guardan variables de monitoreo
FILE *mapas;
bool t;

// DECLARAR funciones (prototipo de las funciones que se definen al final del cÃ³digo)
float evaluacion(uchar *);  //funciÃ³n que recibe el string que forma al cromosoma, lo decodifica, y devuelve su fitness
void mostrar(uchar *);  //funciÃ³n que recibe al cromosoma y lo muestra en pantalla (visualizaciÃ³n)

int main(){
    //apuntador auxiliar a un cromosoma
    CLASECromosoma *apuntador = NULL;

    ag.InicializarSemillaRand(true);    //incializo la semilla aleatoria
    ag.PoblacionAleatoria(N_INDIVIDUOS, N_BYTES);   //configuraciÃ³n de la poblaciÃ³n inicial
    ag.FuncionEvaluacion(evaluacion);   //indico cual es la funciÃ³n de decodificaciÃ³n/fitness
    ag.dTasaMutacion = 0.1f;            //tasa de mutaciÃ³n

    //archivo de excel
    archivo = fopen("ejemplo01_evol.xls", "w+");

    fprintf(archivo, "Mejor:\tPoblacion:\n"); // \n\r para windows

    //Se abre el archivo donde esta el mapa
    mapas = fopen("matriz.prn", "r");


    t=importTabFile(mapas,mapa,N_CASILLAS);


    //inicio ciclo de entrenamiento
    do{
        ag.Generacion();    //itero una generaciÃ³n: selecciÃ³n -> cruce -> mutaciÃ³n
        apuntador = ag.SeleccionarMejor();  //selecciono al mejor
        //imprimo en pantalla (y en el archivo) al fitness del mejor y al de la poblaciÃ³n
        printf("\nMejor: %.3f\tPob: %.3f\t", apuntador->Fitness(), ag.Fitness());
        fprintf (archivo, "%.3f\t%.3f\n", apuntador->Fitness(), ag.Fitness());
        //muestro el contenido del cromosoma del mejor
        mostrar(apuntador->Cromosoma);
    }while(ag.Edad() < 1);    // condicion de parada

    //imprimo la edad de la poblacion: numero de iteraciones totales ejecutadas (generaciones)
    printf ("\n\tGeneracion: %ld \n", ag.Edad());


    for (int i=0; i<N_CASILLAS; i++)
        {

    for (int j=0; j<N_CASILLAS; j++)
		{
            printf("%d ",mapa[i][j]);
		}
		printf("\n");
        }
    //cierro al archivo correctamente
    fclose(archivo);
    return 0;
}

// DEFINICION de funciones
/*
 ** ----------------------------------------------------------------------------
 **     Nombre      :
 **     FunciÃ³n     :
 **     ParÃ¡metros  :
 **     Retorna     :
 ** ----------------------------------------------------------------------------
 */
float evaluacion(uchar* cromosoma)
{
    float fitness = 0;      //auxiliar en el cÃ¡lculo de valor o fitness de la soluciÃ³n
    float Penalizacion = 0; //valor de penalizacion si solucion no es valida
    int Est_actual;
    int Est_siguente;
    int j=0, k=0;
    int dis_x, dis_y,dis_xi, dis_yi;
    float distancia = 0, distancia_i = 0;
    float dis_total = 0;


    //ahora calculo el fitness, o valor neto, en funciÃ³n del ValorTotal, la Penalizacion y el VolumenRest
    fitness = 1/(1 + dis_total);
    return fitness;
}

/*
 ** ----------------------------------------------------------------------------
 **     Nombre      :
 **     FunciÃ³n     :
 **     ParÃ¡metros  :
 **     Retorna     :
 ** ----------------------------------------------------------------------------
 */

void mostrar(uchar* cromosoma)
{
    float fitness = 0;      //auxiliar en el cÃ¡lculo de valor o fitness de la soluciÃ³n
    float Penalizacion = 0; //valor de penalizacion si solucion no es valida
    int Est_actual;
    int Est_siguente;
    int j=0, k=0;
    int dis_x, dis_y,dis_xi, dis_yi;
    float distancia = 0, distancia_i = 0;
    float dis_total = 0;


    fitness = 1/(1 + dis_total);
    printf ("\nFitness= %.3f\tDistancia Total= %.2f\n", fitness, dis_total);



}
