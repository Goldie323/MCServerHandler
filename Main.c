#include "Library-Code/src/cjson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Library-Code/include/MCServerHandler.h"

int main(){


    int returned1 = SetWorldSource("/home/goldie323/Downloads/Server-Worlds/Worlds");

    printf("The function1 returned:\n");
    printf("%d\n\n", returned1);

    int returned2 = SetServerSource("/home/goldie323/Downloads/Server-Worlds/Servers");

    printf("The function2 returned:\n");
    printf("%d\n\n", returned2);

    char* JsonData = GetWorldJson(true, false);

    printf("The function3 returned:\n");
    printf("%s\n\n", JsonData);

    char* JsonData2 = GetServerJson(false);

    printf("The function4 returned:\n");
    printf("%s\n\n", JsonData2);


    return 0;
}