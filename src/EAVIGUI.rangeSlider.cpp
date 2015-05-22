//
//  EAVIGUI.rangeSlider.cpp
//  
//
//  Created by Simon on 22/05/2015.
//
//

#include "EAVIGUI.rangeSlider.h"


namespace EAVIGUI {

    RangeSlider::RangeSlider(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, ofTrueTypeFont *_font, string _text, ofColor _textcolour, ofColor _backgroundColour, ofColor _sliderColour)
    : Slider(_listener, _id, _x, _y, _w, _h, _font, _text, _textcolour, _backgroundColour, _sliderColour) {

     
        mMinLim = 0.2;
        mMaxLim = 0.8;
        mRange = mMaxLim - mMinLim;
        
        int slw = (w - 10);
        mMinTab.set(1 + slw * mMinLim, h * 0.7 , 8, h * 0.3);
        mMaxTab.set(1 + slw * mMaxLim, h * 0.7 , 8, h * 0.3);
        mSlideBar.set(5, 0, slw, h *0.3);
        
        mMinAdj = false;
        
    }
    
    void RangeSlider::drawToBuffer() {
        
        ofPushStyle();
        ofFill();
        ofSetColor(backgroundColour);
        ofRect(5,0, w - 10, h * 0.7);
        
        int slw = (w - 10);
        
        ofSetColor(sliderColour);
        ofRect(5 + slw * mMinLim ,0, slw * mRange * value, h * 0.7);
        ofSetColor(255);
        drawAdjuster(5 + slw * mMinLim, h * 0.7 , 4, h * 0.3);
        drawAdjuster(5 + slw * mMaxLim, h * 0.7 , 4, h * 0.3);

        ofSetColor(colour);
        font->drawString(text, 5, font->getLineHeight());
        ofPopStyle();
    }
    
    void RangeSlider::drawAdjuster(int x, int y, int _w, int _h){
        
        ofPushMatrix();
            ofTranslate(x, y);
            ofBeginShape();
                ofVertex(-_w/2, _h *0.3);
                ofVertex(0, 0);
                ofVertex(_w/2, _h * 0.3);
                ofVertex(_w/2,_h);
                ofVertex(-_w/2,_h);
            ofEndShape(true);
        ofPopMatrix();
        
    }
    
    void RangeSlider::touchDown(ofTouchEventArgs &touch) {
        
            touchTarget = touch.id;
        
        if(mSlideBar.inside(touch.x, touch.y)){
            moveSlider(touch);
            Label::touchDown(touch);
        }else if(mMinTab.inside(touch.x, touch.y)){
            mMinLim = (touch.x+5)/(w-10);
            invalidate();
            mMinAdj = true;
        }
        
        
    }
    
    void RangeSlider::touchMoved(ofTouchEventArgs &touch) {
        
        if (touch.id == touchTarget) {
            
            if(mSlideBar.inside(touch.x, touch.y)){
                cout << touch.x << "," << touch.y << endl;
                Label::touchMoved(touch);
                moveSlider(touch);
            }else if(mMinAdj){
                mMinLim = (touch.x+5)/(w-10);
                invalidate();
            }

        }
    }
    
}