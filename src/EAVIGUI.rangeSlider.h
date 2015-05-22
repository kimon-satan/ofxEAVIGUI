//
//  EAVIGUI.rangeSlider.h
//  
//
//  Created by Simon Katan on 22/05/2015.
//
//

#ifndef __SlApp__EAVIGUI__rangeSlider
#define __SlApp__EAVIGUI__rangeSlider

#include "EAVIGUI.slider.h"
#include <iostream>

using namespace std;

namespace EAVIGUI {

    class RangeSlider : public Slider {
    public:

        RangeSlider(InterfaceListener *_listener, int _id, int _x, int _y, int _w, int _h, ofTrueTypeFont *_font, string _text, ofColor _textcolour, ofColor _backgroundColour, ofColor sliderColour);
        
        void drawToBuffer();
        void drawAdjuster(int x, int y, int _w, int _h);
        void touchDown(ofTouchEventArgs &touch);
        void touchMoved(ofTouchEventArgs &touch);

    protected:
        
        float mMinLim, mMaxLim, mRange;
        ofRectangle mMinTab, mMaxTab, mSlideBar;
        bool mMinAdj;
    };
    
}

#endif /* defined(__SlApp__EAVIGUI__rangeSlider) */
