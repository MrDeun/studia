class Game_Engine{
    private Board front_board;
    private Board back_board;

    void check_next_state(){
        for (int i = 0; i <; i++){
            
        }
    }
    public void swap_boards(){
        Board temp_board = front_board;
        front_board = back_board;
        back_board = temp_board;
    }
    public Game_Engine(string filename){
        
    }
    public Game_Engine(int width, int height){
        front_board = new Board(width,height);
        back_board = new Board(width,height);
    }
};