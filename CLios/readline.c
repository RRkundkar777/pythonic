#include<stdio.h>

// Function read a line from a file
int readline(char *location)
{
    // Initialising a File Pointer in read mode
    FILE *ostream;
    ostream = fopen(location, "r");

    // If file does not exist --> return 0
    if (ostream == NULL)
    {
        return 0;
    }

    // Else read the file character by character
    char result;
    int count = 0;
    result = getc(ostream);

    // While we dont encounter a newline --> continue reading
    while(result != 10)
    {
        printf("%c",result);
        result = getc(ostream);
        count++;
    }
    printf("\n");

    // Return the number of characters read
    return count;
}

// Driver Code
int main()
{
    printf("%d\n",readline("data.txt"));
}