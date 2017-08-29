#include <string>
#include "autoarray.h"

using namespace std;

extern "C"{
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(autoarray)
{
	autoarray<string> *target;

	void setup()
	{
		target = new autoarray<std::string>();
	}
	void teardown()
	{
		target->reset();
		delete target;
	}
};

TEST(autoarray, New)
{
	LONGS_EQUAL(0, target->count);
}

TEST(autoarray, append)
{
	LONGS_EQUAL(0, target->count);

	target->append("hello");
	LONGS_EQUAL(1, target->count);
	STRCMP_EQUAL("hello", (*target)[0].c_str());

	target->append("me");
	LONGS_EQUAL(2, target->count);
	STRCMP_EQUAL("me", (*target)[1].c_str());
	target->reset();
}

TEST(autoarray, remove)
{
	LONGS_EQUAL(0, target->count);
	target->append("hello");
	target->append("me");
	LONGS_EQUAL(2, target->count);

	// remove
	target->remove(0);
	LONGS_EQUAL(1, target->count);
	STRCMP_EQUAL("me", (*target)[0].c_str());

	// remove
	target->remove(0);
	LONGS_EQUAL(0, target->count);
	target->reset();
}

TEST(autoarray, insert)
{
	LONGS_EQUAL(0, target->count);
	target->append("hello");
	LONGS_EQUAL(1, target->count);

	// insert
	target->insert(1, "usagi");
	LONGS_EQUAL(2, target->count);
	STRCMP_EQUAL("usagi", (*target)[1].c_str());

	target->reset();
}
