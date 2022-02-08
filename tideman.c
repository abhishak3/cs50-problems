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

// to check for cycles
bool isCycle(int a, int b);

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
    for(int i = 0; i < candidate_count; i++){
        if(!strcmp(name, candidates[i])){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count-1; i++){
        preferences[ranks[i]][ranks[i]] = 0;
        for(int j = i+1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){
            int a = preferences[i][j];
            int b = preferences[j][i];
            if(a!=b){
                pairs[pair_count].winner = a > b ? i : j;
                pairs[pair_count].loser = a < b ? i : j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[pair_count];
    int maxPos = 0;
    for(int i = 0; i < pair_count; i++){
        strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }
    for(int i = 0; i < pair_count; i++){
        int max = 0;
        for(int j = i; j < pair_count; j++){
            if (max < strength[j]){
                max = strength[j];
                maxPos = j;
            }
        }

        // swapping strength
        int temp = strength[i];
        strength[i] = strength[maxPos];
        strength[maxPos] = temp;

        // swapping respective pair
        pair tempPair = pairs[i];
        pairs[i] =pairs[maxPos];
        pairs[maxPos] = tempPair;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO: check for cycles
    for(int i = 0; i < pair_count; i++){
        if(!isCycle(pairs[i].winer, pairs[i].loser))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for(int i = 0; i < candidate_count; i++){
        bool isSource = true;
        for(int j = 0; j < candidate_count; j++){
            if(locked[j][i]){
                isSource = false;
                break;
            }
        }
        if(isSource) {
            printf("%s\n",candidates[i]);
            return;
        }
    }
    return;
}

bool isCycle(int a, int b){ // check before adding edge a --> b
    if(a == b) return true;
    int stack[candidate_count];
    int count = 0;
    for(int i = 0; i < candidate_count; i++){
        int curr = locked[b][i];
        if(curr) {
            stack[count] = i;
            count++;
        }
    }
    for(int i = 0; i < count; i++){
        if(isCycle(a, stack[i])) return true;
    }
    return false;
}

