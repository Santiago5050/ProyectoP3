#include "include/intervalos.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct intervalo_indexado
{
  uint index;
  intervalo_t intervalo;
};

//Definiciones
bool compatibles(intervalo_t i, intervalo_t j);
void merge_intervalos(intervalo_indexado * intervalo, uint left, uint middle, uint right);
void merge_sort_intervalos(intervalo_indexado *intervalos, uint left ,uint right);
void imprimir(intervalo_indexado *arreglo_intervalos, uint n);
uint max(uint a, uint b);

//Implementaciones

/* La funcion bool compatibles retorna true sii Los
intervalos i y j son compatibles */
bool compatibles(intervalo_t i, intervalo_t j)
{
  return ((i.fin <= j.inicio) || (j.fin <= i.inicio));
}

/*Imprime los intervalos del arreglo_intervalos con el
formato {inicio_fin,inicio_fin,etc}*/
void imprimir(intervalo_indexado *arreglo_intervalos, uint n)
{
  printf("{");
  for (uint i = 0; i < n; i++)
    printf("%d_%d,", arreglo_intervalos[i].intervalo.inicio, arreglo_intervalos[i].intervalo.fin);
  printf("}\n");
}

/*realiza el merge entre los arreglos intervalos[left..middle]
  y el arreglo intervalos[middle+1..right]*/
void merge_intervalos(intervalo_indexado *intervalos, uint left, uint middle, uint right)
{
    uint n1 = middle - left + 1;
    uint n2 = right - middle;

    //arreglos temporales
    intervalo_indexado *arreglo_izq = new intervalo_indexado[n1];
    intervalo_indexado *arreglo_der = new intervalo_indexado[n2];

    //Inicializando los arreglos temporales
    for (uint i = 0; i < n1; i++)
    {
      arreglo_izq[i].intervalo = intervalos[left + i].intervalo;
      arreglo_izq[i].index = intervalos[left + i].index;
    }
    for(uint i = 0; i < n2; i++)
    {
      arreglo_der[i].intervalo = intervalos[middle + 1 + i].intervalo;
      arreglo_der[i].index = intervalos[middle + 1 + i].index;
    }

    //Merge de los arreglos
    uint der = 0; //indice del intervalo derecho
    uint izq = 0; //indice del intervalo izquierdo
    uint i = left; //indice del arreglo solucion
    while((izq < n1)&&( der < n2))
    {
      if(arreglo_izq[izq].intervalo.fin <= arreglo_der[der].intervalo.fin)
      {
        intervalos[i].intervalo = arreglo_izq[izq].intervalo;
        intervalos[i].index = arreglo_izq[izq].index;
        i++;
        izq++;
      }
      else
      {
        intervalos[i].intervalo = arreglo_der[der].intervalo;
        intervalos[i].index = arreglo_der[der].index;
        i++;
        der++;
      }
    }
    //Completo el arreglo izquierdo si no se termino de cargar
    while(izq < n1)
    {
      intervalos[i].intervalo = arreglo_izq[izq].intervalo;
      intervalos[i].index = arreglo_izq[izq].index;
      i++;
      izq++;
    }
    //Completo el arreglo derecho si no se termino de cargar
    while(der < n2)
    {
      intervalos[i].intervalo = arreglo_der[der].intervalo;
      intervalos[i].index = arreglo_der[der].index;
      i++;
      der++;
    }
    delete[] arreglo_der;
    delete[] arreglo_izq;
}

/* Ordena el arreglo de intervalos segun su
tiempo de finalizacion*/
void merge_sort_intervalos(intervalo_indexado *intervalos, uint left ,uint right)
{
  if(left != right)
  {
    uint middle = floor((left + right)/2);
    merge_sort_intervalos(intervalos, left, middle);
    merge_sort_intervalos(intervalos, middle + 1, right);
    merge_intervalos(intervalos, left, middle, right);
  }
}

/*Retorna el maximo entre a y b*/
uint max(uint a, uint b)
{
  if(a >= b)
    return a;
  else
    return b;
}

bool *max_cantidad(const intervalo_t *intervalos, uint n)
{
  //cargamos un arreglo de intervalos con los que vienen de parametro
  intervalo_indexado *arreglo_intervalos = new intervalo_indexado[n];
  for (uint i = 0; i < n; i++)
  {
    arreglo_intervalos[i].intervalo = intervalos[i];
    arreglo_intervalos[i].index = i;
  }
  //paso_1 ordenar los intervalos por tiempo de finalizacion
  merge_sort_intervalos(arreglo_intervalos, 0, n-1);

  //verificar que los intervalos esten ordenados
  //imprimir(arreglo_intervalos, n);

  //paso_2 calcular la solucion final
  //se inicializa el arreglo de la solucion
  bool *intervalos_solucion = new bool[n];
  for (uint i = 0; i < n; i++)
    intervalos_solucion[i] = false;

  //se añade el primer intervalo que termine antes
  intervalos_solucion[arreglo_intervalos[0].index] = true;
  //se marca que el ultimo intervalo agregado fue el primero (indice: 0)
  int ultimo_agregado = 0;
  //se agregan el resto de intervalos a la solucion
  for (uint i = 1; i < n; i++)
  {
    if(arreglo_intervalos[i].intervalo.inicio >= arreglo_intervalos[ultimo_agregado].intervalo.fin)
    {
      ultimo_agregado = i;
      intervalos_solucion[arreglo_intervalos[ultimo_agregado].index] = true;
    }
  }

  //Ver la solucion retornada
  // printf("{");
  // for (uint i = 0; i < n; i++) {
  //   if (intervalos_solucion[i]) {
  //     printf("%d_%d,",intervalos[i].inicio, intervalos[i].fin);
  //   }
  // }
  // printf("}\n");

  delete[] arreglo_intervalos;
  return intervalos_solucion;
}

bool *max_volumen(const intervalo_t *intervalos, uint n)
{
    intervalo_indexado *arreglo_intervalos = new intervalo_indexado[n];
    for (uint i = 0; i < n; i++)
    {
      arreglo_intervalos[i].intervalo = intervalos[i];
      arreglo_intervalos[i].index = i;
    }

    //paso_1 ordenar los intervalos por tiempo de finalizacion
    merge_sort_intervalos(arreglo_intervalos, 0, n-1);

    //verificar que los intervalos esten ordenados
    //imprimir(arreglo_intervalos, n);

    //paso_2 calculo de compatible_anterior(i) para todo i intervalo
    int *compatible_anterior = new int[n];
    for(uint i = 0; i < n; i++)
    {
      compatible_anterior[i] = -1;
    }
    compatible_anterior[0] = -1;
    for(uint i = 1; i < n; i++)
    {
      int left = 0;
      int right = i;
      while(left <= right)
      {
        uint medio = floor((left + right)/2);
        //printf("INTERVALO: %d, LEFT: %d, RIGHT: %d, MEDIO: %d\n",i,left,right, medio);
        if((medio != i) && (arreglo_intervalos[medio].intervalo.fin <= arreglo_intervalos[i].intervalo.inicio))
        {
          compatible_anterior[i] = medio;
          left = medio + 1;
        }
        else
        {
          right = medio - 1;
        }
      }
    }

    //Verificacion compatible anterior correcto
    // for(uint i = 0; i < n; i++)
    // {
    //   printf("El P(%d) es: %d\n", i, compatible_anterior[i]);
    // }

    //paso_3 Calculo del optimal
    uint *optimal = new uint[n];
    for (uint i = 0; i < n; i++)
      optimal[i] = arreglo_intervalos[i].intervalo.volumen;
    for(uint i = 1; i < n; i++)
    {
      if(compatible_anterior[i] >= 0)
        optimal[i] = max(arreglo_intervalos[i].intervalo.volumen + optimal[compatible_anterior[i]], optimal[i - 1]);
      else
        optimal[i] = max(arreglo_intervalos[i].intervalo.volumen, optimal[i - 1]);
      //printf("OPT[%d] = %d; VOLUMEN: %d, OPT_ANT[%d] = %d; OPT[%d] = %d\n",i, optimal[i], arreglo_intervalos[i].intervalo.volumen, compatible_anterior[i], optimal[compatible_anterior[i]], i-1, optimal[i-1]);
    }

    //Verificacion del optimal
    // for(uint i = 0; i < n; i++)
    // {
    //   printf("OPT[%d] = %d, VOLUMEN: %d\n", i, optimal[i], arreglo_intervalos[i].intervalo.volumen);
    // }

    //paso_4 Construccion de la solucion
    bool *solucion = new bool[n];
    for(uint i = 0; i < n; i++) //Inicializacion del arreglo en false;
      solucion[i] = false;
    int j = n-1;
    if(n == 1)
      solucion[0] = true;
    while(j > 0)
    {
      if((compatible_anterior[j] == -1) && (arreglo_intervalos[j].intervalo.volumen > optimal[j-1]))
      {
        solucion[arreglo_intervalos[j].index] = true;
        j = compatible_anterior[j];
      }
      else if((compatible_anterior[j] >= 0) && (arreglo_intervalos[j].intervalo.volumen + optimal[compatible_anterior[j]] > optimal[j-1]))
      {
        solucion[arreglo_intervalos[j].index] = true;
        j = compatible_anterior[j];
      }
      else
        j--;
      if(j == 0)
        solucion[arreglo_intervalos[0].index] = true;
    }

    // Ver la solucion retornada
    // printf("{");
    // for (uint i = 0; i < n; i++) {
    //   if (solucion[i]) {
    //     printf("%d_%d,",intervalos[i].inicio, intervalos[i].fin);
    //   }
    // }
    // printf("}\n");

    //eliminacion de los arreglos auxiliares
    delete[] arreglo_intervalos;
    delete[] compatible_anterior;
    delete[] optimal;

    //retorno la solucion final
    return solucion;
}
