#include <stdio.h>
#include <stdlib.h> //rand
#include <string.h>
#include <time.h>

#define MAX_NAME 100
#define MAX_PHONE 15
#define MAX_ADDRESS 100
#define MAX_ENTRIES 100

struct Abonent {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
};

// Массивы для генерации данных
const char* firstNames[] = {"Иван", "Петр", "Анна", "Мария", "Алексей", "Екатерина", "Дмитрий", "Ольга"};
const char* lastNames[] = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Попов", "Васильев", "Морозов"};
const char* middleNames[] = {"Иванович", "Петрович", "Сергеевич", "Александровна", "Викторович", "Николаевна"};
const char* cities[] = {"Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Казань", "Самара"};
const char* streets[] = {"Ленина", "Мира", "Горская", "Невский", "Баумана", "Советская"};

struct Abonent generateRandomAbonent() {
    struct Abonent ab;

    snprintf(ab.name, MAX_NAME, "%s %s %s",
             lastNames[rand() % 8],
             firstNames[rand() % 8],
             middleNames[rand() % 6]);

    snprintf(ab.phone, MAX_PHONE, "+7999%07d", rand() % 10000000);

    snprintf(ab.address, MAX_ADDRESS, "г. %s, ул. %s, д. %d, кв. %d",
             cities[rand() % 6],
             streets[rand() % 6],
             rand() % 50 + 1,  // дом от 1 до 50
             rand() % 20 + 1); // квартира от 1 до 20

    return ab;
}

void createFile(const char* filename, int n){
    FILE* file = fopen(filename, "wb");
    if (!file){
        printf("Ошибка создания файла\n");
        return;
    }

    for (int i = 0; i < n; i++){
        struct Abonent ab = generateRandomAbonent();
        fwrite(&ab, sizeof(struct Abonent), 1, file);
    }

    fclose(file);
    printf("Файл успешно создан\n");
}

void printFile(const char* filename){
    FILE* file = fopen(filename, "rb");
    if (!file){
        printf("Ошибка открытия файла\n");
        return;
    }

    struct Abonent ab;
    int count = 0;

    printf("\nСодержимое файла:\n");
    printf("-----------------------------------\n");
    while (fread(&ab, sizeof(struct Abonent), 1, file) == 1){ //куда, размер, кол-во эл-тов, откуда
        printf("Абонент %d:\n", ++count);
        printf("ФИО: %s\n", ab.name);
        printf("Телефон: %s\n", ab.phone);
        printf("Адрес: %s\n", ab.address);
        printf("-----------------------------------\n");
    }

    fclose(file);
}

void extractLastName(const char* fullName, char* lastName, size_t maxLen){
    char temp[MAX_NAME];
    strncpy(temp, fullName, MAX_NAME);
    temp[MAX_NAME - 1] = '\0';

    char* space = strchr(temp, ' ');
    if (space){
        *space = '\0';
    }

    strncpy(lastName, temp, maxLen);
    lastName[maxLen - 1] = '\0';
}

void extractFirstName(const char* fullName, char* firstName, size_t maxLen){
    char temp[MAX_NAME];
    strncpy(temp, fullName, MAX_NAME);
    temp[MAX_NAME - 1] = '\0';

    char* firstSpace = strchr(temp, ' ');
    if (firstSpace){
        char* secondSpace = strchr(firstSpace + 1, ' ');
        if (secondSpace){
            *secondSpace = '\0';
            strncpy(firstName, firstSpace + 1, maxLen);
            firstName[maxLen - 1] = '\0';
        } else {
            strncpy(firstName, firstSpace + 1, maxLen);
            firstName[maxLen - 1] = '\0';
        }
    } else {
        firstName[0] = '\0';
    }
}

void extractMiddleName(const char* fullName, char* middleName, size_t maxLen){
    char temp[MAX_NAME];
    strncpy(temp, fullName, MAX_NAME);
    temp[MAX_NAME - 1] = '\0';

    char* firstSpace = strchr(temp, ' ');
    if (firstSpace){
        char* secondSpace = strchr(firstSpace + 1, ' ');
        if (secondSpace){
            strncpy(middleName, secondSpace + 1, maxLen);
            middleName[maxLen - 1] = '\0';
        } else {
            middleName[0] = '\0';
        }
    } else {
        middleName[0] = '\0';
    }
}

void searchInFile(const char* filename){
    FILE* file = fopen(filename, "rb");
    if (!file){
        printf("Ошибка открытия файла\n");
        return;
    }

    int field;
    char searchStr[100];
    struct Abonent ab;
    int found = 0;

    printf("\nВыбирите поле для поиска:\n");
    printf("1 - Фамилия\n");
    printf("2 - Имя\n");
    printf("3 - Отчество\n");
    printf("4 - Последние цифры телефона\n");
    printf("5 - Адрес\n");
    printf("Ваш выбор: ");
    scanf("%d", &field);
    getchar(); // Очистка буфера

    printf("Введите значение для поиска: ");
    fgets(searchStr, 100, stdin);
    searchStr[strcspn(searchStr, "\n")] = 0;

    printf("\nРезультаты поиска:\n");
    printf("----------------------------------------\n");
    while (fread(&ab, sizeof(struct Abonent), 1, file) == 1){
        int match = 0;
        switch (field){
            case 1:
                char lastName[MAX_NAME];
                extractLastName(ab.name, lastName, MAX_NAME);
                match = (strcmp(lastName, searchStr) == 0);
                break;
            case 2:
                char firstName[MAX_NAME];
                extractFirstName(ab.name, firstName, MAX_NAME);
                match = (strcmp(firstName, searchStr) == 0);
                break;
            case 3:
                char middleName[MAX_NAME];
                extractMiddleName(ab.name, middleName, MAX_NAME); 
                match = (strcmp(middleName, searchStr) == 0);
                break;
            case 4:
                int digitCount = strlen(searchStr);
                if (digitCount > 7) digitCount = 7;
                int phoneLen = strlen(ab.phone);
                if (phoneLen >= digitCount){
                    const char* lastDigits = ab.phone + (phoneLen - digitCount);
                    match = (strncmp(lastDigits, searchStr, digitCount) == 0);
                }
                break;
            case 5:
                char address[MAX_ADDRESS];
                match = (strstr(ab.address, searchStr) != NULL);
                break;
            default:
                printf("Неверный выбор поля\n");
                fclose(file);
                return;
        }

        if (match){
            printf("ФИО: %s\n", ab.name);
            printf("Телефон: %s\n", ab.phone);
            printf("Адрес: %s\n", ab.address);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found){
        printf("Записей с такими данными не найдено\n");
    }

    fclose(file);
}

int main(){
    const char* filename = "Abonent.dat";
    int n;

    srand(time(NULL));

    printf("Введите количество абонентов для записи: ");
    scanf("%d", &n);

    if (n > MAX_ENTRIES){
        printf("Максимальное количество записей: %d\n", MAX_ENTRIES);
        n = MAX_ENTRIES;
    }

    createFile(filename, n);
    printFile(filename);
    searchInFile(filename);

    return 0;
}
