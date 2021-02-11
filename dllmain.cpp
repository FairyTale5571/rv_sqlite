// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


using namespace std;
#define CURRENT_VERSION "1.0.0 by FT5571 / rimasrp.life copyright"
#define MACROS_STRNCPY(x) strncpy_s(output, outputSize, x, _TRUNCATE)
#define CBK(x,y) callbackPtr("rv_sqlite",x,y)

extern "C"
{
	__declspec (dllexport) void __stdcall RVExtensionRegisterCallback(int(*callbackProc)(char const* name, char const* function, char const* data));
	__declspec(dllexport) void __stdcall RVExtension(char* output, int outputSize, const char* function);
	__declspec(dllexport) int __stdcall RVExtensionArgs(char* output, int outputSize, const char* function, const char** argv, int argc);
	__declspec(dllexport) void __stdcall RVExtensionVersion(char* output, int outputSize);
}

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

char* err = 0;
sqlite3* db = 0;

int __stdcall 
RVExtensionArgs(char* output, int outputSize, const char* function, const char** argv, int argc)
{
	int i = 0;
	std::string str[11];
	std::string fnStr = function;
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

		if (sqlite3_open(str[0].c_str(), &::db))
		{
			fprintf(stderr, "Error to open database: %s \n", sqlite3_errmsg(::db));
		}
		else {
			std::cout << "Opened: " << str[0] << endl;
			MACROS_STRNCPY("");
		}
	}
	if (!strcmp(function, "update"))
	{
		if (sqlite3_exec(::db, str[0].c_str(), 0, 0, &err))
		{
			fprintf(stderr, "Error to execute: %s \n", err);
		};
	}
	if (!strcmp(function, "return"))
	{

	}
	if (!strcmp(function, "check"))
	{

	}
	if (!strcmp(function, "close"))
	{

	}

	return -1;
}

void __stdcall 
RVExtensionVersion(char* output, int outputSize)
{
	std::strncpy(output, "Test-Extension v1.0", outputSize);
}
