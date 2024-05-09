#include<stdio.h>
#include<SDL2/SDL.h>
#include<math.h>

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
int game=0;
int initialiaz()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("%s\n",SDL_GetError());
        return 0;
    }
    window=SDL_CreateWindow("TASK 102",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,856,623,SDL_WINDOW_ALLOW_HIGHDPI);
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
}

void filledcircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); 
    
    for(int dy = -radius; dy <= radius; dy++)
    {
        for(int dx = -radius; dx <= radius; dx++)
        {
            if(dx*dx + dy*dy <= radius*radius)
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void increased_radius(int x, int y, int initial_radius, Uint8 r, Uint8 g, Uint8 b, int window_width, int window_height)
{
    static int radius = initial_radius;
    radius++;
    if (x - radius <= 0 || x + radius >= window_width || y - radius <= 0 || y + radius >= window_height) {
        radius = initial_radius;
    }
    filledcircle(x, y, radius, r, g, b);
}

int main(int argc,char* argv[])
{
    game=initialiaz();
    while(game==1)
    {
        process_input();
        SDL_SetRenderDrawColor(renderer, 10, 250, 100, 255);
        SDL_RenderClear(renderer);
        increased_radius(400, 300, 150, 2, 150, 102, 856, 623);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    return 0;
}
