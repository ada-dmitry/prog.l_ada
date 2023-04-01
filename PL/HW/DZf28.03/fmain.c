#include "funcHeader.h"

int main()
{
    srand(time(0));
    People *professions1 = malloc(sizeof(People) * COUN);
    People *professions2 = malloc(sizeof(People) * COUN);

    if (professions1 == NULL || professions2 == NULL)
    {
        printf("Mesta net\n");
        exit(1);
    }

    st_rand(professions1, COUN);
    st_rand(professions2, COUN);

    printf("Perviy massiv:\n");
    print_struc(professions1, COUN);
    printf("\nVtoroi massiv:\n");
    print_struc(professions2, COUN);

    sort_sel(professions1, COUN);
    sort_sel(professions2, COUN);

    printf("\nPerviy massiv posle sort:\n");
    print_struc(professions1, COUN);
    printf("\nVtoroi massiv posle sort:\n");
    print_struc(professions2, COUN);

    People *ans = binSearch(professions1, COUN, 15);

    if (ans == NULL)
        printf("\nPeoples net\n");
    else
        printf("\nLength: %2d; name: %s\n", ans->count, ans->name);

    printf("\nElement in perviy massiv: ");
    pst(professions1, COUN, (int)(COUN * 0.7));
    printf("Element in vtoroi massiv: ");
    pst(professions2, COUN, (int)(COUN * 0.3));

    printf("\nNumber of para : %d\n", find_para(professions1, COUN, professions2, COUN));

    st_fprintf(professions1, COUN, "professions.txt", "w");
    st_fprintf(professions2, COUN, "professions.txt", "a");

    int line_number = lines_numf("professions.txt");
    printf("\nNumber of lines in professions.txt is %d\n", line_number);

    People *professions3 = malloc(sizeof(People) * line_number);

    if (professions3 == NULL)
    {
        printf("Mesta net\n");
        exit(1);
    }

    st_fscanf(professions3, line_number, "professions.txt");
    sort_sel(professions3, line_number);

    Sleep(50000);

    printf("\nTTretiy massiv is:\n");
    print_struc(professions3, line_number);
    free(professions1);
    free(professions2);
    free(professions3);
    return 0;
}