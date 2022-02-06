#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(){
    long card_number = get_long("Number: ");
    int sum = 0;
    long copy = card_number; // not changing original cardnumber.
    int count = 0;
    while(copy){
        copy /= 10;
        count ++ ;
    }
    if (count < 13) printf("INVALID\n");
    else{
    copy = card_number; //not wanting to change original card number
    do{
        copy /= 10;
        if((copy%10)*2 < 10) sum += (copy%10)*2;
        else{
            sum += ((copy%10)*2)%10 + 1;
        }
        copy/= 10;
    }while(copy);
    copy = card_number; //not wanting to chagnge original card_number
    int newsum = 0;
    do{
        newsum += (copy % 10);
        copy /= 10;
        copy /= 10;
    }while(copy);
    newsum += sum;

    if(newsum%10 == 0){
        bool printed = false;
        while(card_number && !printed){
            switch(card_number){ //You can use if-else in place of switch
                case 4:
                    printf("VISA\n");
                    printed = true;
                    break;
                case 34:
                case 37:
                    printf("AMEX\n");
                    printed = true;
                    break;
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    printed = true;
                    break;
                default:
                    card_number /= 10;
            }
        }
        if (!printed) printf("INVALID\n");
    }
    else printf("INVALID\n");
    }
}
