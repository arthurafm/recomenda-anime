#include <iostream>
#include <sstream>
#include <string>
#include "..\include\Registro.h"

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

// Construtor para leitura de arquivos
Anime::Anime(){
    id = -1;
    name = "Unknown";
    score = -1;
    genres = "Unknown";
    english_name = "Unknown";
    type = "Unknown";
    episodes = -1;
    aired = "Unknown";
    premiered = "Unknown";
    producers = "Unknown";
    licensors = "Unknown";
    studios = "Unknown";
    source = "Unknown";
    duration = "Unknown";
    rating = "Unknown";
    ranked = -1;
    popularity = -1;
    members = -1;
    favorites = -1;
    watching = -1;
    completed = -1;
    on_hold = -1;
    dropped = -1;
    plan_to_watch = -1;
    score10 = -1;
    score9 = -1;
    score8 = -1;
    score7 = -1;
    score6 = -1;
    score5 = -1;
    score4 = -1;
    score3 = -1;
    score2 = -1;
    score1 = -1;
}

Anime::Anime(int id, std::string name, float score, std::string genres, std::string english_name,std::string type, int episodes, std::string aired, std::string premiered, std::string producers,
             std::string licensors, std::string studios, std::string source, std::string duration, std::string rating, int ranked, int popularity, int members, int favorites, int watching,
             int completed, int on_hold, int dropped, int plan_to_watch, int score10, int score9, int score8, int score7, int score6, int score5, int score4, int score3, int score2, int score1){
    this->id = id;
    this->name = name;
    this->score = score;
    this->genres = genres;
    this->english_name = english_name;
    this->type = type;
    this->episodes = episodes;
    this->aired = aired;
    this->premiered = premiered;
    this->producers = producers;
    this->licensors = licensors;
    this->studios = studios;
    this->source = source;
    this->duration = duration;
    this->rating = rating;
    this->ranked = ranked;
    this->popularity = popularity;
    this->members = members;
    this->favorites = favorites;
    this->watching = watching;
    this->completed = completed;
    this->on_hold = on_hold;
    this->dropped = dropped;
    this->plan_to_watch = plan_to_watch;
    this->score10 = score10;
    this->score9 = score9;
    this->score8 = score8;
    this->score7 = score7;
    this->score6 = score6;
    this->score5 = score5;
    this->score4 = score4;
    this->score3 = score3;
    this->score2 = score2;
    this->score1 = score1;
}

// Construtor classe de Mangas
Manga::Manga(std::string linha){
    std::vector<std::string> row;
    std::string word;

    // Leitura de linhas, separando atributos
    std::istringstream iss(linha);
    while(getline(iss, word, ',')){
        row.push_back(word);
    }
    // Set de atributos
    title = row[0];
    id = std::stoi(row[1]);
    type = row[2];
    if (row[3] == ""){
        chapters = -1;
    }
    else{
        chapters = std::stoi(row[3]);
    }
    if (row[4] == ""){
        volumes = -1;
    }
    else{
        volumes = std::stoi(row[4]);
    }
    status = row[5];
    genres = row[6];
    if (row[7] == ""){
        score = -1;
    }
    else{
        score = std::stof(row[7]);
    }
    if (row[8] == ""){
        ranked = -1;
    }
    else{
        ranked = std::stof(row[8]);
    }
    author = row[9];
    serializations = row[10];
}

// Construtor para leitura de arquivos
Manga::Manga(){

}

// Deconstrutor de classe Anime
Anime::~Anime(){

}

// Desconstrutor de classe Manga
Manga::~Manga(){

}

int Anime::getID(){
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

void Anime::printaAnime()
{
    std::cout << "ID: " << this->getID() << "\n";
    std::cout << "Nome do anime: " << this->getName() << "\n";
    std::cout << "Pontuacao de 1 a 10: " << this->getScore() << "\n";
    std::cout << "Generos: " << this->getGenres() << "\n";
    std::cout << "Nome em ingles: " << this->getEnglishName() << "\n";
    std::cout << "Tipo: " << this->getType() << "\n";
    std::cout << "Numero de episodios: " << this->getEpisodes() << "\n";
    std::cout << "Quando foi ao ar: " << this->getAired() << "\n";
    std::cout << "Temporada: " << this->getPremiered() << "\n";
    std::cout << "Produtores: " << this->getProducers() << "\n";
    std::cout << "Licensiado por: " << this->getLicensors() << "\n";
    std::cout << "Studios: " << this->getStudios() << "\n";
    std::cout << "Fonte: " << this->getSource() << "\n";
    std::cout << "Duracao: " << this->getDuration() << "\n";
    std::cout << "Classificacao indicativa: " << this->getRating() << "\n";
    std::cout << "Rank: " << this->getRanked() << "\n";
    std::cout << "Popularidade: " << this->getPopularity() << "\n";
    std::cout << "Membros: " << this->getMembers() << "\n";
    std::cout << "Favoritos: " << this->getFavorites() << "\n";
    std::cout << "Assistindo: " << this->getWatching() << "\n";
    std::cout << "Ja assistiram: " << this->getCompleted() << "\n";
    std::cout << "Pausaram: " << this->getOnHold() << "\n";
    std::cout << "Desistiram: " << this->getDropped() << "\n";
    std::cout << "Planejam assistir: " << this->getPlanToWatch() << "\n";
    std::cout << "Notas 10: " << this->getScore10() << "\n";
    std::cout << "Notas 9: " << this->getScore9() << "\n";
    std::cout << "Notas 8: " << this->getScore8() << "\n";
    std::cout << "Notas 7: " << this->getScore7() << "\n";
    std::cout << "Notas 6: " << this->getScore6() << "\n";
    std::cout << "Notas 5: " << this->getScore5() << "\n";
    std::cout << "Notas 4: " << this->getScore4() << "\n";
    std::cout << "Notas 3: " << this->getScore3() << "\n";
    std::cout << "Notas 2: " << this->getScore2() << "\n";
    std::cout << "Notas 1: " << this->getScore1() << "\n";
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
