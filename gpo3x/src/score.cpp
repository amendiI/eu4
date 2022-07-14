#include "score.hpp"
#include "graphtypes.hpp"
#include <vector>

double get_dev_mofier(province_data* province){

    double modifier;

    switch (province->prov_terrain)
    {
    case GRASSLANDS:
        modifier =1;
        break;
    case FARMLANDS:
        modifier =1,05;
        break;
    case DRYLANDS:
        modifier =0,95;
        break;
    case COASTLINE:
        modifier =0,85;
        break;
    case SAVANNAH:
        modifier =0,85;
        break;
    case WOODS:
        modifier =0,85;
        break;
    case FOREST:
        modifier =0,8;
        break;
    case HIGHLANDS:
        modifier =0,8;
        break;
    case STEPPES:
        modifier =0,8;
        break;
    case HILLS:
        modifier =0,75;
        break;
    case MARSH:
        modifier =0,75;
        break;
    case COASTAL_DESERT:
        modifier =0,65;
        break;
    case JUNGLE:
        modifier =0,65;
        break;
    case MOUNTAIN:
        modifier =0,65;
        break;
    case DESERT:
        modifier =0,5;
        break;
    case GLACIAL:
        modifier =0,5;
        break;
    default:
        modifier =1;
        break;
    }

    switch (province->prov_climate)
    {
    case TEMPERATE:
        break;
    case ARCTIC:
        modifier -= 0,5;
        break;
    case ARID:
        modifier -= 0,1;
        break;
    case TROPICAL:
        modifier -= 0,1;
        break;

    default:
        break;
    }
    if(modifier < 0.1)
        return 0.1;
    else 
        return modifier;
}

double get_def_value(province_data* province){

    switch (province->prov_terrain)
    {
    case WOODS:
    case FOREST:
    case HIGHLANDS:
    case HILLS:
    case MARSH:
    case JUNGLE:
    case GLACIAL:
        return 1;
    case MOUNTAIN:
        return 2;
    default:
        return 0;
    }
}

int getscore(graphnode** graph, uint16_t id,uint16_t depth){   
    
    std::vector<uint16_t> list ={id};
    std::vector<uint16_t> traited_province ={};
    double dev_modifier;
    double total_score=0;
    while (!list.empty()){
        graphnode* province = graph[list.back()];
        list.pop_back();

        double province_score=1;
        province_score += province->data->trade_modifier / 100 ;
        if (province->data->cot)
            province_score += 0,4 ;
        province_score += province->data->goods_modifier;
        
        province_score += get_def_value(province->data) /10;
        province_score *= get_dev_mofier(province->data);
        province_score += province->data->unique_modifier;
        total_score += province_score;
        traited_province.emplace_back(id);

        for (int i = 0; i < province->n_neighbors; i++){ //pour chaque voisin
            bool traited_neighbor =false;
            for (int j = 0; j < traited_province.size(); j++){//pour chaque noeud traite
                if (traited_province.at(j) == province->neighbors[i]){ //on regarde si il n'a pas été traité
                    traited_neighbor = true ;
                }
            }
            //si on a pas trouve le voisin on l'ajoute
            if(traited_neighbor)
                list.emplace_back(province->neighbors[i]);
        }
           
    }
    graph[id]->score =total_score;

}