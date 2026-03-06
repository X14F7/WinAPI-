# WinAPI

A collection of scripts to learn and understand Defense Evasion with couple of techniques.
These techniques aren't perfect and WILL be detected by AVs!(Educational only)


## Contents

- `procinject.cpp`  
  A script which injects its code into a running Process.

- `dllinject.cpp`  
  A script which injects a DLL into a running Process via LoadLibraryA.
  
- `evildll.cpp`  
  PoC script which is used with dllinject.cpp as the DLL. (Before using you will need to          compile this file into an DLL via g++. For troubleshooting see down below at

- `tokensteal.cpp`  
  A script which steals a token and impersonates an user with it.
  
  **Prerequisites**


## Prerequisites

  Note: Linux users typically have `g++` pre-installed via `apt install g++`. This guide is      for **Windows users**.

### Windows: Install MinGW-w64 (via Chocolatey)
  
  1.Download from the official chocolatey site at https://chocolatey.org
  
  2. Type this into your powershell/cmd: **choco install mingw**

  3. Refresh your shell with **refreshenv**

  4. Verify installation with **g++ --version**

For compiling use this command: **g++ -shared -o evildll.dll evildll.cpp -static-libgcc -static-libstdc++**


