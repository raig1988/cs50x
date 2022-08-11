#include <stdio.h>

int main(void)
{
    int array[4] = {0, 1, 2};

    int sum = array[0] + array[1] + array[2] + array[3] + array[4];
    printf("%i\n", sum);
}

    long hash_value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_value += toupper(word[i]);
    }
    return hash_value % N;