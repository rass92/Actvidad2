#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./lib/clase_ag.cpp"   //incluyo la libreria que estÃ¡ en carpeta contigua
#include "./lib/extra_ag2.cpp"  //incluyo libreria

#define N_BYTES         400  // longitud mÃ¡xima del string (cromosoma). se utiliza a efectos de reserva de espacio
#define N_INDIVIDUOS    100 //cantidad de individuos que forman a la poblaciÃ³n
#define N_PASOS        400      //cantidad de pasos maximos que hara el algoritmo
#define N_MOV        4      //numero de pasos que se pueden realizar: arriba, abajo, izquierda y derecha
#define N_CASILLAS        22      //longitud de un lado del mapa que es de forma de cuadrada


typedef unsigned char uchar;
typedef unsigned long ulong;

// variables
int map[casillas]; //El valor de cada caja


CLASECromosoma a, b, c, d; //varios cromosomas auxiliares
CLASEAGenetico ag;  //poblaciÃ³n de cromosomas a ser cruzadas en el AG (ag=poblaciÃ³n)
FILE *archivo;      //archivo de salida donde se guardan variables de monitoreo
FILE *mapas;
bool t;

// DECLARAR funciones (prototipo de las funciones que se definen al final del cÃ³digo)
float evaluacion(uchar *);  //funciÃ³n que recibe el string que forma al cromosoma, lo decodifica, y devuelve su fitness
void mostrar(uchar *);  //funciÃ³n que recibe al cromosoma y lo muestra en pantalla (visualizaciÃ³n)

int main()
{
    //apuntador auxiliar a un cromosoma
    CLASECromosoma *apuntador = NULL;

    ag.InicializarSemillaRand(true);    //incializo la semilla aleatoria
    ag.PoblacionAleatoria(N_INDIVIDUOS, N_BYTES);   //configuraciÃ³n de la poblaciÃ³n inicial
    ag.FuncionEvaluacion(evaluacion);   //indico cual es la funciÃ³n de decodificaciÃ³n/fitness
    ag.dTasaMutacion = 0.1f;            //tasa de mutaciÃ³n

    //archivo de excel
    archivo = fopen("ejemplo01_evol.xls", "w+");
    mapas = fopen("matriz.prn", "r");
    fprintf(archivo, "Mejor:\tPoblacion:\n"); // \n\r para windows
    t=importTabFile(mapas,*map,N_CASILLAS);
    
    
    //inicio ciclo de entrenamiento
    do{
        ag.Generacion();    //itero una generaciÃ³n: selecciÃ³n -> cruce -> mutaciÃ³n
        apuntador = ag.SeleccionarMejor();  //selecciono al mejor
        //imprimo en pantalla (y en el archivo) al fitness del mejor y al de la poblaciÃ³n
        printf("\nMejor: %.3f\tPob: %.3f\t", apuntador->Fitness(), ag.Fitness());
        fprintf (archivo, "%.3f\t%.3f\n", apuntador->Fitness(), ag.Fitness());
        //muestro el contenido del cromosoma del mejor
        mostrar(apuntador->Cromosoma);
    }while(ag.Edad() < 500);    // condicion de parada

    //imprimo la edad de la poblacion: numero de iteraciones totales ejecutadas (generaciones)
    printf ("\n\tGeneracion: %ld", ag.Edad());
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
    float repetidos = 0; //valor de penalizacion si el paso es repetido
    float chocados = 0; //valor de penalizacion si se choca con obstáculos
    int pasoActual;
    int pasoSiguente;
    //int j=0;
    int k=0;
    float posicion[][]; //este se supone que es el arreglo que viene de mi matriz fija
    int pos_x=0, pos_y=0;
    int ubi_x=0, ubi_y=0;

    int pasosVacios = 327;

    //procedo a decodificar el cromosoma, para ver cuales cajas van dentro del contenedor
    //char mask = 0x01;
    for (int i=0; i < N_PASOS; i++)
    {
        if(pasosVacios==0){
                pasoActual = *(cromosoma + i); //0,1,2,3
                pasoSiguente = *(cromosoma + i + 1); //0,1,2,3

                //j = pasoActual% N_MOV;
                k = pasoSiguente% N_MOV;
                
                if(k==0){
                    pos_y = pos_y + 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_y = ubi_y + 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_y = ubi_y + 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_y = pos_y - 1;
                    }
                }
                
                if(k==1){
                    pos_x = pos_x + 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_x = ubi_x + 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_x = ubi_x + 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_x = pos_x - 1;
                    }
                }
            
                if(k==2){
                    pos_y = pos_y - 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_y = ubi_y - 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_y = ubi_y - 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_y = pos_y + 1;
                    }
                }
            
                if(k==3){
                    pos_x = pos_x - 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_x = ubi_x - 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_x = ubi_x - 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_x = pos_x + 1;
                    }
                }
            //distancia = sqrt((pow(dis_x,2))+(pow(dis_y,2)));
            //dis_total = dis_total + distancia + Penalizacion + distancia_i;
            //Penalizacion = 0;
            //distancia_i = 0;
        }else{
            i=N_PASOS;
        }
    }
    //Ahora debo de calcular el error
    //Para ello chequeo si excedo del mÃ¡ximo permitido. Si estoy dentro del rango, penalizo

    //ahora calculo el fitness, o valor neto, en funciÃ³n del ValorTotal, la Penalizacion y el VolumenRest
    fitness = 1/(1 + repetidos + chocados);
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
    float repetidos = 0; //valor de penalizacion si el paso es repetido
    float chocados = 0; //valor de penalizacion si se choca con obstáculos
    int pasoActual;
    int pasoSiguente;
    //int j=0;
    int k=0;
    float posicion[][]; //este se supone que es el arreglo que viene de mi matriz fija
    int pos_x=0, pos_y=0;
    int ubi_x=0, ubi_y=0;

    int pasosVacios = 327;

    //procedo a decodificar el cromosoma, para ver cuales cajas van dentro del contenedor
    //char mask = 0x01;
    for (int i=0; i < N_PASOS; i++)
    {
        if(pasosVacios==0){
                pasoActual = *(cromosoma + i); //0,1,2,3
                pasoSiguente = *(cromosoma + i + 1); //0,1,2,3

                //j = pasoActual% N_MOV;
                k = pasoSiguente% N_MOV;
                
                if(k==0){
                    pos_y = pos_y + 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_y = ubi_y + 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_y = ubi_y + 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_y = pos_y - 1;
                    }
                }
                
                if(k==1){
                    pos_x = pos_x + 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_x = ubi_x + 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_x = ubi_x + 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_x = pos_x - 1;
                    }
                }
            
                if(k==2){
                    pos_y = pos_y - 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_y = ubi_y - 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_y = ubi_y - 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_y = pos_y + 1;
                    }
                }
            
                if(k==3){
                    pos_x = pos_x - 1;
                    if(posicion[pos_x][pos_y]==0){
                        ubi_x = ubi_x - 1; 
                    }else if(posicion[pos_x][pos_y]==1){
                        ubi_x = ubi_x - 1;
                        repetidos = repetidos + 1;
                    }else{
                         chocados =  chocados + 1;
                         pos_x = pos_x + 1;
                    }
                }
            //distancia = sqrt((pow(dis_x,2))+(pow(dis_y,2)));
            //dis_total = dis_total + distancia + Penalizacion + distancia_i;
            //Penalizacion = 0;
            //distancia_i = 0;
        }else{
            i=N_PASOS;
        }
    }
    //Ahora debo de calcular el error
    //Para ello chequeo si excedo del mÃ¡ximo permitido. Si estoy dentro del rango, penalizo

    //ahora calculo el fitness, o valor neto, en funciÃ³n del ValorTotal, la Penalizacion y el VolumenRest
    fitness = 1/(1 + repetidos + chocados);
    printf ("\nFitness= %.3f\tDistancia Total= %.2f\n", fitness);

