using System.Xml;
using Microsoft.VisualBasic.FileIO;

class GameOfLife{
    private Board front_board;
    private Board back_board;
    private uint width,height;
    private bool should_exit = false;
    private void swap_board(){
        Board temp_board = front_board;
        front_board = back_board;
        back_board = temp_board;
        return;
    }

    public GameOfLife(uint width, uint height){
        this.width = width;
        this.height = height;
        front_board = new Board(width,height);
        back_board = new Board(width,height);
    }
    private void NextStage(){
        for (uint y = 0; y < height; y++){
            for (uint x = 0; x < width; x++){
                back_board.get_cell(x,y).state = front_board.get_cell(x,y).check_next_state(width,height);
            }
        }
    }


    public virtual void View(){
        Console.WriteLine("Please implement proper output for your usage");
        // OUTPUT << front_buffer();
    }


    public void Start(){
        while(!should_exit){
            View();
            NextStage();
            swap_board();
        }
    }


};