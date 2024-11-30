#include <stdio.h>
#include <string.h>
#define PRODUCTOS 5
#define NOMBRES 40

void ingresarProductos(char nombres[][NOMBRES], float recursosTiempo[][2]);
void agregarProducto(char nombres[][NOMBRES], float recursosTiempo[][2]);
void editarProducto(char nombres[][NOMBRES], float recursosTiempo[][2]);
void eliminarProducto(char nombres[][NOMBRES], float recursosTiempo[][2]);
void calcularDemanda(char nombres[][NOMBRES], float recursosTiempo[][2], int cantidades[]);
void mostrarProductos(char nombres[][NOMBRES]);
void visualizarProductos(char nombres[][NOMBRES], float recursosTiempo[][2]);

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
        printf("1.- Agregar producto\n2.- Editar producto\n3.- Eliminar producto\n4.- Calcular cumplimiento de demanda\n5.- Visualizar productos\n6.- Salir\n");
        scanf("%i", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            agregarProducto(nombresProductos, recursosTiempo);
            break;
        case 2:
            editarProducto(nombresProductos, recursosTiempo);
            break;
        case 3:
            eliminarProducto(nombresProductos, recursosTiempo);
            break;
        case 4:
            calcularDemanda(nombresProductos, recursosTiempo, cantidadesDemandadas);
            break;
        case 5:
            visualizarProductos(nombresProductos, recursosTiempo);
            break;
        case 6:
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

        do
        {
            printf("Ingrese la cantidad de recursos que requiere para fabricar una unidad del producto %i (> 0):\n", i + 1);
            scanf("%f", &recursosTiempo[i][0]);
            if (recursosTiempo[i][0] <= 0)
                printf("Error: el valor debe ser mayor a 0.\n");
        } while (recursosTiempo[i][0] <= 0);

        do
        {
            printf("Ingrese el tiempo requerido (en minutos con decimales) para fabricar una unidad del producto %i (> 0):\n", i + 1);
            scanf("%f", &recursosTiempo[i][1]);
            if (recursosTiempo[i][1] <= 0)
                printf("Error: el valor debe ser mayor a 0.\n");
        } while (recursosTiempo[i][1] <= 0);

        getchar();
    }
}

void agregarProducto(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    int espacioDisponible = -1;
    int cont = 0;

    do
    {
        for (int i = 0; i < PRODUCTOS; i++)
        {
            if (strlen(nombres[i]) == 0)
            {
                espacioDisponible = i;
                break;
            }
        }

        if (espacioDisponible == -1)
        {
            printf("No hay espacio disponible para agregar más productos.\n");
            cont = 1;
        }
        else
        {
            printf("Ingrese el nombre del nuevo producto:\n");
            fgets(nombres[espacioDisponible], NOMBRES, stdin);
            strtok(nombres[espacioDisponible], "\n");

            do
            {
                printf("Ingrese la cantidad de recursos que requiere para fabricar una unidad (> 0):\n");
                scanf("%f", &recursosTiempo[espacioDisponible][0]);
                if (recursosTiempo[espacioDisponible][0] <= 0)
                    printf("Error: el valor debe ser mayor a 0.\n");
            } while (recursosTiempo[espacioDisponible][0] <= 0);

            do
            {
                printf("Ingrese el tiempo requerido (en minutos) para fabricar una unidad (> 0):\n");
                scanf("%f", &recursosTiempo[espacioDisponible][1]);
                if (recursosTiempo[espacioDisponible][1] <= 0)
                    printf("Error: el valor debe ser mayor a 0.\n");
            } while (recursosTiempo[espacioDisponible][1] <= 0);

            printf("Producto agregado exitosamente.\n");
            cont = 1;
        }
    } while (cont == 0);
}

void editarProducto(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    int opcion, edit;
    do
    {
        printf("1) Editar nombre\n2) Editar recursos y tiempo\n");
        scanf("%i", &opcion);
        getchar();
        if (opcion < 1 || opcion > 2)
            printf("Opción no válida.\n");
    } while (opcion < 1 || opcion > 2);

    mostrarProductos(nombres);

    do
    {
        printf("Escoja el producto a editar:\n");
        scanf("%d", &edit);
        getchar();
        if (edit < 1 || edit > PRODUCTOS)
            printf("Opción no válida.\n");
    } while (edit < 1 || edit > PRODUCTOS);

    if (opcion == 1)
    {
        printf("Ingrese el nuevo nombre del producto %i:\n", edit);
        fgets(nombres[edit - 1], NOMBRES, stdin);
        strtok(nombres[edit - 1], "\n");
    }
    else if (opcion == 2)
    {
        do
        {
            printf("Ingrese la nueva cantidad de recursos para el producto %i (> 0):\n", edit);
            scanf("%f", &recursosTiempo[edit - 1][0]);
            if (recursosTiempo[edit - 1][0] <= 0)
                printf("Error: el valor debe ser mayor a 0.\n");
        } while (recursosTiempo[edit - 1][0] <= 0);

        do
        {
            printf("Ingrese el nuevo tiempo requerido para el producto %i (> 0):\n", edit);
            scanf("%f", &recursosTiempo[edit - 1][1]);
            if (recursosTiempo[edit - 1][1] <= 0)
                printf("Error: el valor debe ser mayor a 0.\n");
        } while (recursosTiempo[edit - 1][1] <= 0);
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

    do
    {
        printf("Escoja el producto que quiere eliminar:\n");
        scanf("%d", &eliminar);
        getchar();
        if (eliminar < 1 || eliminar > PRODUCTOS)
            printf("Opción no válida.\n");
    } while (eliminar < 1 || eliminar > PRODUCTOS);

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
            do
            {
                printf("\nIngrese la cantidad demandada del producto %s (> 0): ", nombres[i]);
                scanf("%d", &cantidades[i]);
                if (cantidades[i] <= 0)
                    printf("Error: la cantidad debe ser mayor a 0.\n");
            } while (cantidades[i] <= 0);

            float recursosDisponibles, tiempoDisponible;

            do
            {
                printf("Ingrese la cantidad de recursos disponibles para el producto %s (> 0): ", nombres[i]);
                scanf("%f", &recursosDisponibles);
                if (recursosDisponibles <= 0)
                    printf("Error: el valor debe ser mayor a 0.\n");
            } while (recursosDisponibles <= 0);

            do
            {
                printf("Ingrese el tiempo disponible para el producto %s (> 0): ", nombres[i]);
                scanf("%f", &tiempoDisponible);
                if (tiempoDisponible <= 0)
                    printf("Error: el valor debe ser mayor a 0.\n");
            } while (tiempoDisponible <= 0);

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

void visualizarProductos(char nombres[][NOMBRES], float recursosTiempo[][2])
{
    printf("\nListado de Productos con Recursos y Tiempo:\n");
    for (int i = 0; i < PRODUCTOS; i++)
    {
        if (strlen(nombres[i]) > 0)
        {
            printf("%d.- %s\n", i + 1, nombres[i]);
            printf("   Recursos requeridos: %.2f\n", recursosTiempo[i][0]);
            printf("   Tiempo requerido: %.2f minutos\n", recursosTiempo[i][1]);
        }
    }
}