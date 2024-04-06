
class Game_Engine{
    private Board front_board;
    private Board back_board;

    private bool determine_begin(Int32 Input){
        if (Input >= 74)
            return true;
        return false;

    }

    virtual void Show(){}

    void check_next_state(){
        for (int i = 0; i <front_board.height(); i++){
            for(int j = 0; j <front_board.width(); j++){
                uint neighbours = front_board.count_neighbours(i,j);

                if (neighbours > 3 || neighbours < 2){
                    back_board.get_cell(i,j).set_state(false);
                } else if (neighbours == 3) {
                    back_board.get_cell(i,j).set_state(true);
                } else continue;
            }
        }
    }
    public void swap_boards(){
        Board temp_board = front_board;
        front_board = back_board;
        back_board = temp_board;
    }

    public Game_Engine(int width, int height){
        front_board = new Board(width,height);
        back_board = new Board(width,height);
        Random rng = new Random();


        for(int i = 0; i < _width; i++){
            for(int j = 0; j < _height; j++){
                front_board.get_cell(i,j).set_state(determine_begin(rng.next(100)));
            }
        }
    }
};