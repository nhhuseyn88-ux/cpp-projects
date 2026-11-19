#include "MrM.hpp"
#include <thread>
#include <chrono>


int main() {
    MrMCtr::MemoryController<std::string> TUI(64);

    // this a code example that you can make TUI with MrM.hpp

    TUI.iSave(0 , "Hello this is a TUI");
    TUI.iSave(1 , "cool right i can type anything and this can use \\n too");
    TUI.iSave(2 , "this is a string that has slash n \n yo why i am not sticking to n");
    TUI.iSave(3 , "\033[31mWhen my eyes turn red run ahh\033[0m");
    TUI.iSave(4 , "yeah anyways MrM.hpp is cool");

    TUI.dataOfEHIDX("YES");

    // use Ctrl + c to leave program
    while (1) {
        std::this_thread::sleep_for(std::chrono::minutes(10));
    }
  // idk why i put thread just for fun
}
