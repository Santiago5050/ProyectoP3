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
intervalo_indexado *merge_sort_intervalos(intervalo_t *intervalos,uint n);
void imprimir(intervalo_indexado *arreglo_intervalos, uint n);

//Implementaciones

/* La funcion bool compatibles retorna true sii Los
intervalos i y j son compatibles */
bool compatibles(intervalo_t i, intervalo_t j)
{
  return ((i.fin <= j.inicio) || (j.fin <= i.inicio));
}

/* Ordena el arreglo de intervalos segun su
tiempo de finalizacion*/
intervalo_indexado *merge_sort_intervalos(intervalo_indexado *intervalos, uint n)
{
  uint medio = floor(n/2);
  intervalo_indexado *arreglo;
  if(n == 1)
  {
    arreglo = new intervalo_indexado[1];
    arreglo[0].intervalo = intervalos[0].intervalo;
    arreglo[0].index = intervalos[0].index;
  }
  else if(n == 2)
  {
    arreglo = new intervalo_indexado[2];
    if(intervalos[0].intervalo.fin <= intervalos[1].intervalo.fin)
    {
      arreglo[0].intervalo = intervalos[0].intervalo;
      arreglo[0].index = intervalos[0].index;
      arreglo[1].intervalo = intervalos[1].intervalo;
      arreglo[1].index = intervalos[1].index;
    }
    else
    {
      arreglo[0].intervalo = intervalos[1].intervalo;
      arreglo[0].index = intervalos[1].index;
      arreglo[1].intervalo = intervalos[0].intervalo;
      arreglo[1].index = intervalos[0].index;
    }
  }
  else
  {
    arreglo = new intervalo_indexado[n];
    //manipulacion del arreglo ordenado a la izquierda
    intervalo_indexado *arreglo_izq = new intervalo_indexado[medio];
    for(uint i = 0; i < medio; i++)
    {
      arreglo_izq[i].intervalo = intervalos[i].intervalo;
      arreglo_izq[i].index = intervalos[i].index;
    }
    intervalo_indexado *arreglo_izq_sort = merge_sort_intervalos(arreglo_izq, medio);
    delete[] arreglo_izq;

    //manipulacion del arreglo ordenado a la derecha
    intervalo_indexado *arreglo_der = new intervalo_indexado[n - medio];
    for (uint i = 0; i < (n - medio); i++)
    {
      arreglo_der[i].intervalo = intervalos[i + medio].intervalo;
      arreglo_der[i].index = intervalos[i + medio].index;
    }
    intervalo_indexado *arreglo_der_sort = merge_sort_intervalos(arreglo_der, n - medio);
    delete[] arreglo_der;

    //merge del arreglo final.
    uint der = 0;
    uint izq = 0;
    uint i = 0;
    while((der < (n - medio)) && (izq < medio))
    {
      if(arreglo_izq_sort[izq].intervalo.fin <= arreglo_der_sort[der].intervalo.fin)
      {
        arreglo[i].intervalo = arreglo_izq_sort[izq].intervalo;
        arreglo[i].index = arreglo_izq_sort[izq].index;
        i++;
        izq++;
      }
      else
      {
        arreglo[i].intervalo = arreglo_der_sort[der].intervalo;
        arreglo[i].index = arreglo_der_sort[der].index;
        i++;
        der++;
      }
    }
    //si aun no se termino de pasar el arreglo derecho
    if(der < (n - medio))
    {
      while(i < n)
      {
        arreglo[i].intervalo = arreglo_der_sort[der].intervalo;
        arreglo[i].index = arreglo_der_sort[der].index;
        i++;
        der++;
      }
    }
    else if (izq < medio) //si aun no termino el izquierdo
    {
      while(i < n)
      {
        arreglo[i].intervalo = arreglo_izq_sort[izq].intervalo;
        arreglo[i].index = arreglo_izq_sort[izq].index;
        i++;
        izq++;
      }
    }
    
    delete[] arreglo_izq_sort;
    delete[] arreglo_der_sort;
  }
  return arreglo;
}

void imprimir(intervalo_indexado *arreglo_intervalos, uint n)
{
  printf("{");
  for (uint i = 0; i < n; i++)
    printf("%d_%d,", arreglo_intervalos[i].intervalo.inicio, arreglo_intervalos[i].intervalo.fin);
  printf("}\n");
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
  intervalo_indexado *intervalos_ordenados = merge_sort_intervalos(arreglo_intervalos, n);
  //verificar que los intervalos esten ordenados
  //imprimir(intervalos_ordenados, n);
  //paso_2 arreglo S[i] = intervalo_i_inicio
  uint tiempo_inicio[n];
  for (uint i = 0; i < n; i++)
    tiempo_inicio[i] = intervalos_ordenados[i].intervalo.inicio;
  //paso_3 calcular la solucion final
  bool *intervalos_solucion = new bool[n];
  for (uint i = 0; i < n; i++)
    intervalos_solucion[i] = false;
  //se añade el primer intervalo que termine antes
  intervalos_solucion[intervalos_ordenados[0].index] = true;
  int ultimo_agregado = 0;
  for (uint i = 1; i < n; i++)
  {
    if(tiempo_inicio[i] >= intervalos_ordenados[ultimo_agregado].intervalo.fin)
    {
      ultimo_agregado = i;
      intervalos_solucion[intervalos_ordenados[ultimo_agregado].index] = true;
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
  delete[] intervalos_ordenados;
  delete[] arreglo_intervalos;
  return intervalos_solucion;
}

bool *max_volumen(const intervalo_t *intervalos, uint n)
{
    bool *arreglo = new bool[1];
    return arreglo;
}
