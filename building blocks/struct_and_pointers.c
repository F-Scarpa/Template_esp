#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>

typedef struct Person_struct{                      //create a struct
    char firstName [20];
    char lastName[20];
    int age;
} Person;

void updatePerson(Person *p){
    strcpy(p->firstName, "Bob");        //strcpy to allocate strings inside structure
    strcpy(p->lastName, "Dod");         //we use pointers with structures so we can use them in functions
    p->age = 33;                        //we change the value at address and not the copy of the variable
}

void exclamIt(char *p){            //we pass a pointer as parameter so the varialbe passed as so is modified, not the copy
    strcat(p, "!");
}

void app_main(void){

Person person;   //define a Person struct as person
char phrase[20] = {"Hello world"};
updatePerson(&person);          // to pass a pointer parameter we use & which give us the address where the data is stored in hex,
                                // without & we pass a copy of the structure
printf("%s, %s, %d\n", person.firstName, person.lastName, person.age);

exclamIt(phrase);
printf("%s\n",phrase);
while(false)
{


}

            
}
