#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MAX_ATTEMPTS 10
#include <windows.h>

///For screen Refresh
void clearScreen()
{

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}

///Color management
void setColor(int color)
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

///Hangman Figure
void drawHangman(int attemptsleft)
{

    // Color changing system
    if(attemptsleft > 6)
        setColor(10); // Green

    else if(attemptsleft > 3)
        setColor(14); // Yellow

    else
        setColor(12); // Red

    switch(attemptsleft)
    {

    case 10:
        printf("\n");
        printf("  +---+\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("     ===\n");
        break;

    case 9:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("     ===\n");
        break;

    case 8:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("     ===\n");
        break;

    case 7:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf(" /|   |\n");
        printf("      |\n");
        printf("     ===\n");
        break;

    case 6:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf("      |\n");
        printf("     ===\n");
        break;

    case 5:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" /    |\n");
        printf("     ===\n");
        break;

    case 4:
        printf("\n");
        printf("  +---+\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("     ===\n");
        break;

    case 3:
        printf("\n");
        printf("  +---+\n");
        printf(" [O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("     ===\n");
        break;

    case 2:
        printf("\n");
        printf("  +---+\n");
        printf(" [O]  |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("     ===\n");
        break;

    case 1:
        printf("\n");
        printf("  +---+\n");
        printf(" [X]  |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("     ===\n");
        break;

    case 0:
        printf("\n");
        printf("  +---+\n");
        printf(" [X]  |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf(" DEAD |\n");
        printf("     ===\n");
        break;
    }
}

///Game's word handle part
struct WordData
{

    char word[20];

    char question[150];

    char hint1[150];

    char hint2[150];

    char hint3[150];
};



int main()
{

    int length;

    char replay;

    int difficulty;

    int gamemode;

    int timelimit;


    setColor(11);


    printf("=================================\n");
    printf("Welcome To Hangman Game!!\n");
    printf("=================================\n\n");

    setColor(7);

    srand(time(NULL));

    do
    {

        printf("Select Game Mode\n");

        printf("1. Single Player\n");
        printf("2. Multiplayer\n");

        printf("\nEnter choice: ");

        scanf("%d", &gamemode);

        printf("Select Difficulty Level\n");

        printf("1. Easy\n");
        printf("2. Medium\n");
        printf("3. Hard\n");

        printf("\nEnter choice: ");

        scanf("%d", &difficulty);

        char customword[20];

        char customquestion[150];

        char customhint1[150];

        char customhint2[150];

        char customhint3[150];

        struct WordData data[100];
        FILE *file;

        file = fopen("Word.txt", "r");

        if(file == NULL)
        {

            printf("Cannot open Word.txt");

            return 1;
        }

        int count = 0;

        while(fscanf(file,
                     "%19[^|]|%149[^|]|%149[^|]|%149[^|]|%149[^\n]\n",
                     data[count].word,
                     data[count].question,
                     data[count].hint1,
                     data[count].hint2,
                     data[count].hint3) == 5)
        {

            count++;
        }

        fclose(file);

        char *wordtoguess;

        int set = 0;

        if(gamemode == 1)   ///For 1 or 2 player mode
        {

            // Single Player

            int size = count;

            set = rand() % size;

            wordtoguess = data[set].word;

        }
        else if(gamemode == 2)
        {

            // Multiplayer

            printf("\nPLAYER 1 SETUP\n");

            printf("Enter secret word: ");
            scanf("%19s", customword);

            for(int i = 0; customword[i] != '\0'; i++)
            {

                customword[i] = tolower(customword[i]);
            }

            printf("Enter question: ");
            getchar();
            fgets(customquestion, sizeof(customquestion), stdin);

            customquestion[strcspn(customquestion, "\n")] = '\0';

            printf("Enter Hint 1: ");
            fgets(customhint1, sizeof(customhint1), stdin);

            customhint1[strcspn(customhint1, "\n")] = '\0';

            printf("Enter Hint 2: ");
            fgets(customhint2, sizeof(customhint2), stdin);

            customhint2[strcspn(customhint2, "\n")] = '\0';

            printf("Enter Hint 3: ");
            fgets(customhint3, sizeof(customhint3), stdin);

            customhint3[strcspn(customhint3, "\n")] = '\0';

            wordtoguess = customword;

            clearScreen();

            printf("PLAYER 2 TURN!\n");

            printf("Press Enter to continue...");
            getchar();
            getchar();

        }
        else
        {

            printf("\nInvalid mode! Defaulting to Single Player.\n");

            int size = count;

            set = rand() % size;

            wordtoguess = data[set].word;
        }

        // Word length
        length = strlen(wordtoguess);

        // Hidden word
        char guessedword[100];

        // Fill with *
        for(int i = 0; i < length; i++)
        {

            guessedword[i] = '_';
        }

        guessedword[length] = '\0';

        int attemptsleft = MAX_ATTEMPTS;

        int hintsleft;

        int score = 0;

        FILE *fp;

        int highscore = 0;

        // LOAD HIGH SCORE
        fp = fopen("highscore.txt", "r");

        if(fp != NULL)
        {

            fscanf(fp, "%d", &highscore);

            fclose(fp);
        }

        int multiplier;

        if(difficulty == 1)  /// Difficulty choosing part
        {

            attemptsleft = 10;
            hintsleft = 3;
            multiplier = 1;

            timelimit = 120; // 2 minutes

        }
        else if(difficulty == 2)
        {

            attemptsleft = 7;
            hintsleft = 2;
            multiplier = 2;

            timelimit = 90; // 1.5 minutes

        }
        else if(difficulty == 3)
        {

            attemptsleft = 5;
            hintsleft = 1;
            multiplier = 3;

            timelimit = 60; // 1 minute

        }
        else
        {

            printf("\nInvalid choice! Defaulting to Easy mode.\n");

            attemptsleft = 10;

            hintsleft = 3;

            multiplier = 1;
        }


        time_t starttime;

        int hintused = 0;

        char guess;

        char choice;

        char usedletters[100];

        int usedcount = 0;

        starttime = time(NULL);

        while(attemptsleft > 0)
        {

            clearScreen();

            time_t currenttime = time(NULL);

            int elapsed = (int)(currenttime - starttime);

            int remaining = timelimit - elapsed;

// TIME OUT CHECK
            if(remaining <= 0)
            {

                clearScreen();

                printf("\n=================================\n");
                printf("TIME'S UP!\n");
                printf("The word was: %s\n", wordtoguess);
                printf("Final Score: %d\n", score);
                printf("=================================\n");

                break;
            }

            if(gamemode == 1)
            {

                printf("Question: %s\n\n", data[set].question);

            }
            else
            {

                printf("Question: %s\n\n", customquestion);
            }

            drawHangman(attemptsleft);

            printf("\nWord: ");

            for(int i = 0; i < length; i++)
            {

                printf("%c ", guessedword[i]);
            }

            printf("\n");

            printf("\nAttempts left: %d\n", attemptsleft);

            printf("Score: %d\n", score);

            printf("High Score: %d\n", highscore);

            printf("Time Left: %d seconds\n", remaining);

            printf("Multiplier: x%d\n", multiplier);

            printf("\nUsed letters: ");

            for(int i = 0; i < usedcount; i++)
            {

                printf("%c ", usedletters[i]);
            }

            printf("\n");

            // Hint section
            if(hintsleft > 0)
            {

                printf("\nDo you want to use a hint? (y/n): ");

                scanf(" %c", &choice);

                choice = tolower(choice);

                if(choice == 'y' && hintused < 3)
                {

                    if(hintused == 0)
                    {

                        printf("\nHint 1: %s\n", (gamemode == 1) ? data[set].hint1 : customhint1);

                    }
                    else if(hintused == 1)
                    {

                        printf("\nHint 2: %s\n", (gamemode == 1) ? data[set].hint2 : customhint2);

                    }
                    else if(hintused == 2)
                    {

                        printf("\nHint 3: %s\n", (gamemode == 1) ? data[set].hint3 : customhint3);
                    }

                    hintused++;

                    hintsleft--;

                    printf("\nHints left: %d\n", hintsleft);
                }

            }
            else
            {

                printf("\nNo hints left!\n");
            }

            // User input
            printf("\nEnter a letter: ");

            scanf(" %c", &guess);

            guess = tolower(guess);

            // Input validation

            if(!isalpha(guess) || guess == ' ')
            {

                printf("\nPlease enter a valid letter!\n");

                printf("Press Enter to continue...");

                getchar();
                getchar();

                continue;
            }



            // Check repeated guesses
            int alreadyused = 0;

            for(int i = 0; i < usedcount; i++)
            {

                if(usedletters[i] == guess)
                {

                    alreadyused = 1;

                    break;
                }
            }

            if(alreadyused)
            {

                printf("\nYou already guessed '%c'!\n", guess);

                printf("Press Enter to continue...");
                getchar();
                getchar();

                continue;
            }

            /// Store guess
            usedletters[usedcount] = guess;

            usedcount++;

            int found = 0;

            // Check word
            for(int i = 0; i < length; i++)
            {

                if(wordtoguess[i] == guess)
                {

                    guessedword[i] = guess;

                    found = 1;
                }
            }

            if(found) ///Scoring function begins
            {

                score += 10 * multiplier;

                setColor(10);

                printf("\nCorrect Guess!\n");

                setColor(7);

            }
            else
            {

                attemptsleft--;

                score -= 5 * multiplier;

                setColor(12);

                printf("\nWrong Guess!\n");

                setColor(7);
            }

            /// Win condition
            if(strcmp(wordtoguess, guessedword) == 0)
            {

                clearScreen();

                drawHangman(attemptsleft);

                score += 50 * multiplier;

                score += attemptsleft * 5 * multiplier;

                setColor(10);

                printf("\n=================================\n");
                printf("CONGRATULATIONS!\n");
                printf("You guessed the word: %s\n", wordtoguess);
                printf("Final Score: %d\n", score);
                printf("=================================\n");

                setColor(7);

                break;
            }

            printf("\nPress Enter to continue...");
            getchar();
            getchar();
        }
        /// Lose condition
        if(attemptsleft == 0)
        {

            setColor(12);
            printf("\n=================================\n");
            printf("GAME OVER!\n");
            printf("The word was: %s\n", wordtoguess);
            printf("Final Score: %d\n", score);
            printf("=================================\n");
            setColor(7);
        }

        if(score > highscore)
        {

            highscore = score;

            fp = fopen("highscore.txt", "w");

            if(fp != NULL)
            {

                fprintf(fp, "%d", highscore);

                fclose(fp);
            }

            printf("\nNEW HIGH SCORE!\n");
        }


        printf("Current High Score: %d\n\n", highscore);

        printf("\nPress Enter to continue...");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        printf("\nDo you want to play again? (y/n): ");

        scanf(" %c", &replay);

        replay = tolower(replay);

        clearScreen();

    }
    while(replay == 'y');

    return 0;
}




