#include "utils.h"

const double temp_util::cel_kel_diff = 273.15;

double temp_util::fahr_to_cel(double fahr)
{
    return (fahr - 32.0) / 1.8;
}
double temp_util::fahr_to_kel(double fahr)
{
    return ((fahr - 32.0) / 1.8) - cel_kel_diff;
}

double temp_util::cel_to_fahr(double cel)
{
    return (cel * 9/5) + 32.0;
}
double temp_util::kel_to_fahr(double cel)
{
    return (cel * 9/5) + 32.0 + cel_kel_diff;
}
