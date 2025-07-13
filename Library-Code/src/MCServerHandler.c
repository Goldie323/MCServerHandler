#include "../include/MCServerHandler.h"
#include "cjson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include "Tools.c"



static char WorldSrcDir[MAX_PATH];
static char ServerSrcDir[MAX_PATH];
static char WorldWorkDir[MAX_PATH];
static char ServerWorkDir[MAX_PATH];

void FreeString(char* Str) {
    if (Str!=NULL) {
        free(Str);
    }
}

int SetWorldSource(const char* Dir) {

    if (!RealDir(Dir)) {
        return 1;
    }

    strcpy(WorldSrcDir, Dir);

    return 0;
}

int SetServerSource(const char* Dir) {

    if (!RealDir(Dir)) {
        return 1;
    }

    strcpy(ServerSrcDir, Dir);

    return 0;
}

int SetWorldDir(const char* Dir, bool ForceNonEmpty) {

    if (!RealDir(Dir)) {
        return 1;
    }

    if (!ForceNonEmpty&&EmptyDir(Dir)) {
        return 1;
    }

    strcpy(WorldWorkDir, Dir);

    return 0;
}

int SetServerDir(const char* Dir, bool ForceNonEmpty) {

    if (!RealDir(Dir)) {
        return 1;
    }

    if (!ForceNonEmpty&&EmptyDir(Dir)) {
        return 1;
    }

    strcpy(ServerWorkDir, Dir);

    return 0;
}

char* GetWorldSource() {
    char* ReturnSource = malloc(strlen(WorldSrcDir)+1);
    if (ReturnSource==NULL) {
        return NULL;
    }
    strcpy(ReturnSource, WorldSrcDir);
    return ReturnSource;
}

char* GetServerSource() {
    char* ReturnSource = malloc(strlen(ServerSrcDir)+1);
    if (ReturnSource==NULL) {
        return NULL;
    }
    strcpy(ReturnSource, ServerSrcDir);
    return ReturnSource;
}

char* GetWorldWorkDir() {
    char* ReturnSource = malloc(strlen(WorldWorkDir)+1);
    if (ReturnSource==NULL) {
        return NULL;
    }
    strcpy(ReturnSource, WorldWorkDir);
    return ReturnSource;
}

char* GetServerWorkDir() {
    char* ReturnSource = malloc(strlen(ServerWorkDir)+1);
    if (ReturnSource==NULL) {
        return NULL;
    }
    strcpy(ReturnSource, ServerWorkDir);
    return ReturnSource;
}

char* GetWorldJson(bool Detailed, bool Pretty) {
    if (WorldSrcDir=="NULL"){
        printf("Error: World Source Directory not set, set using SetWorldSource(char* Dir)\n");
        return NULL;
    }

    DIR *WorldDir = opendir(WorldSrcDir);

    if (!WorldDir){
        printf("Error: Could not open World Source Directory\n");
        return NULL;
    }

    struct dirent *dir;

    int length;
    char FilePath[MAX_PATH];
    char JsonFullPath[MAX_PATH];
    cJSON* JsonArray = cJSON_CreateArray();
    while ((dir = readdir(WorldDir)) != NULL){

        if (strcmp(dir->d_name, ".") == 0){
            continue;
        }

        if (strcmp(dir->d_name, "..") == 0){
            continue;
        }

        snprintf(FilePath, MAX_PATH, "%s/%s", WorldSrcDir, dir->d_name);
        snprintf(JsonFullPath, MAX_PATH, "%s/world.json", FilePath);

        cJSON* JsonObject = ParseJsonFile(JsonFullPath);

        if (JsonObject == NULL) {
            printf("Error: Could not parse JSON file %s\n", JsonFullPath);
            continue;
        }

        if (!Detailed) {
            cJSON_AddItemToArray(JsonArray, JsonObject);
            continue;
        }

        AddJsonFileToObject(FilePath, "banned-ips.json", JsonObject);
        AddJsonFileToObject(FilePath, "banned-players.json", JsonObject);
        AddJsonFileToObject(FilePath, "ops.json", JsonObject);
        AddJsonFileToObject(FilePath, "whitelist.json", JsonObject);

        cJSON_AddItemToArray(JsonArray, JsonObject);

    }

    closedir(WorldDir);
    
    char* result;
    if (Pretty) {
        result = cJSON_Print(JsonArray);
    } else {
        result = cJSON_PrintUnformatted(JsonArray);
    }
    
    cJSON_Delete(JsonArray);
    return result;
}

char* GetServerJson(bool Pretty) {
    if (ServerSrcDir=="NULL"){
        printf("Error: Server Source Directory not set, set using SetServerSource(char* Dir)\n");
        return NULL;
    }

    DIR *ServerDir = opendir(ServerSrcDir);

    if (!ServerDir){
        printf("Error: Could not open Server Source Directory\n");
        return NULL;
    }

    struct dirent *dir;

    int length;
    char FilePath[MAX_PATH];
    cJSON* JsonArray = cJSON_CreateArray();
    while ((dir = readdir(ServerDir)) != NULL){

        if (strcmp(dir->d_name, ".") == 0){
            continue;
        }

        if (strcmp(dir->d_name, "..") == 0){
            continue;
        }

        snprintf(FilePath, MAX_PATH, "%s/%s/%s", ServerSrcDir, dir->d_name, "server.json");

        cJSON* JsonObject = ParseJsonFile(FilePath);

        if (JsonObject == NULL) {
            printf("Error: Could not parse JSON file %s\n", FilePath);
            continue;
        }

        cJSON_AddItemToArray(JsonArray, JsonObject);

    }

    closedir(ServerDir);
    
    char* result;
    if (Pretty) {
        result = cJSON_Print(JsonArray);
    } else {
        result = cJSON_PrintUnformatted(JsonArray);
    }
    
    cJSON_Delete(JsonArray);
    return result;
}

