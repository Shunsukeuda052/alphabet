//
//  scale.cpp
//  20121210_Alphabet_Sequencer_ofxMidi_ver.4.0
//
//  Created by 卯田 駿介 on 2012/12/11.
//
//

#include "scale.h"
#include "testApp.h"

scale::scale()
{

}
scale::~scale()
{

}

void scale::draw()
{
    int i;
    int height = CAMHEIGH/7;
    
    for (i = 0; i < 4; i++) {
        ofFill();
        ofSetColor(0, 0, 255, 60);
        ofRect(0, height*i*2, CAMWIDTH, height);
    }
}