#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    char* text;
    int rows;
    int columns;
    int length;
    int cursor;
} window;

void AllocWindow(window* scr);
int FindLastEmpty(window* scr);
void Add(char* word, window* scr);
void PrintText(window* scr);
void Move(window* scr, int pos);
void AddToPos(char* word, int pos, window* scr);
void AddUnderCursor(char* word, window *scr);
void RemoveFromXtoY(int x, int y, window *scr);
void Delete(window* scr);
void DeleteN(window* scr, int n);
void MoveLeft(int n, window* scr);
void MoveRight(int n, window* scr);
void Upcase(window* scr);
void Lowcase(window* scr);
int* FindOccurrences(window* scr, char* word);
int CountOccurrences(window *scr, char* word);
void ReplaceOne(window* scr, char* old_word, char* new_word, int index);
void ReplaceAll(window *scr, char* old_word, char* new_word);
void FindAndBright(window* scr, char* word);
void SaveFile(window* scr, char*);
void ReadFile(window* scr, char* filename);
