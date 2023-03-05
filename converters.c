int letters_to_numbers(char letter);
int string_to_number(char* str);

int letters_to_numbers(char letter) {
    int number;
    number = 0;
    switch(letter) {
            case 'A' :
            case 'a' :
                number = 1;
            break;
            case 'B' :
            case 'b' :
                number = 2;
            break;
            case 'C' :
            case 'c' :
                number = 3;
            break;
            case 'D' :
            case 'd' :
                number = 4;
            break;
            case 'E' :
            case 'e' :
                number = 5;
            break;
            case 'F' :
            case 'f' :
                number = 6;
            break;
            case 'G' :
            case 'g' :
                number = 7;
            break;
            case 'H' :
            case 'h' :
                number = 8;
            break;
            case 'I' :
            case 'i' :
                number = 9;
            break;
            case 'J' :
            case 'j' :
                number = 10;
            break;
            case 'K' :
            case 'k' :
                number = 11;
            break;
            case 'L' :
            case 'l' :
                number = 12;
            break;
            case 'M' :
            case 'm' :
                number = 13;
            break;
            case 'N' :
            case 'n' :
                number = 14;
            break;
            case 'O' :
            case 'o' :
                number = 15;
            break;
            case 'P' :
            case 'p' :
                number = 16;
            break;
            case 'Q' :
            case 'q' :
                number = 17;
            break;
            case 'R' :
            case 'r' :
                number = 18;
            break;
            case 'S' :
            case 's' :
                number = 19;
            break;
            case 'T' :
            case 't' :
                number = 20;
            break;
            case 'U' :
            case 'u' :
                number = 21;
            break;
            case 'V' :
            case 'v' :
                number = 22;
            break;
            case 'W' :
            case 'w' :
                number = 23;
            break;
            case 'X' :
            case 'x' :
                number = 24;
            break;
            case 'Y' :
            case 'y' :
                number = 25;
            break;
            case 'Z' :
            case 'z' :
                number = 26;
            break;
        }
    return number;
}

int string_to_number(char* str){
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        num = num * 10 + (str[i] - 48);
    }
    return num;
}