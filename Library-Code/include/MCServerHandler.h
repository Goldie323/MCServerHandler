
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
DLL_EXPORT const char* GetWorldSource();
DLL_EXPORT const char* GetServerSource();
DLL_EXPORT const char* GetWorldWorkDir();
DLL_EXPORT const char* GetServerWorkDir();
DLL_EXPORT char* GetWorldJson(bool Detailed, bool Pretty);
DLL_EXPORT char* GetServerJson(bool Pretty);
DLL_EXPORT int NewWorld(const char* Name, const int BackupAmount);
DLL_EXPORT int RemoveWorld();
#endif