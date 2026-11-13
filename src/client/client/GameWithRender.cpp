//
// Created by nicol on 12/11/2026.
//
#include "GameWithRender.h"

#include <thread>

using namespace client;

bool render_running = false;

GameWithRender::GameWithRender() :
gamecore(state::State(mutex)), list_commands(render::ListCommands(mutex)), render(render::Render(gamecore,list_commands)) {
    gamecore.getBoard().createPlayground();
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


