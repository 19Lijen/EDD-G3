#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Node definition
typedef struct Node {
    int id;
    char name[50];
    struct Node* next;
} Node;

// Function prototypes
void menu(Node** head);
Node* insertAtPosition(Node* head, int pos, int id, char* name);
Node* insertAfterID(Node* head, int search_id, int id, char* name);
Node* deleteAtPosition(Node* head, int pos);
Node* deleteAfterID(Node* head, int search_id);
Node* insertAtEnd(Node* head, int id, char* name);
void printList(Node* head);
int countNodes(Node* head);

int main() {
    Node* head = NULL;
    menu(&head);
    // Free memory before exiting
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

void menu(Node** head) {
    int option, id, pos, search_id;
    char name[50];
    do {
        printf("\n----- MENU -----\n");
        printf("1. Insertar nodo en posicion\n");
        printf("2. Insertar nodo despues de un id\n");
        printf("3. Eliminar nodo en posicion\n");
        printf("4. Eliminar nodo despues de un id\n");
        printf("5. Insertar nodo al final\n");
        printf("6. Mostrar lista\n");
        printf("7. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Posicion (empezando en 0): ");
                scanf("%d", &pos);
                printf("ID: ");
                scanf("%d", &id);
                printf("Nombre: ");
                scanf("%49s", name);
                *head = insertAtPosition(*head, pos, id, name);
                break;
            case 2:
                printf("Insertar despues de que ID: ");
                scanf("%d", &search_id);
                printf("ID nuevo nodo: ");
                scanf("%d", &id);
                printf("Nombre: ");
                scanf("%49s", name);
                *head = insertAfterID(*head, search_id, id, name);
                break;
            case 3:
                printf("Posicion a eliminar (empezando en 0): ");
                scanf("%d", &pos);
                *head = deleteAtPosition(*head, pos);
                break;
            case 4:
                printf("Eliminar despues de que ID: ");
                scanf("%d", &search_id);
                *head = deleteAfterID(*head, search_id);
                break;
            case 5:
                printf("ID nuevo nodo: ");
                scanf("%d", &id);
                printf("Nombre: ");
                scanf("%49s", name);
                *head = insertAtEnd(*head, id, name);
                break;
            case 6:
                printList(*head);
                printf("Total nodos: %d\n", countNodes(*head));
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (option != 7);
}

// Function to count elements
int countNodes(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Insert node at a specified position
Node* insertAtPosition(Node* head, int pos, int id, char* name) {
    int i = 0;
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: No se pudo asignar memoria.\n");
        return head;
    }
    newNode->id = id;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';

    if (pos == 0 || !head) {
        newNode->next = head;
        return newNode;
    }
    Node* current = head;
    while (i < pos - 1 && current->next) {
        current = current->next;
        i++;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Insert a node after a specific ID
Node* insertAfterID(Node* head, int search_id, int id, char* name) {
    Node* current = head;
    while (current && current->id != search_id) {
        current = current->next;
    }
    if (!current) {
        printf("ID no encontrado.\n");
        return head;
    }
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: No se pudo asignar memoria.\n");
        return head;
    }
    newNode->id = id;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Delete a node at a specified position
Node* deleteAtPosition(Node* head, int pos) {
    if (!head) {
        printf("La lista ya esta vacia.\n");
        return head;
    }
    Node *temp;
    if (pos == 0) {
        temp = head;
        head = head->next;
        free(temp);
        printf("Nodo eliminado de la posicion 0.\n");
        return head;
    }
    Node* current = head;
    int i = 0;
    while (i < pos - 1 && current->next) {
        current = current->next;
        i++;
    }
    if (!current->next) {
        printf("Posicion invalida o fuera de rango.\n");
        return head;
    }
    temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("Nodo eliminado de la posicion %d.\n", pos);
    return head;
}

// Delete a node after a specific ID
Node* deleteAfterID(Node* head, int search_id) {
    Node* current = head;
    while (current && current->id != search_id) {
        current = current->next;
    }
    if (!current || !current->next) {
        printf("ID no encontrado o no hay nodo para eliminar despues.\n");
        return head;
    }
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("Nodo despues de ID %d eliminado.\n", search_id);
    return head;
}

// Insert a node at the end
Node* insertAtEnd(Node* head, int id, char* name) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: No se pudo asignar memoria.\n");
        return head;
    }
    newNode->id = id;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->next = NULL;
    if (!head) {
        return newNode;
    }
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Print the list
void printList(Node* head) {
    if (!head) {
        printf("Lista vacia\n");
        return;
    }
    printf("--- Contenido de la Lista ---\n");
    while (head) {
        printf("ID: %d, Nombre: %s\n", head->id, head->name);
        head = head->next;
    }
    printf("---------------------------\n");
}