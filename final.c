#include <stdio.h>
#include <string.h>
#define PRODUCTOS 5
#define NOMBRES 40

void ingresarProductos(char nombres[][NOMBRES], float recursosTiempo[][2]);
void editarProducto(char nombres[][NOMBRES], float recursosTiempo[][2]);
void eliminarProducto(char nombres[][NOMBRES], float recursosTiempo[][2]);
void calcularDemanda(char nombres[][NOMBRES], float recursosTiempo[][2], int cantidades[]);
void mostrarProductos(char nombres[][NOMBRES]);

int main()
{
    char nombresProductos[PRODUCTOS][NOMBRES] = {0};
    float recursosTiempo[PRODUCTOS][2] = {0};
    int cantidadesDemandadas[PRODUCTOS] = {0};
    int opcion, cont = 0;

    ingresarProductos(nombresProductos, recursosTiempo);

    do
    {
        printf("\nSelecciona entre las opciones:\n");
        printf("1.- Editar producto\n2.- Eliminar producto\n3.- Calcular cumplimiento de demanda\n4.- Salir\n");
        scanf("%i", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            editarProducto(nombresProductos, recursosTiempo);
            break;
        case 2:
            eliminarProducto(nombresProductos, recursosTiempo);
            break;
        case 3:
            calcularDemanda(nombresProductos, recursosTiempo, cantidadesDemandadas);
            break;
        case 4:
            printf("Gracias por utilizar el sistema.\n");
            cont++;
            break;
        default:
            printf("Opción no válida, inténtelo de nuevo.\n");
        }
    } while (cont == 0);

    return 0;
}

void ingresarProductos(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    for (int i = 0; i < PRODUCTOS; i++)
    {
        printf("Ingrese el nombre del producto %i:\n", i + 1);
        fgets(nombres[i], NOMBRES, stdin);
        strtok(nombres[i], "\n");

        printf("Ingrese la cantidad de recursos que requiere para fabricar una unidad del producto %i:\n", i + 1);
        scanf("%f", &recursosTiempo[i][0]);

        printf("Ingrese la cantidad de tiempo (minutos en enteros, segundos en decimales) que requiere para fabricar una unidad del producto %i:\n", i + 1);
        scanf("%f", &recursosTiempo[i][1]);
        getchar();
    }
}

void editarProducto(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    int opcion, edit;
    printf("1) Editar nombre\n2) Editar recursos y tiempo\n");
    scanf("%i", &opcion);
    getchar();

    mostrarProductos(nombres);

    printf("Escoja el producto a editar:\n");
    scanf("%d", &edit);
    getchar();

    if (edit < 1 || edit > PRODUCTOS)
    {
        printf("Opción no válida.\n");
        return;
    }

    if (opcion == 1)
    {
        printf("Ingrese el nuevo nombre del producto %i:\n", edit);
        fgets(nombres[edit - 1], NOMBRES, stdin);
        strtok(nombres[edit - 1], "\n");
    }
    else if (opcion == 2)
    {
        printf("Ingrese la nueva cantidad de recursos:\n");
        scanf("%f", &recursosTiempo[edit - 1][0]);
        printf("Ingrese el nuevo tiempo de producción:\n");
        scanf("%f", &recursosTiempo[edit - 1][1]);
        getchar();
    }
    else
    {
        printf("Opción no válida.\n");
    }
}

void eliminarProducto(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    int eliminar;

    mostrarProductos(nombres);

    printf("Escoja el producto que quiere eliminar:\n");
    scanf("%d", &eliminar);
    getchar();

    if (eliminar < 1 || eliminar > PRODUCTOS)
    {
        printf("Opción no válida.\n");
        return;
    }

    for (int i = eliminar - 1; i < PRODUCTOS - 1; i++)
    {
        strcpy(nombres[i], nombres[i + 1]);
        recursosTiempo[i][0] = recursosTiempo[i + 1][0];
        recursosTiempo[i][1] = recursosTiempo[i + 1][1];
    }

    strcpy(nombres[PRODUCTOS - 1], "");
    recursosTiempo[PRODUCTOS - 1][0] = 0;
    recursosTiempo[PRODUCTOS - 1][1] = 0;
}

void calcularDemanda(char nombres[][NOMBRES], float recursosTiempo[][2], int cantidades[])
{
    for (int i = 0; i < PRODUCTOS; i++)
    {
        if (strlen(nombres[i]) > 0)
        {
            printf("\nIngrese la cantidad demandada del producto %s: ", nombres[i]);
            scanf("%d", &cantidades[i]);

            float recursosDisponibles, tiempoDisponible;
            printf("Ingrese la cantidad de recursos disponibles para el producto %s: ", nombres[i]);
            scanf("%f", &recursosDisponibles);
            printf("Ingrese el tiempo disponible para el producto %s: ", nombres[i]);
            scanf("%f", &tiempoDisponible);

            float recursosNecesarios = recursosTiempo[i][0] * cantidades[i];
            float tiempoNecesario = recursosTiempo[i][1] * cantidades[i];

            printf("\nProducto: %s\n", nombres[i]);
            printf("Recursos necesarios: %.2f\n", recursosNecesarios);
            printf("Tiempo necesario: %.2f\n", tiempoNecesario);

            if (recursosNecesarios <= recursosDisponibles && tiempoNecesario <= tiempoDisponible)
            {
                printf("¡Se puede cumplir la demanda para este producto!\n");
            }
            else
            {
                printf("¡No es posible cumplir la demanda para este producto!\n");
            }
        }
    }
}

void mostrarProductos(char nombres[][NOMBRES])
{
    for (int i = 0; i < PRODUCTOS; i++)
    {
        if (strlen(nombres[i]) > 0)
        {
            printf("%i.- %s\n", i + 1, nombres[i]);
        }
    }
}
