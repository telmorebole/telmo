
//Usa como entrada ruido blanco y genera una gráfica
//del contenido frecuencial resultado de filtrar 
//empleando el filtro diseñado en Calc_FIR
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fft-complex.h"
#include "dislin.h"

static double complex *random_complexes(int n);
static void *memdup(const void *src, size_t n);
void dibuja(float *ind,float *resul,int n,float maxim);

#define NUMCOEFS (uint16_t) 47
uint16_t N=NUMCOEFS;

int16_t memoriaI[NUMCOEFS+1]={};

// Coeficientes paso alto (HPF)
int16_t coefsPA[NUMCOEFS] = {
    53, 59, -115, 0, 192, -156, -204, 426, 0, -684, 526, 650, -1288, 0, 1912,
    -1440, -1763, 3530, 0, -5785, 4914, 7533, -24693, 32767, -24693, 7533, 4914,
    -5785, 0, 3530, -1763, -1440, 1912, 0, -1288, 650, 526, -684, 0, 426, -204,
    -156, 192, 0, -115, 59, 53
};


// Coeficientes paso bajo (LPF)
int16_t coefsPB[NUMCOEFS] = {
    -36, -39, 76, 0, -128, 104, 136, -284, 0, 456, -351, -433, 859, 0, -1275, 960,
    1175, -2353, 0, 3856, -3276, -5022, 16462, 32767, 16462, -5022, -3276, 3856,
    0, -2353, 1175, 960, -1275, 0, 859, -433, -351, 456, 0, -284, 136, 104, -128,
    0, 76, -39, -36
};


#define SIZE_RUIDO 8192

int16_t ruido[SIZE_RUIDO];

int16_t *pcoef;

int32_t desplaza=17; //17 de los que mejor resultado ha dado

//AÑADIDO POR NOSOTROS
int16_t Calc_FIR(int16_t nuevamuestra, int16_t *memoria) {
    int64_t suma = 0;  // Acumulador de 64 bits
    uint16_t i;

    // Desplazar las muestras en el registro de memoria hacie delante
	// y la nueva muestra se coloca al inicio del registro
    for (i = NUMCOEFS; i > 0; i--) {
        memoria[i] = memoria[i - 1];  
    }
    memoria[0] = nuevamuestra;  // Insertar la nueva muestra al inicio

    // Calcular la salida del filtro FIR
	//multiplica cada muestra por su coeficiente correspondiente y acumula el resultado en suma
    for (i = 0; i < NUMCOEFS; i++) {
        suma += (int64_t)memoria[i] * pcoef[i];  // Convolución
    }

    // Escalar el resultado para ajustarlo a 16 bits
    return (int16_t)(suma >> desplaza);
}


int main(int argc, char *argv[]) {
	int i;

	srand(time(NULL));
	int n=SIZE_RUIDO;
	float resultado[SIZE_RUIDO];
	float indice[SIZE_RUIDO];
	double complex *input = random_complexes(n);
	double complex *actual = memdup(input, n * sizeof(double complex));

	////////////////////////////////
	// para evitar saturaciones o errores de precisión de salida
	// probamos con desplaza=15, finalmente el que mejor ha ido es 17

	if (argc>1){
	  if ((argv[1])[0]=='A'){
	    pcoef=coefsPA;
	    desplaza=17;//Cambiar (antes era 0)
	  }else{
	    pcoef=coefsPB;
	    desplaza=17;//Cambiar
	  }
        }else{
	  pcoef=coefsPB;
	  desplaza=17;//Cambiar
	}

	////////////////////////////////
	
	srand(time(NULL));   
	for (i=0;i<N+1;i++){
	  memoriaI[i]=0;
	}    
	for (i=0;i<SIZE_RUIDO;i++){
	  ruido[i]=(rand() % 65536) - 32768;
	}
	
	////////////////////////////////
	clock_t begin = clock();

	int16_t *inicio=ruido;
	int16_t lSample=0;
	for (uint16_t i=0;i< SIZE_RUIDO;i=i+1){

	  int16_t lSample = (int16_t) inicio[0] ;
	  lSample=Calc_FIR(lSample,memoriaI);
	  
	  inicio[0] = lSample;
	  inicio=&inicio[1];
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tiempo: %f",time_spent);
    
	FILE *f = fopen("outcome.data", "wb");    
	fwrite(ruido, sizeof(char), sizeof(ruido), f);
	fclose(f);
	////////////////////////////////
	for (i=0;i<n;i++){  //Creamos num complejo para entrada FFT
	  actual[i]=(float)ruido[i]+0*I;
	}
	////////////////////////////////  
	Fft_transform(actual, n, false); //Calculo FFT

	//Pasamos a escala log y obtenemos maximo para la grafica
	float maximo=0;  
	for (i=0;i<n;i++){
	  resultado[i]=20*log10(cabs(actual[i]));
	  indice[i]=i/(n/2.0);  //Normalizacion matlab
	  if (resultado[i]>maximo){
	    maximo=resultado[i];
	  }
	}
	///////////////////////////////
	
	dibuja(indice,resultado,n,maximo);
	///////////////////////////////////
	free(input);
	free(actual);	
	 
	return 0;
}

double complex *random_complexes(int n) {
	double complex *result = malloc(n * sizeof(double complex));
	for (int i = 0; i < n; i++) {
		double re = (rand() / (RAND_MAX + 1.0)) * 2 - 1;
		double im = (rand() / (RAND_MAX + 1.0)) * 2 - 1;
		result[i] = re + im * I;
	}
	return result;
}

void *memdup(const void *src, size_t n) {
	void *dest = malloc(n);
	if (n > 0 && dest != NULL)
		memcpy(dest, src, n);
	return dest;
}


void dibuja(float *ind,float *resul,int n,float maxim){
  int ic;
        //metafl ("cons");
	metafl ("PDF");
	scrmod ("revers");
	disini ();
	pagera ();
	complx ();
	axspos (450, 1800);
	axslen (2200, 1200);

	name   ("Frecuencia normalizada", "x");
	name   ("20*log10(abs(FFT))", "y");

	labdig (-1, "x");
	ticks  (9, "x");
	ticks  (10, "y");

	//titlin ("FFT of the signal", -1);

	ic =   intrgb (0.95,0.95,0.95);
	axsbgd (ic);

	graf   (0.0, 2, 0, 1, 0, maxim, 0, 100);
	setrgb (0.7, 0.7, 0.7);
	grid   (1, 1);

	color  ("fore");
	height (50);
	title  ();

	color  ("red");
	curve  (ind, resul, n);
	disfin ();
}
