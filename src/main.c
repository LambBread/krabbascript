#include <stdio.h>
#include <common/common.h>

#include <toml/tomlc17.h>
#include <string.h>

#include <unistd.h>
#include <tokenizer/tokenizer.h>

#include <parser/parser.h>

int main(int argc, char* argv[])
{
    (void)argv;

    if (argc < 2)
    {
        printUsage();

        return 0;
    }

    if (strcmp(argv[1], "version") == 0)
    {
        printf("KrabbaScript (kscript) %d.%d.%d-%s (%s)\n",
               KSCRIPT_VERSION_MAJOR,
               KSCRIPT_VERSION_MINOR,
               KSCRIPT_VERSION_PATCH,
               KSCRIPT_VERSION_IDENT,
               KSCRIPT_VENDOR);

        printf("Copyright © 2026 KrabbaTek Group\n");

        return 0;
    }
    else if (strcmp(argv[1], "build") == 0)
    {
        if (argc < 3)
        {
            printf("\033[1;31mERROR\033[0m: No input file|directory\n");
            usageBuild();

            return 1;
        }

        int result = isFile(argv[2]);
        if (result == KSCRIPT_FILE)
        {
            char_vector_t* source = fileToCharVector(argv[2]);

            token_vector_t* tokens = tokenize(source, argv[2]);
            deTokenize(tokens);

            size_t index = 0;
            astParseExpression(tokens, &index, 0.0f);

            printErrorsGenerated();
        }

        else if (result == KSCRIPT_DIRECTORY)
        {
            errors_generated++;
            printf("\033[1;31mNOT IMPLEMENTED ERROR\033[0m: Building a "
                   "directory is not implemented yet\n");

            printErrorsGenerated();
        }
        else
        {
            errors_generated++;
            printf("\033[1;31mOPENING ERROR\033[0m: No such file or directory "
                   "\"%s\"\n",
                   argv[2]);
            printErrorsGenerated();
        }

        return 0;
    }
    else if (strcmp(argv[1], "krabba") == 0)
    {
        printKrabba();
        printf("Krabba!\n");
        return 0;
    }

    printf("\033[1;31mERROR\033[0m: Unknown command \"%s\"\n", argv[1]);
    printUsage();

    return 64;
}
