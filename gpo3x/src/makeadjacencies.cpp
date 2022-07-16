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
#include "fileinput.hpp"

unsigned char** readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[71];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    std::cout << std::endl;
    std::cout << "Name: " << filename << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    fread(info, sizeof(unsigned char), 71, f); 
    int row_padded = (width*3 + 3);// & (~3);
    //int row_padded = width*3+3;
    unsigned char** data = new unsigned char*[height];

    unsigned char tmp;
    std::cout << "size y :"<< height<< std::endl;
    std::cout << "size x :"<< row_padded<< std::endl;
    for(int i = 0; i < height; i++)
    {
        data[i] = new unsigned char[row_padded];
        fread(data[i], sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[i][j];
            data[i][j] = data[i][j+2];
            data[i][j+2] = tmp;

            //std::cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< std::endl;
        }
    }
    fclose(f);
    return data;
}

typedef struct {
    uint16_t R;
    uint16_t G;
    uint16_t B;
} pixelcolor ;

pixelcolor getpixelcolor(unsigned char** data, uint16_t x, uint16_t y ){

    pixelcolor p ;

    p.R = (uint16_t)data[y][3*x];
    p.R = (uint16_t)data[y][3*x+1];
    p.B = (uint16_t)data[y][3*x+2];
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

uint16_t get_id_by_color(uint16_t** provinces, pixelcolor p){

    for (int i = 0; i < N_PROV; i++)
    {
        if (is_same_color(p,provinces[i]))
            return provinces[i][0];
        
    }
    return -1; //erreur 
}

uint16_t makeadjacencies(){
    char * nom_fichier;
    nom_fichier = (char*)malloc(sizeof(char)*100);
    std::strcpy(nom_fichier,"../data/provinces.bmp");
    unsigned char** data = readBMP(nom_fichier);
    free(nom_fichier);

    uint16_t** color = new u_int16_t* [N_PROV];
    get_colors(color);

    pixelcolor pcolor;
    std::vector<pixelcolor> adj_colors ={};
    std::ofstream file("../data/neighbors.txt");

    for (uint16_t i = 0; i < N_PROV; i++)
    {
        std::cout << "couleur du pixel "<< color[i][0]<<" : " << color[i][1]<<";"<< color[i][2]<<";" <<color[i][3]<< std::endl;
        for (uint16_t y = 0; y < HEIGHT_MAP-1; y++)
        {
            for (uint16_t x = 0; x < WIDTH_MAP-1; x++)
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
                    }
                    if(y != HEIGHT_MAP){// Y +1
                        pcolor = getpixelcolor(data,x,y+1);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }
                    if(x != 0){// X -1
                        pcolor = getpixelcolor(data,x-1,y);
                        if (!is_same_color(pcolor,color[i])){
                            if (!color_in_list(adj_colors,pcolor))
                                adj_colors.emplace_back(pcolor);
                        }
                    }
                    if(y != WIDTH_MAP){// X + 1
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



    file.close();
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
        delete data[i];
    }
    delete data;


    for (int i = 0; i < N_PROV; i++)
    {
        delete color[i];
    }
    delete color;
    return 0;
    
}
    