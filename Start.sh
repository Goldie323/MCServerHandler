#!/bin/bash

gcc -o main Main.c Library-Code/src/cjson/cJSON.c Library-Code/src/MCServerHandler.c && ./main