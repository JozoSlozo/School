#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int get_width(TGAHeader *self){
    return self->width[1] << 8 | self->width[0];
}
int get_heigth(TGAHeader *self){
    return self->height[1] << 8 | self->height[0];
}

typedef struct {
    TGAHeader header;
    byte * date;
}TGA;

TGA *newTGA(int width, int heaigth, int depth){

}

int main(){
    FILE* file = fopen("imag.tga", "rb");
    assert(file);
    
    TGAHeader header = {};
    assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);
    
    printf("Image type: %d, pixel depth: %d\n", header.image_type, header.depth);
    printf("Image width: %d, heigth: %d\n", get_width(&header), get_heigth(&header));

    return 0;
}