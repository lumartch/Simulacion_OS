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
    while (getchar() != EOF);
    if(ch != EOF) {
        return ch;
    }
    return 0;
}

void kbhitOpc(){
    int ch = kbhit();
    if(ch == 105 or ch == 73){
        cout << "Interrupcion" << endl;
    }
    else if(ch == 101 or ch == 69){
        cout << "Error" << endl;
    }
    else if(ch == 112 or ch == 80){
        cout << "Pausa" << endl;
        while (getchar() != EOF);
        while(true){
            if(kbhit()){
                ch = getchar();
                if(ch == 99 or ch == 67){
                    cout << "Continuar" << endl;
                    break;
                }
            }
        }
    }
}

int main() {
    new Interfaz;
    /*while(true) {
        cout << "Prueba" << endl;
        kbhitOpc();
        sleep(1);
    }*/
    return 0;
}
