#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <stdlib.h>

#define KSCRIPT_DIRECTORY 0
#define KSCRIPT_FILE 1

#define KSCRIPT_VERSION_MAJOR 2
#define KSCRIPT_VERSION_MINOR 3
#define KSCRIPT_VERSION_PATCH 3

#define KSCRIPT_VERSION_IDENT "prototype"

#ifndef KSCRIPT_VENDOR

#    define KSCRIPT_VENDOR "None"

#endif
void printUsage();

void usageInit();
void usageBuild();

void printKrabba();

int isFile(const char* name);

extern int errors_generated;

void printErrorsGenerated();