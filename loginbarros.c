#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAX_ALUNOS 100

typedef struct {
    char nome[100];
    char cpf[15];
    char data_nascimento[11];
    int matricula;
    float notas[3]; // 3 notas por aluno
} Aluno;

Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

// variáveis globais para definir logins e senhas
char logins[3][20] = {"assistente", "professor", "aluno"};
char senhas[3][20] = {"assistente", "professor", "aluno"};

void telaLogin();
void menuAdmin();
void matricula();
void menuAluno();
void menuProfessor();
void getPassword();
void matricularAluno();
void boletim();
void nota();

int main() {
    setlocale(LC_ALL, "Portuguese"); // Definir idioma
    telaLogin(); // Chamar a função da tela de login
    return 0;
}

int gerarNumeroMatricula() {
    srand(time(NULL));
    return rand() % 900000 + 100000; // Gera um número de matrícula entre 100000 e 999999
}

void getPassword(char *password, int length) {
    int i = 0;
    char ch;

    while (i < length - 1) {
        ch = _getch(); // Captura o caractere sem exibi-lo
        if (ch == '\r') break; // Enter finaliza a entrada
        if (ch == '\b' && i > 0) { // Backspace apaga caracteres
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*"); // Exibe asterisco
        }
    }
    password[i] = '\0';
    printf("\n");
}

void telaLogin() {
    char login[20], senha[20], opcao;
    int i, login_sucesso = 0; // variável para indicar se o login foi bem-sucedido

    while (1) {
        system("cls");
        printf("\t\t\t\t\t |============= LOGIN =============|\n");
        printf("\t\t\t\t\t |Digite o login: ");
        scanf("%s", login); // Recebe o que o usuário digitou no login
        getchar(); // Consome o '\n'
        printf("\t\t\t\t\t |Digite a senha: ");
        getPassword(senha, sizeof(senha));

        // Verifica todos os logins e senhas
        if (strcmp(login, logins[0]) == 0 && strcmp(senha, senhas[0]) == 0) {
            login_sucesso = 1;
        } else if (strcmp(login, logins[2]) == 0 && strcmp(senha, senhas[2]) == 0) {
            login_sucesso = 2;
        } else if (strcmp(login, logins[1]) == 0 && strcmp(senha, senhas[1]) == 0) {
            login_sucesso = 3;
        }

        if (login_sucesso == 1) {
            printf("\n\t\t\t\t\t Login bem-sucedido!\n");
            printf("\n\t\t\t\t\t Carregando menu");
            for (i = 0; i < 3; i++) {
                printf(".");
                Sleep(1000); // Atraso de 1 segundo
            }
            menuAdmin();
            break;
        } else if (login_sucesso == 2) {
            printf("\n\t\t\t\t\t Login bem-sucedido!\n");
            printf("\n\t\t\t\t\t Carregando menu");
            for (i = 0; i < 3; i++) {
                printf(".");
                Sleep(1000); // Atraso de 1 segundo
            }
            menuAluno();
            break;
        } else if (login_sucesso == 3) {
            printf("\n\t\t\t\t\t Login bem-sucedido!\n");
            printf("\n\t\t\t\t\t Carregando menu");
            for (i = 0; i < 3; i++) {
                printf(".");
                Sleep(1000); // Atraso de 1 segundo
            }
            menuProfessor();
            break;
        } else { // Caso não dê certo nenhum teste
            system("cls");
            printf("\t\t\t\t\t Login falhou\n");
            printf("\n\t\t\t\t\t Deseja tentar novamente?");
            printf("\n\t\t\t\t\t (S)Sim");
            printf("\n\t\t\t\t\t (N)Não");
            printf("\n\t\t\t\t\t Selecione: ");
            scanf("%c", &opcao); // Recebe o que o usuário escolheu
            getchar(); // Consome o '\n' restante no buffer
            if (opcao == 's' || opcao == 'S') {
                printf("\n\t\t\t   ============ Carregando a tela de login em 5 segundos ============\n");
                Sleep(5000); // Atraso de 5 segundos
            } else {
                printf("\n\t\t\t   ============ Encerrando o sistema em 5 segundos ============\n");
                Sleep(5000); // Atraso de 5 segundos
                break;
            }
        }
    }
}

void obterDadosAluno(char *nome, char *cpf, char *data_nascimento, int *matricula) {
    printf("Nome completo: ");
    fflush(stdin);
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("CPF: ");
    scanf("%s", &cpf);
    
    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", data_nascimento);
    
    *matricula = gerarNumeroMatricula();
}

void menuAdmin() {
    char opcao;
    system("cls"); // Limpa a tela
    // Opções que o usuário tem abaixo
    printf("MENU DO ASSISTENTE:\n");
    printf("\n1. Matricular Aluno");
    printf("\n2. Fechar Sistema");
    printf("\n\nOpção escolhida: ");
    scanf("%c", &opcao); // Lê o que o usuário inseriu
    getchar(); // Consome o '\n' restante no buffer
    system("cls"); // Limpa a tela
    switch (opcao) {
        case '1':
            matricula();
            break;
        case '2':
            printf("\t\t\t   ============ Voltando Para o Login ============\n");
            Sleep(5000);
            telaLogin();
            break;
        default: // Caso o usuário não escolha nenhuma das opções acima, ele chama o menu de novo
            menuAdmin();
            break;
    }
}

void matricula() {
    char opcao;
    system("cls");
    printf("MENU DE MATRÍCULA:\n\n");
    printf("1- Matricular Técnico\n");
    printf("2- Matricular Graduação\n");
    printf("3- Encerrar Sistema\n");
    printf("\nOpção escolhida: ");
    scanf("%c", &opcao);
    system("cls");
    switch (opcao) {
        case '1':
        case '2':
            matricularAluno();
            break;
        case '3':
            printf("\t\t\t   ============ Voltando Para o Login ============\n");
            Sleep(5000);
            telaLogin();
            break;
        default: // Caso o usuário não escolha nenhuma das opções acima, ele chama o menu de novo
            matricula();
            break;
    }
}

void menuAluno() {
    char opcao;
    system("cls"); // Limpa a tela
    // Opções que o usuário tem abaixo
    printf("MENU DO ALUNO:\n");
    printf("\n1. Consultar Boletim");
    printf("\n2. Fechar Sistema");
    printf("\n\nOpção escolhida: ");
    scanf("%c", &opcao); // Lê o que o usuário inseriu
    getchar(); // Consome o '\n' restante no buffer
    system("cls"); // Limpa a tela
    switch (opcao) {
        case '1':
            boletim();
            break;
        case '2':
            printf("\t\t\t   ============ Voltando Para o Login ============\n");
            Sleep(5000);
            telaLogin();
            break;
        default: // Caso o usuário não escolha nenhuma das opções acima, ele chama o menu de novo
            menuAluno();
            break;
    }
}

void menuProfessor() {
    char opcao;
    system("cls"); // Limpa a tela
    // Opções que o usuário tem abaixo
    printf("MENU DO PROFESSOR:\n");
    printf("\n1. Consultar Boletim");
    printf("\n2. Lançar Nota");
    printf("\n3. Encerrar sistema");
    printf("\n\nOpção escolhida: ");
    scanf("%c", &opcao); // Lê o que o usuário inseriu
    getchar(); // Consome o '\n' restante no buffer
    system("cls"); // Limpa a tela
    switch (opcao) {
        case '1':
            boletim();
            break;
        case '2':
            nota();
            break;
        case '3':
            printf("\t\t\t   ============ Voltando Para o Login ============\n");
            Sleep(5000);
            telaLogin();
            break;
        default: // Caso o usuário não escolha nenhuma das opções acima, ele chama o menu de novo
            menuProfessor();
            break;
    }
}

void matricularAluno() {
	int i;
    if (totalAlunos >= MAX_ALUNOS) {
        printf("\nLimite de alunos atingido!\n");
        return;
    }
    
    system("cls");
    printf("Matrícula de Novo Aluno\n");
    obterDadosAluno(alunos[totalAlunos].nome, alunos[totalAlunos].cpf, alunos[totalAlunos].data_nascimento, &alunos[totalAlunos].matricula);
    
    // Inicializa notas com zero
    for (i = 0; i < 3; i++) {
        alunos[totalAlunos].notas[i] = 0.0;
    }
    
    printf("\nAluno matriculado com sucesso!\n");
    printf("Nome: %s\nCPF: %s\nData de Nascimento: %s\nNúmero de Matrícula: %d\n", 
            alunos[totalAlunos].nome, alunos[totalAlunos].cpf, alunos[totalAlunos].data_nascimento, alunos[totalAlunos].matricula);
    totalAlunos++;
    Sleep(3000);
    matricula();
}

void boletim() {
	int i;
	int j;
    int matricula;
    system("cls");
    printf("Digite o número de matrícula: ");
    scanf("%d", &matricula);
    
    for ( i = 0; i < totalAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("\nBoletim do aluno %s:\n", alunos[i].nome);
            for (j = 0; j < 3; j++) {
                printf("Nota %d: %.2f\n", j + 1, alunos[i].notas[j]);
            }
            Sleep(3000);
            menuAluno();
            return;
        }
    }
    printf("\nAluno não encontrado!\n");
    Sleep(3000);
    menuAluno();
}

void nota() {
    int matricula, i, j;
    float novaNota;
    system("cls");
    printf("Digite o número de matrícula do aluno: ");
    scanf("%d", &matricula);
    
    for (i = 0; i < totalAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("\nLançando nota para o aluno %s:\n", alunos[i].nome);
            for (j = 0; j < 3; j++) {
                printf("Digite a nota %d: ", j + 1);
                scanf("%f", &novaNota);
                alunos[i].notas[j] = novaNota;
            }
            printf("Notas lançadas com sucesso!\n");
            Sleep(3000);
            menuProfessor();
            return;
        }
    }
    printf("\nAluno não encontrado!\n");
    Sleep(3000);
    menuProfessor();
}
