//
//  main.c
//  bmp-for-opengl
//
//  Created by Adenike Adeyemi on 2/14/18.
//  Copyright © 2018 Adenike Adeyemi. All rights reserved.
//

#include <stdio.h>
#include "glbmp.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    glBMP hi;
    int size;
    printf("Hello, World!\n");
    
    hi = initGLBMP("alpha.bmp");
    
    printf("Height: %i\n", hi.height);
    printf("Width: %i\n", hi.width);
    printf("Alpha?: %i\n", hi.hasAlpha);
    size = hi.height*hi.width*4;
    
    
    for(int i = 0; i <size; i++){
        if(i%16 == 0) printf("\n");
        printf("%x ", hi.pixelData[i]);
    }

    printf("\n");
    
    
    
    return 0;
}
