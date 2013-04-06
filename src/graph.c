#include <stdio.h>
#include <string.h>

#define MAXN 510
#define MAXL 10

typedef int (*distance_func)(char *a, char *b, int length);

int graph_matrix[MAXN][MAXN];
char fragments[MAXN][MAXL + 1];
int n_fragments;
int length = 10;

int n_shifted(char *a, char *b, int length)
{
    int n_common = 0;
    int i;

    for (i = 0; i < length; i++) {
        if (strncmp(a + i, b, length - i) == 0) {
            return i;
        }
    }
    return length;
}

int read_fragments(char *filename)
{
    FILE *f;
    int i, n_read;

    f = fopen(filename, "r");
    for (i = 0; i < MAXN; i++) {
        if (fscanf(f, "%s", fragments[i]) == EOF) {
            n_read = i;
            break;
        }
    }
    fclose(f);
    return n_read;
}

void build_graph(distance_func d)
{
    int i, j;
    for (i = 0; i < MAXN; i++) {
        for (j = 0; j < MAXN; j++) {
            graph_matrix[i][j] = d(fragments[i], fragments[j], length);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <data_file>\n", argv[0]);
        return 1;
    }

    n_fragments = read_fragments(argv[1]);
    build_graph(n_shifted);

    int i, j;
    for (i = 0; i < n_fragments; i++) {
        for (j = i; j < n_fragments; j++) {
            int d = graph_matrix[i][j];
            if (d > 0 && d < 3) {
                printf("%s ~ %s %d\n",
                       fragments[i], fragments[j], graph_matrix[i][j]);
            }
        }
    }

    return 0;
}
