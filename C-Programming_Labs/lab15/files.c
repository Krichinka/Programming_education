#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int id;
    char level[20];
} Employee;

Employee employees[MAX];
int empCount = 0;

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка открытия CSV");
        exit(1);
    }

    char line[128];

    while (fgets(line, sizeof(line), file) != NULL) {
        Employee emp;
        char *token = strtok(line, ";");
        if (!token) continue;
        strncpy(emp.name, token, sizeof(emp.name));
        token = strtok(NULL, ";");
        if (!token) continue;
        emp.id = atoi(token);
        token = strtok(NULL, ";\n");
        if (!token) continue;
        strncpy(emp.level, token, sizeof(emp.level));
        employees[empCount++] = emp;
    }

    if (fclose(file) != 0) {
        perror("Ошибка закрытия CSV");
    }
}

void printTable() {
    printf("\n|%-20s|%-10s|%-10s|\n", "Name", "ID", "Level");
    printf("-------------------------------------------\n");

    for (int i = 0; i < empCount; i++) {
        printf("|%-20s|%-10d|%-10s|\n",
               employees[i].name,
               employees[i].id,
               employees[i].level);
    }
    printf("-------------------------------------------\n");
}

void saveBinary(const char *filename) {
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Ошибка открытия database.dat");
        exit(1);
    }
    if (fwrite(&empCount, sizeof(int), 1, file) != 1) {
        perror("Ошибка записи count");
    }
    if (fwrite(employees, sizeof(Employee), empCount, file) != empCount) {
        perror("Ошибка записи массива");
    }
    fflush(file);
    if (fclose(file) != 0) {
        perror("Ошибка закрытия файла");
    }
}

void searchEmployee(const char *filename) {
    FILE *file = fopen(filename, "rb");
    int n;
    if (file == NULL) {
        perror("Ошибка открытия database.dat");
        return;
    }

    if (fread(&n, sizeof(int), 1, file) != 1) {
        perror("Ошибка чтения count");
        fclose(file);
        return;
    }

    int searchID;
    printf("\nВведите ID: ");
    scanf("%d", &searchID);

    Employee temp;
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (fread(&temp, sizeof(Employee), 1, file) != 1) {
            perror("Ошибка чтения структуры");
            break;
        }

        if (temp.id == searchID) {
            printf("\nНайден:\n%s | %d | %s\n",
                   temp.name, temp.id, temp.level);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Сотрудник не найден\n");
    }

    fclose(file);
}

void compress(const char *input, const char *output) {
    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");

    if (!in || !out) {
        perror("Ошибка открытия файлов");
        exit(1);
    }

    int prev = fgetc(in);
    if (prev == EOF) return;

    int count = 1;
    int curr;

    while ((curr = fgetc(in)) != EOF) {
        if (curr == prev && count < 255) {
            count++;
        } else {
            fputc(count, out);
            fputc(prev, out);
            prev = curr;
            count = 1;
        }
    }

    fputc(count, out);
    fputc(prev, out);

    fflush(out);

    fclose(in);
    fclose(out);
}

void decompress(const char *input, const char *output) {
    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");
    int count, value;
    if (!in || !out) {
        perror("Ошибка открытия файлов");
        exit(1);
    }
    while ((count = fgetc(in)) != EOF) {
        value = fgetc(in);
        for (int i = 0; i < count; i++) {
            fputc(value, out);
        }
    }
    fflush(out);
    fclose(in);
    fclose(out);
}

long getSize(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s staff.csv\n", argv[0]);
        return 1;
    }
    //read_file(argv[1]);
    //printTable();
    //saveBinary("database.dat");
    //searchEmployee("database.dat");
    compress("Picturee.jpg", "database.rle");
    decompress("database.rle", "restored.jpg");

    long before = getSize("Picturee.jpg");
    long after = getSize("database.rle");

    printf("\nОтчет:\n");
    printf("До: %ld байт\nПосле: %ld байт\n", before, after);

    if (before > 0) {
        printf("Сжатие: %.2f%%\n",
               100.0 * (before - after) / before);
    }
}