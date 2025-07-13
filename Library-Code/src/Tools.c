

#ifndef TOOLS_C
#define TOOLS_C

#include "cjson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define MAX_JSON 32

#if defined(_WIN32) || defined(_WIN64)

    #include <windows.h>
    #define MAX_PATH 260

    int CreateSymLink(const char* target, const char* link) {
        char command[MAX_PATH * 2 + 32]; // Enough for both paths and the command

        // Format: mklink /J "link" "target"
        snprintf(command, sizeof(command), "cmd /C mklink /J \"%s\" \"%s\"", link, target);

        int result = system(command);
        if (result != 0) {
            fprintf(stderr, "Failed to create junction. Exit code: %d\n", result);
            return 1;
        }

        printf("Junction created: %s -> %s\n", link, target);
        return 0;
    }

#else // POSIX systems (Linux, macOS, FreeBSD)

    #include <unistd.h>
    #include <errno.h>

    #define MAX_PATH 4096

    static int CreateSymLink(const char* target, const char* link) {
        if (symlink(target, link) != 0) {
            perror("Failed to create symbolic link");
            return 1;
        }

        printf("Symbolic link created: %s -> %s\n", link, target);
        return 0;
    }

    static bool IsAdmin() {
        static bool Admin = false;
        static bool AdminChecked = false;

        if (!AdminChecked && (geteuid()==0)) {
            Admin = true;
            AdminChecked = true;
        }

        return Admin;

    }

#endif


static bool EmptyDir(const char* Dir) {

    DIR* dir = opendir(Dir);

    if (!dir) {
        printf("Error: Could not open directory\n");
        return 0;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                closedir(dir);
                printf("Error: Directory is not empty\n");
                return 0;
        }
    }

    closedir(dir);

    return 1;
}

static bool RealDir(const char* Dir) {
    struct stat statbuf;

    if (stat(Dir, &statbuf) != 0) {
        printf("Error: File failed to load statistics about itself\n");
        return 0;
    }

    if (!S_ISDIR(statbuf.st_mode)){
        printf("Error: File is not a folder\n");
        return 0;
    }

    return 1;
}

static cJSON* ParseJsonFile(const char* FileName) {
    FILE* JsonFile = fopen(FileName, "r");
    if (JsonFile == NULL) {
        printf("Error: Couldn't open file: %s\n", FileName);
        return NULL;
    }

    fseek(JsonFile, 0, SEEK_END);
    long filesize = ftell(JsonFile);
    fseek(JsonFile, 0, SEEK_SET);

    char* FileContent = malloc(filesize + 1);
    fread(FileContent, 1, filesize, JsonFile);
    fclose(JsonFile);
    FileContent[filesize] = '\0';

    cJSON* json = cJSON_Parse(FileContent);
    free(FileContent);

    return json;
}

static char* RemoveJsonExtension(const char* Str, char* NewStr) {
    strcpy(NewStr, Str);
    int Len = strlen(NewStr)+1;
    if (Len >= 5 && strcmp(NewStr + Len - 5, ".json") == 0) {
        NewStr[Len - 5] = '\0'; // Truncate ".json"
    }
    return NewStr;
}

static void AddJsonFileToObject(const char* BasePath, const char* FileName, cJSON* Object) {
    char FullPath[MAX_PATH];

    snprintf(FullPath, MAX_PATH, "%s/%s", BasePath, FileName);
    cJSON* JsonData = ParseJsonFile(FullPath);
    if (JsonData == NULL) {
        printf("Error: Could not parse JSON file %s\n", FullPath);
        return;
    }

    char Name[MAX_JSON];
    RemoveJsonExtension(FileName, Name);
    cJSON_AddItemToObject(Object, Name, JsonData);
    return;
}

#endif