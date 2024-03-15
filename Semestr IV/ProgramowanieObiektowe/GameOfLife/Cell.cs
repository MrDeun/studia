using System.Numerics;

class Cell{
    public bool state;
    private uint id_x;
    private uint id_y;

    public Cell(uint position_x, uint position_y) {
        id_x = position_x;
        id_y = position_y;
        state = false;
    }

    private uint count_neighbours(uint max_width,uint max_height){
        uint count = 0;
        return count;
    }

    public bool check_next_state(uint max_width, uint max_height) {
        uint neighbours = count_neighbours(max_width, max_height);
        if(/*Some statements for certaing count for being alive*/){
            return true;
        } else {
            return false;
        }
    }


};