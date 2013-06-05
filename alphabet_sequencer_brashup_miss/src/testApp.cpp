#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    ///// setup gui-slider ////////////////////////////////////////////////////////////////
    gui = new ofxUICanvas(CAMWIDTH,0,CONTROL_PANEL_WIDTH, CAMHEIGHT);
    gui->addWidgetDown(new ofxUILabel("Alphabet Sequencer", OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUILabel("Design by Shunsuke Uda", OFX_UI_FONT_SMALL));
    gui->addSlider("Threshold", 0.0, 255.0, 30, 150.0, 20.0);
    gui->addSlider("TEMP", 0.0, 255.0, 30, 150.0, 20.0);
    //gui->addWidgetDown(new ofxUISlider(250,20,60.0,800.0,6.0,"TEMP"));
    //gui->addWidgetDown(new ofxUIButton(20, 20, false, "ALL RESET"));
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    
    
    camera.setVerbose(true);
    camera.initGrabber(CAMWIDTH,CAMHEIGHT);
    
    GRID_WINDOW_WIDTH = GRID_WINDOW_X_END-GRID_WINDOW_X_START;
    GRID_WINDOW_HEIGHT = GRID_WINDOW_Y_END-GRID_WINDOW_Y_START;
    
    for( int i = 0; i < 16; i++ ){
        object_position[i].x = GRID_WINDOW_X_START+GRID_WINDOW_WIDTH/4*(i%4)+GRID_WINDOW_WIDTH/4/2;
        object_position[i].y = GRID_WINDOW_Y_START+GRID_WINDOW_HEIGHT/4*(i/4)+GRID_WINDOW_HEIGHT/4/2;
    }
}


//--------------------------------------------------------------
void testApp::update(){
    mst.update();
    camera.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    camera.draw(0, 0);
    
    image_fullcolor.allocate(CAMWIDTH, CAMHEIGHT, OF_IMAGE_COLOR);
    image_fullcolor.setFromPixels(camera.getPixels(), CAMWIDTH, CAMHEIGHT, OF_IMAGE_COLOR);
    image_fullcolor.setImageType(OF_IMAGE_GRAYSCALE);
    image_grayscale.setFromPixels(image_fullcolor);
    image_grayscale.threshold(value_threshold);
    image_grayscale.draw(0, 0);
    
    
    
    
    ofLine(GRID_WINDOW_X_START, GRID_WINDOW_Y_START, GRID_WINDOW_X_START, GRID_WINDOW_Y_END);
    ofLine(GRID_WINDOW_X_END, GRID_WINDOW_Y_START, GRID_WINDOW_X_END, GRID_WINDOW_Y_END);


    
    ofCircle(object_position[mst.getSequencerPosition()].x,
             object_position[mst.getSequencerPosition()].y,
             50);
    char str[64];
    sprintf(str, "%d", mst.getSequencerPosition());
    ofSetColor(255,255,255);
    ofDrawBitmapString(str,
                       object_position[mst.getSequencerPosition()].x,
                       object_position[mst.getSequencerPosition()].y);
    sprintf(str, "%d", scaleCV.getScale());

}

//--------------------------------------------------------------
void testApp::exit(){

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
};