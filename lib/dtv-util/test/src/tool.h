#include <gtest/gtest.h>
#include "../../src/tool.h"
#include "../../src/registrator.h"

class ToolTest : public testing::Test {
public:
	ToolTest();
	virtual ~ToolTest();

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

	std::list<util::reg::Registrator *> _init;
	std::list<util::reg::Registrator *> _fin;
};

