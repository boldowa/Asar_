#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

class string {
public:
char * str;
int len;

int truelen() const
{
	return len?len:strlen(str);
}

void fixlen()
{
	if (!len) len=strlen(str);
}

private:
//char shortbuf[32];
int bufferlen;

void resize(int len)
{
	if (len>=bufferlen-4)
	{
		while (len>=bufferlen-4) bufferlen*=2;
		str=(char*)realloc(str, sizeof(char)*bufferlen);
		memset(str+len, 0, bufferlen-len);
	}
}

void init()
{
	bufferlen=32;
	str=(char*)malloc(sizeof(char)*bufferlen);
	memset(str, 0, bufferlen);
	len=0;
}

public:

void assign(const char * newstr)
{
	if (!newstr) newstr="";
	len=strlen(newstr);
	resize(len);
	strcpy(str, newstr);
}

void assign(const char * newstr, int newlen)
{
	if (!newstr) return;
	len=newlen;
	resize(len);
	memcpy(str, newstr, len);
	len=strlen(str);
}

string& operator=(const char * newstr)
{
	if (bufferlen == 0) init();
	assign(newstr);
	return *this;
}

string& operator=(string newstr)
{
	if (bufferlen == 0) init();
	assign(newstr);
	return *this;
}

string& operator+=(const string& newstr)
{
	fixlen();
	resize(len+newstr.truelen());
	strcpy(str+len, newstr.str);
	len+=newstr.len;
	return *this;
}

string& operator+=(const char * newstr)
{
	fixlen();
	int newlen=strlen(newstr);
	resize(len+newlen);
	strcpy(str+len, newstr);
	len+=newlen;
	return *this;
}

string& operator+=(char c)
{
	fixlen();
	resize(len);
	str[len]=c;
	str[len+1]='\0';
	len++;
	return *this;
}

string operator+(char right) const
{
	string ret=*this;
	ret+=right;
	return ret;
}

const char * operator+(int right) const
{
	return str+right;
}

string operator+(const char * right) const
{
	string ret=*this;
	ret+=right;
	return ret;
}

string operator+(const string& right) const
{
	string ret=*this;
	ret+=right;
	return ret;
}

char& operator*()
{
	len=0;
	return str[0];
}

bool operator==(const char * right) const
{
	return !strcmp(str, right);
}

bool operator==(string& right) const
{
	return !strcmp(str, right.str);
}

bool operator!=(const char * right) const
{
	return strcmp(str, right);
}

bool operator!=(string& right) const
{
	return strcmp(str, right.str);
}

bool operator<(string& right) const
{
	return strcmp(str, right.str)<0;
}

char& operator[](int id)
{
	static char nul;
	nul='\0';
	if (id<0) return nul;
	len=0;
	resize(id);
	return str[id];
}

operator const char*() const
{
	return str;
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
explicit
#endif
operator bool() const
{
	return str[0];
}

string()
{
	init();
}
string(const char * newstr)
{
	init();
	assign(newstr);
}
string(const char * newstr, int newlen)
{
	init();
	assign(newstr, newlen);
}
string(const string& old)
{
	init();
	assign(old.str);
}
string(int intval)
{
	init();
	char buf[16];
	memset(buf, sizeof(buf), intval);
	sprintf(buf, "%i", intval);
	assign(buf);
}
~string()
{
	free(str);
}

string& replace(const char * instr, const char * outstr, bool all=true);
string& qreplace(const char * instr, const char * outstr, bool all=true);

#ifdef SERIALIZER
void serialize(serializer & s)
{
	s(str, bufferlen);
	len=strlen(str);
}
#endif
#define SERIALIZER_BANNED
};
#define S (string)

class cstring {
public:
const char * str;

cstring& operator=(const char * newstr)
{
	str=newstr;
	return *this;
}

cstring& operator=(cstring newstr)
{
	str=newstr.str;
	return *this;
}

char operator*() const
{
	return str[0];
}

bool operator==(const char * right) const
{
	return !strcmp(str, right);
}

bool operator==(cstring& right) const
{
	return !strcmp(str, right.str);
}

bool operator!=(const char * right) const
{
	return strcmp(str, right);
}

bool operator!=(cstring& right) const
{
	return strcmp(str, right.str);
}

bool operator<(cstring& right) const
{
	return strcmp(str, right.str)<0;
}

char operator[](int id) const
{
	return str[id];
}

operator const char*() const
{
	return str;
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
explicit
#endif
operator bool() const
{
	return str;
}

cstring()
{
	str=NULL;
}
cstring(const char * newstr)
{
	str=newstr;
}
cstring(const cstring& old)
{
	str=old.str;
}

string operator+(const cstring& right) const
{
	return (string)str+(const char*)right;
}
string operator+(const string& right) const
{
	return (string)str+(const char*)right;
}
string operator+(const char * right) const
{
	return (string)str+right;
}
};

//string operator+(const char * left, string right)
//{
//	string s=left;
//	s+=right;
//	return s;
//}

char * readfile(const char * fname);
bool readfile(const char * fname, char ** data, int * len);//if you want an uchar*, cast it
char ** nsplit(char * str, const char * key, int maxlen, int * len);
char ** qnsplit(char * str, const char * key, int maxlen, int * len);
char ** qpnsplit(char * str, const char * key, int maxlen, int * len);
inline char ** split(char * str, const char * key, int * len=NULL) { return nsplit(str, key, 0, len); }
inline char ** qsplit(char * str, const char * key, int * len=NULL) { return qnsplit(str, key, 0, len); }
inline char ** qpsplit(char * str, const char * key, int * len=NULL) { return qpnsplit(str, key, 0, len); }
inline char ** split1(char * str, const char * key, int * len=NULL) { return nsplit(str, key, 2, len); }
inline char ** qsplit1(char * str, const char * key, int * len=NULL) { return qnsplit(str, key, 2, len); }
inline char ** qpsplit1(char * str, const char * key, int * len=NULL) { return qpnsplit(str, key, 2, len); }
//void replace(string& str, const char * instr, const char * outstr, bool all);
//void qreplace(string& str, const char * instr, const char * outstr, bool all);
bool confirmquotes(const char * str);
bool confirmqpar(const char * str);

inline string hex(unsigned int value)
{
	char buffer[64];
	if(0);
	else if (value<=0x000000FF) sprintf(buffer, "%.2X", value);
	else if (value<=0x0000FFFF) sprintf(buffer, "%.4X", value);
	else if (value<=0x00FFFFFF) sprintf(buffer, "%.6X", value);
	else if (value<=0xFFFFFFFF) sprintf(buffer, "%.8X", value);
	return buffer;
}

inline string hex(unsigned int value, int width)
{
	char buffer[64];
	sprintf(buffer, "%.*X", width, value);
	return buffer;
}

inline string hex0(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%X", value);
	return buffer;
}

inline string hex2(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.2X", value);
	return buffer;
}

inline string hex3(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.2X", value);
	return buffer;
}

inline string hex4(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.4X", value);
	return buffer;
}

inline string hex5(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.5X", value);
	return buffer;
}

inline string hex6(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.6X", value);
	return buffer;
}

inline string hex8(unsigned int value)
{
	char buffer[64];
	sprintf(buffer, "%.8X", value);
	return buffer;
}

inline string dec(int value)
{
	char buffer[64];
	sprintf(buffer, "%i", value);
	return buffer;
}

inline string bin(unsigned int value)
{
	char buffer[64];
	int len;
	for (len=0;!len || value || (len&7);len++)
	{
		buffer[len+31]=(value&1)|0x30;
		value>>=1;
	}
	buffer[len+31]=0;
	for (int i=0;i<len;i++)
	{
		buffer[i]=buffer[len+31-i-1];
	}
	buffer[len]=0;
	return buffer;
}

inline string ftostr(long double value)
{
	char rval[256];
	// RPG Hacker: Ridiculously high precision, I know, but we're working with long doubles
	// here and can afforc it, so no need to waste any precision
	sprintf(rval, "%.100lf", static_cast<double>(value));
	if (strchr(rval, '.'))//nuke useless zeroes
	{
		char * end=strrchr(rval, '\0')-1;
		while (*end=='0')
		{
			*end='\0';
			end--;
		}
		if (*end=='.') *end='\0';
	}
	return rval;
}

// Same as above, but with variable precision
inline string ftostrvar(long double value, int precision)
{
	int clampedprecision = precision;
	if (clampedprecision < 0) clampedprecision = 0;
	if (clampedprecision > 100) clampedprecision = 100;

	// RPG Hacker: Not the prettiest solution, but simple enough, and avoids security risks from using sprintf()
	// (Note that those really matter that much)
	static const char * formats[] =
	{
		"%.0f", "%.1f", "%.2f", "%.3f", "%.4f", "%.5f", "%.6f", "%.7", "%.8f", "%.9f",
		"%.10f", "%.11f", "%.12f", "%.13f", "%.14f", "%.15f", "%.16f", "%.17", "%.18f", "%.19f",
		"%.20f", "%.21f", "%.22f", "%.23f", "%.24f", "%.25f", "%.26f", "%.27", "%.28f", "%.29f",
		"%.30f", "%.31f", "%.32f", "%.33f", "%.34f", "%.35f", "%.36f", "%.37", "%.38f", "%.39f",
		"%.40f", "%.41f", "%.42f", "%.43f", "%.44f", "%.45f", "%.46f", "%.47", "%.48f", "%.49f",
		"%.50f", "%.51f", "%.52f", "%.53f", "%.54f", "%.55f", "%.56f", "%.57", "%.58f", "%.59f",
		"%.60f", "%.61f", "%.62f", "%.63f", "%.64f", "%.65f", "%.66f", "%.67", "%.68f", "%.69f",
		"%.70f", "%.71f", "%.72f", "%.73f", "%.74f", "%.75f", "%.76f", "%.77", "%.78f", "%.79f",
		"%.80f", "%.81f", "%.82f", "%.83f", "%.84f", "%.85f", "%.86f", "%.87", "%.88f", "%.89f",
		"%.90f", "%.91f", "%.92f", "%.93f", "%.94f", "%.95f", "%.96f", "%.97", "%.98f", "%.99f",
		"%.100f"
	};

	char rval[256];
	sprintf(rval, formats[clampedprecision], value);
	if (strchr(rval, '.'))//nuke useless zeroes
	{
		char * end = strrchr(rval, '\0') - 1;
		while (*end == '0')
		{
			*end = '\0';
			end--;
		}
		if (*end == '.') *end = '\0';
	}
	return rval;
}

inline bool stribegin(const char * str, const char * key)
{
	for (int i=0;key[i];i++)
	{
		if (tolower(str[i])!=tolower(key[i])) return false;
	}
	return true;
}

inline bool striend(const char * str, const char * key)
{
	const char * keyend=strrchr(key, '\0');
	const char * strend=strrchr(str, '\0');
	while (key!=keyend)
	{
		keyend--;
		strend--;
		if (tolower(*strend)!=tolower(*keyend)) return false;
	}
	return true;
}

//function: return the string without quotes around it, if any exists
//if they don't exist, return it unaltered
//it is not guaranteed to return str
//it is not guaranteed to not edit str
//the input must be freed even though it's garbage, the output must not
inline const char * dequote(char * str)
{
	if (*str!='"') return str;
	int inpos=1;
	int outpos=0;
	while (true)
	{
		if (str[inpos]=='"')
		{
			if (str[inpos+1]=='"') inpos++;
			else if (str[inpos+1]=='\0') break;
			else return NULL;
		}
		if (!str[inpos]) return NULL;
		str[outpos++]=str[inpos++];
	}
	str[outpos]=0;
	return str;
}

inline char * strqchr(const char * str, char key)
{
	while (*str)
	{
		if (*str=='"')
		{
			str++;
			while (*str!='"')
			{
				if (!*str) return NULL;
				str++;
			}
			str++;
		}
		else
		{
			if (*str==key) return (char*)str;
			str++;
		}
	}
	return NULL;
}

inline char * strqrchr(const char * str, char key)
{
	char * ret=NULL;
	while (*str)
	{
		if (*str=='"')
		{
			str++;
			while (*str!='"')
			{
				if (!*str) return NULL;
				str++;
			}
			str++;
		}
		else
		{
			if (*str==key) ret=(char*)str;
			str++;
		}
	}
	return ret;
}

inline string substr(const char * str, int len)
{
	string s;
	s.assign(str, len);
	return s;
}

char * trim(char * str, const char * left, const char * right, bool multi=false);
char * itrim(char * str, const char * left, const char * right, bool multi=false);

//edited from nall
inline bool strwcmp(const char *s, const char *p) {
  const char *cp = 0, *mp = 0;
  while(*s && *p != '*') {
    if(*p != '?' && *s != *p) return true;
    p++, s++;
  }
  while(*s) {
    if(*p == '*') {
      if(!*++p) return false;
      mp = p, cp = s + 1;
    } else if(*p == '?' || *p == *s) {
      p++, s++;
    } else {
      p = mp, s = cp++;
    }
  }
  while(*p == '*') p++;
  return *p;
}

inline bool striwcmp(const char *s, const char *p) {
  const char *cp = 0, *mp = 0;
  while(*s && *p != '*') {
    if(*p != '?' && tolower(*s) != tolower(*p)) return true;
    p++, s++;
  }
  while(*s) {
    if(*p == '*') {
      if(!*++p) return false;
      mp = p, cp = s + 1;
    } else if(*p == '?' || tolower(*p) == tolower(*s)) {
      p++, s++;
    } else {
      p = mp, s = cp++;
    }
  }
  while(*p == '*') p++;
  return *p;
}

#ifndef _MSC_VER//I thought this one was FreeBSD-only, and now it suddenly exists in MSVC but not GCC?
inline char * strdup(const char * str)
{
	char * a=(char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(a, str);
	return a;
}
#endif

inline int strpos(const char * str, char key)
{
	if (str<(char*)0+64) return -1;//Someone needs to kill me for this.
	const char * pos=strchr(str, key);
	if (!pos) return -1;
	return pos-str;
}

inline int strpos(const char * str, const char * key)
{
	if (str<(char*)0+64) return -1;
	const char * pos=strstr(str, key);
	if (!pos) return -1;
	return pos-str;
}

inline string upper(const char * old)
{
	string s=old;
	for (int i=0;s.str[i];i++) s.str[i]=toupper(s.str[i]);
	return s;
}

inline string lower(const char * old)
{
	string s=old;
	for (int i=0;s.str[i];i++) s.str[i]=tolower(s.str[i]);
	return s;
}

string urlencode(const char * in);

inline int isualnum ( int c )
{
	return (c=='_' || isalnum(c));
}

inline int isualpha ( int c )
{
	return (c=='_' || isalpha(c));
}

#define ctype(type) \
		inline bool ctype_##type(const char * str) \
		{ \
			while (*str) \
			{ \
				if (!is##type(*str)) return false; \
				str++; \
			} \
			return true; \
		} \
		\
		inline bool ctype_##type(const char * str, int num) \
		{ \
			for (int i=0;i<num;i++) \
			{ \
				if (!is##type(str[i])) return false; \
			} \
			return true; \
		}
ctype(alnum);
ctype(alpha);
ctype(cntrl);
ctype(digit);
ctype(graph);
ctype(lower);
ctype(print);
ctype(punct);
ctype(space);
ctype(upper);
ctype(xdigit);
ctype(ualnum);
ctype(ualpha);
#undef ctype

inline char * stristr(const char * string, const char * pattern)
{
	if (!*pattern) return (char*)string;
	char * pptr;
	char * sptr;
	char * start;
	for (start=(char*)string;*start!=0;start++)
	{
		for (;(*start && (toupper(*start)!=toupper(*pattern)));start++);
		if (!*start) return NULL;
		pptr=(char*)pattern;
		sptr=start;
		while (toupper(*sptr)==toupper(*pptr))
		{
			sptr++;
			pptr++;
			if (!*pptr) return start;
		}
	}
	return NULL;
}

const char * unhtml(const char * html);
const char * tohtml(const char * text);
const char * htmlentities(const char * text);



// Returns number of connected lines - 1
template<typename stringarraytype>
inline int getconnectedlines(stringarraytype& lines, int startline, string& out)
{
	out = string("");
	int count = 1;

	for (int i = startline; lines[i]; i++)
	{
		// The line should already be stripped of any comments at this point
		int startpos = strlen(lines[i]);

		bool found = false;

		for (int j = startpos; j > 0; j--)
		{
			if (!isspace(lines[i][j]) && lines[i][j] != '\0' && lines[i][j] != ';')
			{
				if (lines[i][j] == '\\')
				{
					count++;
					out += string(lines[i], j);
					found = true;
					break;
				}
				else
				{
					out += string(lines[i], j + 1);
					return count - 1;
				}
			}
		}

		if (!found)
		{
			out += string(lines[i], 1);
			return count - 1;
		}
	}

	return count - 1;
}
