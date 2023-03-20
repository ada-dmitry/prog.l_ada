#include<stdio.h>
#include<stdlib.h>

struct list {
    char name[20];
    int age;
    float salary;
};

int main(){
    struct list *person;
    int i, n = 2;
    person = malloc(n*sizeof(struct list));

    for(i = 0; i<n; i++){
        printf("Enter name %d: ", i+1);
        scanf("%s", &(person+i)->name);

        printf("Enter age %d: ", i+1);
        scanf("%d", &(person+i)->age);

        printf("Enter salary %d: ", i+1);
        scanf("%f", &(person+i)->salary);
    }

    for(i=0; i<n; i++){
        printf("Name: %s\n Age: %d\n Salary: %.2f\n", (person+i)->name, (person+i)->age, (person+i)->salary);
 
    }
    free(person);
    return 0;

}