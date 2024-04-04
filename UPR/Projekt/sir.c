#include <stdlib.h>
#include <stdio.h>
#include "sir.h"

int inithistory(Parameters *param, int len){
    param->history = (SIR*)malloc(sizeof(SIR) * len);
    for (int i = 0; i < len; i++)
    {
        param->history[i].s = -1;
        param->history[i].i = -1;
        param->history[i].r = -1;
    }
    return 0;
}
int freehistory(Parameters *param){
    free(param->history);
    return 0;
}

double S(int d, Parameters params){
    if (d == 0)
    {
        return ((double)params.suspectable / (params.suspectable + params.infected + params.recovered));
    }
    else if (params.history[d].s == -1)
    {
        double daybefore = S(d - 1, params);
        double suspectable = (daybefore - params.b * daybefore * I(d - 1, params));
        params.history[d].s = suspectable;
        return suspectable;
    }
    else
    {
        return params.history[d].s;
    }
}
double I(int d, Parameters params){
    if (d == 0)
    {
        return ((double)params.infected / (params.suspectable + params.infected + params.recovered));
    }
    else if (params.history[d].i == -1)
    {
        double daybefore = I(d - 1, params);
        double infected = (daybefore + (params.b * S(d - 1, params) * daybefore - params.y * daybefore));
        params.history[d].i = infected;
        return infected;
    }
    else{
        return params.history[d].i;
    }
}
double R(int d, Parameters params){
    if (d == 0)
    {
        return ((double)params.recovered / (params.suspectable + params.infected + params.recovered));
    }
    else if (params.history[d].r == -1)
    {   
        double recovered = (R(d - 1, params) + params.y * I(d-1, params));
        params.history[d].r = recovered;
        return recovered;
    }
    else{
        return params.history[d].r;
    }
}