#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // if no cmd arg provided or too many args provided
    if(!argv[1] || argv[2]){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //determining length and validity of key
    int length = 0;
    string key = argv[1];
    int i = 0; // counter
    while(key[i] != '\0'){
        char ch = key[i];

        if(isupper(ch)) ch+=32; // converting to lowercase
        else ch+=0;

        if(ch < 'a' || ch > 'z'){
            printf("Invalid Key!\n");
            return 1;
        }
        key[i] = ch;

        length++;
        i++;
    }

    // if length of key is not 26
    if(length != 26){
        printf("Key must contain 26 letters!\n");
        return 1;
    }

    //checking for duplicate characters
    bool check[26];
    for(int j = 0; j < 26; j++) check[j] = 0; //intiliazing array to zero
    for(int j = 0; j < 26; j++){
        if(check[key[j]-'a'] != 0){
            printf("Duplicate characters not allowed in key!\n");
            return 1;
        }
        else check[key[j]-'a']++;
    }

    // taking plaintext input from user
    string toEncrypt = get_string("plaintext: ");
    length = 0;
    while(toEncrypt[length] != '\0') length++;

    //encrypting
    char encrypted[length+1];
    i = 0;
    while(toEncrypt[i] != '\0'){
        char ch = toEncrypt[i];
        if(isupper(ch)) ch += 32; // to lowercase
        else ch += 0;

        if(ch >= 'a' && ch <= 'z'){
            if(isupper(toEncrypt[i])) encrypted[i] = key[ch-'a'] - 32;
            else encrypted[i] = key[ch-'a'];
        }
        else encrypted[i] = ch;
        i++;
    }
    encrypted[length] = '\0'; // inserting null terminator
    printf("ciphertext: %s\n", encrypted);

    return 0;
}
