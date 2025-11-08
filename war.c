#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

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
void create_territory(territory *t);

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    territory t[MAX];
    
    int option;
    bool run_game = true; // Flag to control game flow
    while(run_game) {
        show_menu();
        scanf("\d", option);
        switch (option) {
            case 0:
                run_game = false;
                break;
            case 1:
                create_territory(*t[]);
        
        }
    
    }
    return 0;
}

void show_menu(void) {
    printf("-----------------------------------\n");
    printf("                MENU               \n");
    printf("-----------------------------------\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar território\n");
    printf("2 - Visualizar estado atual do mapa\n");
    printf("------------------------------------\n");
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
