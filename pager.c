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
    // char type[10] = "FIFO";
    char infile[100] = "pager.in";
    char memLocationString[100];
    char processName[20];
    int numFrames = 3;
    int memorySize = 4096;
    int pagesize = 512;
    int algCode = 1;
    int firstIn = 0;
    int numPageFaults = 0;
    int maxMemAddress, numMemLocations, numPages;
    int memoryLocations[MAX_MEM_LOCATIONS];
    BOOL fileFlag = FALSE;
    BOOL textFound = FALSE;
    PAGE pageNum;
    FILE *file;

    PAGETABLE table;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-type"))
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING VALUE\n");
                return 0;
            }
            //strcpy(type, argv[i + 1]);
            if (!strcasecmp(argv[i + 1], "FIFO"))
            {
                algCode = FIFO_CODE;
            }
            if (!strcasecmp(argv[i + 1], "LRU"))
            {
                algCode = LRU_CODE;
            }
            if (!strcasecmp(argv[i + 1], "MFU"))
            {
                algCode = MRU_CODE;
            }
            if (!strcmp(argv[i + 1], "RANDOM"))
            {
                algCode = RANDOM_CODE;
            }
            else
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
        maxMemAddress = memorySize - 1;
        if (memorySize % pagesize != 0)
        {
            printf("ERROR: MEMORY MUST BE DIVISIBLE BY PAGE SIZE.\n");
            return 0;
        }
        //set the number of pages
        numPages = memorySize / pagesize;
        //set the size of our page table (number of frames) EDIT LATER
        table.size = numFrames;

        file = fopen(infile, "r");
        if (file)
        {
            int currentMemLocation = 0, c;
            if (fscanf(file, "%d\n", &c) != EOF)
            {
                textFound = TRUE;
                fscanf(file, "%s", processName);
                while (fscanf(file, "%s\n", memLocationString) != EOF)
                {
                    //take in the line & save values
                    printf("read in: %s\n", memLocationString);
                    currentMemLocation = isArgNum(memLocationString);
                    if (currentMemLocation == -1)
                    {
                        printf("ERROR: MEMORY LOCATIONS MUST BE A NON-NEGATIVE INTEGER.\n");
                        return 0;
                    }
                    //test to make sure no vertex name is too long
                    if (currentMemLocation > maxMemAddress)
                    {
                        printf("ERROR: MEMORY LOCATION %d IS GREATER THAN MAXIMUM OF %d\n", currentMemLocation, maxMemAddress);
                        return 0;
                    }
                    //add the read memory location into an array of memory locations
                    storeMemoryLocations(memoryLocations, numMemLocations, currentMemLocation);
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

    //initialize frames' valid bit
    for (int i = 0; i < table.size; i++)
    {
        table.frames[i].page = -1;
        table.frames[i].validBit = FALSE;
    }

    printf("process name: %s\n", processName);
    printf("Type: ");
    if (algCode == FIFO_CODE)
    {
        printf("FIFO\n");
    }
    if (algCode == LRU_CODE)
    {
        printf("LRU\n");
    }
    if (algCode == MRU_CODE)
    {
        printf("MRU\n");
    }
    if (algCode == RANDOM_CODE)
    {
        printf("RANDOM\n");
    }

    switch (algCode)
    {
    case FIFO_CODE:
        numPageFaults = FIFO(&table, memoryLocations, numMemLocations, pagesize);
        break;
    case LRU_CODE:
        //LRU(table, pageNum, leastRecentlyUsed);
        //pageFault++;
        break;
    case MRU_CODE:
        //MRU(table, pageNum, mostRecentlyUsed);
        //pageFault++;
        break;
    case RANDOM_CODE:
        //RANDOM(table, pageNum);
        //pageFault++;
        break;
    default:
        printf("ERROR: YOU HAVE ENTERED AN INVALID ALGORITHM\n"); // It should never get here, but black magic exists, so just in case.
        return 0;
        break;
    }

    printf("\n\n*** NUMBER OF PAGE FAULTS: %d ***\n\n", numPageFaults);
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
    if (outNum < 0)
    {
        return -1;
    }
    return outNum;
}

void storeMemoryLocations(int memoryLocations[], int numMemoryLocations, int currentMemoryLocation)
{
    memoryLocations[numMemoryLocations] = currentMemoryLocation;
}