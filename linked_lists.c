#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
    struct node *down;
};

typedef struct node node_t;

node_t *newNode(int data){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->down = NULL;
    
    return new_node;
}

node_t* appendBack(node_t *head, int data){
    node_t* new_node = newNode(data);

    if (head == NULL){
        return new_node;
    }

    node_t* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }

    cur->next = new_node;

    return head;
}

node_t* appendBack2(node_t *head, int data, node_t** last){
    node_t* new_node = newNode(data);

    if (head == NULL){
        *last = new_node;
        return new_node;
    }

    node_t* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    } 

    cur->next = new_node; 
    new_node->prev = cur; //!!!!!
    *last = new_node;
    return head;
}

void linkLists(node_t* first, node_t* second){
    node_t* cur1 = first;
    node_t* cur2 = second;

    while (cur1 != NULL && cur2 != NULL) {
        cur2->down = cur1;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
}

void printList(node_t *head){
    node_t* cur = head;
    while(cur != NULL){
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

void printExtraLinks(node_t* second){
    node_t* cur = second;
    while(cur != NULL){
        printf("(%d) -> (%d)\n", cur->data, cur->down ? cur->down->data : -1); //!!!!!!!
        cur = cur->next;
    }
}

void navigateList(node_t* firstList, node_t* secondList, node_t* S){
    node_t* cur = S;
    char command;

    printf("\nНавигация по спискам:\n");
    printf("Для второго списка (верхнего): A(4) - влево, S(2) - вниз\n");
    printf("Для первого списка (нижнего): D(6) - вправо\n");
    printf("Q - вернуться в начало (к S)\n");
    printf("E - выход\n");

    while (1) {
        printf("Текущий элемент: %d\n", cur->data);

        // Определяем, в каком списке находится текущий узел
        node_t* temp = secondList;
        int inSecondList = 0;
        while (temp != NULL) {
            if (temp == cur) {
                inSecondList = 1;
                break;
            }
            temp = temp->next;
        }

        scanf(" %c", &command);

        switch (command) {
            case 'E': case 'e': // Выход из навигации
                return;
            case 'Q': case 'q': // Вернуться к началу (S)
                cur = S;
                printf("Вернулись к началу (элемент %d)\n", cur->data);
                break;
            case 'A': case 'a': case '4': // Влево (только во втором списке)
                if (inSecondList && cur->prev != NULL) {
                    cur = cur->prev;
                } else {
                    printf("Нельзя двигаться влево (не во втором списке или начало списка).\n");
                }
                break;
            case 'S': case 's': case '2': // Вниз (из второго списка в первый через prev)
                if (inSecondList && cur->down != NULL) {
                    cur = cur->down; // Переход к связанному элементу в первом списке
                } else {
                    printf("Нельзя двигаться вниз (не во втором списке или нет связей).\n");
                }
                break;
            case 'D': case 'd': case '6': // Вправо (только в первом списке)
                if (!inSecondList && cur->next != NULL) {
                    cur = cur->next;
                } else {
                    printf("Нельзя двигаться вправо (не в первом списке или конец списка).\n");
                }
                break;
            case 'W': case 'w': case '8': // Вверх (недоступно)
                printf("Нельзя двигаться вверх (направление недоступно).\n");
                break;
            default:
                printf("Неверная команда.\n");
        }
    }
}

void freeList(node_t *head){
    node_t *cur = head;
    while (cur != NULL){
        node_t *temp = cur;
        cur = cur->next;
        free(temp);
    }
}

int main(){
    node_t* firstList = NULL;
    node_t* secondList = NULL;
    node_t* S = NULL;
    node_t* lastSecond = NULL;
    int N, K, value;

    printf("Введите элементы первого списка (завершение ввода - 0):\n");
    while(1){
        scanf("%d", &value);
        if (value == 0) break;
        firstList = appendBack(firstList, value);
    }

    printf("Введите элементы второго списка (завершение ввода - 0):\n");
    while(1){
        scanf("%d", &value);
        if (value == 0) break;
        secondList = appendBack2(secondList, value, &lastSecond);
    }

    S = lastSecond;

    linkLists(firstList, secondList);

    printf("Первый список: ");
    printList(firstList);

    printf("Второй список: ");
    printList(secondList);

    printf("Связи второго списка с первым:\n");
    printExtraLinks(secondList);

    navigateList(firstList, secondList, S);

    freeList(firstList);
    freeList(secondList);
}
