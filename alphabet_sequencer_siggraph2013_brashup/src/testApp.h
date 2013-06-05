#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxUI.h"
#include "ofxOcrad.h"
#include "musicalSequenceTImer.h"
#include "ofxNHocr.h"


#define CAMWIDTH 640
#define CAMHEIGH 480

#define END_OF_RIGHT_WINDOW 110
#define START_STEP_X 192

#define STEP_WIDTH (CAMWIDTH-START_STEP_X)/4
#define STEP_HEIGH CAMHEIGH/4

#define SET_INSTRUMENTS_CARD_POSITION_Y 60
#define SET_REC_RESET_CARD_POSITION_Y 283


#define SET_INSTRUMENTS_CARD_POSITION_WIDTH 170



#define INSTRUMENTS 16

#define X0 START_STEP_X
#define X1 START_STEP_X+STEP_WIDTH
#define X2 START_STEP_X+STEP_WIDTH*2
#define X3 START_STEP_X+STEP_WIDTH*3
#define X4 START_STEP_X+STEP_WIDTH*4

#define Y0 0
#define Y1 STEP_HEIGH
#define Y2 STEP_HEIGH*2
#define Y3 STEP_HEIGH*3
#define Y4 STEP_HEIGH*4


#define ON 1
#define OFF 0

#define C 60
#define D 62
#define E 64
#define F 65
#define G 67
#define A 69
#define B 71


class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
		
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		
    
    //GUI-Slider
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    float value_threshold;
    float temp;
    
    //Font系
    ofTrueTypeFont	font;
    
    //映像系
    ofVideoGrabber camera;
    ofImage image_fullcolor;
    ofxCvGrayscaleImage image_grayscale;
    
    ofImage image;
    ofImage ofimage_recognition;
    
    ofxOcrad ocrad;
    ofxNHocr NHocr;
    
    
    bool debug_mode_window;
    bool record_flg;
    
    
    int roi_x = 200;
    int roi_y = 200;
    int roi_width = 50;
    int roi_height = 50;
    
    int NH_roi_x = 200;
    int NH_roi_y = 350;
    int NH_roi_width = 220;
    int NH_roi_height = 220;
    
};