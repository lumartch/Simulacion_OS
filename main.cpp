#include <iostream>
#include "interfaz.h"

#include <termios.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>

using namespace std;

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int main() {
    new Interfaz;
    /*while(true) {
        cout << "Prueba" << endl;
        if(kbhit()){
            cout << "Tecla: ";
            int ch = getchar();
            cout << ch << endl;
        }
        sleep(1);
    }*/
    return 0;
}
