#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

struct _arr {
    unsigned short *arr;
    int size;
    int capacity;
};

int main(int argc, char const *argv[]) {
    struct _arr original = { (malloc(BUFFER_SIZE * sizeof(unsigned short))), 0, BUFFER_SIZE };
    struct _arr dupes = { (malloc(BUFFER_SIZE * sizeof(unsigned short))), 0, BUFFER_SIZE };

    if (original.arr == NULL || dupes.arr == NULL) {
        printf("Ошибка выделения памяти\n");
        return EXIT_FAILURE;
    }

    int number;
    char ch;

    printf("Введите числа, разделенные пробелами (нажмите Enter для завершения):\n");

    while (1) {
        // Проверяем, вводится ли число или пустая строка
        int result = scanf("%d", &number);

        // Если результат не число и это не конец ввода (Enter)
        if (result == 0) {
            // Считываем символ (например, Enter или пробел)
            ch = getchar();
            if (ch == '\n') {
                // Если это Enter, выходим из цикла
                break;
            } else {
                // Если это не Enter, продолжаем ожидание ввода
                continue;
            }
        }

        // Если массив оригиналов заполнен, увеличиваем его размер
        if (original.size == original.capacity) {
            original.capacity += BUFFER_SIZE;
            original.arr = realloc(original.arr, original.capacity * sizeof(unsigned short));
            if (original.arr == NULL) {
                printf("Ошибка перераспределения памяти\n");
                return EXIT_FAILURE;
            }
        }

        // Проверяем, есть ли это число в оригинальном массиве
        int originalMatch = 0;
        for (int i = 0; i < original.size; i++) {
            if (original.arr[i] == number) {
                originalMatch = 1;
                break;
            }
        }

        if (originalMatch == 0) {
            original.arr[original.size] = number;
            original.size++;
        } else {
            // Проверяем, есть ли это число уже в массиве дубликатов
            int dupeMatch = 0;
            for (int i = 0; i < dupes.size; i++) {
                if (dupes.arr[i] == number) {
                    dupeMatch = 1;
                    break;
                }
            }

            if (dupeMatch == 0) {
                if (dupes.capacity == dupes.size) {
                    dupes.capacity += BUFFER_SIZE;
                    dupes.arr = realloc(dupes.arr, dupes.capacity * sizeof(unsigned short));
                    if (dupes.arr == NULL) {
                        printf("Ошибка перераспределения памяти\n");
                        return EXIT_FAILURE;
                    }
                }

                dupes.arr[dupes.size] = number;
                dupes.size++;
            }
        }
    }

    // Вывод неуникальных чисел
    printf("Неуникальные числа: ");
    for (int i = 0; i < dupes.size; i++) {
        printf("%hu ", dupes.arr[i]);
    }
    printf("\n");

    free(original.arr);
    free(dupes.arr);
    return EXIT_SUCCESS;
}
