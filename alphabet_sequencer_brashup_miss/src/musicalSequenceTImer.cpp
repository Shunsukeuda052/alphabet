//
//  musicalSequenceTImer.cpp
//  alphabet_sequencer_brashup
//
//  Created by 卯田 駿介 on 2013/05/10.
//
//

#include "musicalSequenceTimer.h"

musicalSequenceTimer::musicalSequenceTimer(){
    bIsFirstPositionChange = false;
    time_start = ofGetElapsedTimeMillis();
    time_step = 500;
    number_of_division = 16;
}

musicalSequenceTimer::~musicalSequenceTimer(){
}

void musicalSequenceTimer::update(){
    static int previous_step_position=0;
    time_sequencer = (ofGetElapsedTimeMillis()-time_start)%(number_of_division*time_step);
    if( previous_step_position != getSequencerPosition() ){
        bIsFirstPositionChange = true;
    }
    else{
        bIsFirstPositionChange = false;
    }
    previous_step_position = getSequencerPosition();
}

int musicalSequenceTimer::getSequencerPosition(){
    return time_sequencer/time_step;
}

void musicalSequenceTimer::draw(int x, int y){
    char str[64];
    sprintf(str,"sequence time: %d\n", time_sequencer);
    ofDrawBitmapString(str, x,y);
}