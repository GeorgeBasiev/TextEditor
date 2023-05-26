#include <stdio.h>
#include <stdlib.h>
#include "texteditor.h"
#include "ministring.h"

#define SPACE_ERROR "\nNo more space for this word\n"
#define RED "\033[1;31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RESET_COLOUR "\033[0m"

void AllocWindow(window* scr)
{
    scr->text = malloc(scr->length * sizeof(char));
    for (int i = 0; i < scr->length; ++i)
        scr->text[i] = ' ';
}

void PrintText(window* scr)
{
    printf(RED "@");
    for (int i = 0; i < scr->columns; ++i)
        printf("-");
    printf("@\n" RESET_COLOUR);

    for (int i = 0; i < scr->length; ++i)
    {
        if (i % scr->columns == 0)
        {
            if (i != 0)
                printf(RED "|\n");
            printf(RED "|" RESET_COLOUR);
        }
        if (i == scr->cursor - 1)
            printf(BLUE "%c" RESET_COLOUR, scr->text[i]);
        else
            printf("%c", scr->text[i]);
    }

    printf(RED "|\n@");
    for (int i = 0; i < scr->columns; ++i)
        printf("-");
    printf("@\n" RESET_COLOUR);
}

int FindLastEmpty(window* scr)
{
    int cursor;
    for (int i = scr->length - 1; i >= 0; --i)
    {
        if (scr->text[i] != ' ')
        {
            cursor = i + 1;
            return cursor;
        }
    }
    cursor = 0;
    return cursor;
}

void Add(char* word, window* scr)
{
    int last_empty = FindLastEmpty(scr) + 1;
    int length_of_word = Length(word);

    if (last_empty + length_of_word >= scr->length)
    {
        scr->cursor = scr->length / 2;
        printf(SPACE_ERROR);
        return;
    }

    for (int i = 0; i < length_of_word; ++i)
        scr->text[i + last_empty] = word[i];
    scr->cursor = last_empty + length_of_word;
}

void Move(window* scr, int pos)
{
    scr->cursor = pos;
}

void AddToPos(char* word, int pos, window* scr)
{
    int last_empty = FindLastEmpty(scr);
    int length_of_word = Length(word);

    if (last_empty + length_of_word >= scr->length)
    {
        scr->cursor = scr->length / 2;
        printf(SPACE_ERROR);
        return;
    }

    for (int i = scr->length; i >= pos + length_of_word; --i)
        scr->text[i] = scr->text[i - length_of_word];
    for (int i = 0; i < length_of_word; ++i)
        scr->text[pos + i] = word[i];

    scr->cursor = pos + length_of_word;
}

void AddUnderCursor(char* word, window* scr)
{
    AddToPos(word, scr->cursor, scr);
}

void RemoveFromXtoY(int x, int y, window* scr)
{
    if (x > y || x > scr->length || y > scr->length)
    {
        printf("Error Remove: Index out of range\a\n");
        return;
    }

    for (int i = x; i <= y; ++i)
        scr->text[i] = ' ';

    scr->cursor = x;
}

void Delete(window* scr)
{
    scr->text[scr->cursor - 1] = ' ';
    --scr->cursor;
}

void DeleteN(window* scr, int n)
{
    for (int i = scr->cursor - n - 1; i <= scr->cursor - 1; ++i)
        scr->text[i] = ' ';
    scr->cursor -= n;
}

void MoveLeft(int n, window* scr)
{
    int count_of_words = 0;
    int old_cursor = scr->cursor;
    while (count_of_words < n)
    {
        --scr->cursor;
        if (scr->cursor < 0)
        {
            printf("MoveLeft Error: more words than exists\n");
            scr->cursor = old_cursor;
            return;
        }
        if ((scr->text[scr->cursor] == ' ' && scr->text[scr->cursor + 1] != ' ') || scr->cursor == 0)
            ++count_of_words;
    }
}

void MoveRight(int n, window* scr)
{
    int count_of_words = 0;
    int old_cursor = scr->cursor;
    while (count_of_words < n)
    {
        ++scr->cursor;
        if (scr->cursor > scr->length)
        {
            printf("MoveRight Error: more words than exists\n");
            scr->cursor = old_cursor;
            return;
        }
        if ((scr->text[scr->cursor] == ' ' && scr->text[scr->cursor - 1] != ' ') ||
            scr->cursor == scr->length)
            ++count_of_words;
    }
}

void Upcase(window* scr)
{
    if (scr->text[scr->cursor] == ' ')
    {
        return;
    }

    int pos = scr->cursor;
    while (scr->text[pos] != ' ' && pos != -1)
        --pos;
    ++pos;
    while (scr->text[pos] != ' ' && pos != scr->length + 1)
    {
        scr->text[pos] = toupper(scr->text[pos]);
        ++pos;
    }
}

void Lowcase(window* scr) //все слово изменять
{
    if (scr->text[scr->cursor] == ' ')
    {
        return;
    }

    int pos = scr->cursor;
    while (scr->text[pos] != ' ' && pos != -1)
        --pos;
    ++pos;
    while (scr->text[pos] != ' ' && pos != scr->length + 1)
    {
        scr->text[pos] = tolower(scr->text[pos]);
        ++pos;
    }
}

int CountOccurrences(window* scr, char* word) {
    int length_of_word = Length(word);
    int count = 0;


    for (int i = 0; i <= scr->length - length_of_word; ++i) {
        int index = 0;
        for (int j = 0; j < length_of_word; j++) {
            if (scr->text[i + j] != word[j]) {
                index = -1;
                break;
            }
        }
        if (index == 0) {
            count++;
        }
    }


    return count;
}


int* FindOccurrences(window* scr, char* word) {
    int length_of_word = Length(word);
    int count = CountOccurrences(scr, word);

    int* occurrences = malloc(count * sizeof(int));

    int occurrence_index = 0;
    for (int i = 0; i <= scr->length - length_of_word; i++) {
        int index = 0;
        for (int j = 0; j < length_of_word; j++) {
            if (scr->text[i + j] != word[j]) 
            {
                index = -1;
                break;
            }
        }
        if (index == 0) 
        {
            occurrences[occurrence_index] = i;
            occurrence_index++;
        }
    }

    return occurrences;
}

void ReplaceOne(window* scr, char* old_word, char* new_word, int index)
{
    int old_length = Length(old_word);
    int new_length = Length(new_word);
    int gap = new_length - old_length;
    int last_empty = FindLastEmpty(scr);
    char tail[last_empty - index - old_length];
    for (int i = index + old_length; i < last_empty; ++i)
    {
        tail[i - index - old_length] = scr->text[i];
    }
    if (gap > 0)
    {
        for (int i = 0; i < new_length; ++i)
        {
            scr->text[i + index] = new_word[i];
        }
        for (int i = 0; i < last_empty - index - old_length; ++i)
        {
            scr->text[i + index + new_length] = tail[i];
        }
        return;
    }
    if (gap < 0)
    {
        for (int i = 0; i < new_length; ++i)
        {
            scr->text[i + index] = new_word[i];
        }
        for (int i = 0; i < last_empty - index - old_length; ++i)
        {
            scr->text[i + index + new_length] = tail[i];
        }
        for (int i = last_empty + gap; i < last_empty; ++i)
            scr->text[i] = ' ';
        return;
    }
    for (int i = 0; i < new_length; ++i)
        scr->text[i + index] = new_word[i];
}

void ReplaceAll(window* scr, char* old_word, char* new_word)
{
    int count_of_words = CountOccurrences(scr, old_word);
    int* indexes = FindOccurrences(scr, old_word);
    int gap = Length(new_word) - Length(old_word);
    printf("A%dA\n", gap);
    for (int i = 0; i < count_of_words; ++i)
    {
        ReplaceOne(scr, old_word, new_word, indexes[i]);
        if (i != count_of_words - 1)
            for (int j = i + 1; j < count_of_words; ++j)
            {
                indexes[j] += gap;
                //printf("%d ", indexes[j]);
            }
    }
    free(indexes);
}

void FindAndBright(window* scr, char* word)
{
    int length_of_word = Length(word);
    int* indexes = FindOccurrences(scr, word);
    int count_of_words = CountOccurrences(scr, word);
    if (count_of_words == 0)
    {
        printf("Error: 404 not found\n\a");
        return;
    }
    scr->cursor = indexes[0];
    printf(RED "@");
    for (int i = 0; i < scr->columns; ++i)
        printf("-");
    printf("@\n" RESET_COLOUR);

    for (int i = 0; i < scr->length; ++i)
    {
        if (i % scr->columns == 0)
        {
            if (i != 0)
                printf(RED "|\n");
            printf(RED "|" RESET_COLOUR);
        }
        int flag_is_word = 0;
        for (int j = 0; j < count_of_words; ++j)
            if (i >= indexes[j] && i <= indexes[j] + length_of_word)
                flag_is_word = 1;
        if (flag_is_word == 1)
            printf(YELLOW "%c" RESET_COLOUR, scr->text[i]);
        else
            printf("%c", scr->text[i]);
    }

    printf(RED "|\n@");
    for (int i = 0; i < scr->columns; ++i)
        printf("-");
    printf("@\n" RESET_COLOUR);
}

void SaveFile(window* scr, char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < scr->length; ++i)
    {
        if (i % scr->columns == 0 && i != 0)
        {
            fprintf(file, "\n");
        }
        if (i == scr->cursor - 1)
            fprintf(file, "%c", scr->text[i]);
        else
            fprintf(file, "%c", scr->text[i]);
    }
    fclose(file);
}

void ReadFile(window* scr, char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char c;
    int index = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\0' || c == '\n')
            continue;
        scr->text[index] = c;
        ++index;
    }

    if (index < scr->length)
    {
        for (int i = index; i < scr->length; ++i)
            scr->text[i] = ' ';
    }

    fclose(file);
}


