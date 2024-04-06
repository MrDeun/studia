#pragma once

class Cell{
    private:
        bool is_alive;
        size_t id_x,id_y;
    public:
        Cell(size_t _id_x,size_t _id_y);
        ~Cell();
};