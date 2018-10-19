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
//intervalo_indexado *merge_sort_intervalos(intervalo_t *intervalos,uint n);
void merge_sort_intervalos(intervalo_indexado intervalos[], uint n);
void imprimir(intervalo_indexado arreglo_intervalos[], uint n);
uint max(uint a, uint b);

//Implementaciones

/* La funcion bool compatibles retorna true sii Los
intervalos i y j son compatibles */
bool compatibles(intervalo_t i, intervalo_t j)
{
  return ((i.fin <= j.inicio) || (j.fin <= i.inicio));
}

/* Ordena el arreglo de intervalos segun su
tiempo de finalizacion*/
// intervalo_indexado *merge_sort_intervalos(intervalo_indexado *intervalos, uint n)
// {
//   uint medio = floor(n/2);
//   intervalo_indexado *arreglo;
//   if(n == 1)
//   {
//     arreglo = new intervalo_indexado[1];
//     arreglo[0].intervalo = intervalos[0].intervalo;
//     arreglo[0].index = intervalos[0].index;
//   }
//   else if(n == 2)
//   {
//     arreglo = new intervalo_indexado[2];
//     if(intervalos[0].intervalo.fin <= intervalos[1].intervalo.fin)
//     {
//       arreglo[0].intervalo = intervalos[0].intervalo;
//       arreglo[0].index = intervalos[0].index;
//       arreglo[1].intervalo = intervalos[1].intervalo;
//       arreglo[1].index = intervalos[1].index;
//     }
//     else
//     {
//       arreglo[0].intervalo = intervalos[1].intervalo;
//       arreglo[0].index = intervalos[1].index;
//       arreglo[1].intervalo = intervalos[0].intervalo;
//       arreglo[1].index = intervalos[0].index;
//     }
//   }
//   else
//   {
//     arreglo = new intervalo_indexado[n];
//     //manipulacion del arreglo ordenado a la izquierda
//     intervalo_indexado *arreglo_izq = new intervalo_indexado[medio];
//     for(uint i = 0; i < medio; i++)
//     {
//       arreglo_izq[i].intervalo = intervalos[i].intervalo;
//       arreglo_izq[i].index = intervalos[i].index;
//     }
//     intervalo_indexado *arreglo_izq_sort = merge_sort_intervalos(arreglo_izq, medio);
//     delete[] arreglo_izq;
//
//     //manipulacion del arreglo ordenado a la derecha
//     intervalo_indexado *arreglo_der = new intervalo_indexado[n - medio];
//     for (uint i = 0; i < (n - medio); i++)
//     {
//       arreglo_der[i].intervalo = intervalos[i + medio].intervalo;
//       arreglo_der[i].index = intervalos[i + medio].index;
//     }
//     intervalo_indexado *arreglo_der_sort = merge_sort_intervalos(arreglo_der, n - medio);
//     delete[] arreglo_der;
//
//     //merge del arreglo final.
//     uint der = 0;
//     uint izq = 0;
//     uint i = 0;
//     while((der < (n - medio)) && (izq < medio))
//     {
//       if(arreglo_izq_sort[izq].intervalo.fin <= arreglo_der_sort[der].intervalo.fin)
//       {
//         arreglo[i].intervalo = arreglo_izq_sort[izq].intervalo;
//         arreglo[i].index = arreglo_izq_sort[izq].index;
//         i++;
//         izq++;
//       }
//       else
//       {
//         arreglo[i].intervalo = arreglo_der_sort[der].intervalo;
//         arreglo[i].index = arreglo_der_sort[der].index;
//         i++;
//         der++;
//       }
//     }
//     //si aun no se termino de pasar el arreglo derecho
//     if(der < (n - medio))
//     {
//       while(i < n)
//       {
//         arreglo[i].intervalo = arreglo_der_sort[der].intervalo;
//         arreglo[i].index = arreglo_der_sort[der].index;
//         i++;
//         der++;
//       }
//     }
//     else if (izq < medio) //si aun no termino el izquierdo
//     {
//       while(i < n)
//       {
//         arreglo[i].intervalo = arreglo_izq_sort[izq].intervalo;
//         arreglo[i].index = arreglo_izq_sort[izq].index;
//         i++;
//         izq++;
//       }
//     }
//
//     delete[] arreglo_izq_sort;
//     delete[] arreglo_der_sort;
//   }
//   return arreglo;
// }


void imprimir(intervalo_indexado arreglo_intervalos[], uint n)
{
  printf("{");
  for (uint i = 0; i < n; i++)
    printf("%d_%d,", arreglo_intervalos[i].intervalo.inicio, arreglo_intervalos[i].intervalo.fin);
  printf("}\n");
}

void merge_sort_intervalos(intervalo_indexado intervalos[], uint n)
{
  // if(n == 2)
  // {
  //   intervalo_indexado arreglo[2];
  //   if(intervalos[0].intervalo.fin <= intervalos[1].intervalo.fin)
  //   {
  //     arreglo[0].intervalo = intervalos[0].intervalo;
  //     arreglo[0].index = intervalos[0].index;
  //     arreglo[1].intervalo = intervalos[1].intervalo;
  //     arreglo[1].index = intervalos[1].index;
  //   }
  //   else
  //   {
  //     arreglo[0].intervalo = intervalos[1].intervalo;
  //     arreglo[0].index = intervalos[1].index;
  //     arreglo[1].intervalo = intervalos[0].intervalo;
  //     arreglo[1].index = intervalos[0].index;
  //   }
  //   intervalos = arreglo;
  // }
  // else
  if(n > 1)
  {
    //Ordenamiento del arreglo izquierdo
    uint medio = floor(n/2);
    intervalo_indexado arreglo_izq[medio];
    for (uint i = 0; i < medio; i++)
    {
      arreglo_izq[i].intervalo = intervalos[i].intervalo;
      arreglo_izq[i].index = intervalos[i].index;
    }
    merge_sort_intervalos(arreglo_izq, medio);

    //Ordenamiento del arreglo derecho
    intervalo_indexado arreglo_der[n - medio];
    for(uint i = 0; i < (n - medio); i++)
    {
      arreglo_der[i].intervalo = intervalos[i + medio].intervalo;
      arreglo_der[i].index = intervalos[i + medio].index;
    }
    merge_sort_intervalos(arreglo_der, (n - medio));

    //Merge de los arreglos
    uint der = 0;
    uint izq = 0;
    uint i = 0;
    while((izq < medio)&&( der < (n - medio)))
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
    while(izq < medio)
    {
      intervalos[i].intervalo = arreglo_izq[izq].intervalo;
      intervalos[i].index = arreglo_izq[izq].index;
      i++;
      izq++;
    }
    //Completo el arreglo derecho si no se termino de cargar
    while(der < (n - medio))
    {
      intervalos[i].intervalo = arreglo_der[der].intervalo;
      intervalos[i].index = arreglo_der[der].index;
      i++;
      der++;
    }
  }
}


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
  intervalo_indexado arreglo_intervalos[n];
  for (uint i = 0; i < n; i++)
  {
    arreglo_intervalos[i].intervalo = intervalos[i];
    arreglo_intervalos[i].index = i;
  }
  //paso_1 ordenar los intervalos por tiempo de finalizacion
  merge_sort_intervalos(arreglo_intervalos, n);

  //verificar que los intervalos esten ordenados
  //imprimir(arreglo_intervalos, n);

  //paso_2 arreglo S[i] = intervalo_i_inicio
  uint tiempo_inicio[n];
  for (uint i = 0; i < n; i++)
    tiempo_inicio[i] = arreglo_intervalos[i].intervalo.inicio;

  //paso_3 calcular la solucion final
  bool *intervalos_solucion = new bool[n];
  for (uint i = 0; i < n; i++)
    intervalos_solucion[i] = false;

  //se añade el primer intervalo que termine antes
  intervalos_solucion[arreglo_intervalos[0].index] = true;
  int ultimo_agregado = 0;
  for (uint i = 1; i < n; i++)
  {
    if(tiempo_inicio[i] >= arreglo_intervalos[ultimo_agregado].intervalo.fin)
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

  return intervalos_solucion;
}

bool *max_volumen(const intervalo_t *intervalos, uint n)
{
    // bool *arreglo = new bool[1];
    // return arreglo;
    intervalo_indexado arreglo_intervalos[n];
    for (uint i = 0; i < n; i++)
    {
      arreglo_intervalos[i].intervalo = intervalos[i];
      arreglo_intervalos[i].index = i;
    }

    //paso_1 ordenar los intervalos por tiempo de finalizacion
    merge_sort_intervalos(arreglo_intervalos, n);

    //verificar que los intervalos esten ordenados
    //imprimir(arreglo_intervalos, n);

    //paso_2 calculo de compatible_anterior(i) para todo i intervalo
    int compatible_anterior[n];
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
    uint optimal[n];
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
    // for(uint i = n-1; i >= 1; i--) //Construccion de la solucion final;
    // {
    //   if((arreglo_intervalos[i].intervalo.volumen + optimal[compatible_anterior[i]]) >= optimal[i-1])
    //   {
    //     solucion[arreglo_intervalos[i].index] = true;
    //     i = compatible_anterior[i];
    //   }
    // }

    //retorno la solucion final
    // Ver la solucion retornada
    // printf("{");
    // for (uint i = 0; i < n; i++) {
    //   if (solucion[i]) {
    //     printf("%d_%d,",intervalos[i].inicio, intervalos[i].fin);
    //   }
    // }
    // printf("}\n");
    return solucion;
}
