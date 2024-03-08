class temp_util
{
    public:
        enum {ver = 113};
    protected:
        static const double cel_kel_diff; // 273.15 
    public:
        static double cel_to_kel(double cel) {return cel + cel_kel_diff;}
        static double kel_to_cel(double kel) {return kel - cel_kel_diff;}
        static double fahr_to_cel(double fahr);
        static double fahr_to_kel(double fahr);
        static double cel_to_fahr(double cel);
        static double kel_to_fahr(double kel);
};