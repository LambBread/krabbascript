#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define KSCRIPT_VERSION_MAJOR 1
#define KSCRIPT_VERSION_MINOR 0
#define KSCRIPT_VERSION_PATCH 0

#define KSCRIPT_VERSION_IDENT "prototype"

#define KSCRIPT_VENDOR        "KrabbaTek"
#define KSCRIPT_VENDOR_VERSION_MAJOR 1
#define KSCRIPT_VENDOR_VERSION_MINOR 0
#define KSCRIPT_VENDOR_VERSION_PATCH 0

void printUsage();

void usageInit();
void usageBuild();

int isFile(const char* name);