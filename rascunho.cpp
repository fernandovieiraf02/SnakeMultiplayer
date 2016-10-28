#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<windows.h>
#include<time.h>
#include<SDL.h>

#define TAM 10

typedef struct{
    int x;
    int y;
}Posicao;

typedef struct{
    Posicao corpo[TAM];
    int tamanho;
    char direcao;
}Minhoca;

Minhoca fernando;

char mat[TAM][TAM] = {};

void inicializa();

void imprime();

void gera_semente();

int SDL_main(int argc, char* args[])
{

    fernando.corpo[0].x = 0;
    fernando.corpo[0].y = 0;
    fernando.tamanho = 1;
    fernando.direcao = 'd';


    SDL_Event evento;

    inicializa();
    imprime();
    while(true)
    {
        int flag = 0;
        char dir;

        system("cls");
        gera_semente();
        imprime();

        scanf("\n%c", &fernando.direcao);
        Posicao curva = fernando.corpo[0];
        switch(fernando.direcao)
        {
            case 'd':
                while(flag==0)///ate colidir com comida
                {
                    int tam = fernando.tamanho;
                    for(int i=0;i<fernando.tamanho;i++)///andar
                    {
                        mat[fernando.corpo[tam-1].x][fernando.corpo[tam-1].y] = ' ';
                        fernando.corpo[i].y++;
                        if(fernando.corpo[i].x<curva.x)
                            fernando.corpo[i].x++;
                        else if(fernando.corpo[i].x>curva.x)
                            fernando.corpo[i].x--;
                    }
                    if(mat[fernando.corpo[0].x][fernando.corpo[0].y] == '*')///colisao
                    {
                        fernando.corpo[tam].x = fernando.corpo[tam-1].x;
                        fernando.corpo[tam].y = fernando.corpo[tam-1].y-1;
                        fernando.tamanho++;
                        flag = 1;
                        //imprime();
                    }
                    //system("pause");
                    system("cls");
                    imprime();
                    Sleep(100);
                }
                break;
            case 's':
                while(flag==0)///ate colidir com comida
                {
                    int tam = fernando.tamanho;
                    for(int i=0;i<fernando.tamanho;i++)///andar
                    {
                        mat[fernando.corpo[tam-1].x][fernando.corpo[tam-1].y] = ' ';
                        fernando.corpo[i].x++;
                        if(fernando.corpo[i].y<curva.y)
                        {
                            mat[fernando.corpo[tam-1].x][fernando.corpo[tam-1].y] = ' ';
                            fernando.corpo[i].y++;
                            fernando.corpo[i].x++;
                        }
                        else if(fernando.corpo[i].y>curva.y)
                        {
                            mat[fernando.corpo[tam-1].x][fernando.corpo[tam-1].y] = ' ';
                            fernando.corpo[i].y--;
                        }
                        system("pause");
                    }
                    if(mat[fernando.corpo[0].x][fernando.corpo[0].y] == '*')///colisao
                    {
                        fernando.corpo[tam].x = fernando.corpo[tam-1].x-1;
                        fernando.corpo[tam].y = fernando.corpo[tam-1].y;
                        fernando.tamanho++;
                        flag = 1;
                        //imprime();
                    }
                    //system("pause");
                    system("cls");
                    imprime();
                    Sleep(100);
                }
                break;
        }

        /*
        while(SDL_PollEvent(&evento)!=0);
        SDL_WaitEventTimeout(&evento, INFINITE);
        if(evento.type==SDL_KEYDOWN)
        {
            switch(evento.key.keysym.sym)
            {
                case SDLK_d:
                    ///verificar se n vai vai bater na parede

                    //SDL_Log("ENTREI POHA!\n");
                    printf("Entrei POHA!\n");
                    Posicao cabeca;
                    cabeca = fernando.corpo[0];

                    for(int i=0;i<fernando.tamanho;i++)
                    {
                        fernando.corpo[i].x++;
                    }

                    imprime();
                    break;
            }
        }
        while(SDL_PollEvent(&evento)!=0);
        */
        //Sleep(1000);
    }

    return 0;
}

void inicializa()
{
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            mat[i][j] = ' ';
}

void imprime()
{
    for(int i=0;i<fernando.tamanho;i++)
        mat[fernando.corpo[i].x][fernando.corpo[i].y] = 220;

    for(int i=0;i<TAM;i++)
    {
        for(int j=0;j<TAM;j++)
            printf("%c", mat[i][j]);
        printf("\n");
    }
}

void gera_semente()
{
    int x, y;
    srand(time(NULL));
    while(true)
    {
        x = rand()%TAM/2;
        y = rand()%TAM;
        if(mat[x][y]==' ')
        {
            mat[x][y] = '*';
            break;
        }
    }
}


