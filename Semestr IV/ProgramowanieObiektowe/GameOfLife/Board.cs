class Board{
    private Cell[,] board;
    private int width,height;
    public Board(int width_in, int height_in){
        width = width_in;
        height = height_in;
        board = new Cell[width,height];
    }

    public void init_board(string filename){
        // TO DO: initializing board with a file;
    }


};