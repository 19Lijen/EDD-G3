#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure Definition
typedef struct {
    char brand[50];
    char model[50];
    int year;
    char plate[10];
    char color[50];
    char type; // Corregido: tipo es un solo caracter
    float price;
    char state; // Corregido: estado es un solo caracter
} Vehicle;


//Exist Plate
int exist_plate(char *plate) {
    FILE *file;
    Vehicle v;

    file = fopen("vehicle.dat", "rb");
    if (file == NULL) {
        return 0;
    }

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (strcmp(v.plate, plate) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
//New Vehicle Function
void add_vehicle(){
    FILE *file;
    Vehicle v;

    file = fopen("vehicle.dat", "ab");
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("\n--- Agregar nuevo vehiculo ---\n");
    printf("Marca: ");
    scanf("%s", v.brand);
    printf("Modelo: ");
    scanf("%s", v.model);
    printf("Año: ");
    scanf("%d", &v.year);

    do {
        printf("Placa: ");
        scanf("%s", v.plate);
        if (exist_plate(v.plate)) {
            printf("Error: La placa ya existe. Por favor ingrese una diferente.\n");
        }
    } while (exist_plate(v.plate));
    
    printf("Color: ");
    scanf("%s", v.color);
    printf ("Tipo (P/C): ");
    scanf(" %c", &v.type);
    printf("Precio: ");
    scanf("%f", &v.price);
    v.state = 'A';

    fwrite(&v, sizeof(Vehicle), 1, file);
    fclose(file);
    printf("\nVehiculo agregado con exito.\n");
}

//Brand-model Search Function
void brand_model_search() {
    FILE *file;
    Vehicle v;
    char searched_brand[50], searched_model[50];
    int found = 0;

    file= fopen("vehicle.dat", "rb");
    if (file== NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehiculo por marca y modelo ---\n");
    printf("Ingrese la marca a buscar: ");
    scanf("%s", searched_brand);
    printf("Ingrese el modelo a buscar: ");
    scanf("%s", searched_model);

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (v.state == 'A' && strcmp(v.brand, searched_brand) == 0 && strcmp(v.model, searched_model) == 0) {
            printf("\nVehiculo encontrado:\n");
            printf("----------------------------\n");
            printf("Marca: %s\n", v.brand);
            printf("Modelo: %s\n", v.model);
            printf("Año: %d\n", v.year);
            printf("Precio: %.2f\n", v.price);
            printf("Placa: %s\n", v.plate);
            printf("Tipo: %c\n", v.type);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos con la marca y modelo especificados.\n");
    }

    fclose(file);
}

//Price Search Function
void price_search() {
    FILE *file;
    Vehicle v;
    float min_price, max_price;
    int found = 0;

    file = fopen("vehicle.dat", "rb");
    if (file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehículo por rango de precio ---\n");
    printf("Ingrese el precio minimo: ");
    scanf("%f", &min_price);
    printf("Ingrese el precio maximo: ");
    scanf("%f", &max_price);

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (v.state == 'A' && v.price >= min_price && v.price <= max_price) {
            printf("\nVehiculo encontrado:\n");
            printf("----------------------------\n");
            printf("Marca: %s\n", v.brand);
            printf("Modelo: %s\n", v.model);
            printf("Año: %d\n", v.year);
            printf("Precio: %.2f\n", v.price);
            printf("Placa: %s\n", v.plate);
            printf("Tipo: %c\n", v.type); 
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos en ese rango de precio.\n");
    }

    fclose(file);
}

//Type Search Function
void type_search() {
    FILE *file;
    Vehicle v;
    char searched_type;
    int found = 0;

    file = fopen("vehicle.dat", "rb");
    if (file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehiculo por tipo ---\n");
    printf("Ingrese el tipo a buscar ('P' para Propio, 'C' para Consignado): ");
    scanf(" %c", &searched_type);

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (v.state == 'A' && v.type == searched_type) {
            printf("\nVehiculo encontrado:\n");
            printf("----------------------------\n");
            printf("Marca: %s\n", v.brand);
            printf("Modelo: %s\n", v.model);
            printf("Año: %d\n", v.year);
            printf("Precio: %.2f\n", v.price);
            printf("Placa: %s\n", v.plate);
            printf("Tipo: %c\n", v.type); 
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos del tipo especificado.\n");
    }

    fclose(file);
}

//Modify Vehicle Function
void modify_vehicle() {
    FILE *read_file, *write_file;
    Vehicle v;
    char searched_plate[10];
    int found = 0;
    int modify_option;

    read_file = fopen("vehicle.dat", "rb");
    if (read_file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Modificar vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo a modificar: ");
    scanf("%s", searched_plate);

    write_file = fopen("temp.dat", "wb");
    
    while (fread(&v, sizeof(Vehicle), 1, read_file) == 1) {
        if (strcmp(v.plate, searched_plate) == 0) {
            found = 1;
            printf("\nVehiculo encontrado:\n");
            printf("Marca: %s, Modelo: %s, Placa: %s\n", v.brand, v.model, v.plate);

            printf("\nQue desea modificar?\n");
            printf("1. Precio\n");
            printf("2. Tipo\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &modify_option);

            switch(modify_option) {
                case 1:
                    printf("Ingrese el nuevo precio: ");
                    scanf("%f", &v.price);
                    printf("Precio actualizado con exito.\n");
                    break;
                case 2:
                    printf("Ingrese el nuevo tipo (P/C): ");
                    scanf(" %c", &v.type);
                    printf("Tipo actualizado con exito.\n");
                    break;
                default:
                    printf("Opcion no valida. No se realizaron cambios.\n");
            }
        }
        fwrite(&v, sizeof(Vehicle), 1, write_file);
    }

    fclose(read_file);
    fclose(write_file);

    if (found) {
        remove("vehicle.dat");
        rename("temp.dat", "vehicle.dat");
        printf("\nModificacion guardada correctamente.\n");
    } else {
        remove("temp.dat");
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }
}

//Switch State Function
void switch_state() {
    FILE *read_file, *write_file;
    Vehicle v;
    char searched_plate[10];
    int found = 0;

    read_file = fopen("vehicle.dat", "rb");
    if (read_file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Cambiar estado de vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo: ");
    scanf("%s", searched_plate);

    write_file = fopen("temp.dat", "wb");

    while (fread(&v, sizeof(Vehicle), 1, read_file) == 1) {
        if (strcmp(v.plate, searched_plate) == 0) {
            found = 1;
            printf("\nVehiculo encontrado: Marca: %s, Placa: %s, Estado actual: %c\n", v.brand, v.plate, v.state);
            if (v.state == 'A') {
                printf("Cambiando estado a 'Eliminado' (E).\n");
                v.state = 'E';
            } else {
                printf("Cambiando estado a 'Activo' (A).\n");
                v.state = 'A';
            }
        }
        fwrite(&v, sizeof(Vehicle), 1, write_file);
    }

    fclose(read_file);
    fclose(write_file);

    if (found) {
        remove("vehicle.dat");
        rename("temp.dat", "vehicle.dat");
        printf("\nEstado del vehiculo actualizado con exito.\n");
    } else {
        remove("temp.dat");
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }
}

//Main Function
int main(){
    int option;

    do{
        printf("\n\n--- Gestion de Vehiculos ---\n");
        printf("1. Agregar nuevo vehiculo\n");
        printf("2. Buscar vehiculo por marca y modelo\n");
        printf("3. Buscar vehiculo por rango de precio\n");
        printf("4. Buscar vehiculo por tipo\n");
        printf("5. Modificar un vehiculo\n");
        printf("6. Cambiar estado de un vehiculo\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);

        switch (option){
        case 1:
            add_vehicle();
            break;
        case 2:
            brand_model_search();
            break;
        case 3:
            price_search();
            break;
        case 4:
            type_search();
            break;
        case 5:
            modify_vehicle();
            break;
        case 6:
            switch_state();
            break;
        case 7:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nOpcion no valida. Intente nuevamente.\n");
        }
    } while (option != 7);
    return 0;
}