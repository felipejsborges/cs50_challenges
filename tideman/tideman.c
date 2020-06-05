#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer candidate i over candidate j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j -> there's an arrow linkin candidate i to candidate j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner; // the (candidates[index])  of the winner
    int loser; // the (candidates[index]) of the loser
}
pair;

// Array of candidates - each item of this array is the name of a candidate
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

void testCycle(int winnerIndex, int loserIndex);

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
    // search for a registered candidate with this name
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            // if we find it, update ranks array and returns true
            ranks[rank] = k;
            return true;
        }
    }
    // if we not find, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // compare each item of ranks array with the nexts items to update preferences 2D array
    for (int j = 0; j < candidate_count - 1; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            preferences[ranks[j]][ranks[k]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // compare each head-to-head preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // if i is preferred over j, i is winner, and j is loser
            if (preferences[i][j] > preferences[j][i])
            {
                pair toPairsArray;
                toPairsArray.winner = i;
                toPairsArray.loser = j;
                pairs[pair_count] = toPairsArray;
                pair_count++;
            }
            // if j is preferred over i, j is winner, and i is loser
            else if (preferences[j][i] > preferences[i][j])
            {
                pair toPairsArray;
                toPairsArray.winner = j;
                toPairsArray.loser = i;
                pairs[pair_count] = toPairsArray;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // lets use Bubble Sort
    int swapArraySize = pair_count;

    // set swap counter to a non-zero value
    int swapCounter = -1;

    // repeat until the swap counter is 0, because when all elements are sorted, swapCounter is not going to be added
    while (swapCounter != 0)
    {
        // setting swap counter to zero to start the iteration
        swapCounter = 0;

        // looking at each adjacent pair
        for (int i = 0; i < swapArraySize - 1; i++)
        {
            // if they are not in order, swap them and add one to swap counter
            if ((preferences[pairs[i].winner][pairs[i].loser]) < (preferences[pairs[i + 1].winner][pairs[i + 1].loser]))
            {
                pair cache = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = cache;
                swapCounter++;
            }
        }
        // when we just finish a iteration, the last item is sorted, so our array size is previous iteration size -1
        swapArraySize--;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // the first two items of pair array will never create a cycle. So, just lock it
    locked[pairs[0].winner][pairs[0].loser] = true;
    locked[pairs[1].winner][pairs[1].loser] = true;

    // Now, for each other item, we have to test if it will create a cycle
    for (int i = 2; i < pair_count; i++)
    {
        // at first, set it true
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Look at locked pairs and see if the winner is the loser of our currently pair
        for (int j = 0; j < i; j++)
        {
            // if the winner of a past locked pair is the loser of our currently pair, it will create a cycle
            if (pairs[j].winner == pairs[i].loser)
            {
                // so set this lock as false
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winnerBool[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        winnerBool[i] = true;
    }

    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true && i != j)
            {
                winnerBool[j] = false;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (winnerBool[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    // print that has no edge pointed to it

    // run candidates array. for each one, verify if has one locked true as a loser, and set the array winner = false
    // if dont have lock as a loser, set true

    return;
}
