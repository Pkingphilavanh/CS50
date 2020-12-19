#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates SET MAX CANDIDATE LIMIT (9)
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: "); // USER ENTERS HOW MANY VOTES

    // Loop over all voters FOR EVERY VOTE USER WILL TYPE NAME IN
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote IF NAME DONT EXIST PRINT INVALID, DOESNT EXIT THO
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
       if (strcmp(name, candidates[j].name) == 0)
       {
           candidates[j].votes++;
           return true;
       }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // THIS NESTED LOOP IS HOW YOU PERFORM LINEAR SEARCH LEFT TO RIGHT AND COMPARE NUMBERS. Probably a little more complicated if we try to do alphabetic nonsense.

    for (int k = 0; k < candidate_count; k++)
    {
        int notawinner = 0;

        for (int y = 0; y < candidate_count - 1; y++)
        {
            if (candidates[k].votes < candidates[y].votes)
            {
                notawinner++;
                break;
            }
        }

        if (notawinner < 1)
        {
        printf("%s\n", candidates[k].name);
        }
    }
    return;
}

