#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class ImagePlayerFit : public ImagePlayer {
protected:
    std::string property() const { return "fit"; };

    std::string getFitExpectedPath( std::string subProperty, std::string fileName ) const {
        fs::path root;
        root = getExpectedPath(subProperty);
        root /= fileName;
        return root.string();
    }
};

TEST_F( ImagePlayerFit, hidden_equal_size ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );		
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("hidden", "equal_size") ) );
}

TEST_F( ImagePlayerFit, hidden_smaller ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "smaller") ) );
}

TEST_F( ImagePlayerFit, hidden_bigger ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "bigger") ) );
}

TEST_F( ImagePlayerFit, hidden_equal_size_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("hidden", "equal_size" )  ) );
}

TEST_F( ImagePlayerFit, hidden_smaller_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "smaller") ) );
}

TEST_F( ImagePlayerFit, hidden_bigger_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "bigger") ) );
}

TEST_F( ImagePlayerFit, hidden_equal_size_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("hidden", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, hidden_smaller_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, hidden_bigger_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "bigger_alpha") ) );
}

TEST_F( ImagePlayerFit, hidden_equal_size_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("hidden", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, hidden_smaller_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,20) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "smaller_alpha") ) );
}

TEST_F( ImagePlayerFit, hidden_bigger_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("hidden", "bigger_alpha") ) );
}

TEST_F( ImagePlayerFit, fill_equal_size ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size") ) );
}

TEST_F( ImagePlayerFit, fill_default ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, fill_smaller ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, fill_bigger ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, fill_equal_size_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, fill_smaller_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, fill_bigger_dynamic) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, fill_equal_size_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_default_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_smaller_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_bigger_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_equal_size_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("fill", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_smaller_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, fill_bigger_alpha_dynamic) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ));
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","fill" ));
	ASSERT_TRUE ( util::compareImages(canvas(), getFitExpectedPath("fill", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_equal_size ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, meet_smaller ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,300) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, meet_bigger ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, meet_equal_size_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, meet_smaller_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, meet_bigger_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, meet_equal_size_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_smaller_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_bigger_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_equal_size_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_smaller_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_bigger_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meet" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_equal_size ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_smaller ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_bigger ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_equal_size_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_smaller_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_bigger_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_equal_size_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_smaller_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_bigger_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_equal_size_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_smaller_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, meet_best_bigger_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","meetBest" ) );
	ASSERT_TRUE ( util::compareImages( canvas(), getFitExpectedPath("meet_best", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_equal_size ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "equal_size") ) );
}

TEST_F( ImagePlayerFit, slice_smaller ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "smaller") ) );
}

TEST_F( ImagePlayerFit, slice_bigger ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, slice_equal_size_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 500,375) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "equal_size" ) ) );
}

TEST_F( ImagePlayerFit, slice_smaller_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 150,150) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "smaller" ) ) );
}

TEST_F( ImagePlayerFit, slice_bigger_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "bigger" ) ) );
}

TEST_F( ImagePlayerFit, slice_equal_size_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_smaller_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_bigger_alpha ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green" ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "bigger_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_equal_size_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 171,44) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "equal_size_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_smaller_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 100,20) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "smaller_alpha" ) ) );
}

TEST_F( ImagePlayerFit, slice_bigger_alpha_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("lifia.png") ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0, 720,576) ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "fit","slice" ) );
	ASSERT_TRUE( util::compareImages( canvas(), getFitExpectedPath("slice", "bigger_alpha" ) ) );
}
