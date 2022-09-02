#include <iostream>
#include <sstream>
#include "../include/Registro.h"

Registro::Registro(std::string linha){
    std::vector<std::string> row;
    std::string word;

    std::istringstream iss(linha);
    while(getline(iss, word, ',')){
        row.push_back(word);
    }
    id = std::stoi(row[0]);
    name = row[1];
    score = std::stof(row[2]);
    genres = row[3];
    english_name = row[4];
    type = row[5];
    if(row[6] == "Unknown"){
        episodes = -1;
    }
    else{
        episodes = std::stoi(row[6]);
    }
    aired = row[7];
    premiered = row[8];
    producers = row[9];
    licensors = row[10];
    studios = row[11];
    source = row[12];
    duration = row[13];
    rating = row[14];
    ranked = std::stoi(row[15]);
    popularity = std::stoi(row[16]);
    members = std::stoi(row[17]);
    favorites = std::stoi(row[18]);
    watching = std::stoi(row[19]);
    completed = std::stoi(row[20]);
    on_hold = std::stoi(row[21]);
    dropped = std::stoi(row[22]);
    plan_to_watch = std::stoi(row[23]);
    score10 = std::stoi(row[24]);
    score9 = std::stoi(row[25]);
    score8 = std::stoi(row[26]);
    score7 = std::stoi(row[27]);
    score6 = std::stoi(row[28]);
    score5 = std::stoi(row[29]);
    score4 = std::stoi(row[30]);
    score3 = std::stoi(row[31]);
    score2 = std::stoi(row[32]);
    score1 = std::stoi(row[33]);
}

Registro::~Registro(){

}
