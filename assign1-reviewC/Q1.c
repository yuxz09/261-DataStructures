/* CS261- Assignment 1 - Q.1*/
/* Name: Yuxi Zhang
 * Date: Jan 13th, 2019
 * Solution description:
 *   allocate()
 *     use malloc to allocate memory for 10 struct students 
 *   generate()
 *     use random to generate ID
 *     use flag array to mark if random ID has been used for one student
 *     random score
 *    summary()
 *      find min, max, average score among 10 students
 *    deallocate()
 *      free 10 students malloc
 *     
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate()
{
     /*Allocate memory for ten students*/
    struct student *stu = malloc(10 * sizeof(struct student));
     /*Return the pointer*/
    return stu;
}

//student students[10]
void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/

  //flag array: mark random number not been selected as ID, flag[0] ~ flag[10], ignore flag[0]
  int flag[11] = {0};
  int randnum = 0;

  for (int i = 0; i < 10; i++)
  {
    randnum = rand() % 10 + 1;
    while (flag[randnum] != 0)
    {
      randnum = rand() % 10 + 1;    
    }
    if (flag[randnum] == 0)
    {
      flag[randnum] = 1;
    }
    students[i].id = randnum;
    students[i].score = rand() % 101;  
  }   
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

  for (int i = 0; i < 10; i++)
  {
    printf("id: %d score: %d\n", students[i].id, students[i].score);
  }

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
  int min = students[0].score;
  int max = students[0].score;
  double avg;
  int sum = students[0].score;
  for (int i = 1; i < 10; i++)
  {
    sum += students[i].score;
    if (students[i].score < min)
    {
      min = students[i].score;
    }
    if (students[i].score > max)
    {
      max = students[i].score;
    }
  }
  avg = sum * 1.0 / 10;
  printf("min: %d, max: %d, avg: %.1lf\n", min, max, avg);
}

void deallocate(struct student* stud)
{
 /*Deallocate memory from stud*/
  free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*Call allocate*/
    stud = allocate();

    /*Call generate*/
    generate(stud);
    
    /*Call output*/
    output(stud);
    
    /*Call summary*/
    summary(stud);
    
    /*Call deallocate*/
    if(stud != 0)
    {
      deallocate(stud);
    }

    return 0;
}

