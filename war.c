#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 5
int count = 0;

/*Buffer cleaner (safe for scanf)*/
void clean_buffer(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF) {};
}

/*Remove newline safely from fgets input*/
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/*Check if string contains only digits*/
bool is_number(const char string[]) {
    if (string[0] == '\0') return false;
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit((unsigned char)string[i])) return false;
    }
    return true;
}

/*Check if string contains only alphabetical characters*/
bool is_alpha(const char string[]) {
    if (string[0] == '\0') return false;

    for (int i = 0; string[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)string[i];
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}

/*Default color names*/
typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    UNKNOWN
} color;

/*User-friendly color names*/
const char *color_names[] = {
    "vermelho",
    "verde",
    "azul",
    "amarelo",
    "indefinido"
};

/*Converts string to enum color*/
color str_to_color(const char *c) {
    for (int i = 0; i < UNKNOWN; i++) {
        if (strcmp(c, color_names[i]) == 0) {
            return (color)i;
        }
    }
    return UNKNOWN;
}

/*Converts enum color to readable string*/
const char *color_to_str(color c) {
    if (c >= RED && c <= YELLOW) {
        return color_names[c];
    }
    return "indefinido";
}

/*Main structure*/
typedef struct {
    char name[50];
    color army_color;
    unsigned int army_size;
} territory;

void show_territory(const territory t[]);
void show_menu(void);
void creation_menu(territory t[]);

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    territory t[MAX];
    int option;

    while (true) {
        show_menu();
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            clean_buffer();
            continue;
        }
        clean_buffer();

        if (option == 0) {
            printf("Encerrando o jogo...\n");
            break;
        }
        else if (option == 1) {
            if (count < MAX) {
                creation_menu(t);
            } else {
                printf("Limite máximo de territórios cadastrados (%d) atingido.\n", MAX);
            }
        }
        else if (option == 2) {
            if (count == 0) {
                printf("Nenhum território cadastrado ainda.\n");
            } else {
                show_territory(t);
            }
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}

/*Menu display*/
void show_menu(void) {
    printf("\n======= MENU WAR =======\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar território\n");
    printf("2 - Visualizar territórios\n");
    printf("=========================\n");
    printf("Escolha: ");
}

/*Show registered territories*/
void show_territory(const territory t[]) {
    printf("\n===== TERRITÓRIOS CADASTRADOS =====\n");
    for (int i = 0; i < count; i++) {
        printf("\n-------TERRITÓRIO %d-------\n", i + 1);
        printf("Nome: %s\n", t[i].name);
        printf("Cor do Exército: %s\n", color_to_str(t[i].army_color));
        printf("Número de Tropas: %d\n", t[i].army_size);
    }
    printf("\nTotal: %d territórios cadastrados.\n", count);
}

/*Creation of one territory*/
void creation_menu(territory t[]) {
    char input[50];
    bool valid;

    /* Name */
    do {
        printf("\nDigite o nome do território: ");
        fgets(input, sizeof(input), stdin);
        remove_newline(input);

        if (is_alpha(input)) {
            strcpy(t[count].name, input);
            valid = true;
        } else {
            printf("Nome inválido! Digite apenas letras, sem espaços, números ou símbolos.\n");
            valid = false;
        }
    } while (!valid);

    /* Army color */
    do {
        printf("Digite a cor do exército [vermelho, verde, azul, amarelo]: ");
        fgets(input, sizeof(input), stdin);
        remove_newline(input);

        if (!is_alpha(input)) {
            printf("Cor inválida! Digite apenas letras sem acentos ou números.\n");
            valid = false;
            continue;
        }

        t[count].army_color = str_to_color(input);
        valid = (t[count].army_color != UNKNOWN);

        if (!valid) {
            printf("Cor não reconhecida. Escolha entre: vermelho, verde, azul ou amarelo.\n");
        }

    } while (!valid);

    /* Army size */
    do {
        printf("Digite o tamanho do exército: ");
        fgets(input, sizeof(input), stdin);
        remove_newline(input);

        if (!is_number(input) || atoi(input) <= 0) {
            printf("Entrada inválida! Digite apenas números inteiros maiores que zero.\n");
            valid = false;
        } else {
            t[count].army_size = atoi(input);
            valid = true;
        }
    } while (!valid);

    count++;
    printf("\nTerritório cadastrado com sucesso! (%d/%d)\n", count, MAX);
}
