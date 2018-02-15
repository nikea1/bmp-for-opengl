//
//  glbmp.c
//  bmp-for-opengl
//
//  Created by Adenike Adeyemi on 2/14/18.
//  Copyright © 2018 Adenike Adeyemi. All rights reserved.
//

#include "glbmp.h"
#include <stdio.h>
#include <stdlib.h>

glBMP initGLBMP(char* input){
    //check if string is right
    
    FILE *fp;
    glBMP out;
    unsigned char buffer[56];
    int offset;
    
    //open file
    fp = fopen(input,"rb+");
    if(fp == NULL){
        printf("File failed to open\n");
        exit(EXIT_FAILURE);
    }
    
    
    //read 14 bytes to buffer
    if(fread(buffer, 1, 14, fp) != 14){
        printf("Something went horrible wrong in retrieving header information! Abort abort!\n");
        exit(EXIT_FAILURE);
    }
    
    //check for file format
    if(buffer[0] != 'B' || buffer[1] != 'M'){
        printf("Something is wrong with the BMP file\n");
        exit(EXIT_FAILURE);
    }
    
    //get img offest
    offset = *(int *)&buffer[0x0A];
    
    //read offset - 14 bytes
    if(fread(buffer, 1, offset - 14, fp) != offset - 14){
        printf("Something went horrible wrong in retrieving image information! Abort abort!\n");
        exit(EXIT_FAILURE);
    }
    
    //check size
    //if 56 bytes or up
    
    if((offset - 14) >= 56)
        //get mask data
        out.hasAlpha = *(int *)&buffer[0x42 - 0x0E];
    else
        out.hasAlpha = 0;
    
    out.width = *(int *)&buffer[0x12 - 0x0E];
    out.height = *(int *)&buffer[0x16 - 0x0E];
    
    //get width and height
    if(fread(out.pixelData,1, (*(int *)&buffer[0x22 - 0x0E]), fp) != (*(int *)&buffer[0x22 - 0x0E])){
        printf("Something went horrible wrong in getting pixel data! Abort abort!\n");
        exit(EXIT_FAILURE);
    }
    //return struct
    return out;
}
