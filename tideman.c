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
pair tmppairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(int start, int count, pair array[]);
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
            // string name;
            // if (i == 0)
            // {
            //     name = s1[j];
            // }
            // if (i == 1)
            // {
            //     name = s2[j];
            // }
            // if (i == 2)
            // {
            //     name = s3[j];
            // }
            // if (i == 3)
            // {
            //     name = s4[j];
            // }
            // if (i == 4)
            // {
            //     name = s5[j];
            // }
            //printf("%s\n", name);
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
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("P%i ", preferences[pairs[i].winner][pairs[i].loser]);
    // }
    // printf("\n");
    sort_pairs(0, pair_count - 1, pairs);
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("P%i %i %i ", preferences[pairs[i].winner][pairs[i].loser], pairs[i].winner, pairs[i].loser);
    // }
    // printf("\n");
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
            //printf("%i %i %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    //printf("Add Pairs: %i %i %i\n", pairs[pair_count].winner, pairs[pair_count].loser, preferences[pairs[pair_count].winner][pairs[pair_count].loser]);
                    pair_count += 1;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    //printf("Add Pairs: %i %i %i\n", pairs[pair_count].winner, pairs[pair_count].loser, preferences[pairs[pair_count].winner][pairs[pair_count].loser]);
                    pair_count += 1;
                }

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(int start, int count, pair array[])
{
    // TODO
    if (count - start == 0)
    {
        return;
    }

    int midpoint;
    if (start == 0)
    {
        midpoint = (count - start) / 2;
    }
    else
    {
        midpoint = start + ((count - start) / 2);
    }
    //printf("Sort Pairs: %i %i %i\n", start, count, midpoint);

    sort_pairs(start, midpoint, array);
    sort_pairs(midpoint + 1, count, array);

    int tmpadd = start;;
    for (int i = 0; i <= count; i++)
    {
        tmppairs[i] = pairs[i];

    }

    for (int i = start; i <= midpoint; i++)
    {
        for (int j = midpoint + 1; j <= count; j++)
        {
            if (tmppairs[i].winner != -1 && tmppairs[j].winner != -1)
            {
                if (preferences[tmppairs[i].winner][tmppairs[i].loser] < preferences[tmppairs[j].winner][tmppairs[j].loser])
                {
                    //printf("l1- %i %i %i\n", i, j, tmpadd);
                    array[tmpadd] = tmppairs[j];
                    tmppairs[j].winner = -1;
                    tmpadd += 1;
                    if (j == count)
                    {
                        array[tmpadd] = tmppairs[i];
                        tmpadd += 1;
                    }
                }
                else
                {
                    //printf("l2- %i %i %i\n", i, j, tmpadd);
                    array[tmpadd] = tmppairs[i];
                    tmppairs[i].winner = -1;
                    tmpadd += 1;
                    break;
                }


            }

            // for (int k = start; k <= count; k++)
            // {
            //     printf("%i", preferences[array[k].winner][array[k].loser]);
            // }
            // printf("\n");
        }


        //printf("%i", preferences[pairs[i].winner][pairs[i].loser]);

    }
    // for (int k = start; k <= count; k++)
    // {
    //     printf("%i", preferences[array[k].winner][array[k].loser]);
    // }
    // printf("\n");

    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool check = false;
    for (int i = 0; i < pair_count; i++)
    {
        if (i == pair_count - 1)
        {
            for (int j = 0; j < pair_count; j++)
            {
                if (pairs[i].loser != pairs[j].winner)
                {
                    locked[pairs[i].winner][pairs[i].loser] = true;
                    //printf("%i %i\n", i, j);
                    break;
                }

            }
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("%i\n", i);
        }


    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        bool winner = true;
        for (int j = 0; j < pair_count; j++)
        {
            //printf("IP: %s %i %i\n", candidates[pairs[i].winner], pairs[i].winner, pairs[j].loser);
            if (pairs[i].winner != pairs[j].loser)
            {
                winner = true;
                //printf("True: %s\n", candidates[pairs[i].winner]);
            }
            else
            {
                winner = false;
                //printf("False: %s\n", candidates[pairs[i].winner]);
                break;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[pairs[i].winner]);
            return;
        }
    }
    return;
}

