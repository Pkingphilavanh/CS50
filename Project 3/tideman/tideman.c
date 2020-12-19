#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclecheck(int initialwinner, int therecentloser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
       if (strcmp(name, candidates[i]) == 0)
       {
           ranks[rank] = i;
           // I had to watch a video for this. Fuck the directions. To be very straight forward, you want the ranks array to hold the fucking index of the person in the candidates list
           return true;
       }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //Ranks array represent index of person.
            //Preferences is a 2D grid where the X and Y are represented by the index of the candidates.
            //So candidate 1 is preferred over candidate 2 and 3 , basically the ranks array looks like this ranks[] = {1,3,2}
            //So ranks[0] = 1 , means that candidate 1 is preferrred over candidate 3 ranks[1] = 3, yada yada yada
            //so here you would go to coordinates (1,3) (on your 2d graph if u drew it)
            //to increment the value there by 1 which signifies that 1 voter has a preference of candidate 1 over candidate 3
            //then go to (1,2) and increment that by 1.
            //then start this process over at 3 this time. Don't do the last value in the ranks array.
            //you do all this with a nested for loop where i and j cleverly map to the appropriate values in the ranks array.
            //Watch this video: https://www.youtube.com/watch?v=U8F-AnujLOk
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Compare every pair in the Preference 2D Array, then add who is the winner of that pair into the pair data structure THEN increment pair count.
    //DO NOT add  ties into the pair structure and do not account for ties, just ignore them.
    //the size of the pair data structure or the position inside it is the count of "pair_count" Remeber trying to catch every pair where there is a preferred winner.
    //whichever candidate wins, take their index on the 2d graph and put it in the winners of the pairs data structure
    //whoever loses, put that in the losers of pairs data structure.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences [j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Homework is vague in my opinion, in any case the strength is defined as the ratio of preferred votes.
    //if 3 ppl prefer candidate 1 over 2 and 2 prefer candidate 2 over 1, then the strength is 3/2
    //You'll need to analyze the preferences 2d array to get the preferences for every pair.
    //I did this with bubble sort. I'd like to do with merge sort but I wanted to move the fuck on honestly.
    //week 3 doesnt give a lot of example of implementation for the algorithms.
    int strength = 0;
    int strength2 = 0;
    pair holder[0];
    int count = 0;

    do
    {
        count = 0;
        for (int i = 0; i < pair_count; i++)
        {
        strength = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        strength2 = preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner];

            if (strength < strength2)
            {
                holder[0] = pairs[i];
                pairs[i] = pairs[i+1];
                pairs[i+1] = holder[0];
                count++;
            }

        }



    } while (count > 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //iterate
    for (int i=0; i < pair_count; i++)
    {
        //A cycle cannot exist on the first pair aka the strongest victory so just put true in the locked array
        if (i < 1)
            locked[pairs[i].winner][pairs[i].loser] = true;

        //Now call recursive function
        else
        {
            if (cyclecheck(pairs[i].winner, pairs[i].loser) == false)
                locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int candidatestrength[MAX] = {0};
    int notwinner = 0;
    
    //debug check for tie cases sets 0,0 to true and using hw example output should result in a tie between Candidate 1 and 3
    //locked[0][0] = true;

    // Tallies the number of edges from candidate i to another candidate j
    for (int i =0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //DEBUG PRINTS Locked Pair Array
            //printf ("%s ", locked[i][j] ? "true" : "false");
            if (locked[i][j] == true)
                candidatestrength[i]++;
        }

        //DEBUG PRINTS Locked Pair Array
        //printf ("\n");

    }

    for (int k = 0; k < candidate_count; k++)
    {
        notwinner = 0;
        printf("Candidate Name %s\n", candidates[k]);
        for (int t = 0; t < candidate_count; t++)
        {
            if (candidatestrength[k] < candidatestrength[t])
            {
                notwinner++;
                break;
            }
        }

        if (notwinner == 0)
        {
            printf("%s\n",candidates[k]);
        }
        
    }
    
    return;
}

bool cyclecheck(int initialwinner, int therecentloser)
{

    // Base Case if the loser is equal to the winner a full cycle has been created.
    if (initialwinner == therecentloser)
        return true;

    //iterate through the columns and see if anything in locked array is connected to the recent loser (aka = true)
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[therecentloser][i] == true) //if true recursively call function and go forward in the cycle
        {
            if (cyclecheck(initialwinner, i))
                return true;
        }
    }

    return false;

}
