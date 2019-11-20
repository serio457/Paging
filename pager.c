// FILE: pager.c
//
//Comments
//We considered adding flags to prevent multiple specifications for a single flag, but
//instead decided to leave them out since Bash allows for multiple specifcations of the
//same flag, so ours does too ;)
//
#include "pager.h"

int main(int argc, char *argv[])
{
    if (argc > 11)
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        return 0;
    }
    //
    char type[10] = "FIFO";
    char infile[100] = "pager.in";
    char memLocationString[100];
    char processName[20];
    int numFrames = 3;
    int memorySize = 4096;
    int pagesize = 512;
    int maxMemAddress, numMemLocations;
    int memoryLocations[MAX_MEM_LOCATIONS];
    BOOL fileFlag = FALSE;
    BOOL textFound = FALSE;
    FILE *file;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-type"))
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING VALUE\n");
                return 0;
            }
            strcpy(type, argv[i + 1]);
            if (!((!strcasecmp(argv[i + 1], "FIFO")) || (!strcasecmp(argv[i + 1], "LRU")) || (!strcasecmp(argv[i + 1], "MFU")) || (!strcmp(argv[i + 1], "RANDOM"))))
            {
                printf("ERROR: INVALID TYPE. VALID TYPES INCLUDE: FIFO, LRU, MFU, and RANDOM\n");
                return 0;
            }
            i++;
        }
        if (!strcmp(argv[i], "-frames"))
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING VALUE\n");
                return 0;
            }
            numFrames = isArgNum(argv[i + 1]);
            if (numFrames == -1)
            {
                printf("ERROR: ARGUMENT MUST BE A POSITIVE, NON-ZERO INTEGER.\n"); // EDIT: PASS IN FLAG NAME FOR CLARIFICATION
                return 0;
            }
            i++;
        }
        if (!strcmp(argv[i], "-memory"))
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING VALUE\n");
                return 0;
            }
            memorySize = isArgNum(argv[i + 1]);
            if (memorySize == -1)
            {
                printf("ERROR: ARGUMENT MUST BE A POSITIVE, NON-ZERO INTEGER.\n"); // EDIT: PASS IN FLAG NAME FOR CLARIFICATION
                return 0;
            }
            i++;
        }
        if (!strcmp(argv[i], "-pagesize"))
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING VALUE\n");
                return 0;
            }
            pagesize = isArgNum(argv[i + 1]);
            if (pagesize == -1)
            {
                printf("ERROR: ARGUMENT MUST BE A POSITIVE, NON-ZERO INTEGER.\n"); // EDIT: PASS IN FLAG NAME FOR CLARIFICATION
                return 0;
            }
            i++;
        }
        //checking for infile argument by seeing if previous argument had a hyphen
        if (strncmp(argv[i - 1], "-", 1))
        {
            //if (fileFlag)
            //{
            //    printf ("ERROR: TOO MANY FILES SPECIFIED.\n");
            //    return 0;
            //}
            strcpy(infile, argv[i]);
            fileFlag = 1;
        }

        //set the maximum memory location
        maxMemAddress = memorySize -1;

        file = fopen(infile, "r");
        if (file)
        {
            int currentMemLocation = 0, c;
            if (fscanf(file, "%d", &c) != EOF)
            {
                textFound = TRUE;
                fscanf(file, "%s", processName);
                while (fscanf(file, "%d", &c) != EOF)
                {
                    //take in the line & save values
                    fscanf(file, "%s", memLocationString);
                    printf ("read in: %s", memLocationString);
                    currentMemLocation = isArgNum (memLocationString);
                    if (currentMemLocation == -1)
                    {
                        printf("ERROR: MEMORY LOCATIONS MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                        return 0;
                    }
                    //test to make sure no vertex name is too long
                    if (currentMemLocation > maxMemAddress)
                    {
                        printf("ERROR: MEMORY LOCATION %d IS GREATER THAN MAXIMUM OF %d\n", currentMemLocation, maxMemAddress);
                        return 0;
                    }
                    printf ("Current Mem Location: %d, Num Memory Locations: %d\n", currentMemLocation, numMemLocations);
                    //add the read memory location into an array of memory locations
                    storeMemoryLocations (memoryLocations, numMemLocations, currentMemLocation);
                    numMemLocations++;
                }
            }
            fclose(file);
            if (!textFound)
            {
                printf("ERROR: INPUT FILE CONTAINS NO TEXT\n");
                return 0;
            }
        }
        else
        {
            //error if an input file is not found
            printf("ERROR: INPUT FILE NOT FOUND\n");
            return 0;
        }
    }
    printf ("process name: %s\n", processName);
    printf("Type: %s\n", type);
    printf("Frames: %d\n", numFrames);
    printf("Memory: %d\n", memorySize);
    printf("Pagesize: %d\n", pagesize);
    printf("infile: %s\n", infile);
    
    for (int i=0; i<numMemLocations; i++)
    {
        printf("Memory location %d: %d\n", i, memoryLocations[i]);
    }
}

//FUNCTIONS

int isArgNum(char stringIn[])
{
    int j, outNum;
    const int len = strlen(stringIn);
    char numString[len];
    strcpy(numString, stringIn);

    for (j = 0; j < len; j++)
    {
        if (!isdigit(numString[j]))
        {
            return -1;
        }
    }
    outNum = atoi(stringIn);
    if (outNum <= 0)
    {
        return -1;
    }
    return outNum;
}

void storeMemoryLocations(int memoryLocations[], int numMemoryLocations, int currentMemoryLocation)
{
    memoryLocations[numMemoryLocations] = currentMemoryLocation;
}