
#include "testApp.h"


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
    
    //image.loadImage("2.jpg");
}


//--------------------------------------------------------------
void testApp::update(){

  ofSetWindowTitle("Alphabet Sequencer");
    
	ofBackground(100,100,100);
    camera.update();
        
}

//--------------------------------------------------------------
void testApp::draw(){
    
    camera.draw(0, 0);
    //image.draw(CAMWIDTH, 0);
    
    
        
    /////////////////////// setup image
    image_fullcolor.allocate(CAMWIDTH, CAMHEIGH, OF_IMAGE_COLOR);
    image_fullcolor.setFromPixels(camera.getPixels(), CAMWIDTH, CAMHEIGH, OF_IMAGE_COLOR);
    image_fullcolor.setImageType(OF_IMAGE_GRAYSCALE);
    image_grayscale.setFromPixels(image_fullcolor);
    image_grayscale.threshold(value_threshold);
    
    
    
    
        
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
}