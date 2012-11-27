#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include <canvas/rect.h>

class ImagePlayerFocus : public ImagePlayer {
protected:
    std::string property() const { return "focus"; };
};


TEST_F( ImagePlayerFocus, invalid_values ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	//	Invalid values
	ASSERT_FALSE ( _player->setProperty( "focus", "invalidValue") );
	ASSERT_FALSE ( _player->setProperty( "focusBorderColor", "invalidColourValue") );
	ASSERT_FALSE ( _player->setProperty( "selBorderColor", "invalidColourValue") );
	ASSERT_FALSE ( _player->setProperty( "focusBorderWidth", 1.1f) );
	ASSERT_FALSE ( _player->setProperty( "focusBorderWidth", -1.0f) );
	ASSERT_FALSE ( _player->setProperty( "focusBorderWidth", "InvalidValue") );
	ASSERT_FALSE ( _player->setProperty( "focusBorderTransparency", 2.0f) );
	ASSERT_FALSE ( _player->setProperty( "focusSrc", util::getImageName("invalidValue")) );
	ASSERT_FALSE ( _player->setProperty( "focusSelSrc", util::getImageName("invalidValue")) );
}

TEST_F( ImagePlayerFocus,  with_focus_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );	
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );		
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  without_focus_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );	
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );			
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "focus", false ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  on_off_on ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) ); 
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "focus", false ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );	
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  selected_without_focus ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  with_focus ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );			
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  without_focus) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", false ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  with_focus_white ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "white") );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus_white" ) ) );
}

TEST_F( ImagePlayerFocus,  with_focus_selected ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true) );
	ASSERT_TRUE ( _player->setProperty( "selBorderColor", "green") );
		
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  with_focus_selected__with_source_and_border ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSelSrc", util::getImageName("green.jpg")) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", -10) );
 	ASSERT_TRUE ( _player->setProperty( "selBorderColor", "blue") );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true) );

	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus_selected__with_source_and_border" ) ) );
}

TEST_F( ImagePlayerFocus, selected_when_no_focus) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", false) );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true) );
		
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus, borderWidthInZero) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 0) );
	
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus, borderWidthIn10) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );
	
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("withBorderWidthIn10" ) ) );
}

TEST_F( ImagePlayerFocus, borderWidthInMinus10 ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", -10) );
	
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("withBorderWidthInMinus10" ) ) );
}

TEST_F( ImagePlayerFocus,  withBorderTransparencyIn0) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );	
	ASSERT_TRUE ( _player->setProperty( "focusBorderTransparency", 0.0f) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  withTotalBorderTransparency) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderTransparency", 1.0f) );
		
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus, withBorderTransparency) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderTransparency", 0.5f) );
		
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("50%BoderTransparency" ) ) );
}

TEST_F( ImagePlayerFocus, focus_src) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSrc", util::getImageName("green.jpg")) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("green_square_with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  srcWithoutFocus) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", false) );
	ASSERT_TRUE ( _player->setProperty( "focusSrc", util::getImageName("green.jpg")) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("without_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  selSrcNoSelected) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );			
	ASSERT_TRUE ( _player->setProperty( "focusSelSrc", util::getImageName("green.jpg")) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  srcAndSelSrcSelected) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSrc", util::getImageName("yellow.jpg")) );
	ASSERT_TRUE ( _player->setProperty( "focusSelSrc", util::getImageName("green.jpg")) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("green_square_with_focus" ) ) );
}

TEST_F( ImagePlayerFocus,  selSrc) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSelected", true) );
	ASSERT_TRUE ( _player->setProperty( "focusSelSrc", util::getImageName("green.jpg")) );
	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("green_square_with_focus" ) ) );
}

TEST_F( ImagePlayerFocus, limit_left_top_corner ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_left_top_corner" ) ) );
}

TEST_F( ImagePlayerFocus, limit_top_side ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(310,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_top_side" ) ) );
}

TEST_F( ImagePlayerFocus, limit_right_top_corner ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_right_top_corner" ) ) );
}

TEST_F( ImagePlayerFocus, limit_right_side ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,238,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_right_side" ) ) );
}

TEST_F( ImagePlayerFocus, limit_right_bottom_corner ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,476,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_right_bottom_corner" ) ) );
}

TEST_F( ImagePlayerFocus, limit_bottom_side) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(310,476,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_bottom_side" ) ) );
}

TEST_F( ImagePlayerFocus, limit_left_bottom_corner) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,476,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_left_bottom_corner" ) ) );
}

TEST_F( ImagePlayerFocus, limit_left_side) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,238,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "focus", true ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "focusBorderWidth", 10) );	
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("limit_left_side" ) ) );
}

