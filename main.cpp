#include <iostream>
#include "interfaz.h"

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
        while (getchar() != EOF);
        return ch;
    }
    while (getchar() != EOF);
    return 0;
}

int main() {
    new Interfaz;
    /*while(true) {
        cout << "Prueba" << endl;
        cout << kbhit() << endl;

        getchar();
        cin.get();
        sleep(1);
    }
    cin.get();
    getchar();*/
    return 0;
}
