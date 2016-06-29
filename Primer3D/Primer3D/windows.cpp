//
//  windows.cpp
//  Primer3D
//
//  Created by cnhao on 16/6/28.
//  Copyright © 2016年 cnhao. All rights reserved.
//

#include "windows.hpp"

void _primer3d_window::init(){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)    return;
    
    pWindow = SDL_CreateWindow("Shit SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if (NULL == pWindow)    return;
    
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    if (NULL == pRenderer)    return;
    
//    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
}


void _primer3d_window::drawBeauty(){
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float jFloat = static_cast<float>(j);
            float iFloat = static_cast<float>(i);
            pixels[width*i+j] = ARGB( int(jFloat/width*255),
                                     int(iFloat/height*255), 255, 255);
        }
    }
}

void _primer3d_window::drawPixel(int x, int y, Uint32 color){
//    pixels[(height-y-2)*width+x] = color;
    pixels[width*y+x] = color;
}

void _primer3d_window::drawLine(int x0, int y0, int x1, int y1, Uint32 color){
    
    int x, y, dx, dy, dx2, dy2, xstep, ystep, error, index;
    x = x0;
    y = y0;
    dx = x1 - x0;
    dy = y1 - y0;
    
    if (dx >= 0) // 从左往右画
    {
        xstep = 1; // x步进正1
    }
    else // 从右往左画
    {
        xstep = -1; // x步进负1
        dx = -dx; // 取绝对值
    }
    
    if (dy >= 0) // 从上往下画
    {
        ystep = 1; // y步进正1
    }
    else // 从下往上画
    {
        ystep = -1; // y步进负1
        dy = -dy; // 取绝对值
    }
    
    dx2 = dx << 1; // 2 * dx
    dy2 = dy << 1; // 2 * dy
    
    if (dx > dy) // 近X轴直线
    {
        error = dy2 - dx;
        for (index = 0; index <= dx; ++index)
        {
            _primer3d_window::drawPixel(x, y, color);
            if (error >= 0)
            {
                error -= dx2;
                y += ystep;
            }
            error += dy2;
            x += xstep;
        }
    }
    else // 近Y轴直线
    {
        error = dx2 - dy;
        for (index = 0; index <= dy; ++index)
        {
            _primer3d_window::drawPixel(x, y, color);
            if (error >= 0)
            {
                error -= dy2;
                x += xstep;
            }
            error += dx2;
            y += ystep;
        }
    }
    
}


void _primer3d_window::run(){
    
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
