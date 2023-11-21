#ifndef FORCA_H
#define FORCA_H

#define MAX_ERROS 6
#define MAX_LETRAS 26

typedef struct No
{
    char letra;
    struct No *prox;
} No;

typedef struct
{
    No *palavra;
    No *palpite;
    char tentativasIncorretas[MAX_LETRAS];
    int numTentativasIncorretas;
    int tentativas;
    int erros;
} JogoForca;

void inicializaJogo(JogoForca *jogo, const char *palavra);
void exibeEstado(const JogoForca *jogo);
int processaPalpite(JogoForca *jogo, char palpite);
void liberaJogo(JogoForca *jogo);
void desenhaForca(int erros);

#endif