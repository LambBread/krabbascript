#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define KSCRIPT_VERSION_MAJOR 1
#define KSCRIPT_VERSION_MINOR 2
#define KSCRIPT_VERSION_PATCH 0

#define KSCRIPT_VERSION_IDENT "prototype"

#ifndef KSCRIPT_VENDOR

#define KSCRIPT_VENDOR        "None"

#endif
void printUsage();

void usageInit();
void usageBuild();

int isFile(const char* name);

extern int errors_generated;