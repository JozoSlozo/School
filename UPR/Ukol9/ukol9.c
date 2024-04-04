#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int char_height = 33;
int size_space = 10;//size of space character
int spacing_between = 1;//size of space between characters
float space_t_b = 0.02;//spacing from the top and bottom in percentage of page

// Header
typedef unsigned char byte;
typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

int get_width(TGAHeader *self) {
    return self->width[1] << 8 | self->width[0];
}

int get_height(TGAHeader *self) {
    return self->height[1] << 8 | self->height[0];
}

// Pixel
typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

Pixel *load_pixels(TGAHeader header, FILE *file) {
    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * get_width(&header) * get_height(&header));
    assert(fread(pixels, sizeof(Pixel) * get_width(&header) * get_height(&header), 1, file) == 1);
    return pixels;
}

int is_black(Pixel pixel) {
    if (pixel.blue < 40 && pixel.red < 40 && pixel.green < 40)
    {
        return 1;
    }
    return 0;
}

// TGA
typedef struct {
    TGAHeader header;
    Pixel *data;
    int height;
    int width;
} TGA;

TGA init_tga(FILE *file) {
    TGAHeader temp_header = {};
    fread(&temp_header, sizeof(TGAHeader), 1, file);

    int temp_height = get_height(&temp_header);
    int temp_width = get_width(&temp_header);

    Pixel *temp_pixels = load_pixels(temp_header, file);
    TGA temp = {temp_header, temp_pixels, temp_height, temp_width};
    return temp;
}

//utility
int get_index(char c) {
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; i++) {
        if (toupper(alphabet[i]) == toupper(c)) {
            return i;
        }
    }
    return -1;
}

int draw_letter(TGA main_image, int start_width, int start_height, TGA font_image) {
    for (int row = 0; row < font_image.height; row++) {
        for (int col = 0; col < font_image.width; col++) {
            if (!is_black(font_image.data[row * font_image.width + col])) {
                main_image.data[(start_width + row) * main_image.width + start_height + col] = font_image.data[row * font_image.width + col];
            }
        }
    }
    return 0;
}

int get_line_len(char *line, TGA *array) {
    int temp = 0;
    int a = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (isspace(line[i])) {
            temp += size_space;
        } else {
            temp += array[get_index(line[i])].width;
        }
        a = i;
    }
    return temp + (a - 1) * spacing_between;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        puts("Wrong parameters");
        return 1;
    }
    char *input_file_name = argv[1];
    char *output_file_name = argv[2];
    char *font_folder_name = argv[3];

    //input image
    FILE* input_file = fopen(input_file_name, "rb");
    if (input_file == NULL)
    {
        puts("Could not load image");
        return 1;
    }
    TGA main_image = init_tga(input_file);

    //font images
    TGA font_image_array[26];
    for (int i = 0; i < 26; i++)
    {
        char temp_char[100];
        sprintf(temp_char, "%s/%c.tga", font_folder_name, alphabet[i]);

        FILE* temp_file = fopen(temp_char, "rb");
        if (temp_file == NULL)
        {
            return 1;
        }
        font_image_array[i] = init_tga(temp_file);
        fclose(temp_file);
    }

    //init input
    char line_init[5];
    fgets(line_init, sizeof(line_init), stdin);
    int top = line_init[0] - '0';
    int bottom = line_init[2] - '0';

    int spacing_top = (int)(main_image.height * space_t_b);

    //the main loop
    for (int i = 0; i < (top + bottom); i++)
    {
        char line[101];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        int spacing_start = (int)(main_image.width - get_line_len(line, font_image_array))/2;
        if (spacing_start < 0)
        {
            printf("too many characters in a line\n");
            continue;
        }

        if (i == top)
        {
            spacing_top = (main_image.height - (int)(main_image.height * space_t_b)) - (bottom * char_height + (bottom - 1) * 10);
        }
        else if(i != 0){
            spacing_top += char_height + 10;
        }

        for (int l = 0; line[l] != '\0'; l++)
        {
            if (isspace(line[l]))
            {
                spacing_start = spacing_start + size_space;
            }
            else{
                TGA temp_tga = font_image_array[get_index(line[l])];

                draw_letter(main_image, spacing_top, spacing_start, temp_tga);

                spacing_start = spacing_start + temp_tga.width + spacing_between;
            }
        }
    }

    //writing to file
    FILE* output_file = fopen(output_file_name, "wb");
    fwrite(&main_image.header, sizeof(TGAHeader), 1, output_file);
    for (int i = 0; i < (main_image.width * main_image.height); i++)
    {
        fwrite(&main_image.data[i], sizeof(Pixel), 1, output_file);
    }

    //close and free
    fclose(output_file);
    fclose(input_file);
    free(main_image.data);
    for (int i = 0; i < 26; i++)
    {
        free(font_image_array[i].data);
    }
    return 0;
}