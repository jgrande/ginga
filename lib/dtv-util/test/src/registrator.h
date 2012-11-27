#include <list>
#include <gtest/gtest.h>

namespace util{
namespace reg{
	class Registrator;
}
}

class Registrator : public testing::Test{
public:
	Registrator();
	virtual ~Registrator();
	void callFin();
protected:
	virtual void SetUp();
	virtual void TearDown();

	std::list<util::reg::Registrator *> _list;
};




