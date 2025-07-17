#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void shuffle(char n[20]);
int compare(char real_randome_name[20]);

int main()
{
    char languages_name[10][20] = {
        "C",
        "Go",
        "C++",
        "Java",
        "Python",
        "JavaScript",
        "Rust",
        "Swift",
        "Kotlin",
        "TypeScript"};

    char randome_name[20];
    char real_randome_name[20];
    char shuffle_name[20];
    int randome;
    int points = 0;
    srand(time(NULL)); // Only once at program start
    printf("if you want to back to the score board press 3\n\n");
    score:
    do
    {
        randome = rand() % 10;
        strcpy(randome_name, languages_name[randome]);
        strcpy(shuffle_name, randome_name);
        shuffle(shuffle_name);
        printf("Guess the language: %s\n", shuffle_name);
        
        do
        {
            int iscompare =compare(randome_name);
            if ( iscompare == 0)
            {
                printf(" Correct!\n");
                points += 1;
                printf(" Score: %d points\n\n\n", points);
                
                break;
            }
            else if(iscompare==3){ 
                
                printf("\n\n\n\n your total points are %d\n\n\n" , points);
                goto score ; 
                
                }
            else
            {
                printf(" Wrong! Try again.\n");
                points -= 1;
                if (points < 0)
                {
                    points = 0;
                    printf("ooopss you lose try again\n\n");
                    break;
                }
                printf(" Score: %d points\n\n\n", points);
            }
            
        } while (1);

    } while (1);

    return 0;
}

void shuffle(char n[20])
{
    int len = strlen(n);
    for (int i = len - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp = n[i];
        n[i] = n[j];
        n[j] = temp;
    }
}

int compare(char real_randome_name[20])
{
    char user_input[20];
    printf("Enter your answer: ");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = 0;

    if(strcmp(user_input, "3")==0){ return 3;}
    return strcmp(user_input, real_randome_name);
}