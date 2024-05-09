#include<stdio.h>
#include<SDL2/SDL.h>
#include<math.h>

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
int game=0;
#define CIRCLE_RADIUS 30
#define CIRCLE_SPEED 1
#define CONTROLLED_CIRCLE_RADIUS 26
int cx = -CIRCLE_RADIUS;
int cy = 640 / 2;
int rcx =  480/ 2;
int rcy = 0;
int initialiaz()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("%s\n",SDL_GetError());
        return 0;
    }
    window=SDL_CreateWindow("TASK 103",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_ALLOW_HIGHDPI);
    if(window==NULL)
    {
        printf("%s\n",SDL_GetError());
        return 0;
    }

    renderer=SDL_CreateRenderer(window,-1,0);
    
    if(renderer==NULL)
    {
        printf("%s\n",SDL_GetError());
        return 0;
    }
    return 1;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT: game=0;
        break;
        case SDL_KEYDOWN: 
        if(event.key.keysym.sym==SDLK_ESCAPE) game=0;
        break;
    }
    if(event.type==SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP: 
            rcy-=20;
            break;
            case SDLK_DOWN:
            rcy += 20;
            break;
            case SDLK_LEFT:
            rcx -= 20;
            break;
            case SDLK_RIGHT:
            rcx += 20;
            break;
        }
    }
}

bool checkCollision(int x1, int y1, int x2, int y2, int r1, int r2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int DX = dx * dx + dy * dy;
    int DY = (r1 + r2) * (r1 + r2);
    return DX <= DY;
}

void Circle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void drawControlledCircle(SDL_Renderer* renderer, int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    Circle(renderer, x, y, CONTROLLED_CIRCLE_RADIUS);
}

int main(int argc,char* argv[])
{
    game=initialiaz(); 
    while(game==1)
    {
        process_input();
        cx+=CIRCLE_SPEED;
        if(cx>(856+CIRCLE_RADIUS)) cx=-CIRCLE_RADIUS;
        SDL_SetRenderDrawColor(renderer, 100, 110, 178, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 40, 53, 255);
        Circle(renderer, cx, cy, CIRCLE_RADIUS);
        
        SDL_Color controlledColor = {255, 255, 100, 255};
        if (checkCollision(cx, cy, rcx, rcy, CIRCLE_RADIUS, CONTROLLED_CIRCLE_RADIUS)) {
            controlledColor = {12, 9, 100, 255};
        }
        drawControlledCircle(renderer, rcx, rcy, controlledColor);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    return 0;
}
