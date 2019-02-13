/* CS261- Assignment 1 - Q. 0*/
/* Name: Yuxi Zhang
 * Date: Jan 13th, 2019
 * Solution description:
 * fooA
 *     change value pointer variable points to, and find different
 * fooB
 *     change pointer variable content, address of pointer variablem, and find different
 *     
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr)
{
     /*Print the value and address of the integer pointed to by iptr*/
    printf("A before: %d %p\n", *iptr, iptr);
          
     /*Increment the value of the integer pointed to by iptr by 5*/
    *iptr = *iptr + 5;
          
     /*Print the address of iptr itself*/
    printf("A after: %p\n", iptr);

    /*Dummy variable, ignore the warning*/
   int c=5;  
}


void fooB(int* jptr)
{
     /*Print the value and address of the integer pointed to by jptr*/
    printf("B before: %d %p\n", *jptr, jptr);
               
     /*Decrement the address by 1 pointed to by jptr using jptr */
    jptr = jptr - 1;
//    printf("B after, jptr: %p\n", jptr);//this statement prints address jptr points to
      
     /*Print the address of jptr itself*/
    printf("B after, address of jptr: %p\n", &jptr);
}



int main()
{
    /*Declare an integer x and initialize it randomly to a value in [0,10] */
    int x = rand() % 11;
    
    /*Print the value and address of x*/
    printf("value of x: %d\n", x);
    printf("address of x: %p\n", &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*Print the value of x*/
    printf("after calling fooA: %d\n", x);

    
    /*Call fooB() with the address of x*/
    fooB(&x);

    /* my own question
    expected: address of x = 15 is same as address of x = 10

    revise: &x(x = 15) is different with &x(x = 10, original one) different address pass into fooB()
    */

    /*Print the value and address of x*/
    printf("fooB: %d\n", x);
    printf("fooB: %p\n", &x);
 
    /* question2
    are the value and address of x different than value and address were printed before the call to fooB? why or why not

    same one, since no change on value and address of value, in fooB, 
    we change content of int pointer(a variable different from variable x)
    but parameter jptr is int pointer, not address pointer or pointer points to pointer,
    if pointer b points to pointer a, then address of a change, back to main it will change,
    however, in fooB, pointer to x, no effect

     */ 

    printf("\n"); 

    return 0;
}



/**************

//jptr is a pointer points to an int pointer


2
void fooC(int** jptr)
{
  
    printf("C: %p\n", jptr);
    printf("C: %d %p\n", **jptr, *jptr);
               
    //change address of x, the int pointer 
    *jptr = *jptr - 1;

      
     //Print the address of jptr itself
    printf("C: %p\n", *jptr);
}

void fooC(int** jptr)
{
    printf("C: %p\n", jptr);
    printf("C: %d %p\n", **jptr, *jptr);
               
    //change address of x, the int pointer 
    *jptr = *jptr - 1;
      
     //Print the address of jptr itself
    printf("C: %p\n", *jptr);
}


//4
//jptr is a pointer points to an int pointer
void fooD(int** jptr)
{
    printf("D: %p\n", jptr);
    printf("D: %d %p\n", **jptr, *jptr);
               
    jptr = jptr - 1;
      
    //Print the address of jptr itself 
    printf("D: %p\n", jptr);
}

//zptr is a pointer, its content is  address of x 
//1
    int* zptr = &x; 
    printf("&x: %p\n", &x);
    printf("zptr, address of x: %p\n", zptr);
    printf("&zptr: %p\n", &zptr);

    //pass address of address of x 
    //change address of x in fooC
    printf("fooC\n");
    fooC(&zptr);
//3
    printf("x: %d\n", x);
    printf("&x: %p\n", &x);
    printf("zptr, address of x: %p\n", zptr);
    printf("address of zptr: %p\n", &zptr);

    printf("fooD\n");
    fooD(&zptr);

//5
    printf("x: %d\n", x);
    printf("&x: %p\n", &x);
    printf("zptr, address of x: %p\n", zptr);
    printf("address of zptr: %p\n", &zptr);

**************/


