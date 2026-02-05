#include <common/common.h>

int errors_generated = 0;

void printUsage() {
    printf("Usage: kscript [options]\n\n");
    printf("Commands: \n");

    printf("    init    <name>      Create a new Krabbascript project\n");
    printf("    build   <file|dir>  Build a project or a file\n");
    printf("    version             Display the current compiler version\n");
}

void usageInit() {
    printf("Usage: kscript init <name>\n");
}

void usageBuild() {
    printf("Usage: kscript build <file|dir>\n");
}

int isFile(const char* name) {
    DIR* directory = opendir(name);

    if (directory != NULL) {
        closedir(directory);
        return 0;
    }

    if (errno == ENOTDIR)
        return 1;


    return -1;
}