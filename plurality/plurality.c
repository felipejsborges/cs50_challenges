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

    // Populate array of candidates
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

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int votes[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        votes[i] = candidates[i].votes;
    }

    int swapArraySize = candidate_count;

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
            if (votes[i] > votes[i + 1])
            {
                int cache = votes[i];
                votes[i] = votes[i + 1];
                votes[i + 1] = cache;
                swapCounter++;
            }
        }
        // when we just finish a iteration, the last item is sorted, so our array size is previous iteration size -1
        swapArraySize--;
    }

    candidate winners[1];
    winners[0].name = 0x0;
    winners[0].votes = 0;

    int winnersLength = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == votes[candidate_count - 1])
        {
            candidate cache = winners[winnersLength];
            winners[winnersLength] = candidates[i];
            winners[winnersLength + 1] = cache;
            winnersLength++;
        }
    }
    for (int i = 0; i < winnersLength; i++)
    {
        printf("%s\n", winners[i].name);
    }
    return;
}

