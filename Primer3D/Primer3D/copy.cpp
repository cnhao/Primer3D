#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>


#define ARGB(r, g, b, a) ((a) + ((b) << 8) + ((g) << 16) + ((r) << 24))



int width = 700;
int height = 590;

void example04()
{
    SDL_Window		*pWindow = NULL;
    SDL_Renderer    *pRenderer = NULL;
    SDL_Texture		*pTexture;

    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)    return;
    
    pWindow = SDL_CreateWindow("Shit SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 590, 0);
    if (NULL == pWindow)    return;
    
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    if (NULL == pRenderer)    return;
    
//    SDL_SetRenderDrawColor(pRenderer, 70, 200, 122, SDL_ALPHA_OPAQUE);
    
    
    uint32_t* pixels = (uint32_t*)calloc(width*height,4);

    int  depth, pitch;
    
    pitch = height*4;	// 每行图像所占直接数
    depth = 4*8;		// 每像素所占位数
    
    for (int i = 0; i < width*height; i++) {
        pixels[i] = ARGB(rand()%256, rand()%256, rand()%256, 255);
    }
    
    
    int rmask, gmask, bmask, amask;
    rmask = 0xFF000000; gmask = 0x00FF0000; bmask = 0x0000FF00; amask = 0x000000FF;
    // RGBA8888模式
    SDL_Surface    *pTmpSurface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
    if (NULL == pTmpSurface)    return;
    
    pTexture = SDL_CreateTextureFromSurface(pRenderer,pTmpSurface);
    if (NULL == pTexture)    return;
    //SDL_FreeSurface(pTmpSurface);
    
    
    
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;
    
    const Uint32 FPS = 1000/60;//60可替换为限制的帧速
    Uint32 _FPS_Timer = 0;
    
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }
        
        SDL_RenderClear(pRenderer);
    
        SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);
    
        SDL_RenderPresent(pRenderer);
        
        if(SDL_GetTicks()-_FPS_Timer<FPS){
            SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
        }
        _FPS_Timer=SDL_GetTicks();
    
    }
    
}

int main()
{
    example04();
    return 1;
}
