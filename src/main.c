#include <stdio.h>
#include <common/common.h>

#include <toml/tomlc17.h>
#include <string.h>

#include <unistd.h> 

int main(int argc, char *argv[]) {
    (void)argv;

    if (argc < 2) {
        printUsage();

        return 0;
    }

    if (strcmp(argv[1], "version") == 0) {
        printf("KrabbaScript (kscript) %d.%d.%d-%s (%s %d.%d.%d)\n",
            KSCRIPT_VERSION_MAJOR,
            KSCRIPT_VERSION_MINOR,
            KSCRIPT_VERSION_PATCH,
            KSCRIPT_VERSION_IDENT,
            KSCRIPT_VENDOR,
            KSCRIPT_VENDOR_VERSION_MAJOR,
            KSCRIPT_VENDOR_VERSION_MINOR,
            KSCRIPT_VENDOR_VERSION_PATCH);

        printf("Copyright © 2026 KrabbaTek Group\n");

        return 0;
    }

    printf("\e[1;31mERROR\e[0m: Unknown command \"%s\"\n", argv[1]);
    printUsage();

    return 1;
}