#include "AsarBuildTime.h"

AsarBuildTime::AsarBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

AsarBuildTime::~AsarBuildTime()
{
}

const char* AsarBuildTime::GetDateTime()
{
    return dateTime;
}

