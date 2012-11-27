#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

class SurfaceMeasureText : public Surface {
protected:
    std::string getSubDirectory() const { return "MeasureText"; }
};

#define THRESHOLD 2

// Set font and then draw a basic text in the surface 
TEST_F( SurfaceMeasureText, basic_setFont){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255,0,0));
    f.size(10);
    s->setFont(f);
    ASSERT_TRUE(s->measureText("Hola Mundo !!!", tam));

    ASSERT_TRUE( abs(tam.h-13) <= THRESHOLD );
    ASSERT_TRUE( abs(tam.w-67) <= THRESHOLD );

    getCanvas()->destroy( s );
}

// Draw a basic text in the surface
TEST_F( SurfaceMeasureText, basic){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255,0,0));    
    ASSERT_TRUE(s->measureText("Hola Mundo !!!", tam));

    ASSERT_TRUE( abs(tam.h-13) <= THRESHOLD );
    ASSERT_TRUE( abs(tam.w-67) <= THRESHOLD );

    getCanvas()->destroy( s );
}

// Call measureText with empty text
TEST_F( SurfaceMeasureText, null){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setFont(f);
    s->measureText("", tam);
    ASSERT_TRUE(tam.h == 0);
    ASSERT_TRUE(tam.w == 0);

    getCanvas()->destroy( s );
}
