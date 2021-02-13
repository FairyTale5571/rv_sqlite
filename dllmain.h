#pragma once

BOOL APIENTRY DllMain(HMODULE hModule,
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
