#include "texteditor.h"
#include "ministring.h"

int CountArgs(char* str, char c)
{
    int index = 0;
    int length = Length(str);
    if (length == 0)
        return 0;

    int start = 0;
    int end = length - 1;
    while (str[start] == c)
        start++;
    while (str[end] == c)
        end--;
    if (start > end)
        return 0;
    for (int i = start; i <= end; i++) {
        if (str[i] == c && str[i + 1] == c)
            continue;
        if (str[i] == c && str[i + 1] != c)
            index++;
    }
    return (index + 1);
}

char** TakeCommand(char* str)
{
    char c = ' ';
    int length = Length(str);
    int count_of_subs = CountArgs(str, c);
    char** result = malloc(sizeof(char*) * (count_of_subs + 1));
    int start = 0;
    int end = length - 1;
    while (str[start] == c)
        ++start;
    while (str[end] == c)
        --end;
    if (start > end)
    {
        printf("Split Error: no other chars in string found\n");
        return NULL;
    }

    int index = 0;
    int current = start;
    int prev = start;
    for (int i = start + 1; i <= end; ++i)
    {
        if (str[i] == c)
        {
            if (str[i - 1] != c)
            {
                int temp_length = i - prev + 1;
                char* temp_str = malloc(sizeof(char) * temp_length);
                for (int j = 0; j < temp_length - 1; ++j)
                    temp_str[j] = str[j + prev];
                temp_str[temp_length - 1] = '\0';
                result[index] = temp_str;
                ++index;
            }
            prev = i + 1;
        }
    }
    int temp_length = end - prev + 2;
    char* temp_str = malloc(sizeof(char) * temp_length);
    for (int j = 0; j < temp_length - 1; ++j)
        temp_str[j] = str[j + prev];
    temp_str[temp_length - 1] = '\0';
    result[index] = temp_str;
    result[count_of_subs] = NULL;
    return result;
}

void ReadStringFromConsole(char* buffer, int buffer_size)
{
    int i = 0;
    char ch;
    while (i < buffer_size - 1) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        buffer[i] = ch;
        i++;
    }

    buffer[i] = '\0';
}

void CommandCenter(window* scr, char* command, char* filename)
{
    int exit = 1;
    while (exit > 0)
    {
        ReadStringFromConsole(command, scr->length + 12);
        char** args = TakeCommand(command);
        if (args == NULL)
            continue;
        int count_of_args = CountArgs(command, ' ');
        if(count_of_args > 3)
        {
            printf("Command Error: too many args\n");
        }
        char* list_of_commands[] = { "Stop", "Add", "Move",
        "Insert","Put","Remove", "Del",
        "Movelw","Moverw","Upcase",
        "Lowcase","Replace","Find","Save", "Load" };
        int number_of_command = -1;
        for (int i = 0; i < 15; ++i) //15
        {
            if (StrCmp(args[0], list_of_commands[i]) == 0)
                number_of_command = i;
        }
        //printf("%d\n", number_of_command);
        switch (number_of_command)
        {
        case 0:
        {
            --exit;
            break;
        }
        case 1:
        {
            if (count_of_args == 2)
            {
                Add(args[1], scr);
                PrintText(scr);
            }
            else
                printf("Error Add: not enough args\n");
            break;
        }
        case 2:
        {
            if (count_of_args == 2 && IsPositiveNumeric(args[1]))
            {
                int index = atoi(args[1]);
                if (index < scr->length)
                {
                    Move(scr, index);
                    PrintText(scr);
                }
                else
                    printf("Error Move: index out of range or negative int\n");
            }
            else
                printf("Error Move: not enough args or not int arg[1]\n");
            break;
        }
        case 3:
        {
            if (count_of_args == 3 && IsPositiveNumeric(args[1]))
            {
                int index = atoi(args[1]);
                if (index < scr->length)
                {
                    AddToPos(args[2], index, scr);
                    PrintText(scr);
                }
                else
                    printf("Error Insert: index out of range\n");
            }
            else
                printf("Error Insert: not enough args or not int arg[2]\n");
            break;
        }
        case 4:
        {
            if (count_of_args == 2)
            {
                AddUnderCursor(args[1], scr);
                PrintText(scr);
            }
            else
                printf("Error Put: not enough args");
            break;
        }
        case 5:
        {
            if (count_of_args == 3 && IsPositiveNumeric(args[1]) && IsPositiveNumeric(args[2]))
            {
                int start = atoi(args[1]);
                int end = atoi(args[2]);
                RemoveFromXtoY(start, end, scr);
                PrintText(scr);
            }
            else
                printf("Error Remove: not enough args or not int args[1] & args[2]\n");
            break;
        }
        case 6:
        {
            if(count_of_args == 1)
            {
                Delete(scr);
                PrintText(scr);
            }
            else if(count_of_args == 2 && IsPositiveNumeric(args[1]))
            {
                int n = atoi(args[1]);
                if(scr->cursor - n >= 0)
                {
                    DeleteN(scr, n);
                    PrintText(scr);
                }
                else
                    printf("Error Del: too big n\n");
            }
            else
                printf("Error Del: not enough args or not int arg[1]\n");
            break;
        }
        case 7:
        {
            if(count_of_args == 2 && IsPositiveNumeric(args[1]))
            {
                int n = atoi(args[1]);
                MoveLeft(n, scr);
                PrintText(scr);
            }
            else
                printf("Error Movelw: not enough args or not int args[1]\n");
            break;
        }
        case 8:
        {
            if(count_of_args == 2 && IsPositiveNumeric(args[1]))
            {
                int n = atoi(args[1]);
                MoveRight(n, scr);
                PrintText(scr);
            }
            else
                printf("Error Moverw: not enough args or not int args[1]\n");
            break;
        }
        case 9:
        {
            if(count_of_args == 1)
            {
                Upcase(scr);
                PrintText(scr);
            }
            else
                printf("Error Upcase: too many args\n");
            break;
        }
        case 10:
        {
            if(count_of_args == 1)
            {
                Lowcase(scr);
                PrintText(scr);
            }
            else
                printf("Error Lowcase: too many args\n");
            break;
        }
        case 11:
        {
            if(count_of_args == 3)
            {
                ReplaceAll(scr, args[1], args[2]);
                FindAndBright(scr, args[2]);
            }
            else
                printf("Error Replace: not enough args\n");
            break;
        }
        case 12:
        {
            if(count_of_args == 2)
                FindAndBright(scr, args[1]);
            else
                printf("Error Find: wrong number of args\n");
            break;
        }
        case 13:
        {
            if(count_of_args == 1)
                SaveFile(scr, filename);
            else 
                printf("Error Save: wrong number of args\n");
            break;
        }
        case 14:
        {
            if(count_of_args == 1)
            {
                ReadFile(scr, filename);
                PrintText(scr);
            }
            else
                printf("Error Load: wrong number of args\n");
            break;
        }
        default:
        {
            printf("Something went wrong... Try again\n");
        }
        }
        for (int i = 0; i < count_of_args; ++i)
            free(args[i]);
        free(args);
    }
}