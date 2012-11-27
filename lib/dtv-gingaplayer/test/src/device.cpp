#include "player.h"
#include "../../src/device.h"
#include "../../src/types.h"

class Device : public Player {
	virtual std::string playerType() const { return ""; }
	virtual std::string property() const { return ""; }
	virtual player::type::type type() const { return player::type::image; }
};

TEST_F( Device, DISABLED_download_jpg ) {
	std::string file;
	std::string url("http://novalettres.files.wordpress.com/2011/08/tux.jpg");
	ASSERT_TRUE( device()->download(url, file) );
	ASSERT_TRUE( file.find(".jpg") != std::string::npos );
}

TEST_F( Device, DISABLED_download_png ) {
	std::string file;
	std::string url("http://3.bp.blogspot.com/-rCaw1GuwrDA/TaEo3ek6x0I/AAAAAAAAAJM/Yojz-Drqf_M/s320/tux.png");
	ASSERT_TRUE( device()->download(url, file) );
	ASSERT_TRUE( file.find(".png") != std::string::npos );
}

TEST_F( Device, DISABLED_download_gif ) {
	std::string file;
	std::string url("http://upload.wikimedia.org/wikipedia/commons/e/e6/Walking_baby_tux.gif");
	ASSERT_TRUE( device()->download(url, file) );
	ASSERT_TRUE( file.find(".gif") != std::string::npos );
}
