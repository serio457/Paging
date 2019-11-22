//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE: pager.c
//// Main Pager file
//// Takes in optional parameters (pagesize, memory, infile, frames, type) to find the number of page faults using various algorithms (FIFO, LRU, MFU, Random)
////
////Comments
//// if you type in a hyphen with an invalid argument after it doesn't error, it just ignores it

#include "pager.h"

int main(int argc, char *argv[])
{
    // seeds random with time
    srand(time(0));
    if (argc > 11)
    {
        printf("ERROR: TOO MANY ARGUMENTS\n");
        return 0;
    }
    // global variables, including default values, flags, and variables necessary throughout
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
    BOOL pagesizeFlag = FALSE;
    BOOL framesFlag = FALSE;
    BOOL typeFlag = FALSE;
    BOOL memoryFlag = FALSE;
    BOOL fileFlag = FALSE;
    BOOL textFound = FALSE;
    int verbose = 0;
    PAGE pageNum;
    FILE *file;
    PAGETABLE table;

    // reading in command line arguments and assigning of parameters
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-type"))
        {
            if (typeFlag)
            {
                printf("ERROR: MULTIPLE INSTANCES OF \'-type\' PARAMETER\n");
                return 0;
            }
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING TYPE VALUE\n");
                return 0;
            }
            if (!strcasecmp(argv[i + 1], "FIFO"))
            {
                algCode = FIFO_CODE;
            }
            else if (!strcasecmp(argv[i + 1], "LRU"))
            {
                algCode = LRU_CODE;
            }
            else if (!strcasecmp(argv[i + 1], "MFU"))
            {
                algCode = MFU_CODE;
            }
            else if (!strcmp(argv[i + 1], "RANDOM"))
            {
                algCode = RANDOM_CODE;
            }
            else
            {
                printf("ERROR: INVALID TYPE. VALID TYPES INCLUDE: FIFO, LRU, MFU, and RANDOM\n");
                return 0;
            }
            typeFlag = TRUE;
            i++;
            continue;
        }
        if (!strcmp(argv[i], "-frames"))
        {
            if (framesFlag)
            {
                printf("ERROR: MULTIPLE INSTANCES OF \'-frames\' PARAMETER\n");
                return 0;
            }
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING FRAMES VALUE\n");
                return 0;
            }
            numFrames = isArgNum(argv[i + 1]);
            if (numFrames == -1)
            {
                printf("ERROR: FRAMES MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                return 0;
            }
            i++;
            continue;
        }
        if (!strcmp(argv[i], "-memory"))
        {
            if (memoryFlag)
            {
                printf("ERROR: MULTIPLE INSTANCES OF \'-memory\' PARAMETER\n");
                return 0;
            }
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING MEMORTY VALUE\n");
                return 0;
            }
            memorySize = isArgNum(argv[i + 1]);
            if (memorySize == -1)
            {
                printf("ERROR: MEMORY MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                return 0;
            }
            memoryFlag = TRUE;
            i++;
            continue;
        }
        if (!strcmp(argv[i], "-pagesize"))
        {
            if (pagesizeFlag)
            {
                printf("ERROR: MULTIPLE INSTANCES OF \'-pagesize\' PARAMETER\n");
                return 0;
            }
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PAGESIZE VALUE\n");
                return 0;
            }
            pagesize = isArgNum(argv[i + 1]);
            if (pagesize == -1)
            {
                printf("ERROR: PAGESIZE MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
            }
            i++;
            continue;
        }
        if (!strncmp(argv[i], "-v", 2))
        {
            if (verbose)
            {
                printf("ERROR: MULTIPLE INSTANCES OF \'VERBOSE\' FLAG\n");
                return 0;
            }
            verbose = 1; //basic verbose level
            if (!strcmp(argv[i], "-vv"))
            {
                verbose = 2; //advanced verbose level
            }
            continue;
        }

        if (!strcmp(argv[i], "-help"))
        {
            printf("-type: selects paging algorithm; Options are the following: FIFO, LRU, MFU, and Random\n\n");
            printf("-frames: sets the number of physical frames available\n\n");
            printf("-memory: sets the size of memory in bytes\n\n");
            printf("-pagesize: sets the size of the page in decimal number of bytes\n\n");
            printf("file name can be specified, default is pager.in\n\n");
            printf("-v[v]: displays information about the process [and the memory locations being accessed]\n\n");
            return (0);
        }
        //checking for infile argument by seeing if previous argument had a hyphen
        if (strncmp(argv[i], "-", 1))
        {
            if (fileFlag)
            {
                printf("ERROR: TOO MANY FILES SPECIFIED\n");
                return 0;
            }
            if (strcmp(argv[i], "pager.in"))
            {
                strcpy(infile, argv[i]);
            }
            fileFlag = TRUE;
            continue;
        }
    }
    //set the maximum memory location
    maxMemAddress = memorySize - 1;
    if (memorySize % pagesize != 0)
    {
        printf("ERROR: MEMORY MUST BE DIVISIBLE BY PAGE SIZE.\n");
        return 0;
    }
    //reading from infile
    file = fopen(infile, "r");
    if (file)
    {
        int currentMemLocation = 0, c;
        // read from file a line at a time until end of file character is found
        if (fscanf(file, "%d", &c) != EOF)
        {
            textFound = TRUE;
            fscanf(file, "%s", processName);
            while (fscanf(file, "%s", memLocationString) != EOF)
            {
                //take in the line & save values
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
        printf("ERROR: INPUT FILE \'%s\' NOT FOUND\n", infile);
        return 0;
    }

    //set the number of pages
    numPages = memorySize / pagesize;
    //set the size of our page table (number of frames) EDIT LATER
    //test for base 2 stuff
    setTableSize(&table, numFrames);

    //initialize frames' valid bit
    for (int i = 0; i < getTableSize(table); i++)
    {
        *getPage(getFrame(&table, i)) = -1;
        *getValid(getFrame(&table, i)) = FALSE;
    }
    // use case to determine which "-type" to use
    switch (algCode)
    {
    case FIFO_CODE:
        numPageFaults = FIFO(&table, memoryLocations, numMemLocations, pagesize);
        break;
    case LRU_CODE:
        numPageFaults = LRU(&table, memoryLocations, numMemLocations, pagesize);
        break;
    case MFU_CODE:
        numPageFaults = MFU(&table, memoryLocations, numMemLocations, pagesize);
        break;
    case RANDOM_CODE:
        numPageFaults = Random(&table, memoryLocations, numMemLocations, pagesize);
        break;
    default:
        printf("ERROR: YOU HAVE ENTERED AN INVALID ALGORITHM\n"); // It should never get here, but black magic exists, so just in case.
        return 0;
        break;
    }
    if (verbose)
    {
        printf("Process name: %s\n", processName);
        printf("Paging algorithm type: ");
        if (algCode == FIFO_CODE)
        {
            printf("FIFO\n");
        }
        if (algCode == LRU_CODE)
        {
            printf("LRU\n");
        }
        if (algCode == MFU_CODE)
        {
            printf("MFU\n");
        }
        if (algCode == RANDOM_CODE)
        {
            printf("RANDOM\n");
        }
        printf("Pagesize: %d\n", pagesize);
        printf("Number of frames: %d\n", numFrames);
        printf("Number of pages: %d\n", numPages);
        printf("Memory size: %d\n", memorySize);
        if (verbose == 2)
        {
            printf("Memory locations entered and pages associated:\n");
            for (int i = 0; i < numMemLocations; i++)
            {
                printf("\tMemory Location %d is on page %i\n", memoryLocations[i], memoryLocations[i] / pagesize);
            }
        }
    }

    printf("\n*** Number of page faults for %s: %d ***\n\n", processName, numPageFaults);
}

///FUNCTIONS
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
