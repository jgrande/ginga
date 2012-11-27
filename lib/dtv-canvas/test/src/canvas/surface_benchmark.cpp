#include "surface.h"
#include "../../../src/canvas.h"
#include "../../../src/surface.h"


static void flush1( canvas::Canvas *c ) {
	c->flush();
}

static void flush2( canvas::Canvas *c ) {
	c->flush();
}

static void flush3( canvas::Canvas *c ) {
	c->flush();
}

static void flush4( canvas::Canvas *c ) {
	c->flush();
}

static void flush5( canvas::Canvas *c ) {
	c->flush();
}

static void flush6( canvas::Canvas *c ) {
	c->flush();
}

static void flush7( canvas::Canvas *c ) {
	c->flush();
}

static void flush8( canvas::Canvas *c ) {
	c->flush();
}

static void flush9( canvas::Canvas *c ) {
	c->flush();
}

static void flush10( canvas::Canvas *c ) {
	c->flush();
}

static void flush11( canvas::Canvas *c ) {
	c->flush();
}

static void flush12( canvas::Canvas *c ) {
	c->flush();
}

static void flush13( canvas::Canvas *c ) {
	c->flush();
}

static void flush14( canvas::Canvas *c ) {
	c->flush();
}

static void flush15( canvas::Canvas *c ) {
	c->flush();
}


static void blitRect( const canvas::Rect &rect, const canvas::Color &color, canvas::Canvas *c ) {
    canvas::Surface* s = c->createSurface( rect );
    s->autoFlush(true);
    s->setColor( color );
    ASSERT_TRUE( s->fillRect( canvas::Rect(0, 0, rect.w, rect.h) ) );
    c->destroy(s);
}

canvas::Color blue = canvas::Color(0,0,255);
canvas::Color green = canvas::Color(0,255,0);
canvas::Color yellow = canvas::Color(255,255,0);
canvas::Color pink = canvas::Color(255,0,128);
canvas::Color violet = canvas::Color(128,64,255);

TEST_F( Surface, benchmark1 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 8, 8), blue, getCanvas() );
	flush1( getCanvas() );
}

TEST_F( Surface, benchmark2 ) {
	getCanvas()->flush();
        blitRect( canvas::Rect(0, 0, 72, 16), green, getCanvas() );
	flush2( getCanvas() );
}

TEST_F( Surface, benchmark3 ) {
	getCanvas()->flush();
        blitRect( canvas::Rect(0, 0, 720, 576), yellow, getCanvas() );
	flush3( getCanvas() );
}

TEST_F( Surface, benchmark4 ) {
	getCanvas()->flush();
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 2; ++j) {
			blitRect( canvas::Rect(8*i, 8*j, 8, 8), pink, getCanvas() );
		}
	}
	flush4( getCanvas() );
}

TEST_F( Surface, benchmark5 ) {
	getCanvas()->flush();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 36; ++j) {
			blitRect( canvas::Rect(72*i, 16*j, 72, 16), violet, getCanvas() );
		}
	}
	flush5( getCanvas() );
}

TEST_F( Surface, benchmark6 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 100, 10), blue, getCanvas() );
	flush6( getCanvas() );
}

TEST_F( Surface, benchmark7 ) {
	getCanvas()->flush();
	for (int i = 0; i < 10; ++i) {
		blitRect( canvas::Rect(0, i, 100, 1), green, getCanvas() );
	}
	flush7( getCanvas() );
}

TEST_F( Surface, benchmark8 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 72, 96), blue, getCanvas() );
	flush8( getCanvas() );
}

TEST_F( Surface, benchmark9 ) {
	getCanvas()->flush();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 6; ++j) {
			blitRect( canvas::Rect(72*i, 96*j, 72, 96), violet, getCanvas() );
		}
	}
	flush9( getCanvas() );
}

TEST_F( Surface, benchmark10 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 144, 96), blue, getCanvas() );
	flush10( getCanvas() );
}

TEST_F( Surface, benchmark11 ) {
	getCanvas()->flush();
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 6; ++j) {
			blitRect( canvas::Rect(144*i, 96*j, 144, 96), violet, getCanvas() );
		}
	}
	flush11( getCanvas() );
}

TEST_F( Surface, benchmark12 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 240, 192), blue, getCanvas() );
	flush12( getCanvas() );
}

TEST_F( Surface, benchmark13 ) {
	getCanvas()->flush();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			blitRect( canvas::Rect(240*i, 192*j, 240, 192), violet, getCanvas() );
		}
	}
	flush13( getCanvas() );
}

TEST_F( Surface, benchmark14 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 360, 288), blue, getCanvas() );
	flush14( getCanvas() );
}

TEST_F( Surface, benchmark15 ) {
	getCanvas()->flush();
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			blitRect( canvas::Rect(360*i, 288*j, 360, 288), violet, getCanvas() );
		}
	}
	flush15( getCanvas() );
}

TEST_F( Surface, benchmark16 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 720, 50), violet, getCanvas() );
 	blitRect( canvas::Rect(0, 0, 50, 576), violet, getCanvas() );
	flush15( getCanvas() );
}

TEST_F( Surface, benchmark17 ) {
	getCanvas()->flush();
	blitRect( canvas::Rect(0, 0, 720, 50), violet, getCanvas() );
 	blitRect( canvas::Rect(0, 0, 50, 576), violet, getCanvas() );
	getCanvas()->flush();
}
