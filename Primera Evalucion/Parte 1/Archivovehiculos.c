#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char placa[10];
    char marca[30];
    char modelo[30];
    int anio;
    char color[20];
    double valor;
    char tipo;
    char estado;
} tVehiculo;

void limpiarBufferEntrada();
void continuar();
void asegurarArchivoExiste();
void registrarVehiculo();
void consultarVehiculos();
void actualizarVehiculo();
void eliminarActivarVehiculo();
void imprimirDatosVehiculo(tVehiculo vehiculo);
void seleccionVehiculos();
void mostrarLista();

int main() {
    asegurarArchivoExiste();
    int opcion;

    do {
        printf("\n--- CONCESIONARIO DE VEHICULOS ---\n");
        printf("1. Registrar un nuevo vehiculo\n");
        printf("2. Consultar vehiculos activos\n");
        printf("3. Actualizar informacion de un vehiculo\n");
        printf("4. Eliminar/Activar un vehiculo\n");
        printf("5. Mostrar Listas\n");
        printf("6. Filtrar por tipo\n");
        printf("7. Salir\n\n");
        printf("Ingrese su opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Error: Ingrese un numero valido.\n");
            limpiarBufferEntrada();
            opcion = 0;
            continuar();
            continue;
        }

        switch (opcion) {
            case 1:
                registrarVehiculo();
                break;
            case 2:
                consultarVehiculos();
                break;
            case 3:
                actualizarVehiculo();
                break;
            case 4:
                eliminarActivarVehiculo();
                break;
            case 5:
                mostrarLista();
                break;
            case 6:
                seleccionVehiculos();
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                continuar();
                break;
        }

    } while (opcion != 7);

    return 0;
}

void limpiarBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void continuar() {
    printf("\nPresione Enter para continuar...");
    limpiarBufferEntrada();
    getchar();
}

void asegurarArchivoExiste() {
    FILE *arch = fopen("vehiculos.dat", "ab");
    if (arch == NULL) {
        printf("Error critico: No se pudo crear o abrir el archivo de datos.\n");
        exit(1);
    }
    fclose(arch);
}

void imprimirDatosVehiculo(tVehiculo vehiculo) {
    printf("----------------------------------------\n");
    printf("Placa : %s\n", vehiculo.placa);
    printf("Marca : %s\n", vehiculo.marca);
    printf("Modelo: %s\n", vehiculo.modelo);
    printf("Anio  : %d\n", vehiculo.anio);
    printf("Color : %s\n", vehiculo.color);
    printf("Valor : $%.2f\n", vehiculo.valor);
    printf("Tipo  : %s\n", (vehiculo.tipo == 'P') ? "Propio" : "Consignado");
    printf("Estado: %s\n", (vehiculo.estado == 'A') ? "Activo" : "Eliminado");
    printf("----------------------------------------\n");
}

void registrarVehiculo() {
    FILE *arch = fopen("vehiculos.dat", "ab");
    if (arch == NULL) {
        printf("Error al abrir el archivo para registrar.\n");
        return;
    }

    tVehiculo vehiculo;

    printf("\n--- Registro de Nuevo Vehiculo ---\n");

    printf("Ingrese la placa: ");
    limpiarBufferEntrada();
    scanf("%9s", vehiculo.placa);

    printf("Ingrese la marca: ");
    scanf("%29s", vehiculo.marca);

    printf("Ingrese el modelo: ");
    scanf("%29s", vehiculo.modelo);

    printf("Ingrese el anio: ");
    scanf("%d", &vehiculo.anio);

    printf("Ingrese el color: ");
    scanf("%19s", vehiculo.color);

    printf("Ingrese el valor (precio): ");
    scanf("%lf", &vehiculo.valor);

    do {
        printf("Ingrese el tipo ('P' para Propio, 'C' para Consignado): ");
        limpiarBufferEntrada();
        scanf(" %c", &vehiculo.tipo);
        vehiculo.tipo = toupper(vehiculo.tipo);
    } while (vehiculo.tipo != 'P' && vehiculo.tipo != 'C');

    vehiculo.estado = 'A';

    fwrite(&vehiculo, sizeof(tVehiculo), 1, arch);

    fclose(arch);
    printf("\nVehiculo registrado con exito!\n");
    continuar();
}

void consultarVehiculos() {
    int opcion;
    printf("\n--- Consultar Vehiculos Activos ---\n");
    printf("1. Por marca y modelo\n");
    printf("2. Por rango de precio\n");
    printf("3. Por tipo (Propio/Consignado)\n");
    printf("Seleccione el tipo de consulta: ");
    scanf("%d", &opcion);

    FILE *arch = fopen("vehiculos.dat", "rb");
    if (arch == NULL) {
        printf("Error: No se pudo abrir el archivo de datos.\n");
        return;
    }

    tVehiculo vehiculo;
    int encontrados = 0;

    switch (opcion) {
        case 1: {
            char marca[30], modelo[30];
            printf("Ingrese la marca a buscar: ");
            scanf("%29s", marca);
            printf("Ingrese el modelo a buscar: ");
            scanf("%29s", modelo);

            printf("\nVehiculos encontrados para %s %s:\n", marca, modelo);
            while (fread(&vehiculo, sizeof(tVehiculo), 1, arch)) {
                if (strcmp(vehiculo.marca, marca) == 0 && strcmp(vehiculo.modelo, modelo) == 0 && vehiculo.estado == 'A') {
                    imprimirDatosVehiculo(vehiculo);
                    encontrados++;
                }
            }
            break;
        }
        case 2: {
            double min, max;
            printf("Ingrese el precio minimo: ");
            scanf("%lf", &min);
            printf("Ingrese el precio maximo: ");
            scanf("%lf", &max);

            printf("\nVehiculos encontrados en el rango de $%.2f a $%.2f:\n", min, max);
            while (fread(&vehiculo, sizeof(tVehiculo), 1, arch)) {
                if (vehiculo.valor >= min && vehiculo.valor <= max && vehiculo.estado == 'A') {
                    imprimirDatosVehiculo(vehiculo);
                    encontrados++;
                }
            }
            break;
        }
        case 3: {
            char tipo;
            do {
                printf("Ingrese el tipo a buscar ('P' para Propio, 'C' para Consignado): ");
                limpiarBufferEntrada();
                scanf(" %c", &tipo);
                tipo = toupper(tipo);
            } while (tipo != 'P' && tipo != 'C');

            printf("\nVehiculos encontrados de tipo '%c':\n", tipo);
            while (fread(&vehiculo, sizeof(tVehiculo), 1, arch)) {
                if (vehiculo.tipo == tipo && vehiculo.estado == 'A') {
                    imprimirDatosVehiculo(vehiculo);
                    encontrados++;
                }
            }
            break;
        }
        default:
            printf("Opcion de consulta no valida.\n");
            break;
    }

    if (encontrados == 0) {
        printf("\nNo se encontraron vehiculos que cumplan con los criterios de busqueda.\n");
    }

    fclose(arch);
    continuar();
}

void actualizarVehiculo() {
    char placa[10];
    printf("\n--- Actualizar Vehiculo ---\n");
    printf("Ingrese la placa del vehiculo a modificar: ");
    limpiarBufferEntrada();
    scanf("%9s", placa);

    FILE *arch = fopen("vehiculos.dat", "r+b");
    if (arch == NULL) {
        printf("Error al abrir el archivo para modificar.\n");
        return;
    }

    tVehiculo vehiculo;
    int existe = 0;
    while (fread(&vehiculo, sizeof(tVehiculo), 1, arch)) {
        if (strcmp(vehiculo.placa, placa) == 0) {
            printf("\nVehiculo encontrado. Datos actuales:\n");
            imprimirDatosVehiculo(vehiculo);

            int opcion;
            printf("Que desea modificar?\n");
            printf("1. Valor\n2. Tipo\n3. Estado\n");
            printf("Opcion: ");
            scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    printf("Ingrese el nuevo valor: ");
                    scanf("%lf", &vehiculo.valor);
                    break;
                case 2:
                    do {
                        printf("Ingrese el nuevo tipo ('P' o 'C'): ");
                        limpiarBufferEntrada();
                        scanf(" %c", &vehiculo.tipo);
                        vehiculo.tipo = toupper(vehiculo.tipo);
                    } while (vehiculo.tipo != 'P' && vehiculo.tipo != 'C');
                    break;
                case 3:
                    do {
                        printf("Ingrese el nuevo estado ('A' o 'E'): ");
                        limpiarBufferEntrada();
                        scanf(" %c", &vehiculo.estado);
                        vehiculo.estado = toupper(vehiculo.estado);
                    } while (vehiculo.estado != 'A' && vehiculo.estado != 'E');
                    break;
                default:
                    printf("Opcion no valida.\n");
                    fclose(arch);
                    continuar();
                    return;
            }

            long pos = ftell(arch) - sizeof(tVehiculo);
            fseek(arch, pos, SEEK_SET);

            fwrite(&vehiculo, sizeof(tVehiculo), 1, arch);

            printf("\nVehiculo actualizado con exito!\n");
            existe = 1;
            break;
        }
    }

    if (!existe) {
        printf("No se encontro ningun vehiculo con la placa '%s'.\n", placa);
    }

    fclose(arch);
    continuar();
}

void eliminarActivarVehiculo() {
    char placa[10];
    printf("\n--- Eliminar/Activar Vehiculo ---\n");
    printf("Ingrese la placa del vehiculo a cambiar de estado: ");
    limpiarBufferEntrada();
    scanf("%9s", placa);

    FILE *arch = fopen("vehiculos.dat", "r+b");
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    tVehiculo vehiculo;
    int existe = 0;
    while (fread(&vehiculo, sizeof(tVehiculo), 1, arch)) {
        if (strcmp(vehiculo.placa, placa) == 0) {
            printf("\nVehiculo encontrado. Estado actual: %s\n", (vehiculo.estado == 'A') ? "Activo" : "Eliminado");

            if (vehiculo.estado == 'A') {
                vehiculo.estado = 'E';
                printf("El estado del vehiculo ha sido cambiado a 'Eliminado'.\n");
            } else {
                vehiculo.estado = 'A';
                printf("El estado del vehiculo ha sido cambiado a 'Activo'.\n");
            }

            long pos = ftell(arch) - sizeof(tVehiculo);
            fseek(arch, pos, SEEK_SET);
            fwrite(&vehiculo, sizeof(tVehiculo), 1, arch);

            existe = 1;
            break;
        }
    }

    if (!existe) {
        printf("No se encontro ningun vehiculo con la placa '%s'.\n", placa);
    }

    fclose(arch);
    continuar();
}

void seleccionVehiculos() {
    char op;
    tVehiculo v;

    FILE *arch_lec = fopen("vehiculos.dat", "rb");
    if (arch_lec == NULL) {
        printf("Error: No se pudo abrir el archivo de datos.\n");
        return;
    }
    FILE *arch_esc = fopen("seleccion.dat", "wb");
    if (arch_esc == NULL) {
        printf("Error: No se pudo abrir el archivo de seleccion.\n");
        fclose(arch_lec);
        return;
    }

    printf("\n -----Filtro por Tipo-----\n");
    printf("Ingrese el tipo que desea filtrar (P/C): ");
    limpiarBufferEntrada();
    scanf(" %c", &op);
    op = toupper(op);

    while (fread(&v, sizeof(tVehiculo), 1, arch_lec) == 1) {
        if (v.tipo == op) {
            fwrite(&v, sizeof(tVehiculo), 1, arch_esc);
        }
    }
    printf("Archivo 'seleccion.dat' creado con los vehiculos filtrados.\n");

    fclose(arch_esc);
    fclose(arch_lec);
    continuar();
}

void mostrarLista() {
    int op;
    tVehiculo v;

    printf("\n -----Mostrar Listas-----\n");
    printf("Ingrese la lista que desea ver: \n");
    printf("1. Lista de todos los vehiculos\n");
    printf("2. Lista de vehiculos filtrados\n");
    printf("Opcion: ");
    scanf("%d", &op);

    switch (op) {
        case 1: {
            FILE *arch_main = fopen("vehiculos.dat", "rb");
            if (arch_main == NULL) {
                printf("Error: No se pudo abrir el archivo principal.\n");
                return;
            }
            printf("\n--- Vehiculos Activos (Todos) ---\n");
            int encontrados = 0;
            while (fread(&v, sizeof(tVehiculo), 1, arch_main) == 1) {
                if (v.estado == 'A') {
                    imprimirDatosVehiculo(v);
                    encontrados++;
                }
            }
            if (encontrados == 0) {
                 printf("No hay vehiculos activos para mostrar.\n");
            }
            fclose(arch_main);
            break;
        }
        case 2: {
            FILE *arch_fil = fopen("seleccion.dat", "rb");
            if (arch_fil == NULL) {
                printf("Error: No se pudo abrir el archivo filtrado. Genere uno primero (opcion 6).\n");
                return;
            }
            printf("\n--- Vehiculos Activos (Filtrados) ---\n");
            int encontrados = 0;
            while (fread(&v, sizeof(tVehiculo), 1, arch_fil) == 1) {
                if (v.estado == 'A') {
                    imprimirDatosVehiculo(v);
                    encontrados++;
                }
            }
             if (encontrados == 0) {
                 printf("No hay vehiculos activos para mostrar en la lista filtrada.\n");
            }
            fclose(arch_fil);
            break;
        }
        default:
            printf("Opcion no valida.\n");
            break;
    }
    continuar();
}