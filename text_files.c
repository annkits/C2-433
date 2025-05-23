#include <stdio.h> //printf, fopen, fclose, ...
#include <stdlib.h> //remove, rename, ...
#include <string.h> //strlen, strcpy, strcat, ...

#define MAX_LINE 1000
#define MAX_WORD 100
#define MY_NAME "ANN"

int main(int argc, char *argv[]){ //argc - кол-во аргументов, argv - массив строк с аргументами
    if (argc != 2){ //проверка аргументов
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "w"); //открывает файл для записи и проверка
    if (file == NULL){
        perror("Ошибка открытия файла для записи\n");
        return 1;
    }

    const char *text[] = {
        "Это мой гриб, я его ем",
        "Я тебе сейчас объясню, ты чё, дурак что ли?",
        "Это фиаско, братан",
        "Это было очень красиво… но бессмысленно",
        "На чилле, на расслабоне",
        "Ноу ноу ноу мистер фиш ю вонт гоу ту ё фэмили",
        "Нужно что-то сказать обязательно нужно что-то сказать а то он догадается он догадается надо сказать надо сказать ГЕННАДИЙ",
        "У неё прежде времени сохранять невозможно родил началась родила родильная деятельность",
        "Похоня за таврией, похоня за таврией. Прикинь таврия *** мусоров, а тут ещё и ЁЖ",
        "-Фто это у тебя. -Камера. -Ааа, а я думала сова",
        "Зубенко Михаил Петрович, уор в закони, Шумиловский городок, Мафиозник"
    };
    int num_lines = sizeof(text) / sizeof(text[0]); //кол-во строк в массиве

    for (int i = 0; i < num_lines; i++){ //запись текста в файл с добавлением символа новой строки "\n"
        if (fprintf(file, "%s\n", text[i]) < 0){ //указаьтель на файл, формат
            printf("Ошибка записи в файл\n");
            fclose(file);
            return 1;
        }
    }

    if (fclose(file) == EOF){ //закрытие файла, End Of File - проверка
        printf("Ошибка закрытия файла\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r"); //открытие файла для чтения, проверка
    if (input == NULL){
        printf("Ошибка открытия файла %s для чтения\n", argv[1]);
        return 1;
    }

    FILE *temp = fopen("temp.txt", "w"); //создание временного файла для записи измененных строк
    if (temp == NULL){
        printf("Ошибка создания временного файла\n");
        fclose(input);
        return 1;
    }

    //чтение файла построчно
    char line[MAX_LINE]; //буфер для хранения тек строки
    char result[MAX_LINE]; //буфер для измененной строки
    while (fgets(line, MAX_LINE, input) != NULL){ //куда, макс кол-во символов, откуда
        char longest[MAX_WORD] = ""; //буфер для самого длинного слова
        int pos = 0, longest_len = 0, longest_start = 0, longest_end = 0; //тек позиция в строке, длина самого длинного слова, позиции начала и конца длинного слова
        int start = 0; //начало тек слова

        line[strcspn(line, "\n")] = 0; //str c span - оставляет все до символа новой строки, заменяя его на \0

        //поиск самого длинного слова
        while (pos <= strlen(line)){
            if (line[pos] == ' ' || line[pos] == '\0'){
                int len = pos - start;
                if (len > longest_len){
                    longest_len = len;
                    longest_start = start;
                    longest_end = pos;
                    strncpy(longest, line + start, len); //куда, с какого момента, макс кол-во символов
                    longest[len] = '\0'; //завершающий символ
                }
                start = pos + 1;
            }
            pos++;
        }

        //форм новой строки
        strncpy(result, line, longest_start); //копирует до начала самого длинного слова
        result[longest_start] = '\0';
        strcat(result, MY_NAME); //объединяет скопированное с именем
        strcat(result, line + longest_end); //добавляет остаток строки

        if (fprintf(temp, "%s\n", result) < 0){
            printf("Ошибка записи во временный файл\n");
            fclose(input);
            fclose(temp);
            return 1;
        }
    }

    if (fclose(input) == EOF || fclose(temp) == EOF){
        printf("Ошибка закрытия файлов\n");
        return 1;
    }

    //обновление исходного файла
    if (remove(argv[1]) != 0 || rename("temp.txt", argv[1]) != 0){ //удаляет старый и переименовывает временный в исходное имя
        printf("Ошибка обновления файла\n");
        return 1;
    }

    printf("Файл %s успешно обработан\n", argv[1]);
    return 0;
}