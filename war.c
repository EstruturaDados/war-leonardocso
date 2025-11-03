#include <stdio.h>

#define MAX 5

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELOW,
} color;

const char *color_to_str(color c) {
    switch (c) {
    case RED:   return "vermelho";
    case GREEN: return "verde";
    case BLUE:  return "azul";
    case YELOW: return "amarelo";
    default:    return "indefinido";
    }
}

typedef struct {
    char name[50];
    color army_color;
    unsigned int army_size;
} territory;

void show_territory(territory *t);

int main(void) {
    territory t[MAX];

    return 0;
}

void show_territory(territory *t) {
    for (int i = 0; i < MAX; i++) {
        printf(" -------------------- \n");
        printf("Nome: %s\n", t->name);
        printf("Cor do Exército: %s\n", t->army_color);
        printf("Número de Tropas: %d\n", t->army_size);
        printf(" -------------------- \n");
    }
}
