#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

inline void shift_left_onestep(char* text, size_t pos) {
    
    for (size_t i = pos; text[i] != 0; i++) {
        //we begin by shifting from the next pos, because if the pos we received is 0, we will end up
        //shifing to -1 position which is probably an overflow and an error
        text[i] = text[i + 1];
    }
}

inline void swap_chars(char* text, size_t first, size_t second) {
    char temp;
    temp = text[first];
    text[first] = text[second];
    text[second] = temp;
}

void decrypt_alpha(char* cipher_text) {

    for (size_t pos = 0; cipher_text[pos] != 0 && pos < 100001; pos++) {

        if (isupper(cipher_text[pos]) && cipher_text[pos + 1] != 0)
            if (islower(cipher_text[pos + 1]) && cipher_text[pos + 2] != 0)
                if (cipher_text[pos + 2] == '*') {
                    swap_chars(cipher_text, pos, pos + 1);
                    shift_left_onestep(cipher_text, pos + 2);
                }
    }
}

void decrypt_num(char* cipher_text) {
    
    while (cipher_text[0] != 0 && isdigit(cipher_text[0]) && cipher_text[0] != '0') {
        for (size_t pos = strlen(cipher_text); pos > 0; pos--) {
            if (cipher_text[pos] == '0') {
                swap_chars(cipher_text, 0, pos);
                shift_left_onestep(cipher_text, 0);
                break;
            }
        }
    }
}

int main(int argc, char** argv) {

    //assuming ASCII representation for the string, so we use char
    //and for a length up to 100000 we add 1 for the NULL character to be stored in
    //however best practice should be using linked list, it is only for simplicity

    char* cipher_text = (char*)malloc(100001 * sizeof(char));
    fgets(cipher_text, 100001, stdin);
    
    decrypt_alpha(cipher_text);
    decrypt_num(cipher_text);

    printf_s("%s", cipher_text);

    return 0;
}