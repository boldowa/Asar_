#include <string>
#include "assocarr.h"

extern "C"{
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(assocarr)
{
	assocarr<std::string> *target;

	void setup()
	{
		target = new assocarr<std::string>();
	}
	void teardown()
	{
		delete(target);
	}
};

TEST(assocarr, New)
{
	LONGS_EQUAL(0, target->num);
}

/* Note: this class isn't use in asar. */

