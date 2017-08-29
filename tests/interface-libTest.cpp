#if 0
#include "asar.h"
#include "scapegoat.hpp"
#include "libstr.h"
#include "libsmw.h"


// target functions 
extern "C"{
bool asar_init();
void asar_close();
int asar_version();
int asar_apiversion();
bool asar_reset();
bool asar_patch(const char * patchloc , char * romdata, int buflen, int * romlen);
int asar_maxromsize();
const struct errordata * asar_geterrors(int * count);
const struct errordata * asar_getwarnings(int * count);
const char * const * asar_getprints(int * count);
const struct labeldata * asar_getalllabels(int * count);
}

static const char * const FP = "./testsrc.asm";
static bool genSrc(const char * const text)
{
	FILE *f;
	f = fopen(FP, "w");
	if(!f) return false;

	fprintf(f, text);
	fclose(f);
	return true;
}


//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(if_patch)
{
	const static size_t dsize = 0x10000;
	char data[dsize];
	int len;

	void setup()
	{
		memset(data, 0, dsize);
		len = dsize;
		asar_apiversion();
		CHECK(asar_init());
	}
	void teardown()
	{
		CHECK(asar_reset());
		asar_close();
		remove(FP);
	}
};

TEST(if_patch, re_init)
{
	asar_close();
	CHECK(asar_init());
}

TEST(if_patch, input_missing)
{
	CHECK_FALSE(asar_patch(FP, data, dsize, &len));
}

TEST(if_patch, valid_src)
{
	CHECK(genSrc("db $00"));
	//genSrc("db $00");
	//CHECK(asar_patch(FP, data, dsize, &len));
}

#endif
