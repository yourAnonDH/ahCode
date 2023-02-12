#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/utsname.h>
#include <string>
#include <string.h>
using namespace std;

class ahClass {
public:
    int installDependencies();
    int setVolume();
    int scanKeyboard();
    int disableKeyboard();
    int playAhSound();

private:
    char isOnline[9];
    char fgets1[1024];
    char *scanChar;
    size_t pPos;
    size_t pPos2;
    FILE *fileDescriptor;
    fstream fileStream;
    ifstream inputFileStream;
    stringstream scanStringStream;
    string scanString;
    string scanString2;
    string scanString3;
    string finalScanString;
    string disableBuffer;
};

class variables {
public:
    int installDP;
    int scanKM;
};

int ahClass::installDependencies() {
    
    fileDescriptor = popen("../shell_script/is_online.sh","r");

    if (fileDescriptor == NULL) {
        
        perror("Error occured on reading process ( popen() )");
        pclose(fileDescriptor);
        return 1;

    } else if (fileDescriptor != NULL) {

        *fgets1 = *fgets(isOnline, 8, fileDescriptor);

        if (fgets1 != NULL) {

            printf("%s", isOnline);

            if (isOnline == "Online1") {
                
                pclose(fileDescriptor);
                fileDescriptor = popen("../shell_script/deb_install_packages.sh", "r");
                sleep(5);
                pclose(fileDescriptor);
                return 0;

            } else {

                perror("Error occured, system seems to be offline");
                pclose(fileDescriptor);
                return 1;

            }

        } else if (fgets1 == NULL) {
            
            perror("Error occured on writing stream to var ( fgets() )");
            return 1;

        }

    }
    
}

int ahClass::setVolume() {

    fileDescriptor = popen("../shell_script/set_vol_to_max.sh", "r");
    
    if (fileDescriptor == NULL) {

        perror("Error occurred on setting voulume ( popen() )");
        pclose(fileDescriptor);
        return 1;
    
    }
    
    sleep(1);
    pclose(fileDescriptor);
    return 0;

}

int ahClass::scanKeyboard() {
    
    fileDescriptor = popen("../shell_script/scan_key_mouse.sh", "r");
    sleep(1);
    pclose(fileDescriptor);
    inputFileStream.open("../text_files/scan.txt");
    scanStringStream << inputFileStream.rdbuf();
    inputFileStream.close();

    scanString = scanStringStream.str();
    scanString = scanString.substr(scanString.find("keyboard"));
	scanString = scanString.substr(0, scanString.find("B:"));
	scanString = scanString.substr(scanString.find("event") + 5);
	scanString = scanString.substr(0, 1);
    
    scanString2 = scanStringStream.str();
    scanString2 = scanString2.substr(scanString2.find("keyboard"));
	scanString2 = scanString2.substr(0, scanString2.find("B:"));
	scanString2 = scanString2.substr(scanString2.find("event") + 6);
	scanString2 = scanString2.substr(0, 1);

    fileStream.open("../shell_script/get_key_map.sh", ios_base::out);
    fileStream.seekp(25);
    fileStream.write(scanString.c_str(), 2);

    if (strcmp(scanString2.c_str(), " ") != 0) {

        fileStream.seekp(26);
        fileStream.write(scanString2.c_str(), 1);
    
    }

    fileStream.close();

    fileDescriptor = popen("../shell_script/get_key_map.sh", "r");
    sleep(1);
    pclose(fileDescriptor);
    return 0;
}

int ahClass::disableKeyboard() {

    fileStream.open("../text_files/keymap.txt", ios_base::in | ios_base::out);
    scanStringStream << fileStream.rdbuf();
    fileStream.close();
    scanStringStream.clear();
    scanString.clear();
    scanString2.clear();
    scanString = scanStringStream.str();

    while (getline(fileStream, scanString)) {
        pPos = scanString.find("="); // pPos stands for pointer position.
        if (pPos != string::npos) {
            scanString2 += scanString.substr(0, pPos + 1);
            scanString2 += "\n";
        }
    }
    scanString.clear();
    scanString = scanStringStream.str();
    pPos2 = scanString.rfind(":");
    pPos2 + 8;

    scanString3 = scanString.substr(0, pPos2);
    finalScanString = scanString3.append(scanString2);

    fileStream.open("../text_files/keymap2.txt", ios_base::out);
    fileStream.write(finalScanString.c_str(), sizeof(finalScanString.c_str()));
    fileStream.close();

    fileDescriptor = popen("../shell_script/final_keyboard_disable.sh", "r");

    return 0;

}

int ahClass::playAhSound() {
    return 0;
}