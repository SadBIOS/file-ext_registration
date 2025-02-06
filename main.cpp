#include <iostream>
#include <string>
#include <userenv.h>
#include <windows.h>

using namespace std;

extern "C" __declspec(dllimport) string root_loc_finder(VOID);

bool root_privilage_check (VOID) {
    BOOL is_superuser = FALSE;
    PSID superuser_ID = NULL;
    SID_IDENTIFIER_AUTHORITY sudo_priv = SECURITY_NT_AUTHORITY;
    
    if (AllocateAndInitializeSid(&sudo_priv, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &superuser_ID)) {
        CheckTokenMembership(NULL, superuser_ID, &is_superuser);
        FreeSid(superuser_ID);
    }
    return is_superuser == TRUE;
}

int main () {
    const char* shell_void = 
        "powershell -WindowStyle Hidden -Command \"Add-Type -AssemblyName 'System.Windows.Forms'; "
        "[System.Windows.Forms.MessageBox]::Show('Please Select Run as Administrator', 'Privilege Escalation Fail', "
        "[System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Error); "
        "[System.Media.SystemSounds]::Beep.Play()\"";

    HMODULE gazoo = LoadLibrary("reg_loader.dll");

    if (root_privilage_check()) {
        string shell_loader_root = root_loc_finder();
        string iconpath = shell_loader_root + "\\shell_load.ico";  
        string extension_key = "HKCU:\\Software\\Classes\\.MEME"; //change the extension before compilation
        string filetype_key = "HKCU:\\Software\\Classes\\MEME";   //change the class before compilation
        string iconkey = "HKCU:\\Software\\Classes\\MEME\\DefaultIcon"; //change the class before compilation

        string load_icon_to_reg = "powershell -Command \""
        "if ((Test-Path " + extension_key + ") -eq $false) { New-Item -Path " + extension_key + " -Force | Out-Null }; "
        "Set-ItemProperty -Path " + extension_key + " -Name \"'(Default)'\" -Value \"'MEME'\"; " //change the value before compilation
        "if ((Test-Path " + filetype_key + ") -eq $false) { New-Item -Path " + filetype_key + " -Force | Out-Null }; "
        "if ((Test-Path " + iconkey + ") -eq $false) { New-Item -Path " + iconkey + " -Force | Out-Null }; "
        "Set-ItemProperty -Path " + iconkey + " -Name \"'(Default)'\" -Value \"" + iconpath + "\"; \"";

        string reload_icon_cache = "powershell -Command \"ie4uinit.exe -ClearIconCache ; Stop-Process -Name explorer -Force\"";

        system(load_icon_to_reg.c_str());
        system(reload_icon_cache.c_str());
    
        return 1;
    } else {
        system(shell_void);
        return 0;
    }

    FreeLibrary(gazoo);
}