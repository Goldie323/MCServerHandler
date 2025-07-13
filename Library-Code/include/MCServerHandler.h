
#ifndef MCSERVERHANDLER_H
#define MCSERVERHANDLER_H

#ifdef _WIN32
  #define DLL_EXPORT __declspec(dllexport)
#else
  #define DLL_EXPORT
#endif

#include <stdbool.h>

DLL_EXPORT void FreeString(char* Str);
DLL_EXPORT int SetWorldSource(const char *Dir);
DLL_EXPORT int SetServerSource(const char *Dir);
DLL_EXPORT int SetWorldDir(const char* Dir, bool ForceNonEmpty);
DLL_EXPORT int SetServerDir(const char* Dir, bool ForceNonEmpty);
DLL_EXPORT char* GetWorldSource();
DLL_EXPORT char* GetServerSource();
DLL_EXPORT char* GetWorldWorkDir();
DLL_EXPORT char* GetServerWorkDir();
DLL_EXPORT char* GetWorldJson(bool Detailed, bool Pretty);
DLL_EXPORT char* GetServerJson(bool Pretty);

#endif