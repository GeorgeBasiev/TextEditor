#include "commands.h"

int main()
{
    char* filename = "output.txt";
    window scr;
    scr.rows = 25;
    scr.columns = 80;
    scr.length = scr.rows*scr.columns;
    AllocWindow(&scr);
    char* command = malloc(sizeof(char)*scr.length+12);
    CommandCenter(&scr, command, filename);
    free(scr.text);
    free(command);
    return 0;
}