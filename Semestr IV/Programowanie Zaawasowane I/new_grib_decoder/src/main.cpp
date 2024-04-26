#include "grip_decoder.h"
#include <conio.h>
int main() {
    grip_decoder gripDecoder("grip_data.bin");
    if(gripDecoder.find_grip()){
        gripDecoder.scan_PDS();
        if(getch()){
            return 0;
        }
    }
    std::cout << "Reached EOF" << std::endl;
    return 0;
}
