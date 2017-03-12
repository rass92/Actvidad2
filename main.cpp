#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./lib/clase_ag.cpp"   //incluyo la libreria que está en carpeta contigua
#include "./lib/extra_ag2.h"

#define N_BYTES         5  // longitud máxima del string (cromosoma). se utiliza a efectos de reserva de espacio
#define N_INDIVIDUOS    100 //cantidad de individuos que forman a la población
#define N_DATOS      25     // Cantidad de datos dentro del documento de datos
#define N_FUNC      5       //Cantidad de funciones ccon las que se va a comparar

typedef unsigned char uchar;
typedef unsigned long ulong;

CLASECromosoma a, b, c, d; //varios cromosomas auxiliares
CLASEAGenetico ag;  //población de cromosomas a ser cruzadas en el AG (ag=población)
FILE *archivo;      //archivo de salida donde se guardan variables de monitoreo
FILE *mejor;        //archivo donde se guarda los valores del mejor cromosoma final
FILE *fp;           //archivo de datos donde estara los valores reales
bool t;


// DECLARAR funciones (prototipo de las funciones que se definen al final del código)
float evaluacion(uchar *);  //función que recibe el string que forma al cromosoma, lo decodifica, y devuelve su fitness
void mostrar(uchar *);  //función que recibe al cromosoma y lo muestra en pantalla (visualización)
float y_cal[N_DATOS],x_dado[N_DATOS],y_dado[N_DATOS];
int main()
{
    //apuntador auxiliar a un cromosoma
    CLASECromosoma *apuntador = NULL;

    ag.InicializarSemillaRand(true);    //incializo la semilla aleatoria
    ag.PoblacionAleatoria(N_INDIVIDUOS, N_BYTES);   //configuración de la población inicial
    ag.FuncionEvaluacion(evaluacion);   //indico cual es la función de decodificación/fitness
    ag.dTasaMutacion = 0.1f;            //tasa de mutación

    //archivo de excel
    archivo = fopen("ejemplo01_evol.xls", "w+");
    fprintf(archivo, "Mejor:\tPoblacion:\n"); // \n\r para windows

    fp=fopen("data2.xls", "r");     //abriendo el archivo de los valores reales
    t=importTabFile(fp,x_dado,y_dado,N_DATOS);

     mejor=fopen("mejor.txt", "w+");

    //inicio ciclo de entrenamiento
    do{
        ag.Generacion();    //itero una generación: selección -> cruce -> mutación
        apuntador = ag.SeleccionarMejor();  //selecciono al mejor
        //imprimo en pantalla (y en el archivo) al fitness del mejor y al de la población
        printf("\nMejor: %.3f\tPob: %.3f\t", apuntador->Fitness(), ag.Fitness());
        fprintf (archivo, "%.3f\t%.3f\n", (apuntador->Fitness())*100, (ag.Fitness())*100);
        //muestro el contenido del cromosoma del mejor
        mostrar(apuntador->Cromosoma);
    }while(ag.Edad() < 5000);    // condicion de parada



    //imprimo la edad de la poblacion: numero de iteraciones totales ejecutadas (generaciones)
    printf ("\n\tGeneracion: %ld", ag.Edad());

    //metiendo el valores del mejor cromosoma

	for (int z=0; z < N_DATOS; z++)
	{
		fprintf(mejor, "%f\t%f\n", x_dado[z], y_cal[z]);
	}


    //cierro al archivo correctamente
    fclose(archivo);
    fclose(mejor);
    fclose(fp);
    return 0;
}

// DEFINICION de funciones
/*
 ** ----------------------------------------------------------------------------
 **     Nombre      :
 **     Función     :
 **     Parámetros  :
 **     Retorna     :
 ** ----------------------------------------------------------------------------
 */
float evaluacion(unsigned char* cromosoma)
{
    float fitness = 0;      //auxiliar en el cálculo de valor o fitness de la solución
    float Penalizacion = 0; //valor de penalizacion si solucion no es valida
    float error=0;          //el error entre el valor real y el estimado
    int curva;              // numero de funcion que se va a evaluar
    float valor1,valor2,valor3,valor4;      //los coeficientes de la funcion a evaluar
    int i;



    // decodificando cada byte del cromosoma

    curva = cromosoma[0]%N_FUNC;

    valor1 = crDecodificar8(cromosoma[1],5,-5);
    valor2 = crDecodificar8(cromosoma[2],5,-5);
    valor3 = crDecodificar8(cromosoma[3],5,-5);
    valor4 = crDecodificar8(cromosoma[4],5,-5);

    //funcion seno

    if(curva==0){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*sin(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

    //funcion coseno

    if(curva==1){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*cos(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

    //funcion exponencial

     if(curva==2){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*exp(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

        // funcion recta

       if(curva==3){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1+valor2*x_dado[i];
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

    //funcion polinomica

    if(curva==4){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1+valor2*x_dado[i]+valor3*pow(x_dado[i],2)+valor4*pow(x_dado[i],3);
                error=pow((y_cal[i]-y_dado[i]),2);
                Penalizacion=Penalizacion+error;
            }
    }

        //diviendo entre el valor total del error cuadratico medio
    Penalizacion=Penalizacion/N_DATOS;

    fitness = 100/(1 + Penalizacion);


    return fitness;
}

/*
 ** ----------------------------------------------------------------------------
 **     Nombre      :
 **     Función     :
 **     Parámetros  :
 **     Retorna     :
 ** ----------------------------------------------------------------------------
 */

void mostrar(uchar* cromosoma)
{

    float fitness = 0;      //auxiliar en el cálculo de valor o fitness de la solución
    float Penalizacion = 0; //valor de penalizacion si solucion no es valida
    float error=0;
    int curva;
    float valor1,valor2,valor3,valor4;
    int i;






    curva = cromosoma[0]%N_FUNC;
    valor1 = crDecodificar8(cromosoma[1],5,-5);
    valor2 = crDecodificar8(cromosoma[2],5,-5);
    valor3 = crDecodificar8(cromosoma[3],5,-5);
    valor4 = crDecodificar8(cromosoma[4],5,-5);





    if(curva==0){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*sin(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

    if(curva==1){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*cos(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

     if(curva==2){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1*exp(valor2*x_dado[i]+valor3)+valor4;
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

       if(curva==3){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1+valor2*x_dado[i];
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }

    if(curva==4){
            for(i=0;i<N_DATOS;i++){
                y_cal[i]=valor1+valor2*x_dado[i]+valor3*pow(x_dado[i],2)+valor4*pow(x_dado[i],3);
                error=pow(y_cal[i]-y_dado[i],2);
                Penalizacion=Penalizacion+error;
            }
    }
    Penalizacion=Penalizacion/N_DATOS;
    fitness = 100/(1 + Penalizacion);
   printf ("\nFitness= %.3f\t Error Total= %.2f\n Curva=%d\tValor1=%.2f\t Valor2=%.2f\t Valor3=%.2f\t Valor4=%.2f\n", fitness, Penalizacion,curva,valor1,valor2,valor3,valor4);
}
