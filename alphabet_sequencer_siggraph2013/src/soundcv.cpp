//
//  soundcv.cpp
//  20121226_Alphabet_Sequencer_ofxMidi_ver.5.2_practice
//
//  Created by 卯田 駿介 on 2012/12/27.
//
//

#include "soundcv.h"
#include "testApp.h"

_time::_time()
{
    step_now = 0;
    step_x_now = 0;
    step_y_now = 0;
    time_now = ofGetElapsedTimeMillis();
    step_time = 0;
    step_time_loop = 0;
    step_time_previous = 0;
    temp = 0;
}

_time::~_time()
{
}

void _time::setup(int _step_x_kazu, int _step_y_kazu)
{

    step_x_kazu = _step_x_kazu;
    step_y_kazu = _step_y_kazu;
    step_kazu = step_x_kazu*step_y_kazu;
    
    step_width = (CAMWIDTH-160)/step_x_kazu;
    step_heigh = CAMHEIGH/step_y_kazu;
}


void _time::update(float _temp)
{
    temp = _temp;
    step_time = 1000*(60/temp);
    time_now = ofGetElapsedTimeMillis();
    step_time_loop = time_now - step_time_previous;
    
    
    ///// stepがloopしたかどうか
    if (step_time < step_time_loop){
        step_time_previous = time_now;
        check_loop = true;
    }
    else {
        check_loop = false;
    }
    
    ///// step_nowの値
    if (check_loop == true){
        step_now = step_now + 1;
        if ( step_now == 16 ){
            step_now = 0;
        }
    }

    ///// step_x_nowの値
    step_x_now = step_now%step_x_kazu;
    
    ///// step_y_nowの値
    for (int i = 0; i < step_y_kazu; i++ ){
        if ( step_x_kazu*i <= step_now && step_now < step_x_kazu*(i+1) ){
            step_y_now = i;
        }
    }
    
    if ( check_loop == true ){
        if (step_now == 0){
            note_off_flg[15] = true;
            note_on_flg[0] = true;
        }
        else if (step_now == 1){
            note_off_flg[0] = true;
            note_on_flg[1] = true;
        }
        else if (step_now == 2){
            note_off_flg[1] = true;
            note_on_flg[2] = true;
        }
        else if (step_now == 3){
            note_off_flg[2] = true;
            note_on_flg[3] = true;
        }
        else if (step_now == 4){
            note_off_flg[3] = true;
            note_on_flg[4] = true;
        }
        else if (step_now == 5){
            note_off_flg[4] = true;
            note_on_flg[5] = true;
        }
        else if (step_now == 6){
            note_off_flg[5] = true;
            note_on_flg[6] = true;
        }
        else if (step_now == 7){
            note_off_flg[6] = true;
            note_on_flg[7] = true;
        }
        else if (step_now == 8){
            note_off_flg[7] = true;
            note_on_flg[8] = true;
        }
        else if (step_now == 9){
            note_off_flg[8] = true;
            note_on_flg[9] = true;
        }
        else if (step_now == 10){
            note_off_flg[9] = true;
            note_on_flg[10] = true;
        }
        else if (step_now == 11){
            note_off_flg[10] = true;
            note_on_flg[11] = true;
        }
        else if (step_now == 12){
            note_off_flg[11] = true;
            note_on_flg[12] = true;
        }
        else if (step_now == 13){
            note_off_flg[12] = true;
            note_on_flg[13] = true;
        }
        else if (step_now == 14){
            note_off_flg[13] = true;
            note_on_flg[14] = true;
        }
        else if (step_now == 15){
            note_off_flg[14] = true;
            note_on_flg[15] = true;
        }
    }
    
    else {
        for (int i = 0; i < 16; i++){
            note_off_flg[i] = false;
            note_on_flg[i] = false;
        }
    }
    
   // printf("step_now　= %d　\tstep_x_now = %d　\tstep_y_now = %d　\n",step_now, step_x_now,step_y_now);
    
}

void _time:: draw(){
    
}


int _time:: getStep_x_now()
{
    return step_x_now;
}

int _time:: getStep_y_now()
{
    return step_y_now;
}

int _time:: getStep_now()
{
    return step_now;
}





/////////////////////////////////////////// _sequencer

_scoredata:: _scoredata()
{
    set_channel = 0;
    
    for (int i = 0; i < 16; i++){
        channel[i].pitch = -1;
        channel[i].velocity = -1;
        channel[i].pitch_set_flg = false;
        channel[i].rec_flg = false;
    }
    
}

_scoredata:: ~_scoredata()
{
}

void _scoredata::setup()
{
}

void _scoredata::update()
{
}

void _scoredata::draw()
{
}

void _scoredata::setMidiInfo(int _channel, int _pitch, int _velocity, bool _pitch_set_flg)
{
    set_channel = _channel;
    channel[set_channel].pitch = _pitch;
    channel[set_channel].velocity = _velocity;
    channel[set_channel].pitch_set_flg = _pitch_set_flg;
}

void _scoredata:: setRec_flg(int _channel, bool _rec_flg )
{
    channel[_channel].rec_flg = _rec_flg;
}

int _scoredata:: getChannel()
{
    return set_channel;
}

int _scoredata:: getPitch(int _channel)
{
    return channel[_channel].pitch;
}

int _scoredata:: getVelocity(int _channel)
{
    return channel[_channel].velocity;
}

bool _scoredata:: getPitch_set_flg(int _channel)
{
    return channel[_channel].pitch_set_flg;
}

bool _scoredata:: getRec_flg(int _channel)
{
    return channel[_channel].rec_flg;
}


/////////////////////////////////////////// scorecv

_scorecv:: _scorecv()
{
    pitch_now = -1;
    pitch_set_flg = false;
    instrument = 0;
    record_flg = false;
    reset_flg = false;
}

_scorecv:: ~_scorecv()
{
    image_threshold.clear();
    //image_threshold_roi.clear();
    image_ocrad.clear();
}

void _scorecv:: setImage_ocrad(int _x, int _y, int _w, int _h, const unsigned char *_image_threshold)
{
    image_threshold.allocate(CAMWIDTH, CAMHEIGH);
    image_threshold.setFromPixels(_image_threshold, CAMWIDTH, CAMHEIGH);
    image_threshold.setROI(_x, _y, _w, _h);
    image_threshold_roi.setFromPixels(image_threshold.getRoiPixels(),_w,_h);
    
    image_ocrad.setFromPixels(image_threshold_roi.getPixels(), _w, _h, OF_IMAGE_GRAYSCALE);
    
    ofxocrad.setOfImage(&image_ocrad);
    
    if ( strncmp(ofxocrad.str_result, "Do",2) == 0 || strncmp(ofxocrad.str_result, "Oo",2) == 0){
        pitch_now = 60;
        pitch_set_flg = true;
    }

    else if ( strncmp(ofxocrad.str_result, "Re",2) == 0){
        pitch_now = 62;
        pitch_set_flg = true;
    }
    
    else if ( strstr(ofxocrad.str_result, "Mi") > 0 || strstr(ofxocrad.str_result, "mi") > 0){
        pitch_now = 64;
        pitch_set_flg = true;
    }
    
    else if ( strstr(ofxocrad.str_result, "Fa") > 0 || strstr(ofxocrad.str_result, "fa") > 0){
        pitch_now = 65;
        pitch_set_flg = true;
    }
    else if ( strstr(ofxocrad.str_result, "So") > 0 || strstr(ofxocrad.str_result, "so") > 0){
        pitch_now = 67;
        pitch_set_flg = true;
    }
    else if ( strstr(ofxocrad.str_result, "La") > 0){
        pitch_now = 69;
        pitch_set_flg = true;
    }
  
    else if ( strstr(ofxocrad.str_result, "Si") > 0 || strstr(ofxocrad.str_result, "si") > 0){
        pitch_now = 71;
        pitch_set_flg = true;
    }
    
    else if ( strncmp(ofxocrad.str_result, "c", 1) == 0 || strncmp(ofxocrad.str_result, "C", 1) == 0  || strncmp(ofxocrad.str_result, ".c", 2) == 0){
        pitch_now = 60;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "D", 1) == 0  || strncmp(ofxocrad.str_result, ".D", 2) == 0){
        pitch_now = 62;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "E", 1) == 0  || strncmp(ofxocrad.str_result, ".E", 2) == 0){
        pitch_now = 64;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "F", 1) == 0  || strncmp(ofxocrad.str_result, ".F", 2) == 0){
        pitch_now = 65;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "G", 1) == 0  || strncmp(ofxocrad.str_result, ".G", 2) == 0){
        pitch_now = 67;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "A", 1) == 0 || strncmp(ofxocrad.str_result, ".A", 2) == 0){
        pitch_now = 69;
        pitch_set_flg = true;
    }
    else if ( strncmp(ofxocrad.str_result, "B", 1) == 0  || strncmp(ofxocrad.str_result, ".B", 2) == 0){
        pitch_now = 71;
        pitch_set_flg = true;
    }
    else {
        pitch_now = -1;
        pitch_set_flg = false;
    }

}

int _scorecv:: getPitch_now()
{
    return pitch_now;
}

bool _scorecv:: getPitch_set_flg()
{
    return pitch_set_flg;
}

int _scorecv:: getInstrument()
{
  
    if ( strncmp(ofxocrad.str_result, "Piano", 5) == 0 || strncmp(ofxocrad.str_result, "piano", 5) == 0){
        instrument = 1;
    }
    else if ( strncmp(ofxocrad.str_result, "Guitar", 5) == 0){
        instrument = 2;
    }
    else if ( strncmp(ofxocrad.str_result, "trumpet", 7) == 0){
        instrument = 3;
    }
    else if ( strncmp(ofxocrad.str_result, "Drum", 4) == 0 || strncmp(ofxocrad.str_result, "DRUM", 4) == 0 || strncmp(ofxocrad.str_result, "ORUM", 4) == 0 || strncmp(ofxocrad.str_result, "Drum", 4) == 0){
        instrument = 4;
    }
    else if ( strncmp(ofxocrad.str_result, "Violin", 6) == 0 ){
        instrument = 5;
    }
    else if ( strncmp(ofxocrad.str_result, "Sy", 2) == 0){
        instrument = 6;
    }
  
    return instrument;
}

bool _scorecv:: getRecord_flg()
{
    if ( strncmp(ofxocrad.str_result, "REC", 3) == 0 || strncmp(ofxocrad.str_result, "REc", 3) == 0){
        record_flg = true;
    }
    else {
        record_flg = false;
    }
    return record_flg;
}

bool _scorecv:: getReset_flg()
{
    if ( strncmp(ofxocrad.str_result, "RESET", 5) == 0 || strncmp(ofxocrad.str_result, "RESEl", 5) == 0){
        reset_flg = true;
    }
    else {
        reset_flg = false;
    }
    return reset_flg;
}

int _scorecv::struda(char *str_ocrad, char *str_search){
  int count;
  
  count = 0;
  for (int i =0 ; i < strlen(str_ocrad); i++) {
    if( str_ocrad[i] == str_search[i] ){
      count++;
    }
  }
  return count;
}
