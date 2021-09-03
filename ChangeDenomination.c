#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[50];
    int change;
}Person;

int read_file(Person[]);
void get_change_by_name(Person[], int);
void change_to_denominations(int *, int);
void save_csv(Person[], int);

// this function reads the 'coin.txt' file and stores the persons into the array
int read_file(Person arr[]){
    FILE *fp;
    fp = fopen("coin.txt","r");

    char name[50];
    int change;
    int read_count=0;
    int array_count=0;

    // read 'coin.txt' and create Persons (assumption: only up to 10 lines)
    while(fscanf(fp, "%s %d\n", name, &change)==2){

        // check if the name already exist in the array, then add change to the existing entry
        int flag=0;
        for (int i=0; i<array_count; i++)
            // check if person with same name is found
            if (strcmp(arr[i].name,name)==0){
                arr[i].change += change;
                flag=1;
                break;
            }


        // simply add the new person into the array
        if (!flag){
            // create Person using values read
            Person temp;
            strcpy(temp.name, name);
            temp.change = change;
            arr[array_count] = temp;
            array_count++;
        }

        // break out of while-loop if 10-lines have been read from 'coin.txt'
        if (++read_count == 10)
            break;
    }
    fclose(fp);
    return array_count;
}


// this function searches for a name in the array and displays the denominations
void get_change_by_name(Person arr[], int n){

    // declare name variable
    char name[50];

    // declare denominations int array
    int denominations[4];

    // prompt user to enter name
    printf("Enter name: ");

    // input name
    scanf("%s", name);

    // search for name in array and get the change amount
    for (int i=0; i<n; i++)

        // if person with the name is found, call change_to_denominations() to get the denominations
        if (strcmp(arr[i].name, name)==0){

            // get the change amount
            int change = arr[i].change;

            // get denominations
            change_to_denominations(denominations, change);

            // print denominations
            printf("\nCustomer: %s (%d cents)\n\n", name, change);
            printf("Change:\n");
            if (denominations[0] != 0)
                printf("50 cents: %d\n", denominations[0]);
            if (denominations[1] != 0)
                printf("20 cents: %d\n", denominations[1]);
            if (denominations[2] != 0)
                printf("10 cents: %d\n", denominations[2]);
            if (denominations[3] != 0)
                printf("5 cents: %d\n", denominations[3]);
            printf("\n");

            // return from function
            return;
        }

    // display person not found
    printf("\nName: %s\n", name);
    printf("Not found!\n\n");
}

// this function converts the total change into the number of individual denominations
void change_to_denominations(int * denominations, int change){
    // compute number of 50-cent coins
    denominations[0] = change/50;
    change -= denominations[0]*50;

    // compute number of 20-cent coins
    denominations[1] = change/20;
    change -= denominations[1]*20;

    // compute number of 10-cent coins
    denominations[2] = change/10;
    change -= denominations[2]*10;

    // compute number of 5-cent coins
    denominations[3] = change/5;
    change -= denominations[3]*5;
}

// this functions writes the CSV file
void save_csv(Person arr[], int n){
    // open file for writing
    FILE *fp;
    fp = fopen("change.csv","w");

    int denominations[4];
    // loop to write to CSV for each person the the array
    for(int i=0; i<n; i++){
        // calls the change_to_denominations() function to get the denominations
        change_to_denominations(denominations, arr[i].change);

        // write to file
        fprintf(fp, "%s,%d,%d,%d,%d,%d\n", arr[i].name, arr[i].change, denominations[0], denominations[1], denominations[2], denominations[3]);
    }

    fclose(fp);

    printf("The CSV file has been saved!\n");

}

int main()
{
    // declare an array of structs to hold up to 10 Persons
    Person persons_arr[10];

    // read text file and store Persons into persons_arr, also returns the number of persons stored in the array
    int n = read_file(persons_arr);

    // menu loop
    int option;
    while (1){
        printf("---- Menu ----\n");
        printf("1. Enter name\n");
        printf("2. Exit\n");
        printf("Your option: ");
        scanf("%d", &option);

        if (option==1)
            get_change_by_name(persons_arr, n);
        else if (option==2){
            save_csv(persons_arr, n);
            printf("Goodbye!\n");
            break;
        }else
            printf("Please select a valid option!\n\n");
            break;

    }

    return 0;
}
