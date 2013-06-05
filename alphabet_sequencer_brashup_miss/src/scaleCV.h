//
//  scoreCV.h
//  alphabet_sequencer_brashup
//
//  Created by 卯田 駿介 on 2013/05/26.
//
//

#ifndef __alphabet_sequencer_brashup__scoreCV__
#define __alphabet_sequencer_brashup__scoreCV__
#pragma once

#include "ofMain.h"
#include "testApp.h"
#include "ofxOcrad.h"
#include "ofxNHocr.h"

class scaleCV{
public:
    
    scaleCV();
    ~scaleCV();
    
    void setImage(ofImage image);
    void setImage(ofxCvGrayscaleImage image_threshold, int x, int y, int width, int height);
    int getScale();
    int getScale(int number);
    
private:
    
    int scale;
    char alphabet[64];
    bool bIsTrueScaleNHocr();
    
    ofImage image_ocrad;
    ofxCvGrayscaleImage image_threshold_roi;
    ofxOcrad ocrad;
    ofxNHocr NHocr;
};


#endif /* defined(__alphabet_sequencer_brashup__scoreCV__) */
