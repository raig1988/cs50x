#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j - egde from i to j
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
pair pairs[MAX * (MAX - 1) / 2]; // array of all pairs where 1 candidate is preferred above another - if candidates are tied, no need to added

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool cycles(int cycle_start, int loser);
void lock_pairs(void);
void print_winner(void);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // loop for voter ith preference
    for (int i = 0; i < candidate_count; i++)
    {
        // loop in ith preference, voter jth preference
        for (int j = 0; j < candidate_count; j++)
        {
            /* Test function (int j = i + 1)
            preferences[ranks[i]][ranks[j]]++;
            */
            /*
            if (i == j)
            {
                printf("rank[%i] = candidates[%s] / rank[%i] = candidates[%s]\n", i, candidates[ranks[i]], j,  candidates[ranks[j]]);
                preferences[ranks[i]][ranks[j]] = 0;
                //tie++;
                //printf("Tie = %i\n", tie);
                printf("\n");
            }
            if (i > j)
            {
                printf("rank[%i] = candidates[%s] / rank[%i] = candidates[%s]\n", i, candidates[ranks[i]], j,  candidates[ranks[j]]);
                preferences[ranks[i]][ranks[j]] = 0;
                //lose++;
                //printf("Lose = %i\n", lose);
                //printf("\n");
            }*/
            if (i < j)
            {
                //printf("rank[%i] = candidates[%s] / rank[%i] = candidates[%s]\n", i, candidates[ranks[i]], j,  candidates[ranks[j]]);
                //printf("Before : preferences[%i][%i] = %i\n", i, j, preferences[ranks[i]][ranks[j]]);
                preferences[ranks[i]][ranks[j]]++;
                //printf("After : preferences[%i][%i] = %i\n", i, j, preferences[ranks[i]][ranks[j]]);
                //win++;
                //printf("Win = %i\n", win);
                //printf("\n");
            }
            //printf("Out of if: preferences[%i][%i] = %i\n", i, j, preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair tmp;
    // loop for candidates[i]
    for (int i = 0; i < candidate_count; i++)
    {
        // loop for candidates[j] in candidates[i]
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    tmp.winner = i;
                    tmp.loser = j;
                        //printf("pairs[%i].winner = %i\n",i, pairs[i].winner);
                        //printf("pairs[%i].loser = %i\n",i, pairs[i].loser);
                    pairs[pair_count++] = tmp;
                }
             }
        }
        //printf("pair count = %i\n", pair_count);
        //printf("[%i][%i] preferences[candidate: %s][candidate: %s] = %i\n",i, j, candidates[i], candidates[j] ,preferences[i][j]);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair tmp;
    int a, b;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            a = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            b = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (a < b)
            {
                tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
            }
        }

        //printf("pairs[%i].winner = %i - pairs[%i].loser = %i - edge %i\n",i, pairs[i].winner, i, pairs[i].loser, (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]));
    }
    return;
}

bool cycles(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycles(cycle_start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++) // loop to check through row of pairs [i]
    {
            if (!cycles(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
    }

    /*
        if (locked[pairs[i].winner][locked[pairs[i].loser] == false])
        {
            if (locked[pairs[i].loser][locked[pairs[i].loser]] == true)
            {
                locked[pairs[i].winner][locked[pairs[i].loser]] = false;
            }

        }
        else (locked[pairs[i].winner][locked[pairs[i].loser] == true])
        {

        }
        for (int j = 0; j < pair_count; j++) // loop to check through columns of pairs [j]
        {
            // 1 checks if pairs are not locked
            if (locked[pairs[i].winner][pairs[i].loser] == false)
            {
                 0 - 0
                 */
                // 2.1 checks if pairs loser is a winner in other pair
                /* 0 - 1
                  0 - 2
                  */
                 /*
                if (locked[pairs[i].loser][pairs[j].loser] == true)
                {
                    // 2.1.1 chains links with previous winners

                    0 - 2 */
                    /*
                    lock_pairs();
                }
                //2.2 if pairs loser is not a winner, locks tha pair
                else if (locked[pairs[i].loser][pairs[j].loser] == false)
                {
                    locked[pairs[i].winner][pairs[i].loser] = true;
                }
            }
            // 2. checks if pairs are locked
            if (locked[pairs[i].winner][pairs[i].loser] == true)
            {
                if (pairs[i].winner == pairs[j].loser)
                {
                    locked[pairs[i].winner][pairs[i].loser] = false;
                }
            }
        }
    }
    */

    return;
}
        /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (locked[pairs[i].winner][pairs[j].loser] == false)
                {
                    if (locked[pairs[j].winner][pairs[i].loser] == false)
                    {
                        printf("locked[%i][%i] = %i\n", i, j, locked[pairs[i].winner][pairs[j].loser]);
                        locked[pairs[i].winner][pairs[j].loser] = true;
                        lock_pairs();
                        printf("locked[%i][%i] = %i\n", i, j, locked[pairs[i].winner][pairs[j].loser]);
                    }
                }
            }
        }
    }*/


// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner = 0;
    int tie = 0;
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (pairs[i].winner != pairs[j].loser)
                {
                    winner = pairs[i].winner;
                }
            }
        }
    }
    printf("%s\n", candidates[winner]);
    printf("%s\n", candidates[tie]);
    return;
}