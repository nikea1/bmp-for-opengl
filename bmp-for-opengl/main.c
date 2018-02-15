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
    printf("Hello, World!\n");
    
    hi = initGLBMP("test2.bmp");
    
    printf("Height: %i\n", hi.height);
    printf("Width: %i\n", hi.width);
    printf("Alpha?: %i", hi.hasAlpha);
    //printf();
    
    
    
    return 0;
}
