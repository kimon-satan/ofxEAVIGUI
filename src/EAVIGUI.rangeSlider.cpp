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

     
        mMinLim = 0;
        mMaxLim = 1.0;
        mRange = mMaxLim - mMinLim;
        
        mSlideBar.set(5, 0, w - 10, h * 0.7);
        
        mMinTab.set(5 - 6, h * 0.7, 12, h * 0.3);
        mMaxTab.set(mSlideBar.x + mSlideBar.width - 6, h * 0.7, 12, h * 0.3);
       
        
        mMinAdj = false;
        mMaxAdj = false;
        
    }
    
    void RangeSlider::drawToBuffer() {
        
        ofPushStyle();
        ofFill();
        ofSetColor(backgroundColour);
        ofRect(5,0, w - 10, h * 0.7);
        
        int slw = (w - 10);
        
        ofSetColor(sliderColour);
        float lp = mMinTab.x + mMinTab.width/2;
        ofRect(lp ,0, (mSlideBar.width * value) - lp + 5, h * 0.7);
        ofSetColor(255);
        drawAdjuster(lp, h * 0.7 , 4, h * 0.3, ofColor(255,0,0));
        drawAdjuster(mMaxTab.x + mMaxTab.width/2, h * 0.7 , 4, h * 0.3, ofColor(0,255,0));

        ofSetColor(colour);
        font->drawString(text, 5, font->getLineHeight());
        ofPopStyle();
        
        /*ofNoFill();
        ofSetColor(255);
        ofRect(mMinTab);
        ofRect(mMaxTab);*/
    }
    
    void RangeSlider::drawAdjuster(int x, int y, int _w, int _h, ofColor c){
        
        ofPushStyle();
        ofSetColor(c);
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
        ofPopStyle();
        
    }
    
    void RangeSlider::touchDown(ofTouchEventArgs &touch) {
        
        touchTarget = touch.id;
        
        if(mSlideBar.inside(touch.x, touch.y)){
            
            float v = (touch.x-5)/mSlideBar.width;
            value = ofClamp(v, mMinLim, mMaxLim);
            invalidate();
            
        }else if(mMinTab.inside(touch.x, touch.y)){

            mMinAdj = true;
            mMaxAdj = false;
            
        }else if(mMaxTab.inside(touch.x, touch.y)){

            mMinAdj = false;
            mMaxAdj = true;
        }
        
        
    }
    
    void RangeSlider::touchMoved(ofTouchEventArgs &touch) {
        
        if (touch.id == touchTarget) {
            
            Label::touchMoved(touch);
            
            if(mSlideBar.inside(touch.x, touch.y)){
            
                value = (touch.x-5)/mSlideBar.width;

                
            }else if(mMinAdj){
                
                float v = touch.x;
                v = ofClamp(v, 5.0f, w - 5.0f);
                v = min(mMaxTab.x - 10, v);
                mMinLim = (v-5)/mSlideBar.width;
                mMinTab.x = v - mMinTab.width/2;
                mRange = mMaxLim - mMinLim;

                
            }else if(mMaxAdj){
                
                float v = touch.x;
                v = ofClamp(v, 5.0f, w - 5.0f);
                v = max(mMinTab.x + mMinTab.width/2 + 10, v);
                mMaxLim = (v-5)/mSlideBar.width;
                mMaxTab.x = v - mMaxTab.width/2;
                mRange = mMaxLim - mMinLim;

            }
            
            
            value = ofClamp(value, mMinLim, mMaxLim);
            invalidate();

        }
        
    }
    
    void RangeSlider::touchUp(ofTouchEventArgs &touch){
        
        
        //Slider::touchUp(touch);
        touchTarget = -1;
        mMinAdj = false;
        mMaxAdj = false;
        invalidate();
        
    }
    
    void RangeSlider::setNormalisedValue(float f)
    {
        value = ofMap(f, 0.0f,1.0f, mMinLim, mMaxLim);
        invalidate();
    }
    
    float RangeSlider::getNormalisedValue()
    {
        return ofMap(value, mMinLim, mMaxLim, 0.0f, 1.0f);
    }
    
    void RangeSlider::setClampedValue(float f)
    {
        value = ofClamp(f, mMinLim, mMaxLim);
        invalidate();
    }
    
    float RangeSlider::getClampedValue()
    {
        return value;
    }
    
    float RangeSlider::getMinLim(){return mMinLim;}
    float RangeSlider::getMaxLim(){return mMaxLim;}
    
 
    
}