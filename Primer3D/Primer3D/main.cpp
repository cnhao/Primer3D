//
//  main.cpp
//  Primer3D
//
//  Created by cnhao on 16/6/28.
//  Copyright © 2016年 cnhao. All rights reserved.
//

#include <stdio.h>
#include "windows.hpp"

using namespace _primer3d_window;

int main(){
    
    init();
//    drawBeauty();
    for (int i=0; i<10000; i++) {
        drawLine(rand()%width, rand()%height, rand()%width, rand()%height, ARGB(rand()%255, rand()%255, rand()%255, 255));
    }
//    drawLine(0, 0, 900, 600, ARGB(rand()*255, rand()*255, rand()*255, 255));
    run();
}