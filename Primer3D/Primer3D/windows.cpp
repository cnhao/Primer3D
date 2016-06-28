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
    
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
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
