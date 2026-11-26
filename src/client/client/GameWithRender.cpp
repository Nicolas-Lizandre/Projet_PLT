//
// Created by nicol on 12/11/2026.
//
#include "GameWithRender.h"

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace client;

bool render_running = false;

GameWithRender::GameWithRender() :
gamecore(state::State(mutex)), list_commands(render::ListCommands(mutex)), render(render::Render(gamecore,list_commands)) {
    gamecore.getBoard().shuffle();
    gamecore.getPlayers()[1]->move(6,6); //Une fonction ici doit gérer la position et couleur des joueurs


    //Répartition initiale des trésors
    std::array<std::unique_ptr<state::Entity>, 2> & players = gamecore.getPlayers();
    std::array<state::Treasure, 24> treasures{};
    for (int k = 0; k < static_cast<int>(treasures.size()); ++k) {
        treasures[k] = static_cast<state::Treasure>(k + 1);
    }

    std::mt19937 generator(std::random_device{}());
    shuffle(treasures.begin(), treasures.end(), generator);

    for (int p = 0; p < static_cast<int>(players.size()); ++p) {
        std::array<state::Treasure, 12> objectives{};
        std::copy_n(treasures.begin() + p * 12, 12, objectives.begin());
        players[p]->setTreasureList(objectives);
    }
}

GameWithRender::~GameWithRender() = default;

void GameWithRender::run(){
    render.run();
    //WIP : Test avec threads (ft pas)
    /*
    render_running = true;

    std::thread task_exec_commands(&GameWithRender::execQueriedCommands, this);
    std::thread task_render(&render::Render::run, &render);

    task_render.join(); //Attente de la fin du render
    render_running = false;
    task_exec_commands.join();
    */
}

void GameWithRender::execQueriedCommands() { //Doit se faire dans un thread parallèle (se finissant lorsque windowOnClose)
    /* WIP : Ce bout de code est mis dans Render en attendant
    while (render_running) {
        list_commands.exeAll();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    */
}


