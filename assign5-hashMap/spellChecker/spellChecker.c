/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Yuxi Zhang
 * Date: Mar 3rd, 2019
 */

#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */

char* nextWord(FILE* file)
{
    int maxLength = 128;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            {
                word[length] = tolower(c);
            }
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        word = NULL;
        return NULL;
    }
    word[length] = '\0';
    return word;
}

//https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
int levenshtein(char *s1, char *s2) 
{
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int s1len = 0;
    unsigned int s2len = 0;

    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}
 

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
    char* tempWord = nextWord(file);
    while(tempWord != NULL)
    {
        //put word in hashMap
        hashMapPut(map, tempWord, 1); // here 1 is place holder
        free(tempWord); 
        tempWord = NULL;
        tempWord = nextWord(file);
    }

    fclose(file);////////
}

void deleteArr(HashLink* array[], int sz)
{
    for(int i = 0; i < sz; i++)
    {
        free(array[i] -> key);
        free(array[i]);
    }
    free(array);
    array = NULL;
} 
/////////////////////////////////////////////////////
void swap(HashLink** right, HashLink** left)
{
    int maxLength = 128;
    struct HashLink* temp = malloc(sizeof(struct HashLink));
    temp -> key = malloc(sizeof(char) * maxLength);
 //   *temp = malloc(sizeof(struct HashLink));

    strcpy((temp) -> key, (*left) -> key);



  //  (temp) -> key = (*left) -> key;
  //  (temp) -> key = (*left) -> key;
    (temp) -> value = (*left) -> value;
    (temp) -> next = (*left) -> next;
 //   strcpy( (temp) -> next, (*left) -> next);

    strcpy((*left) -> key, (*right) -> key);
  //  (*left) -> key = (*right) -> key;
    (*left) -> value = (*right) -> value;
    (*left) -> next = (*right) -> next;
  //  strcpy( (*left) -> next, (*right) -> next);

 //   (*right) -> key = (temp) -> key;
    strcpy((*right) -> key, (temp) -> key);
  //  (*right) -> key = (temp) -> key;
    (*right) -> value = (temp) -> value;
    (*right) -> next = (temp) -> next;
 //   strcpy((*right) -> next, (temp) -> next);
    free(temp->key);
    temp->key = NULL;
    free(temp);
    temp = NULL;


  //  strcpy((*link) -> key, (*copiedlink) -> key);

}

void sortarr(struct HashLink* array[], int sz)///////
{
    int minDist = 0;
    for (int i = 0; i < sz - 1; i++)
    {
        minDist = array[i] -> value;
        for (int j = i + 1; j < sz; j++)
        {

            if (array[j]->value < minDist)
            {
                minDist = array[j]->value;
                swap(&array[j], &array[i]);
            }

        }
    }
}


//copied link means link be copied
//link will be assigned value of copied link after copylink function
//used for move
void copylink(HashLink** copiedlink, HashLink** link)
{
    strcpy((*link) -> key, (*copiedlink) -> key);
//    (*link) -> key = (*copiedlink) -> key;
    (*link) -> value = (*copiedlink) -> value;
 //   strcpy((*link) -> next, (*copiedlink) -> next);
    (*link) -> next = (*copiedlink) -> next;/////////////////////////////////////

}

//used for compare substring, if it is extremely different, then filter it out
//return 1, filtered
//return 0, similar, do not filted it out
//before added to array




void move(HashLink* array[], int sz, int index)
{
 //   printf("%s %d\n", array[4]->key, array[4]->value);
   // printf("%s %d\n", array[3]->key, array[3]->value);

    for(int i = sz - 1; i > index; i--)
    {
        copylink(&array[i-1], &array[i]);
    }
//    printf("%s %d\n", array[4]->key, array[4]->value);
//    printf("%s %d\n", array[3]->key, array[3]->value);
//    printf("%s %d\n", array[2]->key, array[2]->value);
//    printf("%s %d\n", array[1]->key, array[1]->value);
//    printf("%s %d\n", array[0]->key, array[0]->value);
}


/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    assert(map != 0);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);


    int distance = 0;   
    char inputBuffer[256];
    char* tempWord = NULL;
    int cnt = 0;
    int quit = 0;

    int maxLength = 128;


    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
        else
        {
            //firstly, find if it is in hashMap
            //hashMap has already stored dictionary words by loadDictionary
            if(hashMapContainsKey(map, inputBuffer) == 1)
            {
                printf("The inputted word %s is spelled correctly\n", inputBuffer);
            }
            //not find
            else
            {
                //generate an array of 5 words that are closest matches to inputBuffer based on distance
                struct HashLink** array = malloc(5 * sizeof(struct HashLink*));//////
                for(int i = 0; i < 5; i++)
                {
                    array[i] = malloc(sizeof(struct HashLink));
                }
                for(int i = 0; i < map -> capacity; i++)                    
                {
                    struct HashLink* tempLink = map -> table[i];
                    while(tempLink != NULL)
                    {
                        tempWord = tempLink -> key;           
                        distance = levenshtein(inputBuffer, tempWord);
                        hashMapPut(map, tempWord, distance);

                        
                        if (cnt < 5)
                        {
                    //        array[cnt] = malloc(sizeof(struct HashLink));
                            array[cnt] -> key = malloc(sizeof(char) * maxLength);

                            strcpy(array[cnt] -> key, tempWord);
                       //     array[cnt] -> key = tempWord;
                    
                            array[cnt]->value = tempLink->value;
                 
                            array[cnt] -> next = tempLink->next;
                            cnt++;
                            if(cnt >=2)
                            {
                                sortarr(array, cnt);//////////////                           
                            }
                        }
                        else
                        {
                            if((tempLink->value) <= (array[0]->value))
                                {
                                    move(array, 5, 0);                            
                                    strcpy(array[0]->key, tempWord);
                                    array[0]->value = distance; 
                                                                
                                }
                                else if( (tempLink->value) > (array[0]->value) && (tempLink->value) <= (array[1]->value))
                                {
                                    move(array, 5, 1);                              
                                    strcpy(array[1]->key, tempWord);
                                    array[1]->value = distance; 
                                }
                                else if( (tempLink->value) > (array[1]->value) && (tempLink->value) <= (array[2]->value))
                                {
                                    move(array, 5, 2);                              
                                    strcpy(array[2]->key, tempWord);
                                    array[2]->value = distance;                              
                                }
                                else if ((tempLink->value) > (array[2]->value) && (tempLink->value) <= array[3]->value)
                                {
                                    move(array, 5, 3);                      
                                    strcpy(array[3]->key, tempWord);
                                    array[3]->value = distance;                              
                                }
                                else if ( (tempLink->value) > (array[3]->value) && (tempLink->value) <= (array[4]->value))
                                {
                                    strcpy(array[4]->key, tempWord);
                                    array[4]->value = distance;
                                }
                        }                            
                        tempLink = tempLink -> next;
                    }
                }
                printf("The inputted word %s is spelled incorrectly\n", inputBuffer); 
                printf("Did you mean ");
                for(int i = 0; i < 5; i++)
                {
                    if (array[i] -> key != 0)
                    {
                        printf("%s ", array[i] -> key);
                    }

                }
                printf("\n");
                deleteArr(array, 5);
            }
        }   
    }

    hashMapDelete(map);
    return 0;
}











