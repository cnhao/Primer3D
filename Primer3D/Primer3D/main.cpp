#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>

void GetRGBA8888Data(void *&pixels, int &width, int &height)
{
    // for debug
    width = 700;
    height = 590;
    pixels = calloc(width*height*4,1);	// 一像素占4字节
}

void example04()
{
    SDL_Window		*pWindow = NULL;
    SDL_Renderer    *pRenderer = NULL;
    SDL_Texture		*pTexture;
    SDL_Rect        srcRect;
    SDL_Rect        dstRect;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)    return;
    
    pWindow = SDL_CreateWindow("example04: for mediaplayer", 100, 100, 700, 590, 0);
    if (NULL == pWindow)    return;
    
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    if (NULL == pRenderer)    return;
    
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    
    void *pixels;
    int  width, height, depth, pitch;
    
    GetRGBA8888Data(pixels, width, height);
    pitch = height*4;	// 每行图像所占直接数
    depth = 4*8;		// 每像素所占位数
    
    int rmask, gmask, bmask, amask;
    //rmask = 0xFF000000; gmask = 0x00FF0000; bmask = 0x0000FF00; amask = 0x000000FF;	// RGBA8888模式
    rmask = 0xFF000000; gmask = 0x00FF0000; bmask = 0x0000FF00; amask = 0x00000000;	// RGB8888模式
    SDL_Surface    *pTmpSurface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
    if (NULL == pTmpSurface)    return;
    
    pTexture = SDL_CreateTextureFromSurface(pRenderer,pTmpSurface);
    if (NULL == pTexture)    return;
    //SDL_FreeSurface(pTmpSurface);
    
    dstRect.x = srcRect.x = 0;
    dstRect.y = srcRect.y = 0;
    dstRect.w = srcRect.w = width;
    dstRect.h = srcRect.h = height;
    
    SDL_RenderClear(pRenderer);
    
    SDL_RenderCopy(pRenderer, pTexture, &srcRect, &dstRect);
    
    SDL_RenderPresent(pRenderer);
    
    SDL_Delay(5000);
}

