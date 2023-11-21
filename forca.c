#include "forca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static No *criarNo(char letra)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->letra = letra;
    novo->prox = NULL;
    return novo;
}

void inicializaJogo(JogoForca *jogo, const char *palavra)
{
    No *atual;
    jogo->palavra = criarNo(palavra[0]);
    atual = jogo->palavra;

    for (int i = 1; palavra[i] != '\0'; i++)
    {
        atual->prox = criarNo(palavra[i]);
        atual = atual->prox;
    }

    jogo->palpite = criarNo('_');
    atual = jogo->palpite;
    for (int i = 1; palavra[i] != '\0'; i++)
    {
        atual->prox = criarNo('_');
        atual = atual->prox;
    }

    jogo->tentativas = 6;
    jogo->erros = 0;
    memset(jogo->tentativasIncorretas, 0, sizeof(jogo->tentativasIncorretas));
    jogo->numTentativasIncorretas = 0;
}

void exibeEstado(const JogoForca *jogo)
{
    No *atual = jogo->palpite;
    printf("Palavra: ");
    while (atual != NULL)
    {
        printf("%c ", atual->letra);
        atual = atual->prox;
    }
    printf("\nTentativas restantes: %d\n", jogo->tentativas);
    printf("Tentativas incorretas: ");
    for (int i = 0; i < jogo->numTentativasIncorretas; i++)
    {
        printf("%c ", jogo->tentativasIncorretas[i]);
    }
    printf("\n");
}

int processaPalpite(JogoForca *jogo, char palpite)
{
    int acerto = 0;
    No *atualPalavra = jogo->palavra;
    No *atualPalpite = jogo->palpite;

    while (atualPalavra != NULL)
    {
        if (atualPalavra->letra == palpite)
        {
            atualPalpite->letra = palpite;
            acerto = 1;
        }
        atualPalavra = atualPalavra->prox;
        atualPalpite = atualPalpite->prox;
    }

    if (!acerto && strchr(jogo->tentativasIncorretas, palpite) == NULL)
    {
        jogo->tentativasIncorretas[jogo->numTentativasIncorretas++] = palpite;
    }

    return acerto;
}

void liberaJogo(JogoForca *jogo)
{
    No *atual = jogo->palavra;
    No *temp;

    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }

    atual = jogo->palpite;
    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

void desenhaForca(int erros)
{
    printf("\n  +---+\n  |   |\n");
    if (erros >= 1)
    {
        printf("  O   |\n");
    }
    else
    {
        printf("      |\n");
    }
    if (erros == 2)
    {
        printf("  |   |\n");
    }
    else if (erros == 3)
    {
        printf(" /|   |\n");
    }
    else if (erros >= 4)
    {
        printf(" /|\\  |\n");
    }
    else
    {
        printf("      |\n");
    }
    if (erros == 5)
    {
        printf(" /    |\n");
    }
    else if (erros >= 6)
    {
        printf(" / \\  |\n");
    }
    else
    {
        printf("      |\n");
    }
    printf("      |\n=========\n");
}