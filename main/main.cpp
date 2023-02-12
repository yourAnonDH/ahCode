#include "../includes/includes.h"

int main(int argc, char *argv[]) {
    ahClass ahClass1;
    variables var1;

    var1.installDP = ahClass1.installDependencies();
    var1.setVol = ahClass1.setVolume();
    var1.scanKM = ahClass1.scanKeyboardMouse();

    if (var1.installDP) {

        if (var1.setVol) {

            if (var1.scanKM) {

                // TODO
            } else {
                perror("Error occured on scanning keyboard, mouse");
                exit(1);
            }
        } else {
            perror("Error occurred on setting volume");
            exit(1);
        }
    } else {
        perror("Error occurred on dependancy installation");
        exit(1);
    }
    return 0;
}