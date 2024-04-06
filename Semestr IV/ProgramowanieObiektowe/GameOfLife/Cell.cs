class Cell{
    private bool is_alive = false;
    private int id_x;
    private int id_y;


    public Cell(int new_x, int new_y){
        id_x = new_x;
        id_y = new_y;
    }

    public void set_state(bool state){
        is_alive = state;
    }

    public bool get_state(bool state){
        return is_alive;
    }
}