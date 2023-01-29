#pragma once
#include <windows.h>
#include <TlHelp32.h>

class MemoryManagement{
  public:
    HANDLE proc;

    // Read
    template <class T>
    T ReadMem(uintptr_t addr)
    {
       T x;
      ReadProcessMemory(proc,(LPBYTE *)addr,&x,sizeof(x),NULL);
      return x;
    }
    // Write
    template <class T>
    T WriteMem(uintptr_t addr, T x)
    {
      WriteProcessMemory(proc,(LPBYTE *)addr,&x,sizeof(x),NULL);
      return x;
    }

    // Get PID
    uintptr_t getPid(const wchar_t *p){
      HANDLE process_id = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
      uintptr_t process;
      PROCESSENTRY32W process_entry;
      process_entry.dwSize = sizeof(process_entry);
      do{
        if (!_wcsicmp(process_entry.szExeFile,p)){
          process = process_entry.th32ProcessID;
          CloseHandle(process_id);
          proc = OpenProcess(PROCESS_ALL_ACCESS, false, process);
        }
      } while (Process32NextW(process_id, &process_entry));
      return process;
    }

    // Get module
    uintptr_t getModule(uintptr_t id, const wchar_t *mod){
      HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,id);
      MODULEENTRY32W module_entry;
      module_entry.dwSize = sizeof(module_entry);
      do{ 
        if (!_wcsicmp(module_entry.szModule, mod)){
          CloseHandle(module);
          return (uintptr_t)module_entry.hModule;
        }
      } while(Module32NextW(module,&module_entry));
      return 0;
    }

    // Get Process
    HANDLE getProcess(const wchar_t* p) {
        HANDLE process_id = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        uintptr_t process;
        PROCESSENTRY32W process_entry;
        process_entry.dwSize = sizeof(process_entry);
        do {
            if (!_wcsicmp(process_entry.szExeFile, p)) {
                process = process_entry.th32ProcessID;
                CloseHandle(process_id);
                proc = OpenProcess(PROCESS_ALL_ACCESS, false, process);
            }
        } while (Process32NextW(process_id, &process_entry));
        return proc;
    }

};
