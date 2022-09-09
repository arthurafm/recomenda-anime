#include "../include/Operacoes.h"


// In-staging
void Anime::buscaAnimePorID(int id){
    Anime buffer_anime;
    BPTree buffer_bpt;
    int buffer_ch, buffer_in;
    std::ifstream arq, arq_bpt;
    arq_bpt.open("bpt_anime.bin", std::ios::binary);
    while(!(arq_bpt.eof())){
        arq_bpt.read((char *) &buffer_ch, sizeof(int));
        arq_bpt.read((char *) &buffer_in, sizeof(int));
        buffer_bpt.insereBPTree(buffer_ch, buffer_in);
    }
    buffer_in = buffer_bpt.procuraBPTree(id);
    arq_bpt.close();
    arq.open("anime.bin", std::ios::binary);
    for(int i = 0; i <= buffer_in; i++){
        arq.read((char *) &buffer_anime, sizeof(Anime));
    }
    arq.close();
    this->id = buffer_anime.id;
    this->name = buffer_anime.name;
    this->score = buffer_anime.score;
    this->genres = buffer_anime.genres;
    this->english_name = buffer_anime.english_name;
    this->type = buffer_anime.type;
    this->episodes = buffer_anime.episodes;
    this->aired = buffer_anime.aired;
    this->premiered = buffer_anime.premiered;
    this->producers = buffer_anime.producers;
    this->licensors = buffer_anime.licensors;
    this->studios = buffer_anime.studios;
    this->source = buffer_anime.source;
    this->duration = buffer_anime.duration;
    this->rating = buffer_anime.rating;
    this->ranked = buffer_anime.ranked;
    this->popularity = buffer_anime.popularity;
    this->members = buffer_anime.members;
    this->favorites = buffer_anime.favorites;
    this->watching = buffer_anime.watching;
    this->completed = buffer_anime.completed;
    this->on_hold = buffer_anime.on_hold;
    this->dropped = buffer_anime.dropped;
    this->plan_to_watch = buffer_anime.plan_to_watch;
    this->score10 = buffer_anime.score10;
    this->score9 = buffer_anime.score9;
    this->score8 = buffer_anime.score8;
    this->score7 = buffer_anime.score7;
    this->score6 = buffer_anime.score6;
    this->score5 = buffer_anime.score5;
    this->score4 = buffer_anime.score4;
    this->score3 = buffer_anime.score3;
    this->score2 = buffer_anime.score2;
    this->score1 = buffer_anime.score1;
}
