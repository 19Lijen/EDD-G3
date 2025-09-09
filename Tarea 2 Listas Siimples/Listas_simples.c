#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A struct representing a descriptive trait.
typedef struct TraitNode {
    char id[15];
    char description[50];
    struct TraitNode *next;
} TraitNode;

// A struct representing a person, which is a node in the main linked list.
typedef struct Node {
    int id;
    char name[30];
    TraitNode *traits; // A nested linked list for traits.
    struct Node *next;
} Node;

// Function prototypes
void menu(Node** head);
void addPerson(Node** head, int pos, int search_id, int new_id, char* name, int option_type);
Node* insertAtPosition(Node* head, int pos, Node* newNode);
Node* insertAfterID(Node* head, int search_id, Node* newNode);
Node* insertAtEnd(Node* head, Node* newNode);
Node* deleteAtPosition(Node* head, int pos);
Node* deleteAfterID(Node* head, int search_id);
void printList(Node* head);
int countNodes(Node* head);
void addTraitsToPerson(Node* head, int person_id);
void printTraits(TraitNode* traits_head);
TraitNode* createTrait();
void swapNodeContent(Node* head, int id1, int id2);
void swapNodes(Node** head, int id1, int id2);
Node* findNodeByID(Node* head, int id);
void freeList(Node** head);
void freeTraits(TraitNode* head);


int main() {
    Node* head = NULL;
    menu(&head);
    freeList(&head);
    return 0;
}

// Main menu loop.
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

// Function to handle person creation and insertion logic.
void addPerson(Node** head, int pos, int search_id, int new_id, char* name, int option_type) {
    // Allocate a new node once.
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

    // Call the correct insertion function with the pre-created node.
    switch(option_type) {
        case 1:
            *head = insertAtPosition(*head, pos, newNode);
            break;
        case 2:
            *head = insertAfterID(*head, search_id, newNode);
            break;
        case 3:
            *head = insertAtEnd(*head, newNode);
            break;
        default:
            printf("Tipo de opcion invalido. Nodo no insertado.\n");
            freeTraits(newNode->traits);
            free(newNode);
            break;
    }
}

// Creates a new trait node based on user input.
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

// Adds traits to an existing person node.
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

// Prints the traits of a person.
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

// Prints the entire list, including traits for each person.
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

// Swaps the content (id, name, traits pointer) of two nodes.
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

// Correctly swaps two nodes by manipulating pointers.
void swapNodes(Node** head, int id1, int id2) {
    if (id1 == id2) {
        printf("Los IDs son iguales. No se puede intercambiar el mismo nodo.\n");
        return;
    }

    Node *prev1 = NULL, *curr1 = *head;
    while (curr1 && curr1->id != id1) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    Node *prev2 = NULL, *curr2 = *head;
    while (curr2 && curr2->id != id2) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (!curr1 || !curr2) {
        printf("Uno o ambos nodos no se encontraron.\n");
        return;
    }

    // If node1 is not the head of the list, update the next pointer of its previous node.
    if (prev1) {
        prev1->next = curr2;
    } else { // node1 is the head.
        *head = curr2;
    }

    // If node2 is not the head of the list, update the next pointer of its previous node.
    if (prev2) {
        prev2->next = curr1;
    } else { // node2 is the head.
        *head = curr1;
    }

    // Swap the next pointers of the two nodes.
    Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    printf("Nodos con IDs %d y %d intercambiados.\n", id1, id2);
}

// Finds and returns a node by its ID.
Node* findNodeByID(Node* head, int id) {
    Node* current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    return current;
}

// Inserts a pre-created node at a specific position.
Node* insertAtPosition(Node* head, int pos, Node* newNode) {
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
        printf("Posicion fuera de rango. Nodo no insertado.\n");
        freeTraits(newNode->traits);
        free(newNode);
        return head;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Inserts a pre-created node after a node with a specific ID.
Node* insertAfterID(Node* head, int search_id, Node* newNode) {
    Node* current = findNodeByID(head, search_id);

    if (current == NULL) {
        printf("ID no encontrado.\n");
        freeTraits(newNode->traits);
        free(newNode);
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Deletes a node at a specific position.
Node* deleteAtPosition(Node* head, int pos) {
    if (head == NULL) {
        printf("La lista ya esta vacia.\n");
        return head;
    }
    
    Node* temp = head;
    if (pos == 0) {
        head = head->next;
        freeTraits(temp->traits);
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
    freeTraits(temp->traits);
    free(temp);
    printf("Nodo eliminado de la posicion %d.\n", pos);
    return head;
}

// Deletes a node after a node with a specific ID.
Node* deleteAfterID(Node* head, int search_id) {
    Node* current = findNodeByID(head, search_id);

    if (current == NULL || current->next == NULL) {
        printf("ID no encontrado o no hay nodo para eliminar despues.\n");
        return head;
    }

    Node* toDelete = current->next;
    current->next = toDelete->next;
    freeTraits(toDelete->traits);
    free(toDelete);
    printf("Nodo despues de ID %d eliminado.\n", search_id);
    return head;
}

// Inserts a pre-created node at the end of the list.
Node* insertAtEnd(Node* head, Node* newNode) {
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

// Counts the number of nodes in the list.
int countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Helper function to free a trait list.
void freeTraits(TraitNode* head) {
    while(head) {
        TraitNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// Helper function to free the main person list.
void freeList(Node** head) {
    while (*head) {
        Node* temp = *head;
        *head = (*head)->next;
        freeTraits(temp->traits);
        free(temp);
    }
}