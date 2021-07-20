#include<stdio.h>

// Global variables str for storing the result and length for storing size of result
char str[1024];
int length = 0;

// Alias 
typedef long long infi;

// Just Avoiding Garbage Values incurred after multiple calls
void init(char* string){
    length = 0;
    for(int i = 0; i<1024;i++){
        string[i] = '0';
    }
}

// Power function 
infi power(infi num1,infi num2){
    infi result = 1; //Stores the result 

    // Repeated multiplication 
    for(infi i = 0; i<num2; i++){
        result *= num1;
    }
    return result;
}

// Conversion to Char 
char cint(infi num1){
    return num1  + '0';

}

//Converting the 10,15 into hexadecimal A-F
char chex(infi num1){
    return num1 + 55;
}

// Displaying only the modified string 
void display(char* string){
    // Length is used for displaying only the modified string
    // From length to end of string  
    for(int i = 1024-length;i<1024;i++){
        printf("%c",string[i]);
    }
    printf("\n");
}

// Character to its corresponding integer
char ichar(char chr){
    return chr  - '0';
}

// The Decimal to Binary function 
char* DectoBin(infi num1){
    
    init(str); //Initialising the string
    infi position = 0; //Position is used to place binary bits at right places

    // Handling the Zero number
    if(num1 == 0){
        str[1023 - position] = '0';
        length++;
        return str;
    }

    while(num1>0){
        //Appending from right to left and from LSB to MSB
        str[1023 - position] = cint(num1%2);

        // printf("Loops %c \n",str[position]);
        // Modifying neccessary variables 
        num1 /= 2;
        position++;
        length++;  
    }
    return str;
}

// Decimal to Octal 
char* DectoOct(infi num1){
    
    init(str); //Initialising the string
    infi position = 0; //Position is used to place binary bits at right places

    // Handling the Zero number
    if(num1 == 0){
        str[1023 - position] = '0';
        length++;
        return str;
    }

    while(num1>0){
        //Appending from right to left and from LSB to MSB
        str[1023 - position] = cint(num1%8);

        // printf("Loops %c \n",str[position]);
        // Modifying neccessary variables 
        num1 /= 8;
        position++;
        length++;  
    }
    return str;
}

// Decimal to Hexadecimal
char* DectoHex(infi num1){
    
    init(str); //Initialising the string
    infi position = 0; //Position is used to place binary bits at right places

    // Handling the Zero number
    if(num1 == 0){
        str[1023 - position] = '0';
        length++;
        return str;
    }

    while(num1>0){
        //Appending from right to left and from LSB to MSB

        //Handling the remainders greater than or equal to hex 'A'
        if(num1%16 > 9){
            str[1023 - position] = chex(num1%16);

        }
        else{
        str[1023 - position] = cint(num1%16);
        }

        // printf("Loops %c \n",str[position]);
        
        // Modifying neccessary variables 
        num1 /= 16;
        position++;
        length++;  
    }
    return str;
}

// Function to convert any decimal number into any n ary system 
char* DectoRadix(infi num1,int radix){
    // Intialising the string to prevent garbage  values 
    init(str);
    //Position will be used to place the digits at correct positions 
    int position = 0;

    // Handling Standard Number Systems 
    if(radix==2){
        printf("Deprecation Warning: Use DectoBin() instead\n");
    }

    else if(radix==8){
        printf("Deprecation Warning: Use DectoOct() instead\n");
    }

    else if(radix==16){
        printf("Radix Error: Number System not supported.\n Try using 'DectoHex()'\n");
        return NULL;
    }

    // Main Code 
    else{

        // Handling the Zero number
        if(num1 == 0){
            str[1023 - position] = '0';
            length++;
            return str;
        }

        while(num1>0){
            //Inserting the digits of new number system
            str[1023 - position] = cint(num1%radix);
            
            //Modifying the neccessary varibles
            num1 /= radix;
            position++;
            length++;
        }
    }
    return str;
}

infi RadixtoDec(char* string,infi radix){
    int weight = 0;
    infi dec = 0;
    int i = 0;
    while(string[i] != '\0'){
        dec += ichar(string[i])*(power(radix,weight));
        // printf("Going\n");
        i++;
    }
    return dec;
}

int main(int argc, char const *argv[])
{
    // infi num1 = 8;
    // infi num2 = 2;
    // // printf("%Ld\n",power(8,2));
    // // init(str);

    
    for(int i = 0;i<10;i++){
        display(DectoRadix(i,3));
        // display(DectoBin(i));

    }
    printf("\n\nRadix %Ld\n",RadixtoDec("110",2));
    // printf("%c\n",chex(10));
    // display(DectoOct(8));
    return 0;
}
