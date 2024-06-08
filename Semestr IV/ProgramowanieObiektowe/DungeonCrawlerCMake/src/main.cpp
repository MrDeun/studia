#include "terminal_game.h"
#include <cassert>
int main(){
    constexpr size_t width = 10, height = 5;
    std::vector<char> map_data = {
            '#','#','#','#','#','#','#','#','#','#',
            '#','P','_','_','_','_','_','T','_','#',
            '#','_','_','_','_','_','_','_','_','#',
            '#','_','_','_','_','T','_','_','E','#',
            '#','#','#','#','#','#','#','#','#','#'
            };
    assert(map_data.size() == width * height);
  TerminalGame thisGame{};
  thisGame.Start();
  return 0;
}