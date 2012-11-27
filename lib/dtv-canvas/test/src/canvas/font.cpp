#include <gtest/gtest.h>
#include "../../../src/font.h"
#include <algorithm>

TEST( font, default_constructor ) {
    canvas::Font f;
    std::vector<std::string> families = f.families();
    ASSERT_TRUE( std::find(families.begin(), families.end(), DEFAULT_FONT) != families.end() );
    ASSERT_TRUE( f.size() == 10);
    ASSERT_TRUE( f.bold() == false );
    ASSERT_TRUE( f.italic() == false);
    ASSERT_TRUE( f.smallCaps() == false);
  
}

TEST( font, constructor_from_string ) {
    canvas::Font f("DejaVuSans", 20);
    ASSERT_TRUE( f.size() == 20);
    ASSERT_TRUE( f.bold() == false );
    ASSERT_TRUE( f.italic() == false);
    ASSERT_TRUE( f.smallCaps() == false);
    ASSERT_TRUE( f.familiesAsString() == "DejaVuSans,Tiresias");
}

TEST( font, constructor_family_size ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Tiresias");
    canvas::Font f(familiesSet, 20);

    std::vector<std::string> familiesGet = f.families();
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Tiresias") != familiesGet.end() );
    ASSERT_TRUE( f.size() == 20);
    ASSERT_TRUE( f.bold() == false );
    ASSERT_TRUE( f.italic() == false);
    ASSERT_TRUE( f.smallCaps() == false);
  
}

TEST( font, set_bold_italic_small ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    canvas::Font f(familiesSet, 20);
    f.bold(true);
    f.italic(true);
    f.smallCaps(true);

    std::vector<std::string> familiesGet = f.families();
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Ubuntu-R") != familiesGet.end() );
    ASSERT_TRUE( f.size() == 20);
    ASSERT_TRUE( f.bold() == true );
    ASSERT_TRUE( f.italic() == true);
    ASSERT_TRUE( f.smallCaps() == true);
  
}

TEST( font, change_size ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    canvas::Font f(familiesSet, 20);
    f.size(25);

    std::vector<std::string> familiesGet = f.families();
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Ubuntu-R") != familiesGet.end() );
    ASSERT_TRUE( f.size() == 25);
  
}

TEST( font, change_family ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    canvas::Font f(familiesSet, 20);

    std::vector<std::string> newFamilies;
    newFamilies.push_back("Tiresias");
    f.families(newFamilies);
    
    std::vector<std::string> familiesGet = f.families();
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Tiresias") != familiesGet.end() );
    ASSERT_TRUE( f.size() == 20);

}

TEST( font, multiples_families ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    familiesSet.push_back("DejaVuSans");
    familiesSet.push_back("Tiresias");
    canvas::Font f(familiesSet, 20);

    std::vector<std::string> familiesGet = f.families();
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Ubuntu-R") != familiesGet.end() );
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "DejaVuSans") != familiesGet.end() );
    ASSERT_TRUE( std::find(familiesGet.begin(), familiesGet.end(), "Tiresias") != familiesGet.end() );
    ASSERT_TRUE( f.size() == 20);
}

TEST( font, familiesAsString ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    familiesSet.push_back("DejaVuSans");
    familiesSet.push_back("Tiresias");
    canvas::Font f(familiesSet, 20);

    ASSERT_TRUE( f.familiesAsString() == "Ubuntu-R,DejaVuSans,Tiresias");
}

TEST( font, familiesAsStringWithoutDefault ) {
    std::vector<std::string> familiesSet;
    familiesSet.push_back("Ubuntu-R");
    familiesSet.push_back("DejaVuSans");
    canvas::Font f(familiesSet, 20);

    ASSERT_TRUE( f.familiesAsString() == "Ubuntu-R,DejaVuSans,Tiresias");
}
