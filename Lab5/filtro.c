//arecord -f S16_LE -B 1000 -Ddefault -t raw |aplay -B 200000 -R 200000 -f S16_LE -t raw --period-size=10
//arecord -f S16_LE -B 1000 -Ddefault -t raw | /usr/local/filtro A|aplay -B 200000 -R 200000 -f S16_LE -t raw --period-size=10
//arecord -f S16_LE -B 1000 -Ddefault -t raw | /usr/local/filtro B|aplay -B 200000 -R 200000 -f S16_LE -t raw --period-size=10
#include <stdio.h>
#include <stdint.h>

#define NUMCOEFS (47)

int16_t memoriaI[NUMCOEFS+1]={};

int16_t coeficientesPA[NUMCOEFS]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Incompleto

int16_t coeficientesPB[NUMCOEFS]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Incompleto

int16_t *pcoef;

int32_t desplaza;

int16_t Calc_FIR(int16_t nuevo,int16_t *memoria){
        int64_t suma =0;
	uint16_t h,g;
    
    	memoria[NUMCOEFS]=nuevo;

	//Incompleto
        return suma>>desplaza;
}

int16_t c;

int main(int argc, char *argv[]){
  	
   if (argc>1)
      {
	  if ((argv[1])[0]=='A')
	    {
	      pcoef=coeficientesPA;
	      desplaza=0;//Cambiar
	    }
	  else if ((argv[1])[0]=='B')
	    {
	      pcoef=coeficientesPB;
	      desplaza=0;//Cambiar  
	    }
	  else
	    { //Posible tercer filtro
	      pcoef=coeficientesPA;
	      desplaza=0;//Cambiar  
	    }
      }else{ //Opcion si no hay parametro adicional
	  pcoef=coeficientesPA;
          desplaza=0;//Cambiar
      }

   while (1)
      {
         if (fread(&c,1,2,stdin)>0)
           {
             c=Calc_FIR(c,memoriaI);
	     fwrite(&c,2,1,stdout);
           }
      }
  return 0;
}
