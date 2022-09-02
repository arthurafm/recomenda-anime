#include <iostream>
#include <sstream>
#include <string>
#include "../include/Registro.h"

// Construtor classe de Animes
Anime::Anime(std::string linha){
    std::vector<std::string> row;
    std::string word;

    // Leitura de linhas, separando atributos
    std::istringstream iss(linha);
    while(getline(iss, word, ',')){
        row.push_back(word);
    }
    // Set de atributos
    id = std::stoi(row[0]);
    name = row[1];
    if(row[2] == "Unknown"){
        score = -1;
    }
    else{
        score = std::stof(row[2]);
    }
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
    if(row[15] == "Unknown"){
        ranked = -1;
    }
    else{
        ranked = std::stoi(row[15]);
    }
    if(row[16] == "Unknown"){
        popularity = -1;
    }
    else{
        popularity = std::stoi(row[16]);
    }
    if(row[17] == "Unknown"){
        members = -1;
    }
    else{
        members = std::stoi(row[17]);
    }
    if(row[18] == "Unknown"){
        favorites = -1;
    }
    else{
        favorites = std::stoi(row[18]);
    }
    if(row[19] == "Unknown"){
        watching = -1;
    }
    else{
        watching = std::stoi(row[19]);
    }
    if(row[20] == "Unknown"){
        completed = -1;
    }
    else{
        completed = std::stoi(row[20]);
    }
    if(row[21] == "Unknown"){
        on_hold = -1;
    }
    else{
        on_hold = std::stoi(row[21]);
    }
    if(row[22] == "Unknown"){
        dropped = -1;
    }
    else{
        dropped = std::stoi(row[22]);
    }
    if(row[23] == "Unknown"){
        plan_to_watch = -1;
    }
    else{
        plan_to_watch = std::stoi(row[23]);
    }
    if(row[24] == "Unknown"){
        score10 = -1;
    }
    else{
        score10 = std::stoi(row[24]);
    }
    if(row[25] == "Unknown"){
        score9 = -1;
    }
    else{
        score9 = std::stoi(row[25]);
    }
    if(row[26] == "Unknown"){
        score8 = -1;
    }
    else{
        score8 = std::stoi(row[26]);
    }
    if(row[27] == "Unknown"){
        score7 = -1;
    }
    else{
        score7 = std::stoi(row[27]);
    }
    if(row[28] == "Unknown"){
        score6 = -1;
    }
    else{
        score6 = std::stoi(row[28]);
    }
    if(row[29] == "Unknown"){
        score5 = -1;
    }
    else{
        score5 = std::stoi(row[29]);
    }
    if(row[30] == "Unknown"){
        score4 = -1;
    }
    else{
        score4 = std::stoi(row[30]);
    }
    if(row[31] == "Unknown"){
        score3 = -1;
    }
    else{
        score3 = std::stoi(row[31]);
    }
    if(row[32] == "Unknown"){
        score2 = -1;
    }
    else{
        score2 = std::stoi(row[32]);
    }
    if(row[33] == "Unknown"){
        score1 = -1;
    }
    else{
        score1 = std::stoi(row[33]);
    }
}

// Deconstrutor
Anime::~Anime(){

}

std::int Anime::getID(){
    return id;
}

std::string Anime::getName()
{
    return name;
}

float Anime::getScore()
{
    return score;
}

std::string Anime::getGenres()
{
    return genres;
}

std::string Anime::getEnglishName()
{
    return english_name;
}

std::string Anime::getType()
{
    return type;
}

int Anime::getEpisodes()
{
    return episodes;
}

std::string Anime::getAired()
{
    return aired;
}

std::string Anime::getPremiered()
{
    return premiered;
}

std::string Anime::getProducers()
{
    return producers;
}

std::string Anime::getLicensors()
{
    return licensors;
}

std::string Anime::getStudios()
{
    return studios;
}

std::string Anime::getSource()
{
    return source;
}

std::string Anime::getDuration()
{
    return duration;
}

std::string Anime::getRating()
{
    return rating;
}

int Anime::getRanked()
{
    return ranked;
}

int Anime::getPopularity()
{
    return popularity;
}

int Anime::getMembers()
{
    return members;
}

int Anime::getFavorites()
{
    return favorites;
}

int Anime::getWatching()
{
    return watching;
}

int Anime::getCompleted()
{
    return completed;
}

int Anime::getOnHold()
{
    return on_hold;
}

int Anime::getDropped()
{
    return dropped;
}

int Anime::getPlanToWatch()
{
    return plan_to_watch;
}

int Anime::getScore10()
{
    return score10;
}

int Anime::getScore9()
{
    return score9;
}

int Anime::getScore8()
{
    return score8;
}

int Anime::getScore7()
{
    return score7;
}

int Anime::getScore6()
{
    return score6;
}

int Anime::getScore5()
{
    return score5;
}

int Anime::getScore4()
{
    return score4;
}

int Anime::getScore3()
{
    return score3;
}

int Anime::getScore2()
{
    return score2;
}

int Anime::getScore1()
{
    return score1;
}

std::string Manga::getTitle(){
    return title;
}

int Manga::getID(){
    return id;
}

std::string Manga::getType(){
    return type;
}

int Manga::getChapters(){
    return chapters;
}

int Manga::getVolumes(){
    return volumes;
}

std::string Manga::getStatus(){
    return status;
}

std::string Manga::getGenres(){
    return genres;
}

float Manga::getScore(){
    return score;
}

int Manga::getRanked(){
    return ranked;
}

std::string Manga::getAuthor(){
    return author;
}

std::string Manga::getSerializations(){
    return serializations;
}
