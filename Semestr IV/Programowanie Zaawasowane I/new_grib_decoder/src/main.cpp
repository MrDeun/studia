#include "grip_decoder.h"
#include <conio.h>
int main() {
    grip_decoder gripDecoder("grip_data.bin");
    if(gripDecoder.find_grip()){
        gripDecoder.scan_PDS();
        if(getch() == 'q'){
            return 0;
        }
        gripDecoder.scan_rest();
    }
    std::cout << "Reached EOF" << std::endl;
    return 0;
}
