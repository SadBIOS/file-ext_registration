#include <iostream>
#include <windows.h>

using namespace std;

extern "C" __declspec(dllexport) string root_loc_finder(VOID) {
    char runtime_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, runtime_path); //literal path to the current working directory
    return runtime_path;
}

extern "C" BOOL APIENTRY DllMain(HMODULE module_handle, DWORD reason_for_call, LPVOID reservation) {
    (void)module_handle; //module handle name
    (void)reason_for_call; //specifies that there is no reason to call it
    (void)reservation; //not reserved
    return TRUE;
}