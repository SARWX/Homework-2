# Домашнее задание по дисциплине "функциональная логика и теория алгоритмов" №2
### Студента группы ИУ4-32Б Новикова Тимофея
Программа получает на вход матрицу инцидентности,<br/>
записывает введенные значения в массив структур<br/>
после выводит сообщение о том является ли граф связным,<br/>
а также создает файл с расширением .gv<br/>
который преобразуется в .png картинку при помощи программы Graphviz
> Команда для исполнения в Linux имеет вид:<br/>
> gcc homework2.c -o hw2.out; ./hw2.out; dot -Tpng graph.gv -o graph.png && sxiv graph.png
