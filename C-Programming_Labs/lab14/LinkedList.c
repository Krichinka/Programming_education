#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct smartphone {
    char model[30];
    int memory_capacity;
    int battery_capacity;
    int price;
} smartphone;

smartphone** make_phones(const char brands[10][30], int N) {
    smartphone** phones = calloc(N, sizeof(smartphone*));
    for (int i = 0; i < N; i++) {
        smartphone* phone = calloc(1, sizeof(smartphone));
        phones[i] = phone;
    }
    
    for (int i = 0; i < N; i++) {
        strcpy(phones[i]->model, brands[rand() % 10]);
        phones[i]->memory_capacity = (int)pow(2, rand() % 4 + 7);
        phones[i]->battery_capacity = ((rand() % 35) * 100) + 4000;
        phones[i]->price = ((rand() % 24) * 50) + 399;
    }
    return phones;
}


void free_phones(smartphone** phones, int N) {
    for (int i = 0; i < N; i++) {
        free(phones[i]);
    }
    free(phones);
}

struct node {
    smartphone *data;
    struct node *next;
    struct node *extra;
};

typedef struct node node_t;

node_t* newNode(smartphone *data) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->extra = NULL;
    return new_node;
}

node_t* appendFront(node_t *head, smartphone *data) {
    node_t *new_node = newNode(data);
    new_node->next = head;
    return new_node;
}

node_t* createList(smartphone** phones, int N) {
    node_t *head = NULL;
    for (int i = N - 2; i >= 0; i--) {
        head = appendFront(head, phones[i]);
    }
    node_t *extra = newNode(phones[N-1]);
    node_t *cur = head;
    while (cur != NULL) {
        cur->extra = (node_t*)extra;
        cur = cur->next;
    }
    
    return head;
}

void printList(node_t *head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }
    
    int count = 1;
    node_t *cur = head;
    
    printf("\n========== СПИСОК ==========\n");
    printf("%-4s %-25s %12s %14s %12s\n", "№", "Model", "Memory (GB)", "Battery (mAh)", "Price ($)");
    printf("---------------------------------------------------------------------\n");
    printf("%-4d %-25s %12d %14d %12d\n",
               0,
               cur->extra->data->model,
               cur->extra->data->memory_capacity,
               cur->extra->data->battery_capacity,
               cur->extra->data->price);
    while (cur != NULL) {
        printf("%-4d %-25s %12d %14d %12d\n",
               count,
               cur->data->model,
               cur->data->memory_capacity,
               cur->data->battery_capacity,
               cur->data->price);
        cur = cur->next;
        count++;
    }
    printf("---------------------------------------------------------------------\n");
    printf("NULL\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    const char brands[10][30] = {
        "Apple iPhone 17",
        "Samsung Galaxy S26",
        "Xiaomi 15 Pro",
        "Google Pixel 8",
        "OnePlus 12",
        "Honor Magic 6",
        "Vivo X100 Pro",
        "Realme GT 5",
        "Sony Xperia 1",
        "Nothing Phone 2"
    };
    
    int N;
    
    if (argc > 1) {
        N = atoi(argv[1]);
    } else {
        printf("Введите N: ");
        scanf("%d", &N);
        getchar();
    }
    
    smartphone** phones = make_phones(brands, N);
    node_t *S = createList(phones, N);
    
    printList(S);
    
    node_t *cur = S;
    int num = 1;
    char c, m;
    
    while (1) {
        printf("\nТекущий элемент %d\n", num);
        printf("Модель: %s\n", cur->data->model);
        printf("Память: %d ГБ\n", cur->data->memory_capacity);
        printf("Батарея: %d мАч\n", cur->data->battery_capacity);
        printf("Цена: $%d\n", cur->data->price);
        
        printf("\nВведите команду (D - следующий, E - extra, Q - выход): ");
        c = getchar();
        getchar();
        
        if (c == 'q' || c == 'Q') {
            break;
        }
        else if (c == 'E' || c == 'e') {
            printf("\nТекущий элемент EXTRA\n");
            printf("Модель: %s\n", cur->extra->data->model);
            printf("Память: %d ГБ\n", cur->extra->data->memory_capacity);
            printf("Батарея: %d мАч\n", cur->extra->data->battery_capacity);
            printf("Цена: $%d\n", cur->extra->data->price);
        }
        else if (c == 'D' || c == 'd') {
            if (cur->next == NULL) {
                printf("\nВернуться в начало? (y/n): ");
                m = getchar();
                getchar();
                if (m == 'y' || m == 'Y') {
                    cur = S;
                    num = 1;
                } else {
                    break;
                }
            } else {
                cur = cur->next;
                num++;
            }
        }
    }
    node_t *extra_to_free = S->extra;
    free(extra_to_free);
    cur = S;
    while (cur != NULL) {
        node_t *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free_phones(phones, N);
    
}