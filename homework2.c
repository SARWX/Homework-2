#include <stdio.h>
#include <stdlib.h>

struct Knot
{
    char name[20];
    int* edge;
};

int power(int n, int pow) {   // возводит n в степень pow
    int i, answer = 1;
    for (i = 0; i < pow; i++)
        answer *= n;
    return(answer);
}

int main() {
    int Knots = 0, Edges = 0;
    int i, j;

    printf("Input the number of your knots: ");
    scanf("%d", &Knots);
                printf("%d", Knots);
    printf("\nInput the number of your edges: ");
    scanf("%d", &Edges);
                printf("%d", Edges);

    struct Knot *knot;      // Объявили указатель на структуру
    knot = (struct Knot *) calloc(Knots, sizeof(struct Knot *) + (sizeof(int) * Edges)*Knots);        // Задали число массивов
    if(!knot) {
        printf ("Allocation failure.");
        exit (1);
    }

    printf("\nInput names of yours knots via Enter: \n");

    for(i = 0; i < Knots; i++) {
        scanf("%s", knot[i].name);
    }

    printf("\t|");
    for(i = 1; i <= Edges; i++)
        printf("%d|", i);
    printf("\n");


    getchar();
    for(i = 0; i < Knots; i++) {
        printf("%s\t|", knot[i].name);

        knot[i].edge = (int*) calloc(Edges, sizeof(int)); // calloc почемуто сжирает место у соседей, а malloc выделяет в другом месте
        if(!knot[i].edge) {
            printf ("Allocation failure.");
            exit (1);
        }

        for (j = 0; j < Edges; j++){
            int x = (getchar() - '0');
            knot[i].edge[j] = x;
            getchar();
        }
    }

// Пишем файл
    int trig = 0;

    FILE *file;
    file = fopen("./graph.gv", "w+t");
    //Пишем в файл
    fprintf(file, "graph HomeWork {\n");
    for (j = 0; j < Edges; j++) {
        for (i = 0; i < Knots; i++) {
//            printf("%d.%d)  %d -- trig = %d\n", j, i, knot[i].edge[j], trig);
            if (knot[i].edge[j] == 1) {
                if (trig == 0) {
                    fprintf(file, "\t%s -- ", knot[i].name);
                    trig = (i + 1);     // +1 чтобы trig не равнялся 0
                }
                else {
                    fprintf(file, "%s\n", knot[i].name);
                    trig = 0;
                }
            }
        }
        if (trig != 0) {
            fprintf(file, "%s\n", knot[(trig-1)].name);
            trig = 0;
        }
    }
    fprintf(file, "}");
    //Закрываем файл
    fclose(file);

    // Проверка на связность
    int answer = 0, mask = 0;

    for (i = 0; i < Knots; i++) {
        for (j = 0; j < Edges; j++){
            if (knot[i].edge[j] == 1)
                mask += power(2,j); //создаем двоичную маску
        }
        if (((answer & mask) != 0) || (i == 0))
            answer = answer | mask;
        mask = 0;
    }

    if (answer == (power(2, Edges) - 1))
        printf("\nYour graph is connected");
    else
        printf("\nYour graph is not connected");

    return 0;
}
