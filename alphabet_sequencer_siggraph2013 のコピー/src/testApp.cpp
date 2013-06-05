

#include "testApp.h"
#include "soundcv.h"


//--------------------------------------------------------------
void testApp::setup(){

    
    
    ///// setup gui-slider ////////////////////////////////////////////////////////////////
    gui = new ofxUICanvas(0,CAMHEIGH,CAMWIDTH, 300);
    gui->addWidgetDown(new ofxUILabel("*** Alphabet Sequencer ***", OFX_UI_FONT_LARGE));
    gui->addSlider("Threshold", 0.0, 255.0, 30, 250.0, 20.0);
    gui->addWidgetDown(new ofxUISlider(250,20,60.0,800.0,6.0,"TEMP"));
    
    //vector<string> hnames; hnames.push_back("Grand Piano"); hnames.push_back("Guiter"); hnames.push_back("Drums");hnames.push_back("test1");hnames.push_back("test2");
	//gui->addWidgetDown(new ofxUIRadio(20, 20, "Instruments", hnames, OFX_UI_ORIENTATION_HORIZONTAL));
    
    //gui->addWidgetDown(new ofxUIButton(20, 20, false, "record"));
    gui->addWidgetDown(new ofxUIButton(20, 20, false, "ALL RESET"));
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    
    //------------------------------------------------setup font
    font.loadFont("font/NewMedia Fett.ttf", 15);
    
    //------------------------------------------------timeline
    ofSetFrameRate(30); //更新を秒間120コマ(fps)
 
    camera.setVerbose(true);
    camera.initGrabber(CAMWIDTH,CAMHEIGH);
    
    midiout.openPort(0);
    time.setup(4,4);
    
    //image.loadImage("2.jpg");
}


//--------------------------------------------------------------
void testApp::update(){

  ofSetWindowTitle("Alphabet Sequencer");
    
	ofBackground(100,100,100);
    camera.update();
    time.update(temp);
    
    //scorecv[time.getStep_now()].update();
    //instrumentcv.update();
    
    image_fullcolor.clear();
    image_grayscale.clear();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    camera.draw(0, 0);
    //image.draw(CAMWIDTH, 0);
    
    int step_now = time.getStep_now();
    int step_x_now = time.getStep_x_now();
    int step_y_now = time.getStep_y_now();
    
    int prev_step_now;
    if (step_now == 0){
        prev_step_now = 15;
    }
    else{
        prev_step_now = step_now -1;
    }
    
        
    /////////////////////// setup image
    image_fullcolor.allocate(CAMWIDTH, CAMHEIGH, OF_IMAGE_COLOR);
    image_fullcolor.setFromPixels(camera.getPixels(), CAMWIDTH, CAMHEIGH, OF_IMAGE_COLOR);
    image_fullcolor.setImageType(OF_IMAGE_GRAYSCALE);
    
    image_grayscale.allocate(CAMWIDTH, CAMHEIGH);
    image_grayscale.setFromPixels(image_fullcolor);
    image_grayscale.threshold(value_threshold);
    
    
    
    /////////////////////// scorecvにroiした画像データのポインタを渡す.
    int _x = START_STEP_X+time.getStep_x_now()*STEP_WIDTH+10;
    int _y = time.getStep_y_now()*STEP_WIDTH+10;
    int _w = 95;
    int _h = 95;
  
    
    /////////////////////// scorecv
    scorecv[step_now].setImage_ocrad(_x, _y, _w, _h, image_grayscale.getPixels());
    instrumentCv.setImage_ocrad(0, SET_INSTRUMENTS_CARD_POSITION_Y, SET_INSTRUMENTS_CARD_POSITION_WIDTH, STEP_WIDTH-10, image_grayscale.getPixels());
    REC.setImage_ocrad(0, SET_REC_RESET_CARD_POSITION_Y,SET_INSTRUMENTS_CARD_POSITION_WIDTH,STEP_WIDTH-10, image_grayscale.getPixels());

    int instrument = instrumentCv.getInstrument();
    int pitch_now = scorecv[step_now].getPitch_now();
    if (instrument == 4){
        pitch_now = pitch_now - 12;
    }
    
    
    if (time.note_on_flg[step_now] == true){
        scoredata[step_now].setMidiInfo(instrument, pitch_now, 64, scorecv[step_now].getPitch_set_flg());
    }

    
    /// 各NoteOn,NoteOffのタイミングでscorecv[step_now]情報を格納
    
    /// rec scoredata recflg
    if (REC.getRecord_flg() == true){
        for (int i = 0; i < 16; i++){
            if (scoredata[i].getPitch_set_flg(instrument) == true && rec_scoredata[i].getRec_flg(instrument) == false){
                rec_scoredata[i].setMidiInfo(instrument, scoredata[i].getPitch(instrument), 64, true);
                rec_scoredata[i].setRec_flg(instrument, true);
            }
            else if (scoredata[i].getPitch_set_flg(instrument) == true && rec_scoredata[i].getRec_flg(instrument) == true){
                rec_scoredata[i].setMidiInfo(instrument, scoredata[i].getPitch(instrument), 64, true);
            }
            
            else if (scoredata[i].getPitch_set_flg(instrument) == false && rec_scoredata[i].getRec_flg(instrument) == false){
                rec_scoredata[i].setMidiInfo(instrument, -1, 0, false);
                rec_scoredata[i].setRec_flg(instrument, false);
            }
        }
    }
    
    /// reset scoredata ree_flg
    if (REC.getReset_flg() == true && REC.getRecord_flg() == false){
        for (int i = 0; i < 16; i++){
                rec_scoredata[i].setMidiInfo(instrument, -1, 0, false);
                rec_scoredata[i].setRec_flg(instrument, false);
        }
    }
    
    
    
    ////////////////////////// sound scoredata
    
    /// NoteOff
    ///now playing
    if (time.note_off_flg[prev_step_now] == true){
        ///rec_scoredata
        for (int i = 0; i < INSTRUMENTS; i++){
            if (rec_scoredata[prev_step_now].getPitch_set_flg(i+1) == true){
                if (rec_scoredata[prev_step_now].getRec_flg(i+1) == true){
                    midiout.sendNoteOff(i+1, rec_scoredata[prev_step_now].getPitch(i+1));
                }
            }
        }
        
        if (scoredata[prev_step_now].getPitch_set_flg(scoredata[prev_step_now].getChannel()) == true){
            midiout.sendNoteOff(scoredata[prev_step_now].getChannel(), scoredata[prev_step_now].getPitch(scoredata[prev_step_now].getChannel()),0);
        }
    }
    
    
    /// NoteOn
    
    /// now playing
    if (time.note_on_flg[step_now] == true){
        /// rec_scoredata
        for (int i = 0; i < INSTRUMENTS; i++){
            if (rec_scoredata[step_now].getPitch_set_flg(i+1) == true){
                if (rec_scoredata[step_now].getRec_flg(i+1) == true){
                    midiout.sendNoteOn(i+1, rec_scoredata[step_now].getPitch(i+1));
                }
            }
        }
        if (scoredata[step_now].getPitch_set_flg(instrument) == true){
            midiout.sendNoteOn(instrument, scoredata[step_now].getPitch(instrument));
        }
    }
  
    
    
    
    
    /// draw debug window
    
    if (debug_mode_window == true){
        
        image.clear();
        
        image_grayscale.draw(0, 0);
        scorecv[step_now].image_threshold_roi.draw(CAMWIDTH+10, 390);
        instrumentCv.image_threshold_roi.draw(CAMWIDTH+10, 0);
        REC.image_threshold_roi.draw(CAMWIDTH+10, 130);
        

        char str_ocr_alphabet[64];
        sprintf(str_ocr_alphabet, "Alphabet = %s", scorecv[step_now].ofxocrad.str_result);
        ofDrawBitmapString(str_ocr_alphabet, CAMWIDTH+10,CAMHEIGH+20);
        sprintf(str_ocr_alphabet, "%s", instrumentCv.ofxocrad.str_result);
        ofDrawBitmapString(str_ocr_alphabet, CAMWIDTH+10,STEP_WIDTH+10);
        sprintf(str_ocr_alphabet, "%s", REC.ofxocrad.str_result);
        ofDrawBitmapString(str_ocr_alphabet, CAMWIDTH+10,STEP_WIDTH*2+20);
      
      
        
        /////////////////////// 確認のためにdraw

        char comment[64];
        int draw_bitmap_x = ofGetWindowWidth()-340;
        
        char str_rec_scoredata[16][64];
        ///// rec_scoredataの描画
        char num[16][64];
        char rec[16][256];
        sprintf(comment, "rec_data[0]-[15].(instrument[key_press]:%d)",debug_window_ch);
        ofDrawBitmapString(comment, draw_bitmap_x, 15);
        
        for (int i = 0; i<16; i++){
            sprintf(num[i], "[%d]",i);
            sprintf(rec[i], "pitch:%d  pitch_flg:%d  rec_flg:%d",rec_scoredata[i].getPitch(debug_window_ch),rec_scoredata[i].getPitch_set_flg(debug_window_ch),rec_scoredata[i].getRec_flg(debug_window_ch));
            ofDrawBitmapString(num[i], draw_bitmap_x, 15*(i+2));
            ofDrawBitmapString(rec[i], draw_bitmap_x+40, 15*(i+2));
          
        }
        
        /////scoredataの描画
        char score[16][256];
        sprintf(comment, "scoredata[0]-[15].(instrument_now:%d)",instrument);
        ofDrawBitmapString(comment, draw_bitmap_x, 285);
        for (int i = 0; i <16; i++){
          sprintf(score[i], "Pitch:%d  Pitch_set_flg:%d",scoredata[i].getPitch(instrument),scoredata[i].getPitch_set_flg(instrument));
          ofDrawBitmapString(num[i], draw_bitmap_x, 300+15*i);
          ofDrawBitmapString(score[i], draw_bitmap_x+40, 300+15*i);          
        }
        
      char str_debug[64];
      sprintf(str_debug, "%d",instrumentCv.struda(instrumentCv.ofxocrad.str_result,"Guitar"));
      ofDrawBitmapString(str_debug, ofGetWindowWidth()-100,
                                 ofGetWindowHeight()-100);
    }
    
    
    ///// infomationの描画
    char info[16][256];
    sprintf(info[0], "ofGetFrameRate() = %f", ofGetFrameRate());
    sprintf(info[1], "time.getStep_now() = %d", time.getStep_now());
    sprintf(info[2], "time.getStep_x_now = %d", time.getStep_x_now());
    sprintf(info[3], "time.getStep_y_now = %d", time.getStep_y_now());
    sprintf(info[4], "instrument = %d", instrument);
    sprintf(info[5], "REC.getRecord_flg() = %d", REC.getRecord_flg());
    sprintf(info[6], "reset.getReset_flg() = %d", reset.getReset_flg());
    for (int i = 0; i < 7; i ++){
        ofDrawBitmapString(info[i], 350, 500+15*(i));
    }
    
  /*
    ///// デバッグ操作方法の描画
    char text[16][256];
    sprintf(text[0], "number key:choose debug instrument");
    sprintf(text[1], "f:Change FullScreen Mode");
    sprintf(text[2], "s:Close Debug Window");
    sprintf(text[3], "d:Open Debug Window");
    sprintf(text[4], "< Key Press >");
    for (int i = 0; i < 5; i ++){
        ofDrawBitmapString(text[i], 10, ofGetWindowHeight()-(15*i+10));
    }
   */
    ofSetColor(255, 255, 255);
    
    
    /////////////////////// ポジションの描画
    ofSetColor(0,255,0,100);
    ofFill();
    ofSetLineWidth(5);
    ofRect(START_STEP_X+time.getStep_x_now()*STEP_WIDTH, time.getStep_y_now()*STEP_WIDTH, STEP_WIDTH, STEP_WIDTH);
    ofSetColor(255, 255, 255);
    
    if (REC.getRecord_flg()==true){
        ofSetColor(255,0,0,100);
        ofFill();
        ofRect(0, SET_REC_RESET_CARD_POSITION_Y, SET_INSTRUMENTS_CARD_POSITION_WIDTH, STEP_WIDTH);
        ofSetColor(255, 255, 255);
    }
    if (REC.getReset_flg() == true){
        ofSetColor(0,0,255,100);
        ofFill();
        ofRect(0, 280, 160, STEP_WIDTH);
        ofSetColor(255, 255, 255);
    }
    for (int i = 0; i < 16; i++){
        
        int x,y;
        
        if (i == 0){
            x = 0, y =0;
        }
        else if (i == 1){
            x = 1, y =0;
        }
        else if (i == 2){
            x = 2, y =0;
        }
        else if (i == 3){
            x = 3, y =0;
        }
        else if (i == 4){
            x = 0, y =1;
        }
        else if (i == 5){
            x = 1, y =1;
        }
        else if (i == 6){
            x = 2, y =1;
        }
        else if (i == 7){
            x = 3, y =1;
        }
        else if (i == 8){
            x = 0, y =2;
        }
        else if (i == 9){
            x = 1, y =2;
        }
        else if (i == 10){
            x = 2, y =2;
        }
        else if (i == 11){
            x = 3, y =2;
        }
        else if (i == 12){
            x = 0, y =3;
        }
        else if (i == 13){
            x = 1, y =3;
        }
        else if (i == 14){
            x = 2, y =3;
        }
        else if (i == 15){
            x = 3, y =3;
        }
        
        if (rec_scoredata[i].getRec_flg(instrument)== true){                                   ofSetColor(255,0,0,100);
            ofFill();
            ofRect(START_STEP_X+STEP_WIDTH*x, STEP_WIDTH*y, STEP_WIDTH, STEP_WIDTH);
            ofSetColor(255, 255, 255);
            }
    }
    

    
    
        
}

//--------------------------------------------------------------
void testApp::exit(){
    
    for (int i = 0; i < INSTRUMENTS; i++){
        midiout.sendNoteOff(i,0,0);
        midiout.sendNoteOff(i,60,0);
        midiout.sendNoteOff(i,62,0);
        midiout.sendNoteOff(i,64,0);
        midiout.sendNoteOff(i,65,0);
        midiout.sendNoteOff(i,67,0);
        midiout.sendNoteOff(i,69,0);
        midiout.sendNoteOff(i,71,0);
    }
    midiout.closePort();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'd' || key == 'D' ){
        debug_mode_window = true;
    }
    else if (key == 's' || key == 'S' ){
        debug_mode_window = false;
        image.loadImage("2.jpg");
    }
    
    if (key == 'f' || key == 'F' ){
        ofToggleFullscreen();
    }

    switch (key) {
        case '1':
            debug_window_ch = 1;
            break;
        case '2':
            debug_window_ch = 2;
            break;
        case '3':
            debug_window_ch = 3;
            break;
        case '4':
            debug_window_ch = 4;
            break;
        case '5':
            debug_window_ch = 5;
            break;
        case '6':
            debug_window_ch = 6;
            break;
        case '7':
            debug_window_ch = 7;
            break;
        case '8':
            debug_window_ch = 8;
            break;
        case '9':
            debug_window_ch = 9;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    
       
    
    if(e.widget->getName() == "Threshold")
    {
        ofxUISlider *slider = (ofxUISlider*)e.widget;
        value_threshold = slider->getScaledValue();
    }
    
    if(e.widget->getName() == "TEMP")
    {
        ofxUISlider *slider = (ofxUISlider*)e.widget;
        temp = slider->getScaledValue();
    }
    
    /*
    if(e.widget->getName() == "record")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        
        if (int(button->getValue()) == 1){
            record_flg = ON;
        }
        else {
            record_flg = OFF;
        }
        printf("%d", record_flg );
    }*/
    
    if(e.widget->getName() == "ALL RESET")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        
        if (int(button->getValue()) == 1){
          midiout.sendNoteOff(4,48,0);
          midiout.sendNoteOff(4,50,0);
          midiout.sendNoteOff(4,51,0);
          midiout.sendNoteOff(4,52,0);
          midiout.sendNoteOff(4,53,0);
          midiout.sendNoteOff(4,54,0);
          midiout.sendNoteOff(4,55,0);
          midiout.sendNoteOff(4,56,0);
          midiout.sendNoteOff(4,57,0);
          midiout.sendNoteOff(4,58,0);
          midiout.sendNoteOff(4,59,0);
          

            for (int i = 0; i < 16; i++) {
              midiout.sendNoteOff(i,60,0);
              midiout.sendNoteOff(i,62,0);
              midiout.sendNoteOff(i,64,0);
              midiout.sendNoteOff(i,65,0);
              midiout.sendNoteOff(i,67,0);
              midiout.sendNoteOff(i,69,0);
              midiout.sendNoteOff(i,71,0);
              midiout.sendNoteOff(i,57,0);
              midiout.sendNoteOff(i,58,0);
              midiout.sendNoteOff(i,59,0);
              
                for (int j = 0; j < 16; j++) {
                    rec_scoredata[i].setMidiInfo(j+1, -1, 0, false);
                    rec_scoredata[i].setRec_flg(j+1, false);
                }
            }
        }
    }
    
    /*
    if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        
        if (name == "Grand Piano" && int(toggle->getValue()) == 1 ){
            instrument = 1;
        }
        else if (name == "Guiter" && int(toggle->getValue()) == 1 ){
            instrument = 2;
        }
        else if (name == "Drums" && int(toggle->getValue()) == 1 ){
            instrument = 3;
        }
        else if (name == "test1" && int(toggle->getValue()) == 1 ){
            instrument = 4;
        }
        else if (name == "test2" && int(toggle->getValue()) == 1 ){
            instrument = 5;
        }
        
        printf("instrument = %d", instrument );
    }*/
}