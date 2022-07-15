#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <filesystem>
#include <fileinput.hpp>
#include <iostream>
#include "constants.hpp"
#include <fstream>
#include <cstring>


unsigned char* readBMP(char* filename)
{
    uint16_t i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f); 

    // extract image height and width from header
    uint16_t width = *(int*)&info[18];
    uint16_t height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    uint16_t size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f); 
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            // flip the order of every 3 bytes
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}

typedef struct {
    uint16_t R;
    uint16_t G;
    uint16_t B;
} pixelcolor ;

pixelcolor getpixelcolor(unsigned char* data, uint16_t x, uint16_t y ){

    pixelcolor p ;

    p.R = (uint16_t)data[3 * (x * WIDTH_MAP + y)];
    p.G = (uint16_t)data[3 * (x * WIDTH_MAP + y)+1];
    p.B = (uint16_t)data[3 * (x * WIDTH_MAP + y)+2];
    return p;

}

bool is_same_color(pixelcolor pixel,uint16_t* province){
    if(pixel.R == province[1] && pixel.G == province[2] && pixel.B == province[3])
        return true;
    return false;
}

bool is_same_color(pixelcolor pixel,pixelcolor pixel2){
    if(pixel.R == pixel2.R && pixel.G == pixel2.G && pixel.B == pixel2.B)
        return true;
    return false;
}

bool color_in_list(std::vector<pixelcolor> adj_colors, pixelcolor pcolor){
    bool already_traited = false;
    for (int i = 0; i < adj_colors.size(); i++){
            if (is_same_color(adj_colors[i],pcolor))
                already_traited = true;
        }
    return already_traited;
}

uint16_t get_id_by_color(uint16_t provinces[N_PROV][4], pixelcolor p){

    for (int i = 0; i < N_PROV; i++)
    {
        if (is_same_color(p,provinces[i]))
            return provinces[i][0];
        
    }
    return -1; //erreur 
}

uint16_t makeadjacencies(){
    char * nom_fichier;
    nom_fichier = (char*)(sizeof(char)*21);
    std::strcpy(nom_fichier,"../data/provinces.bmp");
    unsigned char* data=readBMP(nom_fichier);
    uint16_t color[N_PROV][4];

    pixelcolor pcolor;
    std::vector<pixelcolor> adj_colors ={};
    std::ofstream file("../data/neighbors.txt");

    std::cout << "oui\n";
    for (uint16_t i = 0; i < N_PROV; i++)
    {
        for (uint16_t x = 0; x < WIDTH_MAP; x++)
        {
            for (uint16_t y = 0; y < HEIGHT_MAP; y++)
            {
                pcolor = getpixelcolor(data,x,y);

                if (is_same_color(pcolor,color[i]))
                {
                    // Y -1
                    if (y != 0){
                        pcolor = getpixelcolor(data,x,y-1);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }else if(y != HEIGHT_MAP){// Y +1
                        pcolor = getpixelcolor(data,x,y+1);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }else if(x != 0){// X -1
                        pcolor = getpixelcolor(data,x-1,y);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }else if(y != WIDTH_MAP){// X + 1
                        pcolor = getpixelcolor(data,x+1,y);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }   
                }
            }
        }
        file << i << ":";
        for (int j = 0; j < adj_colors.size(); j++)
        {
            file << get_id_by_color(color, adj_colors[j]);
        }
        file << std::endl;

        adj_colors.clear();
    } 
    return 0;

}
    