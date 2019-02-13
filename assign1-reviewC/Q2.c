/* CS261- Assignment 1 - Q.2*/
/* Name: Yuxi Zhang
 * Date: Jan 13th, 2019
 * Solution description:
 *     foo()
 *         swap pointer variable contents, change one variable value
 *     find before foo() result
 *     find after foo result
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int* temp = NULL;
    temp = a;
    a = b;
    b = temp;
    
    /*Decrement the value of integer variable c*/
    c--;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x, y, z;
    //rval: return value of calling foo
    int rval;
    x = rand() % 11;
    y = rand() % 11;
    z = rand() % 11;  
    
    /*Print the values of x, y and z*/
    printf("before: x: %d  y: %d  z: %d\n", x, y, z);
//    printf("before: &x: %p, &y: %p, &z: %p\n", &x, &y, &z); 

    /*Call foo() appropriately, passing x,y,z as parameters*/
    rval = foo(&x, &y, z);
    
    /*Print the values of x, y and z*/
    printf("after: x: %d, y: %d, z: %d\n", x, y, z);
//    printf("after: &x: %p, &y: %p, &z: %p\n", &x, &y, &z);
  	  
    /*Print the value returned by foo*/
    printf("return value of foo: %d\n", rval);

    /*
    (a) is the return value different than the value of integer z? why or why not?
    yes, different than value of integer z, because the foo function return value of new z(decrement), and received in main function


    (b) are the values of integers x and y different before and after calling the function foo()? why or why not?
	no, since in foo function, just address of x and y swapped, not x and y value swapped, and arguments are int pointers.
	if address of value pass by reference to foo, will change

     */
 
    
    return 0;
}





















    
    


