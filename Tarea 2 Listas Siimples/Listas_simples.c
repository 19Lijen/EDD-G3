#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct TraitNode {
    char id[15];
    char description[50];
    struct TraitNode *next;
} TraitNode;

typedef struct Node {
    int id;
    char name[30];
    TraitNode *traits;
    struct Node *next;
} Node;


void menu(Node** head);
Node* insertAtPosition(Node* head, int pos, int id, char* name);
Node* insertAfterID(Node* head, int search_id, int id, char* name);
Node* deleteAtPosition(Node* head, int pos);
Node* deleteAfterID(Node* head, int search_id);
Node* insertAtEnd(Node* head, int id, char* name);
void printList(Node* head);
int countNodes(Node* head);
void addTraitsToPerson(Node* head, int person_id);
void printTraits(TraitNode* traits_head);
TraitNode* createTrait();
void swapNodeContent(Node* head, int id1, int id2);
void swapNodes(Node** head, int id1, int id2);
void addPerson(Node** head, int pos, int search_id, int new_id, char* name, int option_type);
Node* findNodeByID(Node* head, int id);
Node* findNodeBeforeByID(Node* head, int id);

int main() {
    Node* head = NULL;
    menu(&head);
    while (head) {
        Node* temp = head;
        head = head->next;
        TraitNode* current_trait = temp->traits;
        while(current_trait) {
            TraitNode* temp_trait = current_trait;
            current_trait = current_trait->next;
            free(temp_trait);
        }
        free(temp);
    }
    return 0;
}

void menu(Node** head) {
    int option, pos, id, search_id;
    char name[30];

    do {
        printf("\n----- MENU -----\n");
        printf("1. Insertar nodo en posicion\n");
        printf("2. Insertar nodo despues de un id\n");
        printf("3. Eliminar nodo en posicion\n");
        printf("4. Eliminar nodo despues de un id\n");
        printf("5. Insertar nodo al final\n");
        printf("6. Mostrar lista\n");
        printf("7. Intercambiar contenido de dos nodos (por ID)\n");
        printf("8. Intercambiar dos nodos de la lista (por ID)\n");
        printf("9. Agregar rasgos descriptivos a una persona\n");
        printf("10. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Posicion (empezando en 0): ");
                scanf("%d", &pos);
                printf("ID: ");
                scanf("%d", &id);
                printf("Nombre: ");
                scanf("%29s", name);
                addPerson(head, pos, 0, id, name, 1);
                break;
            case 2:
                printf("Insertar despues de que ID: ");
                scanf("%d", &search_id);
                printf("ID nuevo nodo: ");
                scanf("%d", &id);
                printf("Nombre: ");
                scanf("%29s", name);
                addPerson(head, 0, search_id, id, name, 2);
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
                scanf("%29s", name);
                addPerson(head, 0, 0, id, name, 3);
                break;
            case 6:
                printList(*head);
                printf("Total nodos: %d\n", countNodes(*head));
                break;
            case 7: {
                int id1, id2;
                printf("ID del primer nodo: ");
                scanf("%d", &id1);
                printf("ID del segundo nodo: ");
                scanf("%d", &id2);
                swapNodeContent(*head, id1, id2);
                break;
            }
            case 8: {
                int id1, id2;
                printf("ID del primer nodo a intercambiar: ");
                scanf("%d", &id1);
                printf("ID del segundo nodo a intercambiar: ");
                scanf("%d", &id2);
                swapNodes(head, id1, id2);
                break;
            }
            case 9:
                printf("ID de la persona para agregar rasgos: ");
                scanf("%d", &id);
                addTraitsToPerson(*head, id);
                break;
            case 10:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (option != 10);
}

void addPerson(Node** head, int pos, int search_id, int new_id, char* name, int option_type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    newNode->id = new_id;
    strncpy(newNode->name, name, 29);
    newNode->name[29] = '\0';
    newNode->traits = NULL; 
    
    char response;
    printf("¿Desea agregar rasgos descriptivos a esta persona? (s/n): ");
    scanf(" %c", &response);
    if (response == 's' || response == 'S') {
        printf("--- Agregando rasgos para %s ---\n", name);
        char trait_response;
        do {
            TraitNode* newTrait = createTrait();
            if (newTrait) {
                if (newNode->traits == NULL) {
                    newNode->traits = newTrait;
                } else {
                    TraitNode* currentTrait = newNode->traits;
                    while (currentTrait->next != NULL) {
                        currentTrait = currentTrait->next;
                    }
                    currentTrait->next = newTrait;
                }
            }
            printf("¿Desea agregar otro rasgo? (s/n): ");
            scanf(" %c", &trait_response);
        } while (trait_response == 's' || trait_response == 'S');
    }

    if (option_type == 1) {
        *head = insertAtPosition(*head, pos, new_id, name);
    } else if (option_type == 2) {
        *head = insertAfterID(*head, search_id, new_id, name);
    } else if (option_type == 3) {
        *head = insertAtEnd(*head, new_id, name);
    }
}

TraitNode* createTrait() {
    TraitNode* newTrait = (TraitNode*)malloc(sizeof(TraitNode));
    if (!newTrait) {
        printf("Error: No se pudo asignar memoria para el rasgo.\n");
        return NULL;
    }
    printf("ID del rasgo (ej. 'Estatura'): ");
    scanf("%14s", newTrait->id);
    printf("Descripcion (ej. '175cms'): ");
    scanf("%49s", newTrait->description);
    newTrait->next = NULL;
    return newTrait;
}

void addTraitsToPerson(Node* head, int person_id) {
    Node* person = findNodeByID(head, person_id);
    if (!person) {
        printf("Persona con ID %d no encontrada.\n", person_id);
        return;
    }
    printf("--- Agregando rasgos para %s ---\n", person->name);
    char response;
    do {
        TraitNode* newTrait = createTrait();
        if (newTrait) {
            if (person->traits == NULL) {
                person->traits = newTrait;
            } else {
                TraitNode* current = person->traits;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newTrait;
            }
        }
        printf("¿Desea agregar otro rasgo? (s/n): ");
        scanf(" %c", &response);
    } while (response == 's' || response == 'S');
}

void printTraits(TraitNode* traits_head) {
    if (traits_head == NULL) {
        printf("    No tiene rasgos descriptivos.\n");
        return;
    }
    printf("    --- Rasgos ---\n");
    TraitNode* current = traits_head;
    while (current != NULL) {
        printf("    ID del rasgo: %s, Descripcion: %s\n", current->id, current->description);
        current = current->next;
    }
}

void printList(Node* head) {
    if (head == NULL) {
        printf("Lista vacia.\n");
        return;
    }
    printf("--- Contenido de la Lista ---\n");
    Node* current = head;
    while (current != NULL) {
        printf("ID: %d, Nombre: %s\n", current->id, current->name);
        printTraits(current->traits);
        current = current->next;
    }
    printf("---------------------------\n");
}

void swapNodeContent(Node* head, int id1, int id2) {
    if (id1 == id2) {
        printf("Los IDs son iguales. No se puede intercambiar el mismo nodo.\n");
        return;
    }

    Node* node1 = findNodeByID(head, id1);
    Node* node2 = findNodeByID(head, id2);

    if (!node1 || !node2) {
        printf("Uno o ambos nodos no se encontraron.\n");
        return;
    }

    int temp_id = node1->id;
    char temp_name[30];
    strncpy(temp_name, node1->name, 29);
    temp_name[29] = '\0';
    TraitNode* temp_traits = node1->traits;

    node1->id = node2->id;
    strncpy(node1->name, node2->name, 29);
    node1->name[29] = '\0';
    node1->traits = node2->traits;

    node2->id = temp_id;
    strncpy(node2->name, temp_name, 29);
    node2->name[29] = '\0';
    node2->traits = temp_traits;

    printf("Contenido de nodos con IDs %d y %d intercambiado.\n", id1, id2);
}

void swapNodes(Node** head, int id1, int id2) {
    if (id1 == id2) {
        printf("Los IDs son iguales. No se puede intercambiar el mismo nodo.\n");
        return;
    }
    
    Node* node1 = *head;
    Node* prev1 = NULL;
    while (node1 && node1->id != id1) {
        prev1 = node1;
        node1 = node1->next;
    }
    
    Node* node2 = *head;
    Node* prev2 = NULL;
    while (node2 && node2->id != id2) {
        prev2 = node2;
        node2 = node2->next;
    }
    
    if (!node1 || !node2) {
        printf("Uno o ambos nodos no se encontraron.\n");
        return;
    }
    
    if (prev1) {
        prev1->next = node2;
    } else {
        *head = node2;
    }
    
    if (prev2) {
        prev2->next = node1;
    } else {
        *head = node1;
    }
    
    Node* temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;

    printf("Nodos con IDs %d y %d intercambiados.\n", id1, id2);
}

Node* findNodeByID(Node* head, int id) {
    Node* current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    return current;
}

Node* insertAtPosition(Node* head, int pos, int id, char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->id = id;
    strncpy(newNode->name, name, 29);
    newNode->name[29] = '\0';
    newNode->traits = NULL;

    if (pos == 0) {
        newNode->next = head;
        return newNode;
    }
    
    Node* current = head;
    int i = 0;
    while (i < pos - 1 && current != NULL) {
        current = current->next;
        i++;
    }
    
    if (current == NULL) {
        printf("Posicion fuera de rango. El nodo se insertara al final.\n");
        current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

Node* insertAfterID(Node* head, int search_id, int id, char* name) {
    Node* current = findNodeByID(head, search_id);

    if (current == NULL) {
        printf("ID no encontrado.\n");
        return head;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->id = id;
    strncpy(newNode->name, name, 29);
    newNode->name[29] = '\0';
    newNode->traits = NULL;
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

Node* deleteAtPosition(Node* head, int pos) {
    if (head == NULL) {
        printf("La lista ya esta vacia.\n");
        return head;
    }
    
    Node* temp = head;
    if (pos == 0) {
        head = head->next;
        TraitNode* current_trait = temp->traits;
        while(current_trait) {
            TraitNode* temp_trait = current_trait;
            current_trait = current_trait->next;
            free(temp_trait);
        }
        free(temp);
        printf("Nodo eliminado de la posicion 0.\n");
        return head;
    }

    int i = 0;
    Node* prev = NULL;
    while (i < pos && temp != NULL) {
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Posicion invalida o fuera de rango.\n");
        return head;
    }

    prev->next = temp->next;
    TraitNode* current_trait = temp->traits;
    while(current_trait) {
        TraitNode* temp_trait = current_trait;
        current_trait = current_trait->next;
        free(temp_trait);
    }
    free(temp);
    printf("Nodo eliminado de la posicion %d.\n", pos);
    return head;
}

Node* deleteAfterID(Node* head, int search_id) {
    Node* current = findNodeByID(head, search_id);

    if (current == NULL || current->next == NULL) {
        printf("ID no encontrado o no hay nodo para eliminar despues.\n");
        return head;
    }

    Node* toDelete = current->next;
    current->next = toDelete->next;
    TraitNode* current_trait = toDelete->traits;
    while(current_trait) {
        TraitNode* temp_trait = current_trait;
        current_trait = current_trait->next;
        free(temp_trait);
    }
    free(toDelete);
    printf("Nodo despues de ID %d eliminado.\n", search_id);
    return head;
}

Node* insertAtEnd(Node* head, int id, char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->id = id;
    strncpy(newNode->name, name, 29);
    newNode->name[29] = '\0';
    newNode->traits = NULL;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;
}

int countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}