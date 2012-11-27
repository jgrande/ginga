#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class SurfaceDrawText : public Surface {
protected:
    std::string getSubDirectory() const { return "DrawText"; }
};

// Draw a basic text in the surface
TEST_F( SurfaceDrawText, basic){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "basic" ) ) );

    getCanvas()->destroy(s);
}

// Draw a basic text in the surface and not set font

TEST_F(SurfaceDrawText, basic_not_set_font) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));

    ASSERT_TRUE(s->drawText(canvas::Point(250, 250), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "basic_not_set_font" ) ) );

    getCanvas()->destroy(s);
}

// Draw a basic text in the surface without text

TEST_F(SurfaceDrawText, basic_without_text) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE( s->drawText(canvas::Point(x, y), "" ));
    ASSERT_TRUE(util::compareImages(getCanvas(), "nothing"));

    getCanvas()->destroy(s);
}

// Draw bold text in the surface
TEST_F( SurfaceDrawText, bold){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.bold(true);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "bold" ) ) );
    ASSERT_FALSE(util::compareImages(getCanvas(), getExpectedPath( "basic" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size
TEST_F( SurfaceDrawText, size){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(24);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "size" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size 1
TEST_F( SurfaceDrawText, size_1){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(1);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "size_1" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size 380
TEST_F(SurfaceDrawText, size_380) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(380);
    s->setFont(f);
	int descent = 97;

	tam.h = 475;
	tam.w = 596;
	
    y = (((s->getSize().h - tam.h-descent) / 2) + tam.h );
    x = ((s->getSize().w - tam.w) / 2);
	
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "II--"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "size_380" ) ) );

    getCanvas()->destroy(s);
}

// Draw italic text in the surface
TEST_F( SurfaceDrawText, italic){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.italic(true);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "italic" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with Tiresias family font
TEST_F( SurfaceDrawText, family){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "family" ) ) );

    getCanvas()->destroy(s);
}

// Draw smallcaps text in the surface

TEST_F(SurfaceDrawText, DISABLED_smallcaps) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.smallCaps(true);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "smallcaps" ) ) );

    getCanvas()->destroy(s);
}

// Draw bold,italic,smallcaps text in the surface with specific size and family font

TEST_F(SurfaceDrawText, DISABLED_bold_italic_smallcaps_size_family) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.bold(true);
    f.italic(true);
    f.smallCaps(true);
    f.size(24);
    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "bold_italic_smallcaps_size_family" ) ) );

    getCanvas()->destroy(s);
}

// Draw text on the top right corner of the surface
TEST_F( SurfaceDrawText, top_right){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = 0 + tam.h;
    x = s->getSize().w - tam.w;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "top_right" ) ) );

    getCanvas()->destroy(s);
}

// Draw text on the top left corner of the surface
TEST_F( SurfaceDrawText, top_left){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = 0 + tam.h;

    ASSERT_TRUE(s->drawText(canvas::Point(0, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "top_left" ) ) );

    getCanvas()->destroy(s);
}

// Draw text on the bottom right corner of the surface
TEST_F( SurfaceDrawText, bottom_right){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = 570;
    x = s->getSize().w - tam.w;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "bottom_right" ) ) );

    getCanvas()->destroy(s);
}

// Draw text on the bottom left corner of the surface
TEST_F( SurfaceDrawText, bottom_left){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = 570;
    x = 0;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "bottom_left" ) ) );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (top-left)
TEST_F(SurfaceDrawText, outside_top_left) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = -tam.h;
    x = -tam.w;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (top-right)
TEST_F(SurfaceDrawText, outside_top_right) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = -tam.h;
    x = s->getSize().w;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (bottom-right)

TEST_F(SurfaceDrawText, outside_bottom_right) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = s->getSize().h + 1;
    x = s->getSize().w + 1;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );


    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (bottom-left)
TEST_F(SurfaceDrawText, outside_bottom_left) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = s->getSize().h + 1;
    x = -tam.w;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );


    getCanvas()->destroy(s);
}

// Draw a text with some part outside of the surface (bottom-left)
TEST_F(SurfaceDrawText, some_part_outside_bottom_left) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = s->getSize().h - tam.h + 1;
    x = -1;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text with some part outside of the surface (bottom-right)
TEST_F(SurfaceDrawText, some_part_outside_bottom_right) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = s->getSize().h - tam.h + 1;
    x = s->getSize().w - tam.w + 1;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text with some part outside of the surface (top-right)
TEST_F(SurfaceDrawText, some_part_outside_top_right) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = -1;
    x = s->getSize().w - tam.w + 1;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text with some part outside of the surface (top-left)
TEST_F(SurfaceDrawText, some_part_outside_top_left) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = -1;
    x = -1;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (top)
TEST_F(SurfaceDrawText, completely_out_top) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = -tam.h;
    x = (s->getSize().w / 2)-(tam.w / 2);
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (bottom)
TEST_F(SurfaceDrawText, completely_out_bottom) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = s->getSize().h;
    x = (s->getSize().w / 2)-(tam.w / 2);
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (left)
TEST_F(SurfaceDrawText, completely_out_left) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = (s->getSize().h / 2)-(tam.h / 2);
    x = -(s->getSize().w);
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a text completely out of the surface (right)
TEST_F(SurfaceDrawText, completely_out_right) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = (s->getSize().h / 2)-(tam.h / 2);
    x = s->getSize().w;
    ASSERT_FALSE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!") );

    getCanvas()->destroy(s);
}

// Draw a basic text in the surface
TEST_F( SurfaceDrawText, DejaVuSans_basic){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));

    ASSERT_TRUE( util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_basic" ) ) );
    ASSERT_FALSE( util::compareImages(getCanvas(), getExpectedPath( "basic" ) ) );

    getCanvas()->destroy(s);
}

// Draw a basic text in the surface without text
TEST_F(SurfaceDrawText, DejaVuSans_basic_without_text) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE( s->drawText(canvas::Point(x, y), "" ));

    ASSERT_TRUE(util::compareImages(getCanvas(), "nothing" ) );

    getCanvas()->destroy(s);
}

// Draw bold text in the surface
TEST_F( SurfaceDrawText, DejaVuSans_bold){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.bold(true);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));

    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_bold" ) ) );
    ASSERT_FALSE(util::compareImages(getCanvas(), getExpectedPath( "bold" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size
TEST_F( SurfaceDrawText, DejaVuSans_size){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(24);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_size" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size 1
TEST_F( SurfaceDrawText, DejaVuSans_size_1){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(1);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_size_1" ) ) );

    getCanvas()->destroy(s);
}

// Draw text in the surface with specific size 460
TEST_F(SurfaceDrawText, DejaVuSans_size_400) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.size(400);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
	int descent = 94;
	tam.h = 467;
	tam.w = 524;
	
    y = ((s->getSize().h - tam.h -descent) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;

    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "II--"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_size_400" ) ) );

    getCanvas()->destroy(s);
}

// Draw italic text in the surface
TEST_F( SurfaceDrawText, DejaVuSans_italic){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.italic(true);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_italic" ) ) );

    getCanvas()->destroy(s);
}

// Draw smallcaps text in the surface
TEST_F( SurfaceDrawText, DISABLED_DejaVuSans_smallcaps){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.smallCaps(true);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_smallcaps" ) ) );

    getCanvas()->destroy(s);
}

// Draw bold,italic,smallcaps text in the surface with specific size and family font
TEST_F( SurfaceDrawText, DISABLED_DejaVuSans_bold_italic_smallcaps_size_family){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    canvas::Size tam;
    int y, x;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    f.bold(true);
    f.italic(true);
    f.smallCaps(true);
    f.size(24);
    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    s->measureText("Hola Mundo !!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "DejaVuSans_bold_italic_smallcaps_size_family" ) ) );

    getCanvas()->destroy(s);
}

// Draw a basic text with newline in the surface 
TEST_F(SurfaceDrawText, with_newline) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!! \n Hola ginga!!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!! \n Hola ginga!!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "with_newline" ) ) );

    getCanvas()->destroy(s);   
}

// Draw a basic text with indentation in the surface
TEST_F(SurfaceDrawText, with_indentation) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    s->measureText("Hola Mundo !!!\tHola ginga!!!", tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), "Hola Mundo !!!\tHola ginga!!!"));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "with_indentation" ) ) );

    getCanvas()->destroy(s);   
}

// Test markDirty after drawing a text
TEST_F( SurfaceDrawText, markDirty_drawText ) {
	canvas::Rect rect(0,0,720,576);
	canvas::Surface* s = getCanvas()->createSurface( rect );

	ASSERT_TRUE( s != NULL );
	s->autoFlush(true);
	s->setColor(canvas::Color(255,0,0));
	s->setFont(canvas::Font() );
	getCanvas()->flush();

	canvas::Size size;
	canvas::Point p1(50,50), p2(100,100);

	ASSERT_TRUE( s->measureText("Hola", size ) );
	ASSERT_TRUE( s->drawText( p1, "Hola" ) );
	ASSERT_TRUE( s->drawText( p2, "" ) );

	std::vector<canvas::Rect> dirtyRegions = getCanvas()->dirtyRegions();

	ASSERT_FALSE( dirtyRegions.empty() );
	ASSERT_TRUE( dirtyRegions.size() == 1 );

	//canvas::Rect r(50,50,size.w,size.h);
	canvas::Rect r(50,41,size.w,size.h); // 41 = baseline - ascent + 1
	ASSERT_TRUE( dirtyRegions.at(0) == r );

	getCanvas()->destroy( s );
}

// Draw a basic text in ISO 8859-1 in the surface
TEST_F( SurfaceDrawText, basic_ISO88591){
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;
    int y, x;
    canvas::Size tam;

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));
    s->setFont(f);
    const std::string str("вгде");
    s->measureText(str, tam);
    y = ((s->getSize().h - tam.h) / 2) + tam.h;
    x = (s->getSize().w - tam.w) / 2;
    ASSERT_TRUE(s->drawText(canvas::Point(x, y), str));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "basic_ISO88591" ) ) );

    getCanvas()->destroy(s);
}

// Draw a basic text in ISO 8859-1 in the surface and not set font

TEST_F(SurfaceDrawText, basic_at_point_ISO88591) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));

    ASSERT_TRUE( s != NULL );
    s->autoFlush(true);
    s->setColor(canvas::Color(255, 0, 0));

    const std::string str("вгде");
    ASSERT_TRUE(s->drawText(canvas::Point(250, 250), str));
    ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "basic_not_set_font_ISO88591" ) ) );

    getCanvas()->destroy(s);
}

static std::string getTestFile( const std::string &file ) {
	const char *root=getenv( "DEPOT" );
	if (!root) {
		root = "/";
	}
	fs::path path(root);
	path /= "lib";
	path /= "dtv-canvas";
	path /= "test";
	path /= "images";
	path /= file.c_str();
	
	return path.string();
}

// Test charset encoding ISO-8859-1
TEST_F( SurfaceDrawText, encoding_ISO_8859_1 ) {
	canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
	canvas::Font f;
	f.size(15);
	int y=30, x=0;

	ASSERT_TRUE( s != NULL );
	s->setCharsetEncoding( canvas::charset::ISO_8859_1 );
	s->autoFlush(true);
	s->setColor(canvas::Color(255, 0, 0));
	s->setFont(f);

	std::string str("");
	std::ifstream ifs( getTestFile("iso_8859_1.txt").c_str() );
	while (ifs.good()) {
		char c;
		c = (char) ifs.get();
		ASSERT_TRUE(s->drawText(canvas::Point(x, y), str+c));
		x+=10;
		if (x>700) {
			x=0;
			y+=20;
		}
	}
	ifs.close();

	ASSERT_TRUE(util::compareImages(getCanvas(), getExpectedPath( "encoding_ISO_8859_1" ) ) );

	getCanvas()->destroy(s);
}
