
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100

void matrixMultiply(int matrix1[SIZE][SIZE], int matrix2[SIZE][SIZE], int result[SIZE][SIZE], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result[i][j] = 0;
            for (k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    char* file1 = "matrix1.txt";  // Имя файла для первой матрицы
    char* file2 = "matrix2.txt";  // Имя файла для второй матрицы
    char* fileResult = "result_matrix.txt";  // Имя файла для результирующей матрицы

    int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE], result[SIZE][SIZE];  // Матрицы

    // Открываем файл первой матрицы
    int fd1 = open(file1, O_RDONLY);
    if (fd1 == -1) {
        perror("Не удалось открыть файл для первой матрицы");
        exit(1);
    }

    // Считываем данные первой матрицы из файла
    int bytesRead = read(fd1, matrix1, sizeof(int) * SIZE * SIZE);
    if (bytesRead == -1) {
        perror("Ошибка при чтении первой матрицы");
        exit(1);
    }
    close(fd1);  // Закрываем файл

    // Открываем файл второй матрицы
    int fd2 = open(file2, O_RDONLY);
    if (fd2 == -1) {
        perror("Не удалось открыть файл для второй матрицы");
        exit(1);
    }

    // Считываем данные второй матрицы из файла
    bytesRead = read(fd2, matrix2, sizeof(int) * SIZE * SIZE);
    if (bytesRead == -1) {
        perror("Ошибка при чтении второй матрицы");
        exit(1);
    }
    close(fd2);  // Закрываем файл

    int n = bytesRead / (sizeof(int) * SIZE);  // Размер матрицы

    matrixMultiply(matrix1, matrix2, result, n);  // Выполняем умножение матриц

    // Открываем файл для результирующей матрицы
    int fdResult = open(fileResult, O_WRONLY | O_CREAT | O_TRUNC);
    if (fdResult == -1) {
        perror("Не удалось открыть файл для результирующей матрицы");
        exit(1);
    }

    // Записываем результирующую матрицу в файл
    int bytesWritten = write(fdResult, result, sizeof(int) * n * n);
    if (bytesWritten == -1) {
        perror("Ошибка при записи результирующей матрицы");
        exit(1);
    }
    close(fdResult);  // Закрываем файл

    printf("Результирующая матрица успешно записана в файл '%s'\n", fileResult);

    return 0;
}
