//
//  glbmp.h
//  bmp-for-opengl
//
//  Created by Adenike Adeyemi on 2/14/18.
//  Copyright © 2018 Adenike Adeyemi. All rights reserved.
//

#ifndef glbmp_h
#define glbmp_h

#include <stdio.h>

typedef struct {
    int height;
    int width;
    int hasAlpha; //flag for alpha mask
    unsigned char* pixelData;
}glBMP;

glBMP initGLBMP(char*);


#endif /* glbmp_h */
