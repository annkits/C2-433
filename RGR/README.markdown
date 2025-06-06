# Проект "Шифр Виженера" (Вариант 10)

## Обзор
Этот проект реализует шифр Виженера, классический поливалентный шифр подстановки, для шифрования и дешифрования текста с использованием латинского алфавита (A-Z) и пробелов (всего 27 символов). Программа поддерживает как однопоточные, так и многопоточные режимы шифрования/дешифрования, управление динамической памятью и юнит-тестирование. Проект собран с использованием динамической библиотеки и системы сборки CMake.

### Возможности
- Шифрование и дешифрование текста с использованием шифра Виженера.
- Поддержка латинского алфавита (A-Z) и пробелов в входном тексте.
- Преобразование текста в нижнем регистре в верхний перед обработкой.
- Реализация однопоточных (`encrypt`, `decrypt`) и многопоточных (`parallel_encrypt`, `parallel_decrypt`) режимов с использованием POSIX Threads.
- Создание динамической библиотеки (`libvigenere.so`) для реализации шифра.
- Включение юнит-тестов с использованием CMocka для проверки функциональности.
- Сборка проекта через CMake.
- Чтение входных данных из файла (`input.txt`), запись результата в файл (`output.txt`) и прием ключа через аргументы командной строки.
- Проверка ключа на наличие только заглавных латинских букв (пробелы в ключе запрещены).

## Структура проекта
```
vigenere_project/
├── main.c              # Основная программа для шифрования/дешифрования
├── vigenere.c          # Реализация шифра Виженера (для динамической библиотеки)
├── vigenere.h          # Заголовочный файл с прототипами функций и константами
├── CMakeLists.txt      # Файл конфигурации CMake для сборки проекта
├── tests/
│   └── test_vigenere.c # Юнит-тесты с использованием CMocka
├── input.txt           # Входной файл (например, "HELLO WORLD")
├── output.txt          # Выходной файл (создается программой)
└── README.md           # Этот файл
```

## Требования
- **Операционная система**: Linux (проверено на WSL)
- **Компилятор**: GCC с поддержкой C11
- **Библиотеки**:
  - POSIX Threads (`pthread`) для многопоточности
  - CMocka для юнит-тестирования (должна быть установлена в `/usr/local`)
- **Инструмент сборки**: CMake (версия 3.10 или выше)

## Установка
1. **Клонирование репозитория** (если применимо):
   ```bash
   git clone <url-репозитория>
   cd vigenere_project
   ```

2. **Установка CMocka**:
   ```bash
   git clone https://git.cryptomilk.org/projects/cmocka.git
   cd cmocka
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   export CMAKE_PREFIX_PATH=/usr/local:$CMAKE_PREFIX_PATH
   ```

## Сборка проекта
1. Создайте директорию сборки и запустите CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. Установите путь к динамической библиотеке:
   ```bash
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/vigenere_project/build
   ```

## Использование
1. **Подготовка входного файла**:
   Создайте файл с именем `input.txt` с текстом для шифрования. Например:
   ```
   hello world
   ```
   Программа автоматически преобразует строчные буквы в заглавные (например, "HELLO WORLD").

2. **Запуск программы**:
   Используйте следующую команду для шифрования/дешифрования текста:
   ```bash
   ./vigenera ../input.txt ../output.txt KEY
   ```
   - `../input.txt`: Путь к входному файлу.
   - `../output.txt`: Путь к выходному файлу (будет создан или перезаписан).
   - `KEY`: Ключ шифрования (должен содержать только заглавные латинские буквы, без пробелов).

   **Пример вывода**:
   ```
   Debug: Checking key 'KEY'
   Char 'K' (code: 75), index in alphabet: 10
   Char 'E' (code: 69), index in alphabet: 4
   Char 'Y' (code: 89), index in alphabet: 24
   Input text:
   HELLO WORLD

   Encrypted text:
   RIIVS XFOVH

   Decrypted text:
   HELLO WORLD

   Check: Input and decrypted texts match
   ```

3. **Запуск юнит-тестов**:
   Для проверки функциональности запустите тесты:
   ```bash
   ./test_vigenere
   ```
   Тесты проверяют однопоточное и многопоточное шифрование/дешифрование, а также обработку пробелов в тексте.

## Тестовые случаи
- **Тест 1**: Однопоточное шифрование/дешифрование текста "HELLO" с ключом "KEY".
- **Тест 2**: Многопоточное шифрование/дешифрование текста "HELLO" с ключом "KEY".
- **Тест 3**: Многопоточное шифрование/дешифрование текста "HELLO WORLD" (с пробелами) с ключом "KEY".

Все тесты должны пройти успешно, подтверждая совпадение исходного и дешифрованного текста.

## Ограничения
- Ключ должен состоять только из заглавных латинских букв (A-Z); пробелы в ключе запрещены.
- Поддерживаются только латинский алфавит (A-Z) и пробелы в входном тексте; другие символы (например, цифры, знаки препинания) сохраняются без изменений.
- Программа предполагает, что входной файл существует и доступен для чтения.

## Участие в разработке
Вы можете форкнуть проект, внести улучшения и отправить пулл-реквесты. Для сообщений об ошибках или предложений по новым функциям создайте заявку (issue).

## Лицензия
Этот проект лицензирован под лицензией MIT.

## Благодарности
- Разработано Grok 3, создан xAI.
- Использует CMocka для юнит-тестирования.
- POSIX Threads для многопоточности.
```
