#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

struct _arr
{
    unsigned short *arr;
    int size;
    int capacity;
};

int main(int argc, char const *argv[])
{

    struct _arr original = {(malloc(BUFFER_SIZE * sizeof(unsigned short))), 0, BUFFER_SIZE};
    struct _arr dupes = {(malloc(BUFFER_SIZE * sizeof(unsigned short))), 0, BUFFER_SIZE};

    if (original.arr == NULL || dupes.arr == NULL)
    {
        printf("Memory error\n");
        return EXIT_FAILURE;
    }

    int number;

    while (scanf("%d", &number) == 1)
    {
        char ch = getchar();
        if(ch == '\n')
            break;

            
        if (original.size == original.capacity)
        {
            original.capacity += BUFFER_SIZE;
            original.arr = realloc(original.arr, original.capacity * sizeof(unsigned short));
            if (original.arr == NULL)
            {
                printf("Memory err\n");
                return EXIT_FAILURE;
            }
        }

        int originalMatch = 0;
        for (int i = 0; i < original.size; i++)
        {
            if (original.arr[i] == number)
            {
                originalMatch = 1;
                break;
            }
        }

        if (originalMatch == 0)
        {
            original.arr[original.size] = number;
            original.size++;
        }
        else
        {

            int dupeMatch = 0;

            for (int i = 0; i < dupes.size; i++)
            {
                if (dupes.arr[i] == number)
                {
                    dupeMatch = 1;
                    break;
                }
            }

            if (dupeMatch == 0)
            {
                if (dupes.capacity == dupes.size)
                {
                    dupes.capacity += BUFFER_SIZE;
                    dupes.arr = realloc(dupes.arr, dupes.capacity * sizeof(unsigned short));
                     if (dupes.arr == NULL) {
                        printf("memory error\n");
                        return EXIT_FAILURE;
                    }
                }

                dupes.arr[dupes.size] = number;
                dupes.size++;
            }
        }
    }

    for (int i = 0; i < dupes.size; i++)
    {
        printf("%hu ", dupes.arr[i]);
    }

    free(original.arr);
    free(dupes.arr);
    return EXIT_SUCCESS;
}
