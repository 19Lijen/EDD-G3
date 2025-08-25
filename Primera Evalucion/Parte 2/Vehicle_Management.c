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
    char type;
    float price;
    char state;
} Vehicle;


// Limpia el buffer de entrada para evitar errores con scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Imprime los detalles de un vehículo
void print_vehicle_details(Vehicle *v) {
    printf("----------------------------\n");
    printf("Marca: %s\n", v->brand);
    printf("Modelo: %s\n", v->model);
    printf("Año: %d\n", v->year);
    printf("Color: %s\n", v->color);
    printf("Placa: %s\n", v->plate);
    printf("Tipo: %c\n", v->type);
    printf("Precio: %.2f\n", v->price);
    printf("Estado: %c\n", v->state);
    printf("----------------------------\n");
}

// Exist Plate
int exist_plate(Vehicle *v, int count, char *plate) {

    for (int i = 0; i < count; i++){
        if (strcmp((v + i)->plate, plate) == 0){
            return 1;
        }
    }
    return 0;
}

// New Vehicle Function
void add_vehicle(Vehicle *vehicles, int *count) {
    if (*count >= 50) {
        printf("Error: No se pieden agregar mas vehiculos, el inventario esta lleno.\n");
        return;
    }

    Vehicle *new_vehicle = vehicles + *count;
    char temp_plate[10];

    printf("\n--- Agregar nuevo vehiculo ---\n");
    printf("Marca: ");
    scanf("%s", new_vehicle->brand);
    clear_input_buffer(); 
    printf("Modelo: ");
    scanf("%s", new_vehicle->model);
    clear_input_buffer(); 
    printf("Año: ");
    scanf("%d", &new_vehicle->year);
    clear_input_buffer(); 

    do {
        printf("Placa: ");
        scanf("%s", temp_plate);
        clear_input_buffer();
        if (exist_plate(vehicles, *count, temp_plate)) {
            printf("Error: La placa ya existe. Por favor ingrese una diferente.\n");
        }
    } while (exist_plate(vehicles, *count, temp_plate));
    strcpy(new_vehicle->plate, temp_plate);

    printf("Color: ");
    scanf("%s", new_vehicle->color);
    clear_input_buffer(); 

    do {
        printf ("Tipo ('P' para Propio, 'C' para Consignado): ");
        scanf(" %c", &new_vehicle->type); 
        clear_input_buffer(); 
    } while (new_vehicle->type != 'P' && new_vehicle->type != 'C' && new_vehicle->type != 'p' && new_vehicle->type != 'c');

    if (new_vehicle->type == 'p') new_vehicle->type = 'P';
    if (new_vehicle->type == 'c') new_vehicle->type = 'C';

    printf("Precio: ");
    scanf("%f", &new_vehicle->price);
    clear_input_buffer();

    new_vehicle->state = 'A';

    (*count)++;
    printf("\nVehiculo agregado con exito.\n");
}

// Brand-model Search Function
void brand_model_search(Vehicle *vehicles, int count) {
    char searched_brand[50], searched_model[50];
    int found = 0;

    if (count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehiculo por marca y modelo ---\n");
    printf("Ingrese la marca a buscar: ");
    scanf("%s", searched_brand);
    clear_input_buffer();
    printf("Ingrese el modelo a buscar: ");
    scanf("%s", searched_model);
    clear_input_buffer();

    for (int i = 0; i < count; i++){
        Vehicle *current_vehicle = vehicles + i;

        if (current_vehicle->state == 'A' && strcmp(current_vehicle->brand, searched_brand) == 0 && strcmp(current_vehicle->model, searched_model) == 0) {
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(current_vehicle);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos con la marca y modelo especificados.\n");
    }
}

// Price Search Function
void price_search( Vehicle *vehicles, int count) {
    float min_price, max_price;
    int found = 0;

    if (count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehículo por rango de precio ---\n");
    printf("Ingrese el precio minimo: ");
    scanf("%f", &min_price);
    clear_input_buffer();
    printf("Ingrese el precio maximo: ");
    scanf("%f", &max_price);
    clear_input_buffer();

    for (int i = 0; i < count; i++) {
        Vehicle *current_vehicle = vehicles + i;

        if (current_vehicle->state == 'A' && current_vehicle->price >= min_price && current_vehicle->price <= max_price){
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(current_vehicle);
            found = 1;
        }
    }
    if (!found) {
        printf("\nNo se encontraron vehiculos en ese rango de precio.\n");
    }
}


void type_search(Vehicle *vehicles, int count) {
    char searched_type;
    int found = 0;

    if (count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Buscar vehiculo por tipo ---\n");
    printf("Ingrese el tipo a buscar ('P' para Propio, 'C' para Consignado): ");
    scanf(" %c", &searched_type);
    clear_input_buffer();

    for (int i = 0; i < count; i++){
        Vehicle *current_vehicle = vehicles + i;

        if (searched_type == 'p') searched_type = 'P';
        if (searched_type == 'c') searched_type = 'C';

        if (current_vehicle->state == 'A' && current_vehicle->type == searched_type){
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(current_vehicle);
            found = 1;
        }

    }
    if (!found) {
        printf("\nNo se encontraron vehiculos del tipo especificado.\n");
    }
}

// Modify Vehicle
void modify_vehicle(Vehicle *vehicles, int count) {

    char searched_plate[10];
    int found = 0;
    int modify_option;

    if (count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Modificar vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo a modificar: ");
    scanf("%9s", searched_plate);
    clear_input_buffer();

    for (int i = 0; i < count; i++){
        Vehicle *current_vehicle = vehicles + i;

        if (strcmp(current_vehicle->plate, searched_plate) ==0) {
            found = 1;
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(current_vehicle);

            printf("\nQue desea modificar?\n");
            printf("1. Precio\n");
            printf("2. Tipo\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &modify_option);
            clear_input_buffer();

            switch(modify_option) {
                case 1:
                    printf("Ingrese el nuevo precio: ");
                    scanf("%f", &current_vehicle->price);
                    clear_input_buffer();
                    break;
                case 2:
                    do {
                        printf("Ingrese el nuevo tipo ('P' para Propio, 'C' para Consignado): ");
                        scanf(" %c", &current_vehicle->type);
                        clear_input_buffer();
                    } while (current_vehicle->type != 'P' && current_vehicle->type != 'C' && current_vehicle->type != 'p' && current_vehicle->type != 'c');

                    if (current_vehicle->type == 'p') current_vehicle->type = 'P';
                    if (current_vehicle->type == 'c') current_vehicle->type = 'C';
                    break;
                default:
                    printf("Opcion no valida. No se realizaron cambios.\n");
                    return;
            }
            printf("\nModificacion guardada correctamente.\n");
            return;
        }
    }
    if (!found) {
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }
}

void switch_state(Vehicle *vehicles, int count) {
    char searched_plate[10];
    int found = 0;

    if (count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Cambiar estado de vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo: ");
    scanf("%9s", searched_plate);
    clear_input_buffer();

    for (int i = 0; i < count; i++){
        Vehicle *current_vehicle = vehicles + i;
        if (strcmp(current_vehicle->plate, searched_plate) == 0) {
            found = 1;

            printf("\nVehiculo encontrado: Marca: %s, Placa: %s, Estado actual: %c\n", current_vehicle->brand, current_vehicle->plate, current_vehicle->state);
            
            if (current_vehicle->state == 'A') {
                printf("Cambiando estado a 'Eliminado' (E).\n");
                current_vehicle->state = 'E';
            } else if (current_vehicle->state == 'E') {
                printf("Cambiando estado a 'Activo' (A).\n");
                current_vehicle->state = 'A';
            }
            
            printf("\nEstado del vehiculo actualizado con exito.\n");
            
            break; 
        }

    }
    if (!found) {
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }
}

void sort (Vehicle *vehicles, int *count) {
    if (*count <= 1)
    {
        printf("No hay suficinetes vehiculos para ordenar\n");
        return;
    }
    
    for (int i = 0; i < *count -1; i++)
    {
        for (int j = 0; j < *count -i -1; j++){
            if (strcmp((vehicles + j)->plate, (vehicles + j + 1)->plate) < 0) {
                Vehicle temp = *(vehicles + j);
                *(vehicles + j) = *(vehicles +j +1);
                *(vehicles + j +1) = temp;
            }
        }
    }
    printf("vehiculos ordenados por placa de mayor a menor\n");
}

void print_all_vehicles (Vehicle *vehicles, int count){
    if (count == 0){
        printf("El inventario esta vacio, no hay vehiculos para mostrar");
        return;
    }
    printf("\n---- Lista de vehiculos activos ------\n");
    int found_active = 0;
    for (int i = 0; i < count; i++) {
        Vehicle *current_vehicle = vehicles + i;
        if (current_vehicle->state == 'A') {
            print_vehicle_details(current_vehicle);
            found_active = 1;
        }
    }
    if (! found_active) {
        printf ("No hay vehiculos activos en el inventario");
    }
}
//Main Function
int main(){
    Vehicle *vehicles = (Vehicle *)malloc(50 * sizeof(Vehicle));
    int vehicle_count = 0;
    int option;

    if(vehicles == NULL) {
        printf("Error: No se pudo asignar memoria. \n");
        return 1;
    }

    do{
        printf("\n\n--- Gestion de Vehiculos ---\n");
        printf("1. Agregar nuevo vehiculo\n");
        printf("2. Buscar vehiculo por marca y modelo\n");
        printf("3. Buscar vehiculo por rango de precio\n");
        printf("4. Buscar vehiculo por tipo\n");
        printf("5. Modificar un vehiculo\n");
        printf("6. Cambiar estado de un vehiculo\n");
        printf("7. Ordenar por placa\n");
        printf("8. Mostrar vehiculos activos\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &option) != 1) {
            printf("\nEntrada invalida. Por favor, ingrese un numero.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (option){
        case 1:
            add_vehicle(vehicles, &vehicle_count);
            break;
        case 2:
            brand_model_search(vehicles, vehicle_count);
            break;
        case 3:
            price_search(vehicles, vehicle_count);
            break;
        case 4:
            type_search(vehicles, vehicle_count);
            break;
        case 5:
            modify_vehicle(vehicles, vehicle_count);
            break;
        case 6:
            switch_state(vehicles, vehicle_count);
            break;
        case 7:
            sort(vehicles, &vehicle_count);
            break;
        case 8:
            print_all_vehicles(vehicles, vehicle_count);
            break;
        case 9:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nOpcion no valida. Intente nuevamente.\n");
        }
    } while (option != 9);

    free(vehicles);

    return 0;
}