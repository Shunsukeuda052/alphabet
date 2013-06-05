//
//  soundcv.h
//  20121226_Alphabet_Sequencer_ofxMidi_ver.5.2_practice
//
//  Created by 卯田 駿介 on 2012/12/27.
//
//

#ifndef ___0121226_Alphabet_Sequencer_ofxMidi_ver_5_2_practice__soundcv__
#define ___0121226_Alphabet_Sequencer_ofxMidi_ver_5_2_practice__soundcv__



#include <iostream>
#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxOcrad.h"
#include "ofxMidi.h"
#include "opencv/cv.h"


#include "opencv/highgui.h"
#include <stdlib.h>

class _time{

public:
    _time();
    ~_time();
    void setup(int _step_x_kazu, int _step_y_kazu);
    void update(float _temp);
    void draw();
    
    bool check_loop; //loopした時にtrueを返す.
    
    int getStep_x_now();
    int getStep_y_now();
    int getStep_now();
    
    int step_width;
    int step_heigh;
    
    bool note_off_flg[16];//各stepのnoteoffのタイミングにtrueを返します.
    bool note_on_flg[16];
    
private:
    
    float temp;//テンポ
    
    int step_x_kazu;    //x座標のstepの数
    int step_y_kazu;    //y座標のstepの数
    int step_kazu;  //stepの総数
    
    int step_now;   //現在のstepの値を返します.
    int step_x_now; //現在のstep_xの値を返します.
    int step_y_now; //現在のstep_yの値を返します.
    
    float time_now;   //プログラムが起動してからの時間
    float step_time;    //1拍子の長さ
    float step_time_loop;    //
    float step_time_previous;  //loopした時に時間をプログラム時間を格納
    
    int getPitch();
    
};






//////////////////////////////   scoredata


class _scoredata{
    
public:
    
    _scoredata();
    ~_scoredata();
    
    void setup();
    void update();
    void draw();
    
    void setMidiInfo(int _channel, int _pitch, int _velocity, bool _pitch_set_flg);
    
    void setRec_flg(int _channel, bool _rec_flg);
    
    int getChannel();
    int getPitch(int _channel);
    int getVelocity(int _channel);
    bool getPitch_set_flg(int _channel);
    bool getRec_flg(int _channel);
  
  int set_channel;

private:
    
    struct _channel{
        int pitch;
        int velocity;
        bool pitch_set_flg;
        bool rec_flg;
    }channel[16];
    
    //int set_channel;
    
        
};






//////////////////////////////   scorecv

class _scorecv{
public:
    _scorecv();
    ~_scorecv();
    
    
    void setImage_ocrad(int _x, int _y, int _w, int _h, const unsigned char *_image_threshold);
    int getPitch_now();
    bool getPitch_set_flg();
    int getInstrument();
    bool getRecord_flg();
    bool getReset_flg();
  int struda(char *str_ocrad, char *str_search);
    
    ofxCvGrayscaleImage image_threshold,image_threshold_roi;
    ofImage image_ocrad;
    ofxOcrad ofxocrad;
    
private:
    
    
    
    int pitch_now;  //認識したピッチを返す.その他は -1
    bool pitch_set_flg;  //pitchが入力されたらtrueを返す.
    int instrument;
    bool record_flg;
    bool reset_flg;
};


#endif /* defined(___0121226_Alphabet_Sequencer_ofxMidi_ver_5_2_practice__soundcv__) */
