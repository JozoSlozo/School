#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sir.h"

typedef struct {
    int svg_size_x;
    int svg_size_y;
    int padding_x;
    int padding_y;
    int max_all;
    int simulation_len;
} SVGInfo;

int getSIR(FILE *input, SIR **array, int *days) {
    char line[100];
    while (fgets(line, sizeof(line), input)) {
        *days += 1;
    }
    fseek(input, 0, SEEK_SET);
    *array = (SIR*)malloc(*days * sizeof(SIR));
    for (int i = 0; i < *days; i++) {
        SIR temp;
        fgets(line, sizeof(line), input);
        temp.s = atof(strtok(line, ","));
        temp.i = atof(strtok(NULL, ","));
        temp.r = atof(strtok(NULL, ","));
        (*array)[i] = temp;
        if (temp.s < 0 || temp.i < 0 || temp.r < 0) {
            return 1;
        }
    }
    return 0;
}

double map(double input, double input_start, double input_end, double output_start, double output_end) {
    double slope = 1.0 * (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (input - input_start);
}

int getSIRMax(SIR *array, int len) {
    int max = 0;
    for (int i = 0; i < len; i++) {
        if ((array[i].s + array[i].i + array[i].r) > max) {
            max = (array[i].s + array[i].i + array[i].r);
        }
    }
    return max;
}


int createSVG(FILE* file, SVGInfo info, int days, SIR* input_sir, Parameters pram){
    fprintf(file, "<!DOCTYPE html>\n<html>\n<head>\n<title>Full Page SVG Line Chart</title>\n<style>body{background-color:darkslategrey;}</style>\n</head>\n");
    fprintf(file, "<body>\n<svg viewBox=\"0 0 %d %d\">\n", info.svg_size_x + info.padding_x * 2, info.svg_size_y + info.padding_y * 2);
    fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:black;stroke-width:10\" />\n", info.padding_x, info.padding_y + info.svg_size_y, info.svg_size_x + info.padding_x, info.padding_y + info.svg_size_y);
    fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:black;stroke-width:10\" />\n", info.padding_x, info.padding_y, info.padding_x, info.padding_y + info.svg_size_y);
    //real data
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < days; i++)//sus
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(input_sir[i].s, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(0,0,255,0.5);stroke-width:2\" />\n");
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < days; i++)//infected
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(input_sir[i].i, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(255,0,0,0.5);stroke-width:2\" />\n");
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < days; i++)//recovered
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(input_sir[i].r, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(0,255,0,0.5);stroke-width:2\" />\n");
    //simulation
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < info.simulation_len; i++)//sus
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(S(i, pram) * info.max_all, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(0,0,255,1);stroke-width:3\" />\n");
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < info.simulation_len; i++)//infected
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(I(i, pram) * info.max_all, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(255,0,0,1);stroke-width:3\" />\n");
    fprintf(file, "<polyline points=\"");
    for (int i = 0; i < info.simulation_len; i++)//recovered
    {
        fprintf(file, "%d,%d ", (int)round(info.padding_x + map(i, 0, info.simulation_len, 0, info.svg_size_x)), (int)round((info.padding_y + info.svg_size_y) - map(R(i, pram) * info.max_all, 0, (double)info.max_all, 0, info.svg_size_y)));
    }
    fprintf(file, "\" style=\"fill:none;stroke:rgba(0,255,0,1);stroke-width:3\" />\n");

    //axis labels
    fprintf(file, "<g style=\"font-size:25px;\">\n");
    int line_y = info.padding_y;
    for (int i = 0; i < 11; i++)
    {
        fprintf(file, "<text x=\"%d\" y=\"%d\">%d</text>\n", info.padding_x - 75, line_y, (10 - i) * (info.max_all / 10));
        line_y += info.svg_size_y / 10;
    }
    fprintf(file, "<text style= \"font-weight: bold;\" transform=\"rotate(270 %d %d)\" x=\"%d\" y=\"%d\">people</text>\n", info.padding_x - 100, (info.svg_size_y + info.padding_y * 2) / 2, info.padding_x - 100, (info.svg_size_y + info.padding_y * 2) / 2);
    fprintf(file, "</g>\n<g style=\"font-size:25px;\">\n");
    int line_x = info.padding_x;
    for (int i = 0; i < 11; i++)
    {
        fprintf(file, "<text x=\"%d\" y=\"%d\">%d</text>\n", line_x, info.svg_size_y + info.padding_y + 50, i * (100 / 10));
        line_x += info.svg_size_x / 10;
    }
    fprintf(file, "<text style= \"font-weight: bold;\" text x=\"%d\" y=\"%d\">days</text>\n", (info.svg_size_x + info.padding_x * 2) / 2, info.svg_size_y + info.padding_y + 100);
    fprintf(file, "</g>\n");
    //line color labels
    fprintf(file, "<g style=\"font-size:25px;\">\n");

    fprintf(file, "<text style= \"font-weight: bold;\" x=\"%d\" y=\"60\">simulation:</text>\n", info.padding_x);

    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(0,0,255,1);stroke-width:3\"/>\n", info.padding_x + 250, info.padding_x + 350);
    fprintf(file, "<text x=\"%d\" y=\"50\">Susceptible</text>\n", info.padding_x + 250);
    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(255,0,0,1);stroke-width:3\"/>\n", info.padding_x + 450, info.padding_x + 550);
    fprintf(file, "<text x=\"%d\" y=\"50\">Infected</text>\n", info.padding_x + 450);
    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(0,255,0,1);stroke-width:3\"/>\n", info.padding_x + 650, info.padding_x + 750);
    fprintf(file, "<text x=\"%d\" y=\"50\">Recovered</text>\n", info.padding_x + 650);

    fprintf(file, "<text style= \"font-weight: bold;\" x=\"%d\" y=\"60\">real data:</text>\n", info.padding_x + 1000);

    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(0,0,255,0.5);stroke-width:2\"/>\n", info.padding_x + 1250, info.padding_x + 1350);
    fprintf(file, "<text x=\"%d\" y=\"50\">Susceptible</text>\n", info.padding_x + 1250);
    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(255,0,0,0.5);stroke-width:2\"/>\n", info.padding_x + 1450, info.padding_x + 1550);
    fprintf(file, "<text x=\"%d\" y=\"50\">Infected</text>\n", info.padding_x + 1450);
    fprintf(file, "<line x1=\"%d\" y1=\"75\" x2=\"%d\" y2=\"75\" style=\"stroke: rgba(0,255,0,0.5);stroke-width:2\"/>\n", info.padding_x + 1650, info.padding_x + 1750);
    fprintf(file, "<text x=\"%d\" y=\"50\">Recovered</text>\n", info.padding_x + 1650);

    fprintf(file, "</g>\n");

    fprintf(file, "</svg>\n</body>\n</html>");
    return 0;
}
int main(int argc, char** argv){
    if (argc != 9)
    {
        puts("wrong arguments");
        return 1;
    }

    char* real_data = NULL;
    int infectious_days = 0;
    double infections_per_day = 0;
    char* output = NULL;
    int lines = 0;
    char *ext;

    for (int i = 1; i < 9; i++)
    {
        if (!strcmp(argv[i], "--real_data") && real_data == NULL)
        {
            i++;
            ext = strrchr(argv[i], '.');
            if (!ext) {
                puts("--real_data is not a file");
                return 1;
            } else if(!strcmp("csv", ext+1)) {
                real_data = argv[i];
            }
            else{
                puts("--real_data is not a cvs file");
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--infectious_days") && infectious_days == 0)
        {
            i++;
            if (atoi(argv[i]) > 0)
            {
                infectious_days = atoi(argv[i]);
            }
            else{
                puts("--infectious_days is not a number or its negative");
                return 0;
            }
        }
        else if (!strcmp(argv[i], "--infections_per_day") && infections_per_day == 0)
        {
            i++;
            if (atof(argv[i]) > 0)
            {
                infections_per_day = atof(argv[i]);
            }
            else{
                puts("--infections_per_day is not number or its negative");
            }
        }
        else if (!strcmp(argv[i], "--output") && output == NULL)
        {
            i++;
            ext = strrchr(argv[i], '.');
            if (!ext) {
                puts("--real_data is not a file");
                return 1;
            } else{
                output = argv[i];
            }
        }
        else{
            puts("wrong arguments");
            return 1;
        }
    }
    
    FILE* input = fopen(real_data, "r");
    if (!input)
    {
        printf("failed to open %s\n", real_data);
        return 1;
    }
    SIR *input_sir;
    if (getSIR(input, &input_sir, &lines))
    {
        printf("%s contains non-numbers or negative numbers\n", real_data);
    }

    int sim_len = 100;

    SIR* hist = (SIR*)malloc(sizeof(SIR)*sim_len);
    for (int i = 0; i < sim_len; i++)
    {
        hist[i].s = -1;
        hist[i].i = -1;
        hist[i].r = -1;
    }
    Parameters param = {input_sir[0].s, input_sir[0].i, input_sir[0].r, infections_per_day, (double)1/infectious_days, hist};

    FILE* output_file = fopen(output, "w");
    if (!output_file)
    {
        printf("failed to open %s\n", output);
        return 1;
    }

    SVGInfo svg_info = {2000,1000,250,115,getSIRMax(input_sir, lines), sim_len};

    createSVG(output_file, svg_info, lines, input_sir, param);
   
    fclose(input);
    fclose(output_file);
    free(input_sir);
    free(hist);    
    return 0;
}