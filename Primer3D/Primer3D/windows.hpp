//
//  windows.hpp
//  Primer3D
//
//  Created by cnhao on 16/6/28.
//  Copyright © 2016年 cnhao. All rights reserved.
//

#ifndef windows_hpp
#define windows_hpp

#include <SDL2/SDL.h>

#define ARGB(r, g, b, a) ((a) + ((b) << 8) + ((g) << 16) + ((r) << 24))


namespace _primer3d_window {
    
    static SDL_Window		*pWindow = NULL;
    static SDL_Renderer    *pRenderer = NULL;
    static SDL_Texture		*pTexture;
    static const int width = 900;
    static const int height = 600;
    static const int pitch = width*4;	// 每行图像所占直接数
    static const int depth = 4*8;		// 每像素所占位数
    static int32_t* pixels = (int32_t*)calloc(width*height, 4);
    static int rmask = 0xFF000000;
    static int gmask = 0x00FF0000;
    static int bmask = 0x0000FF00;
    static int amask = 0x000000FF;
    


    void init();
    void drawPixel(int x, int y, int color);
    void drawBeauty();
    void run();

}


#endif /* windows_hpp */
