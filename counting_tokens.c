//CS20B1037
//Habel Saju Zachariah
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct uniqueTokens
{
    char str[100];
    int count;
};
struct uniqueTokens tokens[1000];
 
int a = 0;

void findtoken(char s[])
{
    for (int i = 0; i < a; i++)
    {
        if (strcmp(tokens[i].str, s) == 0)
        {
            tokens[i].count += 1;
            return;
        }
    }
    strcpy(tokens[a].str, s);
    tokens[a].count = 1;
    a++;
    return;
}

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}

bool validIdentifier(char *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

bool isKeyword(char *str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
        !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "char") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return (true);
    return (false);
}

bool isInteger(char *str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

bool isRealNumber(char *str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

char *subString(char *str, int left, int right)
{
    int i;
    char *subStr = (char *)malloc(
        sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void parse(char *str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right)
    {
        if (isDelimiter(str[right]) == false)
            right++;

        if (isDelimiter(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
            {
                if (str[right] != '=')
                {
                    char subStr[2];
                    subStr[0] = str[right];
                    subStr[1] = '\0';
                    findtoken((subStr));
                }
                else if (str[right] == '=' && str[right + 1] != '=')
                {
                    char subStr[2];
                    subStr[0] = str[right];
                    subStr[1] = '\0';
                    findtoken((subStr));
                }
                else
                {
                    char subStr[3] = "==\0";
                    findtoken((subStr));
                }
            }

            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
        {
            char *subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
            {

                findtoken(subStr);
            }

            else if (isInteger(subStr) == true)
            {
                findtoken(subStr);
            }

            else if (isRealNumber(subStr) == true)
            {
                findtoken(subStr);
            }

            else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
            {
                if (subStr[0] == '!')
                {
                    if (str[right] == '=')
                    {
                        subStr[1] = '=';
                        subStr[2] = '\0';
                        findtoken(subStr);\
                    }
                    else
                    {
                        findtoken(subStr);
                    }
                }
                else
                {

                    findtoken(subStr);
                }
            }

            else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
            {
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            }
            left = right;
        }
    }
    return;
}

int main()
{
    FILE *reqFilePtr;
    reqFilePtr = fopen("input.c", "r");
    FILE *outputFilePtr = NULL;
    outputFilePtr = fopen("output.c", "w+");
    int prevChar = '\n';
    int currentChar = fgetc(reqFilePtr);
    while (currentChar != EOF)
    {
        if (currentChar == '*' && prevChar == '/')
        {
            while (1)
            {
                if (currentChar == '/' && prevChar == '*')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        else if (currentChar == '/' && prevChar == '/')
        {
            while (1)
            {
                if (currentChar == '\n')
                {
                    break;
                }
                prevChar = currentChar;
                currentChar = fgetc(reqFilePtr);
            }
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
        else if (currentChar == ' ' && prevChar == ' ')
        {
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
            continue;
        }
        else if (currentChar == '\n' && prevChar == '\n')
        {
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
            continue;
        }
        else
        {
            fputc(prevChar, outputFilePtr);
            prevChar = currentChar;
            currentChar = fgetc(reqFilePtr);
        }
    }
    fclose(outputFilePtr);
    fclose(reqFilePtr);
    reqFilePtr = fopen("output.c", "r");
    char str[1000];
    while (fgets(str, 1000, reqFilePtr) != NULL)
    {

        parse(str);
    }
    printf("Unique Tokens \n");
    char n[2] = "\n\0";
    for (int i = 0, j = 0; i < a; i++, j++)
    {

        if (!strstr(tokens[i].str, n))
            printf("%d. '%s'  ->%d\n", j + 1, tokens[i].str, tokens[i].count);
        else
            j--;
    }
    fclose(reqFilePtr);

    return (0);
}
