/* CS261- Assignment 1 - Q.3*/
/* Name: Yuxi Zhang
 * Date: Jan 17th, 2019
 * Solution description:
 *     isalpha()  -whether char is letter
 *     toUpperCase()  -whether lowercase letter become uppercase
 *     toLowerCase()  -whether uppercase letter become lowercase
 *     stringLength()  -calculate total length of string including nonletter char 
 *     lettersnum()  -count number of letters in string
 *     checkValidity() -filter all nonvalid input, not '_' separate two groups of letters
 *     maxLength() -the maximum length of letter group
 *     transform() -firstly, change all nonletter to '_'
 *                 -secondly, initialize matrix with '_'
 *                 -thirdly, assign char value to matrix cell if it is letter
 *                            if not letter, assign value to matrix cell('_'), and break for loop, which mean enter next row of matrix 
 *                            matrix be filled only char is letter, if not found_letter do not enter else if 
 *                 -assign '\0' for end of word, for terminal sign
 *                 -extract word from matrix and use '_' to connect each group of letters
 *                     if letter, assign to word
 *                     if not letter, '_', enter next row of matrix, extract words from newline
 *                     let the last char be '\0'
 *     camelCase() -received string form like, xxx_xxxxx_xx, make letter after '_' become uppercase
 *     moveforward() -let each character after '_' move forward one by one, calculate number of letters, put '\0' at end of string
 */
#include <stdio.h>
#include <stdlib.h>

//if it is letter
int isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return 1;
    }
    return 0;
}

char toUpperCase(char ch){
    /*Convert ch to upper case, assuming it is in lower case currently*/
    char rval = (char)ch - 32;
    return rval;

}

char toLowerCase(char ch){
    /*Convert ch to lower case, assuming it is in upper case currently*/
    char rval = (char)ch + 32;
    return rval;
}

//length of string
int stringLength(char s[]) {
    /*Return the length of the string*/
    int length = 0;
    while(s[length] != '\0')
    {
        length++;
    }
    return length;
}

//sum number of all letters in string
int lettersnum(char s[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]))
        {
            sum++;
        }
    }
    return sum;
}


//check if input is valid
int checkValidity(char* word)
{
    //use flag array to mark if letter, nonletter and letter appear
    int flag[3] = {0};
    int flagpos[2] = {0};
    for (int i = 0; i < stringLength(word) && flag[0] == 0; i++)
    {
        if (isalpha(word[i]))
        {
            flag[0] = 1;
            flagpos[0] = i;
        }
    }
    if (flag[0] == 0)
    {
        return 0;
    }
    for (int i = flagpos[0]; i < stringLength(word)&& flag[1] == 0; i++)
    {
        if (!isalpha(word[i]))
        {
            flag[1] = 1;
            flagpos[1] = i;
        }
    }
    if (flag[1] == 0)
    {
        return 0;
    }
    for (int i = flagpos[1]; i < stringLength(word); i++)
    {
        if (isalpha(word[i]))
        {
            return 1;
        }
    }
    return 0;
}


int maxLength(char* word)
{
    //get max length of letter, save space and time
    int maxlength = 0;
    int templength = 0;
    int index = 0;
    while(word[index] != '\0')
    {
        if (isalpha(word[index]))
        {
            templength = 0;
        }
        while (isalpha(word[index]))
        {
            index++;
            templength++;
        }
        if (templength > maxlength)
        {
            maxlength = templength;
        }
        index++;
    }
    return maxlength;
}

void transform(char* word)
{
    //get length of word
    int length = stringLength(word);

    //use '_' to replace non letter and underscores
    for (int i = 0; i < length; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] = toLowerCase(word[i]);
        }
        else if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] = word[i];
        }
        else
        {
            word[i] = '_';
        }
    }
    //get max length of each letter part, each letter part separated by '_'
    //matrixcol, max length of each letter part
    int matrixcol = maxLength(word) + 1;

    int matrixrow = length;
    //for example, _random_ _word_provided, matrixcol = 6, matrixrow = 3(23/ 6 = 3)

    //initialize '_'_random_ _word_provided
    char matrix[matrixrow][matrixcol];
    for (int i = 0; i < matrixrow; i++)
    {
        for (int j = 0; j < matrixcol; j++)
        {
            matrix[i][j] = '_';
        }
    }

    //loop until reach string ends
    int cal_row = 0;
    int actual_row = 0;
    int j = 0;
    int found_lettergroup = 0;
    int count = 0;

    while(word[count] != '\0')
    {
        //find letter
        if (isalpha(word[count]))
        {
            printf("%c\n", word[count]);
            matrix[cal_row][j] = word[count];
            j++;
            found_lettergroup = 1;
        }
            //not alpha with condition that already found lettergroup, set '_' to end of letter group
        else if (!isalpha(word[count]) && found_lettergroup == 1)
        {
            matrix[cal_row][j] = '_';
            j = 0;
            cal_row++;
            found_lettergroup = 0;
        }
        count++;
    }
    word[count] = '\0';
//    printf("last one: %c\n", word[count]);
//    printf("%s\n", word);


    //an exceptional condition, the input last char is '_', then will be counter more one line
    while(isalpha(matrix[actual_row][0]))
    {
        actual_row++;
    }
    actual_row = actual_row - 1;

    printf("%s\n", word);
    int cnt = 0;
    //extract letter group for word
    for (int line = 0; line <= actual_row; line++)
    {
        for (int k = 0; k < matrixcol; k++)
        {
            if (isalpha(matrix[line][k]))
            {
    //            printf("%c\n", matrix[line][k]);
                word[cnt] = matrix[line][k];
                cnt++;
            }
                //when encounter first '_', assign it to word and use break to jump out of for loop
            else
            {
    //            printf("%c\n", matrix[line][k]);
                word[cnt] = matrix[line][k];
                cnt++;
                break;
            }
        }

    }
    word[cnt-1] = '\0';
  //  printf("trans %s\n", word);

}


void moveforward(char* word, int num)
{
    int mark = 0;
    //inside for loop, will not change word length
    for (int i = 0; i < stringLength(word); i++)
    {
        if (word[i] == '_')
        {
            printf("%d\n", i);
            //mark index of '_' as next loop start position
            mark = i;
            for (int j = i+1; j < stringLength(word); i++, j++)
            {
                word[i] = word[j];
            }
            //for i++, i need start position mark - 1, then start position
            i = mark - 1;
        }
    }
    word[num] = '\0';
    printf("%s\n", word);
}


void camelCase(char* word)
{
    printf("%s", word);
    /*Convert to camelCase*/
    for (int i = 0; i < stringLength(word); i++)
    {
        //make letter after '_' become uppercase
        if (isalpha(word[i]) && word[i-1] == '_')
        {
            word[i] = toUpperCase(word[i]);
        }
    }

    int num = lettersnum(word, stringLength(word));
    moveforward(word, num);
}


int main()
{
    /*Read the string from the keyboard*/
    char inputstr[100];
    scanf("%[^\n]s",inputstr);

    if (checkValidity(inputstr) == 0)
    {
        printf("invalid input string\n");
        return 0;
    }
    printf("length: %d\n", stringLength(inputstr));
    transform(inputstr);
    /*Call camelCase*/
    camelCase(inputstr);
    /*Print the new string*/
    printf("%s", inputstr);

    return 0;
}