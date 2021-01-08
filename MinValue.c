#include <stdio.h>
#define NUMROWS 2
#define NUMCOLS 3

int main(void)
{

    const int table[NUMROWS][NUMCOLS] = {{9, 2, 5}, {3, -4, -12}};
    int minvals[NUMROWS];

    int i, j;

    printf("Table values:   minimum values \n");

    for (i = 0; i < NUMROWS; i++) // iterate through row
    {
        minvals[i] = table[0][0];     // arbituary value
        for (j = 0; j < NUMCOLS; j++) // iterate through columns
        {
            printf("%5d", table[i][j]);   //  print integer at a specific row and col
            if (table[i][j] < minvals[i]) // compare if the integer at this position is less than curent val in minval
            {

                minvals[i] = table[i][j]; // set minval if it statemt is true
            }
            //minvals[i] = (table[i][j] < minvals[i]) ? table[i][j] : minvals[i];  <- this is called a conditional operator -> does the same thing as above if statement
        }
        printf(":%5d\n", minvals[i]); // print val after each row iteration
    }

    return (0);
}