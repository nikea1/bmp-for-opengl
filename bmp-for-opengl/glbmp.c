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
    out.height = 0;
    out.width = 0;
    out.pixelData = NULL;
    unsigned char buffer[56];
    int offset;
    int test;
    int test2;
    
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
    
    //cut bound offset to 56 if too big
    test = offset-14 >= 56 ? 56 : offset-14;
    //read in image header data
    if(fread(buffer, 1, test, fp) != test){
        printf("Something went horrible wrong in retrieving image information! Abort abort!\n");
        exit(EXIT_FAILURE);
    }
    //check for alpha mask
    if((offset - 14) >= 56)
        //get mask data
        out.hasAlpha = *(int *)&buffer[0x42 - 0x0E];
    else
        out.hasAlpha = 0;
    
   //get width and height
    out.width = *(int *)&buffer[0x12 - 0x0E];
    out.height = *(int *)&buffer[0x16 - 0x0E];
    
    //get image size
    test = *(int *)&buffer[0x22 - 0x0E];
    
    //if image size not found get bpp and calculate image size
    if(test == 0){
        //get bits per pixel
        test2 = *(char *)&buffer[0x1C - 0x0E];
        test = ((out.width)*(test2)+31)/32*4*(out.height);
    }
    
    //allocate space for image data
    out.pixelData = malloc(sizeof(char)*test);
    if(out.pixelData == NULL){
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    //mov file pointer to start of pixel data
    fseek(fp, offset, SEEK_SET);
    
    //read pixel into pixelData
    if(fread(out.pixelData,1, test, fp) != test){
        printf("Something went horrible wrong in getting pixel data! Abort abort!\n");
        exit(EXIT_FAILURE);
    }
    
    //Move alpha value to the right spot in the data if alpha mask is present
    if(out.hasAlpha == 0xFF){
        for(int i = 1; i < test; i++){
            if(i%4==0)
                continue;
            test2 = out.pixelData[i-1];
            out.pixelData[i-1] = out.pixelData[i];
            out.pixelData[i] = test2;
        }//end of for loop
    }//end of if statement
    
    //return struct
    return out;
}
