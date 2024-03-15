class Board{
    private Cell[,] board;
    private uint width;
    private uint height;
    public Board(uint witdh, uint height){
        this.width = witdh;
        this.height = height;
        this.board = new Cell[this.width,this.height];
    }

    public void init(string filename){
    }

    public Cell get_cell(uint x, uint y){
        return board[x,y];
    }

};