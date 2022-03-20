# minishell

> :warning: **This program is implemented under the Mac OS system.**

## Rus

#### Задача:
```
 Создать упрощенную версию bash.
```
#### Реализовано:
```
1. Коммандная строка, отображающая подсказки.
2. В коммандной строке отображается история использованных в процессе комманд.
3. Возможность запуска внутренних исполняемых файлов.
4. Обработка одинарных кавычек - ’.
5. Обработка двойных кавычки - ".
6. Обработка env через '$' и вывод кода ошибки '$?'.
7. Пренаправления(редиректы):
   · < - перенаправление ввода.
   · > - перенаправление вывода.
   · << - следует указать разделитель, затем считывать ввод до тех пор, пока не появится
          строка, содержащая разделитель.
   · >> - перенаправить вывод в режиме добавления.
8. Обработаны пайпы - '|'.
9. Обработаны сигналы ctrl-C, ctrl-D и ctrl-\.
   · ctrl-C - переносит строку.
   · ctrl-D - выход из программы.
   · ctrl-\ ничего не делает.
10. Встроенные функции:
   · echo - с опцией -n.
   · cd - только с относительным или абсолютным путем.
   · pwd без параметров.
   · export без параметров.
   · unset без параметров.
   · env без опций и аргументов.
   · exit без вариантов.
```
#### Рекомендации для запуска:
1. Установить библиотеку readline.
2. Запустить Makefile в коммандной строке: `make`
3. Запустить бинарный файл: `./minishell`

## Eng

#### The task:
```
 Create a simplified version of bash.
```
#### Implemented:
```
1. Command line displaying hints.
2. The command line displays the history of the commands used in the process.
3. Ability to run internal executable files.
4. Handled single quotes - '.
5. Handled double quotes - ".
6. Handled env via '$' and outputting error code '$?'.
7. Redirects:
   · < - input redirection.
   · > - output redirection.
   · << - should be given a delimiter, then read the input until a line containing the
          delimiter is seen
   · >> - should redirect output in append mode.
8. Processed pipes - '|'.
9. Processed signals:
   · ctrl-C displays a new prompt on a new line.
   · ctrl-D exits the shell.
   · ctrl-\ does nothing.
10. Built-in features:
    · echo with option -n.
    · cd with only a relative or absolute path.
    · pwd with no options.
    · export with no options.
    · unset with no options.
    · env with no options or arguments.
    · exit with no options.
```
#### Recommendations for starting:
1. Install the readline library.
2. Run Makefile on the command line: `make`
3. Run the binary: `./minishell`
