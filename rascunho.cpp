#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#define TAM 20

using namespace std;

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

enum TEXTURE{

    T_BODY_SNAKE,
    LENGTH_TEXTURE//Serve para contar quantos elementos tem no enum
};

enum SURFACE{

    S_BODY_SNAKE,
    LENGTH_SURFACE//Serve para contar quantos elementos tem no enum
};

SDL_Window *main_window = NULL;
SDL_Renderer *main_render = NULL;

SDL_Texture *texture[LENGTH_TEXTURE];
SDL_Surface *surface[LENGTH_SURFACE];

//funcoes de grafico
void redraw(SDL_Texture* texture, SDL_Renderer *renderer);

void graphicPos(SDL_Rect dst = { 0,0,0,0 }, SDL_Texture* texture = NULL, int flag = 1, SDL_Renderer* renderer = NULL, SDL_Rect src = { 0,0,0,0 });

//funcoes de controle da minhoca
void gera_semente();

//outras funcoes
void initializer();

void inicializa();

void imprime();


int SDL_main (int argc, char* args[]){

    initializer();

    fernando.corpo[0].x = 0;

    fernando.corpo[0].y = 0;

    fernando.tamanho = 1;

    fernando.direcao = 'd';

    SDL_Event evento;

    inicializa();

    imprime();

    int flag = 1;

    while(true)
    {
        system("cls");

        if(flag==1)
        {
            flag = 0;
            gera_semente();
        }
        imprime();

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
                    /*
                    if(fernando.corpo[i].x<curva.x)
                        fernando.corpo[i].x++;
                    else if(fernando.corpo[i].x>curva.x)
                        fernando.corpo[i].x--;
                    */
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
        }


        while(SDL_PollEvent(&evento)!=0);

        SDL_WaitEventTimeout(&evento, INFINITE);

        if(evento.type==SDL_KEYDOWN)
        {
            switch(evento.key.keysym.sym)
            {
                case SDLK_d:
                    ///verificar se n vai vai bater na parede
                    //SDL_Log("ENTREI POHA!\n");
                    fernando.direcao = 'd';
                    break;

                case SDLK_s:
                    fernando.direcao = 's';
                    break;
                case SDLK_a:
                    fernando.direcao = 'a';
                    break;
                case SDLK_w:
                    fernando.direcao = 'w';
                    break;
            }
        }

        while(SDL_PollEvent(&evento)!=0);

        Sleep(1000);
    }

    return 0;
}

void initializer(){

    SDL_Init(SDL_INIT_EVERYTHING);//inicializa os modulos da SDL

    //Cria a janela com nome de Xsnake com posicao x e y indefinida na tela
    //Com tamanhos definidos por SCREEN_WIDTH e SCREEN_HEIGHT
    //o ultimo parametro é uma flag q serve para criar a janela sem opcao de maximiza
    main_window = SDL_CreateWindow("Xsnake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);// cria a janela

    //cria uma janela de renderizacao, serve para armazenar as texturas na memoria da placa de video
    //primeiro parametro e a janela criada, o segundo serve para detectar automaticamente driver de videos
    //terceiro uma flag para utilizar memoria de video
    main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

    //carrega as imagens para uma surface
    surface[S_BODY_SNAKE] = IMG_Load("image/body.png");

    //cria as texturas
    texture[T_BODY_SNAKE] = SDL_CreateTextureFromSurface(main_render, surface[S_BODY_SNAKE]);

    //libera memoria
    SDL_FreeSurface(surface[S_BODY_SNAKE]);
    surface[S_BODY_SNAKE] = NULL;

    SDL_SetRenderDrawColor(main_render, 255, 255, 255, 255);
    SDL_RenderClear(main_render);
    SDL_RenderPresent(main_render);
}

void gera_semente()
{
    int x, y;
    srand(time(NULL));
    while(true)
    {
        x = rand()%TAM;
        y = rand()%TAM;
        if(mat[x][y]==' ')
        {
            mat[x][y] = '*';
            break;
        }
    }
}

void imprime()
{
    for(int i=0;i<fernando.tamanho;i++)
        mat[fernando.corpo[i].x][fernando.corpo[i].y] = '.';
    for(int i=0;i<TAM;i++)
    {
        for(int j=0;j<TAM;j++)
            printf("%c", mat[i][j]);
        printf("\n");
    }
}

//redesenha a plano de fundo
void redraw(SDL_Texture* texture, SDL_Renderer *renderer)
{
    int w = 0, h = 0;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    graphicPos({ 0,0, w, h }, texture, 1, main_render, { 0,0,w,h });
}

void inicializa()
{
    for(int i=0;i<TAM;i++)

        for(int j=0;j<TAM;j++)

            mat[i][j] = ' ';
}

void graphicPos(SDL_Rect dst, SDL_Texture* texture, int flag, SDL_Renderer* renderer, SDL_Rect src )/**Essa função serve para quando não e necessario uma posição especifica na tela*/
{
    if (src.x == 0 && src.y == 0 && src.w == 0 && src.h == 0)//faz com que seja plotado na posicao 0,0 da tela sem largura ou altura definida.
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    else  SDL_RenderCopy(renderer, texture, &src, &dst);//renderiza uma imagem

    if (flag)//Sinal para saber se a funcao deve plotar a textura na tela agora
        SDL_RenderPresent(renderer);
}
