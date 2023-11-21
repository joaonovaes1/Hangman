#include "forca.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    JogoForca meuJogo;
    char entrada[100];
    char palpite;

    printf("Digite a palavra secreta: ");
    fgets(entrada, 100, stdin);
    entrada[strcspn(entrada, "\n")] = 0; // Remove newline
    for (int i = 0; entrada[i] != '\0'; i++)
    {
        entrada[i] = tolower(entrada[i]);
    }

    inicializaJogo(&meuJogo, entrada);

    while (meuJogo.tentativas > 0)
    {
        limparTela();
        exibeEstado(&meuJogo);
        desenhaForca(meuJogo.erros);

        printf("Digite um palpite (uma letra): ");
        fgets(entrada, 100, stdin);

        if (strlen(entrada) == 2 && isalpha(entrada[0]))
        {
            palpite = tolower(entrada[0]);
            if (!processaPalpite(&meuJogo, palpite))
            {
                printf("Palpite incorreto!\n");
                meuJogo.tentativas--;
                meuJogo.erros++;
            }
        }
        else
        {
            printf("Erro: Por favor, insira apenas uma letra.\n");
            printf("Pressione qualquer tecla para continuar...");
            getchar(); // Pausa até que o usuário pressione uma tecla
            continue;
        }

        // Verificar se o jogo foi ganho
        int ganhou = 1;
        No *atual = meuJogo.palpite;
        while (atual != NULL)
        {
            if (atual->letra == '_')
            {
                ganhou = 0;
                break;
            }
            atual = atual->prox;
        }

        if (ganhou)
        {
            limparTela();
            exibeEstado(&meuJogo);
            desenhaForca(meuJogo.erros);
            printf("Parabéns! Você adivinhou a palavra: %s\n", entrada);
            break;
        }
    }

    if (meuJogo.tentativas == 0)
    {
        limparTela();
        exibeEstado(&meuJogo);
        desenhaForca(meuJogo.erros);
        printf("Game over! A palavra era: %s\n", entrada);
    }

    liberaJogo(&meuJogo);
    return 0;
}