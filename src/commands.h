#include "texteditor.h"

char** TakeCommand(char* str);
int CountArgs(char* str, char c);
void ReadStringFromConsole(char* buffer, int buffer_size);
void CommandCenter(window* scr, char* command, char* file);

// { "Stop", "Add", "Move",
//         "Insert","Put","Remove", "Del",
//         "Movelw","Moverw","Upcase",
//         "Lowcase","Replace","Find","Save", "Load" };