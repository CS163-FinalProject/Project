#include"Tool.h"

int get_index(char key){
    if('0' <= key && key <= '9'){
        return key - '0';
    }else if('a' <= key && key <= 'z'){
        return key - 'a' +10;
    }else if('A' <= key && key <= 'Z'){
        return key -'A' + 10;
    }else if( key == '$'){
        return 36;
    }else if(key == '#'){
        return 37;
    }

    return -1;
}