#include <filesystem>
#include "MrM.hpp"
// idk why i entered filesystem:sob:

int main() {
  // this is the constructor int is the type of memory that MrM gonan use and Main(4) is the number of index's it can have its 0 , 1 , 2 , 3
  // because C++ uses 0 index rule so 0 is 1 and the limit you given lets say 64 its 64 is 65 and actual 64 is 63
    MrMCtr::MemoryController<int> Main(4);
    Main.openTemp(128);
  // this is for opening temp memory it can be rised up to 5MB which is 5.000.000

// for loop tries to run 128 times and its bigger then 4 so Main function needs to use temp memory
// if you delete Main.openTemp(128) its gonan give you OverFlow/OverFlowTemp error
    for (int i = 0; i < 128; i++) {
        Main.save(256);
    }

// These are just types limit of memories and dataOfEHIDX is packaed version of for loop in one line
    std::cout << "Limit of Main Memory " << Main.getLimitMrM() << '\n';
    std::cout << "Limit of Temp Memory " << Main.getLimitMrM("TEMP") << '\n';
    Main.dataOfEHIDX();
    std::cout << "Inside of temp btw" << std::endl;
    Main.dataOfEHIDX("NO" , "YES");

    return 0;
}
