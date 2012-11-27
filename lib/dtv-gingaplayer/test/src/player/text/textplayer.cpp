#include "textplayer.h"
#include "../../util.h"
#include "../../../../src/player/textplayer.h"
#include "../../../../src/device.h"

std::string TextPlayer::playerType() const {
	return "TextPlayer";
}

std::string TextPlayer::property() const {
	return "basic";
}

player::type::type TextPlayer::type() const {
	return player::type::text;
}

TEST_F(TextPlayer, Text_basic) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, Text_basic2) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,620,476) ));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("basic2")));
}

TEST_F(TextPlayer, Text_normal) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "normal"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, Text_size_big) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontSize", 22));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("size_big")));
}

TEST_F(TextPlayer, Text_bold) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontWeight", "bold"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("bold")));
}

TEST_F(TextPlayer, Text_italic) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontStyle", "italic"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("italic")));
}

TEST_F(TextPlayer, DISABLED_Text_smallcaps) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "small-caps"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("smallcaps")));
}

TEST_F(TextPlayer, DISABLED_Text_bold_italic_smallcaps_size) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(_player->setProperty("fontStyle", "italic"));
	ASSERT_TRUE(_player->setProperty("fontWeight", "bold"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "small-caps"));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("bold_italic_smallcaps_size")));
}

TEST_F(TextPlayer, Text_empty) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("empty.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("empty")));
}

TEST_F(TextPlayer, Text_big) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("big.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("big")));
}

TEST_F(TextPlayer, Text_small) {

	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 1));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("small")));

}

TEST_F(TextPlayer, Text_fontFamily_DejaVuSans) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_DejaVuSans")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, Text_fontFamily_normal) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "normal"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_DejaVuSans")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, Text_fontFamily_size_big) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontSize", 22));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_size_big")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("size_big")));
}

TEST_F(TextPlayer, Text_fontFamily_bold) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontWeight", "bold"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_bold")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("bold")));
}

TEST_F(TextPlayer, Text_fontFamily_italic) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontStyle", "italic"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_italic")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("italic")));
}

TEST_F(TextPlayer, DISABLED_Text_fontFamily_smallcaps) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "small-caps"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_smallcaps")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("smallcaps")));
}

TEST_F(TextPlayer, DISABLED_Text_fontFamily_DejaVuSans_bold_italic_smallcaps_size) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(_player->setProperty("fontStyle", "italic"));
	ASSERT_TRUE(_player->setProperty("fontWeight", "bold"));
	ASSERT_TRUE(_player->setProperty("fontVariant", "small-caps"));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_DejaVuSans_bold_italic_smallcaps_size")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("bold_italic_smallcaps_size")));
}

TEST_F(TextPlayer, Text_fontFamily_empty) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("empty.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("empty")));
}

TEST_F(TextPlayer, Text_fontFamily_big) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("big.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("big")));
}

TEST_F(TextPlayer, Text_fontFamily_small) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 1));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("small")));
}

TEST_F(TextPlayer, Text_test) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("test.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 10));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("test")));
}

TEST_F(TextPlayer, invalid_source) {
	ASSERT_FALSE(_player->setProperty("src", util::getImageName("invalid.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_FALSE(play(_player));
}

TEST_F(TextPlayer, play) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,500, 375)));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	play(_player);
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("play")));
}

TEST_F(TextPlayer, stop) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,500, 375)));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	play(_player);
	_player->stop();
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("stopped")));
}

TEST_F(TextPlayer, invalid_file) {
	ASSERT_FALSE(_player->setProperty("src", util::getImageName("invalid.png")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,500, 375)));
	ASSERT_FALSE(play(_player));
}

TEST_F(TextPlayer, play_after_stop) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,500, 375)));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("play")));

	_player->stop();
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("stopped")));

	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,500, 375)));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("play")));
}

TEST_F(TextPlayer, set_src_file) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
}

TEST_F(TextPlayer, set_src_http) {
	ASSERT_TRUE(_player->setProperty("src", "http://path/some.txt"));
}

TEST_F(TextPlayer, set_src_https) {
	ASSERT_TRUE(_player->setProperty("src", "https://path/some.txt"));
}

TEST_F(TextPlayer, set_src_rtsp) {
	ASSERT_FALSE(_player->setProperty("src", "rtsp://path/some.txt"));
}

TEST_F(TextPlayer, set_src_rtp) {
	ASSERT_FALSE(_player->setProperty("src", "rtp://path/some.txt"));
}

TEST_F(TextPlayer, set_src_mirror) {
	ASSERT_FALSE(_player->setProperty("src", "ncl-mirror://path/some.txt"));
}

TEST_F(TextPlayer, set_src_sbtvd) {
	ASSERT_FALSE(_player->setProperty("src", "sbtvd-ts://path/some.txt"));
}

TEST_F(TextPlayer, set_src_invalid_schema) {
	ASSERT_FALSE(_player->setProperty("src", "invalid://path/some.txt"));
}

TEST_F(TextPlayer, fontFamily_multiples_families) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "DejaVuSans,Verdana"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_DejaVuSans")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, fontFamily_multiples_families2) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "Verdana,DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_Verdana")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("basic")));
}

TEST_F(TextPlayer, fontFamily_multiples_families3) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("some.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontFamily", "sdkgdfg,adfsdgdfd,DejaVuSans"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("fontFamily_DejaVuSans")));
	ASSERT_FALSE(util::compareImages(canvas(), getExpectedPath("basic")));
}


TEST_F(TextPlayer, Text_basic_ISO88591) {
	ASSERT_TRUE(_player->setProperty("src", util::getImageName("sample_chars_ISO-8859-1.txt")));
	ASSERT_TRUE(_player->setProperty("bounds", canvas::Rect(0,0,720, 576)));
	ASSERT_TRUE(_player->setProperty("fontColor", "red"));
	ASSERT_TRUE(_player->setProperty("fontSize", 14));
	ASSERT_TRUE(play(_player));
	ASSERT_TRUE(util::compareImages(canvas(), getExpectedPath("basic_ISO88591")));
}
