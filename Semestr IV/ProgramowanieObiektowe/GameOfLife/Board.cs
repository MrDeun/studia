class Board{
    private Cell[,] board;
    private int _width,_height;
    public Board(int width_in, int height_in){
        _width = width_in;
        _height = height_in;
        board = new Cell[_width,_height];
    }

    public void init_board(){
        for(int i = 0; i < _height; i++){
            for(int j = 0; j < _width; j++){
                board[i][j] = new Cell(i,j);
            }
        }
    }

    public uint count_neighbours(int id_x, int id_y){
        uint alive_neighbours = 0;
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if( (id_x + i) < 0 || (id_x + i >= width) ) continue;
                if( (id_y + j) < 0 || (id_y + j >= height) ) continue;
                if( (i != j) && i != 0){
                    alive_neighbours += get_cell(id_x + i, id_x + j).get_state() ? 1:0;
                }
            }
        }
        return alive_neighbours;
    }

    public Cell get_cell(int id_x, int id_y){
        if(id_x < 0 || id_x >= width()) throw "error: tried to access element outside of board";
        if(id_y < 0 || id_y >= height()) throw "error: tried to access element outside of board";

        return board[id_x,id_y];
    }

    public int width(){
        return _width;
    }
    public int height(){
        return _height;
    }


};