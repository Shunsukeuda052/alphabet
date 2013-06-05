//
//  scoreCV.cpp
//  alphabet_sequencer_brashup
//
//  Created by 卯田 駿介 on 2013/05/26.
//
//

#include "scaleCV.h"

scaleCV::scaleCV()
{
}
scaleCV::~scaleCV()
{
}

void scaleCV:: setImage(ofImage image)
{
}

void scaleCV:: setImage(ofxCvGrayscaleImage image_threshold, int x, int y, int width, int height){
    
    image_threshold.allocate(CAMWIDTH, CAMHEIGHT);
    image_threshold.setFromPixels(image_threshold.getPixels(), CAMWIDTH, CAMHEIGHT);
    image_threshold.setROI(x, y, width, height);
    image_threshold_roi.setFromPixels(image_threshold.getRoiPixels(),width,height);
    image_ocrad.setFromPixels(image_threshold_roi.getPixels(), width, height, OF_IMAGE_GRAYSCALE);
    ocrad.setOfImage(&image_ocrad);
    NHocr.setPixels(&image_threshold_roi);
    
};
int scaleCV:: getScale(){
    
    
    // ドレミ　アルファベット表記
    if(strncmp(ocrad.str_result, "Do",2) == 0 ){
        scale = 0;
    }
    else if(strncmp(ocrad.str_result, "Re",2) == 0 ){
        scale = 2;
    }
    else if(strncmp(ocrad.str_result, "Mi",2) == 0 ){
        scale = 4;
    }
    else if(strncmp(ocrad.str_result, "Fa",2) == 0 ){
        scale = 5;
    }
    else if(strncmp(ocrad.str_result, "Sol",3) == 0 ){
        scale = 6;
    }
    else if(strncmp(ocrad.str_result, "La",2) == 0 ){
        scale = 8;
    }
    else if(strncmp(ocrad.str_result, "Si",2) == 0 ){
        scale = 10;
    }
    
    
    // 英語音名
    if(strncmp(ocrad.str_result, "C",1) == 0 ){
        scale = 0;
    }
    
    if(strncmp(ocrad.str_result, "D",1) == 0 ){
        scale = 2;
    }
    if(strncmp(ocrad.str_result, "E",1) == 0 ){
        scale = 4;
    }
    if(strncmp(ocrad.str_result, "F",1) == 0 ){
        scale = 5;
    }
    if(strncmp(ocrad.str_result, "G",1) == 0 ){
        scale = 6;
    }
    if(strncmp(ocrad.str_result, "A",1) == 0 ){
        scale = 8;
    }
    if(strncmp(ocrad.str_result, "B",1) == 0 ){
        scale = 10;
    }
    
    
    //　日本語表記
    if(strncmp(&NHocr.str_result[0], "ド", 1)==0){
        scale = 0;
    }
    
    
    
    
};



int  scaleCV:: getScale(int number){
};