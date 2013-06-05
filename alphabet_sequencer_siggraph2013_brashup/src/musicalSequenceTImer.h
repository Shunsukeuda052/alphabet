//
//  musicalSequenceTImer.h
//  alphabet_sequencer_brashup
//
//  Created by 卯田 駿介 on 2013/05/10.
//
//

#ifndef __alphabet_sequencer_brashup__musicalSequenceTImer__
#define __alphabet_sequencer_brashup__musicalSequenceTImer__

#include <iostream>

#pragma once
#include "ofMain.h"

class musicalSequenceTimer{
public:
    musicalSequenceTimer();
    ~musicalSequenceTimer();
    bool bIsFirstPositionChange;
    void update();
    int getSequencerPosition();
    void draw(int x, int y);
private:
    int sequencer_position;
    int time_step;
    int time_sequencer;
    unsigned long long time_start;
    int number_of_division;
};

#endif /* defined(__alphabet_sequencer_brashup__musicalSequenceTImer__) */
