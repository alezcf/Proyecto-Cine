
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
char sala[5][4];

int sala_llena = 12, ocupacion_actual = 0;
int A = 4, B = 4, C = 4, D = 4, E = 4;

void generar_sala();
void mostrar_sala();
int menu();
void recursos(int *dinero, int *entradas);
void reservas(int *dinero, int *entradas);
bool marcar_asiento(int fila, int columna);
void eliminar_reserva();
void asientos_libres();
void mayor_reserva();

int main()
{
    int opcion, dinero = 0, entradas = 0;
    int *efectivo = &dinero, *boletos = &entradas;

    generar_sala(); 
    mostrar_sala();
    do
    {
    
    opcion = menu();

    if(opcion == 1)
        {
            recursos(&dinero, &entradas);
            reservas(&dinero, &entradas);
        }
    if(opcion == 2)
        {
            eliminar_reserva();
        }
    if(opcion == 3)
        {
            mayor_reserva();
        }
    if(opcion == 4)
        {
            asientos_libres();
        }
    } while (opcion != 5);

}

void generar_sala()
{

    int fila, columna;

    for(fila = 0; fila < 5 ; fila ++)
    {
        for(columna = 0; columna < 4; columna ++)
        {
            sala[fila][columna] = '-';
        }
    }
}

void mostrar_sala()
{
    int fila, columna;

    printf("  ");

    for(columna = 0 ; columna < 4; columna++) // Parte numerica de los asientos.
    {
        printf("%d ", columna+1);
    }

    printf("\n");

    for (fila=0; fila < 5; fila++) // Primer for representa filas, tambien muestra
                                   // por pantalla las letras por posicion.
    {
        if(fila == 0)
        {
            printf("A");
        }
        if(fila == 1)
        {
            printf("B");
        }
        if(fila == 2)
        {
            printf("C");
        }
        if(fila == 3)
        {
            printf("D");
        }
        if(fila == 4)
        {
            printf("E");
        }
        for(columna=0; columna < 4; columna ++) // Segundo for muestra por pantalla las 
                           // posiciones de la matriz ocupadas y libres.
        {
            printf(" %c", sala[fila][columna]);
        }

        printf("\n");
    }
    printf("\n");
}

int menu()
{
    int opcion;

    printf("1. Reservar asiento\n");
    printf("2. Eliminar asiento\n");
    printf("3. Mostrar fila con mas reserva de asientos\n");
    printf("4. Mostrar columna del asiento que este menos ocupada de la sala\n");
    printf("5. Salir\n");

    printf("Ingresa la opcion a ejecutar: ");

    do // Se debe ingresar un numero entre 1 y 5, inclusive.
    {
        scanf("%d", &opcion);
    }while(opcion < 1 || opcion > 5);
    
    return opcion; // Se retorna opcion escogida.
}

void recursos(int *dinero, int *entradas)
{

    int efectivo, boletos;

    printf("\nEscogiste la opcion de reservar asiento, mostraremos la tabla de precios.\n\n");
    printf("\nFila    Precio\n");
    printf("\nA - B   3.500$\n");
    printf("\nC - D   2.000$\n");
    printf("\n  E     1.000$\n");

    printf("Ahora debes ingresar la cantidad de entradas a comprar y tu dinero disponible.\n\n");

    do
    {
        printf("Ingresa tu dinero disponible: ");
        scanf("%d", &efectivo);

        do
        {
            printf("Ingresa la cantidad de entradas a comprar:" );
            scanf("%d", &boletos);

            if(boletos + ocupacion_actual > 12)
            {
                printf("Protocolo COVID: Tu compra rompe el aforo permitido, quedan solo %d entradas disponibles.\n", sala_llena - ocupacion_actual);
                break;
            }
        } while (boletos + ocupacion_actual > 12);

        if (efectivo < boletos *  1000)
        {
            printf("Debes tener un minimo de %d pesos para adquirir las entradas mas baratas.\n", boletos * 1000);
        }
    } while (efectivo < 1000 * boletos || boletos <= 0);

    *entradas = boletos;
    *dinero = efectivo;

}

void reservas(int *dinero, int *entradas)
{
    char letra = 'z';
    int fila, columna, costo, exit;
    int efectivo = *dinero, boletos = *entradas;
    bool disponibilidad;

    /* El usuario debe ingresar la letra que representa las filas
       y el numero de columna. Al momento de ingresar una letra, 
       se reemplazara por un numero entero en la variable 'int fila', 
       el cual permitira concretar un intercambio de "-" por "X" 
       dentro de la matriz.*/  


    printf("Entradas = %d\nDinero = %d", boletos, efectivo);

    do
    {
        if (ocupacion_actual >= sala_llena)
        {
        printf("\nNo hay mas asientos disponibles, protocolo COVID.\n");
        break; 
        }

        if(efectivo < 1000)
        {
            printf("\nEl dinero restante es insuficiente para adquirir otra entrada. Se mantendran las adquiridas previamente.\n");
            break;
        }

        boletos --; 

        printf("Ingresa la letra de la fila:");
        scanf(" %c", &letra);


        if(letra == 'a' || letra == 'A')
        {
            fila = 0;
            costo = 3500;
            efectivo -= costo;

        }
        else if(letra == 'b' || letra == 'B')
        {
            fila = 1;
            costo = 3500;
            efectivo -= costo;
        }
        else if(letra == 'c' || letra == 'C')
        {
            fila = 2;
            costo = 2000;
            efectivo -= costo;
        }
        else if(letra == 'd' || letra == 'D')
        {
            fila = 3;
            costo = 2000;
            efectivo -= costo;
        }
        else if(letra == 'e' || letra == 'E')
        {
            fila = 4;
            costo = 1000;
            efectivo -= costo;
        }
        else
        {
            printf("\nHaz ingresado una letra de fila invalida, regresaras al menu.\n");
            break;
        }

        printf("Ingresa el numero de la columna: ");
        scanf("%d", &columna);

        if(efectivo < 0)
        {
            printf("\nNo te alcanza el dinero para adquirir la entrada, se te regresara el monto previo.\n");
            efectivo += costo;
            printf("Dinero actual: %d\n", efectivo);
            boletos ++;
            do
            {
                printf("\nSi deseas continuar el proceso, ingresa 1, si deseas cancelar una nueva compra, ingresa 2: ");
                scanf("%d", &exit);

            }while (exit < 1 || exit > 2);

            if(exit == 1)
            {
                printf("\nLas entradas compradas previamente se mantendran.\n");
                continue;
            }
            else
            {
                printf("\nLas entradas compradas previamente se mantendran, puedes cancelar asientos con la opcion 2 del menu.\n");
                break;
            }
        }
        else 
        {
            
            if (columna > 4 || columna < 1 && fila > 4 || fila < 0)
            {
                printf("\nLa letra o numero ingresada es invalida, dinero regresado.");
                efectivo += costo;
                boletos ++;
            }  
            else
            {
                disponibilidad = marcar_asiento(fila, columna);

                if(disponibilidad == true)
                {
                    ocupacion_actual += 1;
                    mostrar_sala();
                }
                else
                {
                    ocupacion_actual -= 1;
                    efectivo += costo;
                    boletos ++;
                }
            }

            if(ocupacion_actual == sala_llena)
            {
                printf("\nProtocolo COVID: Hemos llenado la capacidad permitida, no hay mas puestos disponibles.\n");
                break;
            }
            else
            {
                continue;
            }
        }

        
    } while (boletos > 0);
    
}

bool marcar_asiento(int fila, int columna)
{

    if(sala[fila][columna-1] == 'X')
    {
         printf("\nEl asiento escogido ya esta ocupado, se te devolvera el dinero.\n");
         return false;
    }
    else
    {
        sala[fila][columna-1] = 'X';
        return true;
    }
}

void eliminar_reserva()
{
    char letra = 'z';
    int fila = 20, columna;
    printf("Escogiste la opcion de eliminar asiento (reserva)\n");
    /* La letra ingresada por teclado se reemplazara por un numero,
       dependiendo de su posicion*/
    do
    {
        printf("Ingresa la letra de la fila:");
        scanf(" %c", &letra);
        if(letra == 'a' || letra == 'A')
        {
            fila = 0;
        }
        if(letra == 'b' || letra == 'B')
        {
            fila = 1;
        }
        if(letra == 'c' || letra == 'C')
        {
            fila = 2;
        }
        if(letra == 'd' || letra == 'D')
        {
            fila = 3;
        }
        if(letra == 'e' || letra == 'E')
        {
            fila = 4;
        }
        printf("\nIngresa el numero de la columna: ");
        scanf("%d", &columna);

    }while(columna > 4 || columna < 1 || fila > 4 || fila < 0);

    /* Si la posicion escogida no esta reservada, se le hara saber al usuario
       y se le volvera a mostrar los asientos libres y ocupados.*/

    if (sala[fila][columna-1] == '-')
    {
        printf("\nEl asiento seleccionado no se encuentra reservado.\n");
    }
    else if(sala[fila][columna-1] == 'X')
    {
        sala[fila][columna-1] = '-';
        mostrar_sala();
    }
    
}

void mayor_reserva()
{
    int x, y, contador[4], mayor;

    char asiento[6] = {'A', 'B', 'C', 'D', 'E', '\0'};

    /* El contador representara la suma de cada fila,
       al momento de detectar un asiento ocupado, se sumara uno.

       Al terminar de recorrer una fila, se pasara a la siguiente.*/



    for(x=0; x<4; x++)
    {
        contador[x] = 0;
    }

    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            if(sala[x][y] == 'X')
            {
                contador[x] += 1;
            }
        }
    }

    /* La variable "mayor" tomara la posicion 0 del arreglo,
       la cual se ira comparando con las demas filas.

       La fila con mayor numero sera mostrada por pantalla, en caso
       de que existan dos con el mismo numero de filas, se le informara
       al usuario de dos o mas */

    mayor = contador[0];
    for(x=1; x<4; x++)
    {
        if(contador[x] > mayor)
        {
            mayor = contador[x];
        }
    }

    if (mayor == 0)
    {
        printf("\n\nTodos los asientos estan libres.\n\n");
    }

    else
    {
        for(x=0; x<4; x++)
    {
        if(mayor == contador[x])
        {
            printf("\nLa fila %c tiene %d asientos ocupados.\n", asiento[x], contador[x]);
        }
    }
    }

    mostrar_sala();
}

void asientos_libres()
{
    int x, y, contador[4], menor=0;

    for(x=0; x<4; x++)
    {
        contador[x] = 0;
    }

    for(x=0; x<5; x++)
    {
        for(y=0; y<4; y++)
        {
            if (sala[x][y] == 'X')
            {
                contador[y] += 1;
            }
        }
    }

    menor = contador[0];

    for(x=1; x<4; x++)
    {
        if(menor > contador[x])
        {
            menor = contador[x];
        }
    }

    int aux = 0;

    for(y=0; y<4; y++)
    {
        if(contador[y] == contador[y+1])
        {
            aux += 1;
        }
    }

    if(aux == 4)
    {
            printf("\n\nTodos los numeros de columnas tienen la misma cantidad de asientos libres.\n\n");
    }
    else
    {
        for(x=0; x<4; x++)
        {
            if(menor == contador[x])
            {
            printf("\nLa columna con menos asientos ocupados es la numero %d.\n", x+1);
            }
        }  
    }

    mostrar_sala();
}