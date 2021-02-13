// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "sqlite_class.hpp"
#include "dllmain.h"


using namespace std;
using boost::format;
using boost::io::group;


int(*callbackPtr)(char const* name, char const* function, char const* data) = nullptr;
void __stdcall
RVExtensionRegisterCallback(int(*callbackProc)(char const* name, char const* function, char const* data))
{
	callbackPtr = callbackProc;
}

void __stdcall 
RVExtension(char* output, int outputSize, const char* function)
{
	strncpy(output, function, outputSize);
}

int __stdcall 
RVExtensionArgs(char* output, int outputSize, const char* function, const char** argv, int argc)
{
	int i = 0;
	std::string str[11];
	std::string fnStr = function;
	std::string out;
	SQLITE sql;
	while (i < argc)
	{
		std::string s = argv[i];
		str[i] = s.substr(1, s.length() - 2);
		i++;
	}
	if (!callbackPtr)
		return 500;

	if (!strcmp(function, "open"))
	{
		sql.set_name(str[0]);
		if (sql.open())
		{
			out = boost::str(boost::format("Database Connection to %1% error %2%") % argv[0] % sql.get_name());
			MACROS_STRNCPY(out.c_str());
			return 404;
		}
		out = boost::str(boost::format("Database %1% Opened") % str[0]);
		MACROS_STRNCPY( out.c_str() );
		return sql.get_rc();
	}
	if (!strcmp(function, "update"))
	{
		return sql.exec("CREATE TABLE foo(a,b,c,d)");
	}
	if (!strcmp(function, "return"))
	{

	}
	if (!strcmp(function, "check"))
	{
		return sql.get_rc();
	}
	if (!strcmp(function, "close"))
	{
		sql.~SQLITE();
	}

	return -1;
}

void __stdcall 
RVExtensionVersion(char* output, int outputSize)
{
	std::strncpy(output, "RV SqLite wrapper", outputSize);
}
