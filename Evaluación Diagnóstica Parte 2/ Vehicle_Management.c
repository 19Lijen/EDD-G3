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
void print_vehicle_details(Vehicle v) {
    printf("----------------------------\n");
    printf("Marca: %s\n", v.brand);
    printf("Modelo: %s\n", v.model);
    printf("Año: %d\n", v.year);
    printf("Color: %s\n", v.color);
    printf("Placa: %s\n", v.plate);
    printf("Tipo: %c\n", v.type);
    printf("Precio: %.2f\n", v.price);
    printf("Estado: %c\n", v.state);
    printf("----------------------------\n");
}

// Exist Plate
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

// New Vehicle Function
void add_vehicle() {
    FILE *file;
    Vehicle v;

    file = fopen("vehicle.dat", "ab");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("\n--- Agregar nuevo vehiculo ---\n");
    printf("Marca: ");
    scanf("%s", v.brand);
    clear_input_buffer(); 
    printf("Modelo: ");
    scanf("%s", v.model);
    clear_input_buffer(); 
    printf("Año: ");
    scanf("%d", &v.year);
    clear_input_buffer(); 

    do {
        printf("Placa: ");
        scanf("%s", v.plate);
        clear_input_buffer();
        if (exist_plate(v.plate)) {
            printf("Error: La placa ya existe. Por favor ingrese una diferente.\n");
        }
    } while (exist_plate(v.plate));
    
    printf("Color: ");
    scanf("%s", v.color);
    clear_input_buffer(); 
    
    do {
        printf ("Tipo ('P' para Propio, 'C' para Consignado): ");
        scanf(" %c", &v.type); 
        clear_input_buffer(); 
    } while (v.type != 'P' && v.type != 'C' && v.type != 'p' && v.type != 'c');
    
    if (v.type == 'p') v.type = 'P';
    if (v.type == 'c') v.type = 'C';

    printf("Precio: ");
    scanf("%f", &v.price);
    clear_input_buffer();
    
    v.state = 'A';

    fwrite(&v, sizeof(Vehicle), 1, file);
    fclose(file);
    printf("\nVehiculo agregado con exito.\n");
}

// Brand-model Search Function
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
    clear_input_buffer();
    printf("Ingrese el modelo a buscar: ");
    scanf("%s", searched_model);
    clear_input_buffer();

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (v.state == 'A' && strcmp(v.brand, searched_brand) == 0 && strcmp(v.model, searched_model) == 0) {
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(v);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos con la marca y modelo especificados.\n");
    }

    fclose(file);
}

// Price Search Function
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
    clear_input_buffer();
    printf("Ingrese el precio maximo: ");
    scanf("%f", &max_price);
    clear_input_buffer();

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (v.state == 'A' && v.price >= min_price && v.price <= max_price) {
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(v);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos en ese rango de precio.\n");
    }

    fclose(file);
}


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
    clear_input_buffer();

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {

        if (searched_type == 'p') searched_type = 'P';
        if (searched_type == 'c') searched_type = 'C';
        
        if (v.state == 'A' && v.type == searched_type) {
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(v);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo se encontraron vehiculos del tipo especificado.\n");
    }

    fclose(file);
}

// Modify Vehicle
void modify_vehicle() {
    FILE *file;
    Vehicle v;
    char searched_plate[10];
    int found = 0;
    int modify_option;
    
    file = fopen("vehicle.dat", "r+b");
    if (file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Modificar vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo a modificar: ");
    scanf("%9s", searched_plate);
    clear_input_buffer();

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (strcmp(v.plate, searched_plate) == 0) {
            found = 1;

            fseek(file, -sizeof(Vehicle), SEEK_CUR);
            
            printf("\nVehiculo encontrado:\n");
            print_vehicle_details(v);

            printf("\nQue desea modificar?\n");
            printf("1. Precio\n");
            printf("2. Tipo\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &modify_option);
            clear_input_buffer();

            switch(modify_option) {
                case 1:
                    printf("Ingrese el nuevo precio: ");
                    scanf("%f", &v.price);
                    clear_input_buffer();
                    break;
                case 2:
                    do {
                        printf("Ingrese el nuevo tipo ('P' para Propio, 'C' para Consignado): ");
                        scanf(" %c", &v.type);
                        clear_input_buffer();
                    } while (v.type != 'P' && v.type != 'C' && v.type != 'p' && v.type != 'c');

                    if (v.type == 'p') v.type = 'P';
                    if (v.type == 'c') v.type = 'C';
                    break;
                default:
                    printf("Opcion no valida. No se realizaron cambios.\n");
                    fclose(file);
                    return;
            }

            fwrite(&v, sizeof(Vehicle), 1, file);
            printf("\nModificacion guardada correctamente.\n");
            
            break; 
        }
    }

    if (!found) {
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }

    fclose(file);
}

void switch_state() {
    FILE *file;
    Vehicle v;
    char searched_plate[10];
    int found = 0;
    
    file = fopen("vehicle.dat", "r+b");
    if (file == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- Cambiar estado de vehiculo por placa ---\n");
    printf("Ingrese la placa del vehiculo: ");
    scanf("%9s", searched_plate);
    clear_input_buffer();

    while (fread(&v, sizeof(Vehicle), 1, file) == 1) {
        if (strcmp(v.plate, searched_plate) == 0) {
            found = 1;
            
            fseek(file, -sizeof(Vehicle), SEEK_CUR);

            printf("\nVehiculo encontrado: Marca: %s, Placa: %s, Estado actual: %c\n", v.brand, v.plate, v.state);
            
            if (v.state == 'A') {
                printf("Cambiando estado a 'Eliminado' (E).\n");
                v.state = 'E';
            } else if (v.state == 'E') {
                printf("Cambiando estado a 'Activo' (A).\n");
                v.state = 'A';
            }

            fwrite(&v, sizeof(Vehicle), 1, file);
            
            printf("\nEstado del vehiculo actualizado con exito.\n");
            
            break; 
        }
    }

    if (!found) {
        printf("\nNo se encontro un vehiculo con esa placa. No se realizaron cambios.\n");
    }

    fclose(file);
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
        
        if (scanf("%d", &option) != 1) {
            printf("\nEntrada invalida. Por favor, ingrese un numero.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

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