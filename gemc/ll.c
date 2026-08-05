#include <stdio.h>
#include <stdlib.h>

struct nlist {
    unsigned long long x;
    struct nlist *next;
    struct nlist *last;
};

struct nlist* nlist_new(unsigned long long x) {
    struct nlist *node = (struct nlist *)malloc(sizeof(struct nlist));
    if (node == NULL) return NULL; /* Catch memory ceiling */
    node->x = x;
    node->next = NULL;
    node->last = node;
    return node;
}

int main(void) {
    unsigned long long count = 0;
    unsigned long long sum = 0;
    struct nlist *head = NULL;
    struct nlist *tail = NULL;
    
    printf("Probing Termux memory ceiling for dynamic nodes...\n");

    /* Continously allocate until mobile RAM / heap threshold is exhausted */
    while (1) {
        count++;
        struct nlist *node = nlist_new(count);
        if (node == NULL) {
            printf("Memory ceiling hit safely at node count: %llu\n", count - 1);
            break;
        }
        
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        sum += count;

        /* Optional safety valve to prevent total Android OOM kernel panic */
        if (count >= 20000000) { 
            printf("Safely capped test at 20 million nodes to keep Termux stable.\n");
            break;
        }
    }

    printf("Total sum calculated up to ceiling: %llu\n", sum);

    /* Free memory */
    {
        struct nlist *curr = head;
        while (curr != NULL) {
            struct nlist *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return 0;
}