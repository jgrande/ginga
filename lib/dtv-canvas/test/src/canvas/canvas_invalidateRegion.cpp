#include "surface.h"
#include "../../../src/canvas.h"
#include "../../../src/rect.h"

TEST_F( Surface, canvas_invalidateRegion_simple ) {
	canvas::Rect r1(0,0,100,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();
	
	ASSERT_TRUE( dirtyRegions.size()==1 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_not_intersected ) {
	canvas::Rect r1(0,0,100,100);
	canvas::Rect r2(200,200,100,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();
	
	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==r2 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_diagonal ) {
	canvas::Rect r1(0,0,100,100);
	canvas::Rect r2(50,50,100,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==r2 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_diagonal_invert ) {
	canvas::Rect r1(0,0,100,100);
	canvas::Rect r2(50,50,100,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r2);
	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r2 );
	ASSERT_TRUE( dirtyRegions[1]==r1 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_diagonal2 ) {
	canvas::Rect r1(0,0,100,100);
	canvas::Rect r2(20,20,100,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==1 );
	ASSERT_TRUE( dirtyRegions[0]==canvas::Rect(0,0,120,120) );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_horizontal ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(50,140,100,20);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==canvas::Rect(50,140,50,20) );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_horizontal_invert ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(50,140,100,20);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r2);
	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==canvas::Rect(50,140,50,20) );
	ASSERT_TRUE( dirtyRegions[1]==r1 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_vertical ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(140,150,20,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==canvas::Rect(140,200,20,50) );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_vertical_invert ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(140,150,20,100);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r2);
	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==canvas::Rect(140,200,20,50) );
	ASSERT_TRUE( dirtyRegions[1]==r1 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_horizontal_longer ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(50,140,200,20);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==r2 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_horizontal_longer_invert ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(50,140,200,20);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r2);
	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r2 );
	ASSERT_TRUE( dirtyRegions[1]==r1 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_vertical_higher ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(140,50,20,200);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==2 );
	ASSERT_TRUE( dirtyRegions[0]==r1 );
	ASSERT_TRUE( dirtyRegions[1]==r2 );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(120,50,60,200);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r1);
	c->invalidateRegion(r2);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==1 );
	ASSERT_TRUE( dirtyRegions[0]==canvas::Rect(100,50,100,200) );
}

TEST_F( Surface, canvas_invalidateRegion_2_rects_intersected_invert ) {
	canvas::Rect r1(100,100,100,100);
	canvas::Rect r2(120,50,60,200);
	canvas::Canvas *c = getCanvas();

	c->invalidateRegion(r2);
	c->invalidateRegion(r1);
	std::vector<canvas::Rect> dirtyRegions = c->dirtyRegions();

	ASSERT_TRUE( dirtyRegions.size()==1 );
	ASSERT_TRUE( dirtyRegions[0]==canvas::Rect(100,50,100,200) );
}