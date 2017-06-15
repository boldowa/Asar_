#include "CppUTest/TestHarness.h"
#include "AsarBuildTime.h"

TEST_GROUP(AsarBuildTime)
{
  AsarBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new AsarBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(AsarBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

