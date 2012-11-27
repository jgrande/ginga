#include "surface.h"
#include "../util.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"

#define THRESHOLD 3

static bool compare( int value1, int value2, int tolerance ) {
    return abs(value1-value2) <= tolerance;
}

TEST_F(Surface, font_ascent_without_font_family_setted_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare (s->fontAscent(), 20, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted_bold_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(20);
    f.bold(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare(s->fontAscent(), 20, THRESHOLD ));
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.italic(true);
    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted_bold_and_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(20);
    f.bold(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) ); 
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(20);
    f.smallCaps(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted_bold_italic_and_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(20);
    f.bold(true);
    f.smallCaps(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 10, THRESHOLD) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_without_font_family_setted_size50) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    f.size(50);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 50, THRESHOLD) );
    
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_tiresias_family_setted_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_tiresias_family_setted_bold_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(20);
    f.bold(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_tiresias_family_setted_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.italic(true);
    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_tiresias_family_setted_bold_and_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(20);
    f.bold(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD) );
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_tiresias_family_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(20);
    f.smallCaps(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD ) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_tiresias_family_setted_bold_italic_and_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(20);
    f.bold(true);
    f.smallCaps(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 20, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_tiresias_family_setted) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 10, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_tiresias_family_setted_size50) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("Tiresias");
    f.families(families);
    f.size(50);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 50, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}



 TEST_F(Surface, font_ascent_with_dejavusans_family_setted_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    

    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_dejavusans_family_setted_bold_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(20);
    f.bold(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_dejavusans_family_setted_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.italic(true);
    f.size(20);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_dejavusans_family_setted_bold_and_italic_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(20);
    f.bold(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_dejavusans_family_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(20);
    f.smallCaps(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_dejavusans_family_setted_bold_italic_and_smallcaps_size20) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(20);
    f.bold(true);
    f.smallCaps(true);
    f.italic(true);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    
    
    ASSERT_TRUE( compare( s->fontAscent(), 19, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}


TEST_F(Surface, font_ascent_with_dejavusans_family_setted) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );

    
    ASSERT_TRUE( compare( s->fontAscent(), 10, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}



TEST_F(Surface, font_ascent_with_dejavusans_family_setted_size50) {
    canvas::Surface* s = getCanvas()->createSurface(canvas::Rect(0, 0, 720, 576));
    canvas::Font f;

    std::vector<std::string> families;
    families.push_back("DejaVuSans");
    f.families(families);
    f.size(50);
    s->setFont(f);
    
    ASSERT_TRUE( s != NULL );
    ASSERT_TRUE( compare( s->fontAscent(), 47, THRESHOLD ) );
    
    
    getCanvas()->destroy(s);   
}





