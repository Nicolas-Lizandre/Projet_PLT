//
// Created by tompi on 16/10/2026.
//

#include "Game.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <SFML/Window/Touch.hpp>
#include "state/Player.h"
#include "state/easyAI.h"


using namespace std;
using namespace state;

client::Game::Game() : state(state::State(mutex)) {
}

void client::Game::run() {
    int PlayerTurn = 0;
    Board &board = state.getBoard();
    board.shuffle();
    std::array<std::unique_ptr<Entity>, 2> &players = state.getPlayers();
    string s;
    std::array<int, 2> mov;

    // Deal the twenty-four objectives between the two players
    array<Treasure, 24> treasures{};
    for (int k = 0; k < static_cast<int>(treasures.size()); ++k) {
        treasures[k] = static_cast<Treasure>(k + 1);
    }

    mt19937 generator(random_device{}());
    shuffle(treasures.begin(), treasures.end(), generator);

    for (int p = 0; p < static_cast<int>(players.size()); ++p) {
        array<Treasure, 12> objectives{};
        copy_n(treasures.begin() + p * 12, 12, objectives.begin());
        players[p]->setTreasureList(objectives);
    }

    const array<array<int, 2>, 2> startingPositions = {
        players[0]->getPosition(),
        players[1]->getPosition()
    };

    array<int, 2> obtainedTreasures{};

    auto treasureName = [](Treasure treasure) {
        const array<const char*, 25> names = {
            "Aucun", "Dragon", "Fantome", "Genie", "Sorciere",
            "Princesse", "Chauve-souris", "Chouette", "Rat",
            "Araignee", "Scarabee", "Lezard", "Papillon", "Livre",
            "Bourse", "Coffre", "Couronne", "Cle", "Anneau",
            "Chandelier", "Carte", "Epee", "Casque", "Crane", "Gemme"
        };

        return names[static_cast<int>(treasure)];
    };

    // Collect the current player positions
    auto getPositions = [&players]() {
        vector<array<int, 2>> positions;

        for (auto &player : players) {
            positions.push_back(player->getPosition());
        }

        return positions;
    };

    while (true) {
        cout << "Player" << PlayerTurn << "'s turn" << endl;

        Treasure currentTreasure =
            players[PlayerTurn]->getCurrentTreasure();

        board.display({}, getPositions(), currentTreasure);

        cout << "Tresors obtenus : "
             << obtainedTreasures[PlayerTurn] << "/12" << endl;

        if (currentTreasure != Treasure::NONE) {
            cout << "Objectif : \033[1;35m"
                 << treasureName(currentTreasure) << " ["
                 << (static_cast<int>(currentTreasure) < 10 ? "0" : "")
                 << static_cast<int>(currentTreasure)
                 << "]\033[0m" << endl;
        } else {
            cout << "Tous tes tresors sont obtenus ! Retourne en ("
                 << startingPositions[PlayerTurn][0] << ","
                 << startingPositions[PlayerTurn][1] << ")." << endl;
        }

        //old code:
        //
        // bool temp = true;
        // while (temp) {
        //     cout << " Masterplate: ";
        //     board.displayMasterplate();
        //     cout << " \n Do you want to turn the plate? (y/n)";
        //     cin >> s;
        //
        //     if (s == "y") {
        //         board.turnMasterPlate();
        //     } else if (s == "n") {
        //         temp = false;
        //     }
        // }
        //
        // cout << "insert plate where? (write xy)";
        // cin >> s;
        //
        // while (s.size() != 2) {
        //     cout << "Incorrect message length" << endl;
        //     cout << "insert plate where? (write xy)";
        //     cin >> s;
        // }
        // mov[0] = s[0] - '0';
        // mov[1] = s[1] - '0';
        mov = players[PlayerTurn]->chooseInsert(state);
        // Update tiles and players together
        if (!state.applyInsertion(mov[0], mov[1])) {
            cout << "Illegal insertion" << endl;
            continue;
        }

        // Read the position after the insertion
        std::array<int, 2> position =
            players[PlayerTurn]->getPosition();

        vector<array<int, 2>> atteignables =
            board.searchPath(position[0], position[1]);

        board.display(atteignables, getPositions(), currentTreasure);

        cout << "Cases atteignables depuis   "
             << position[0] << position[1] << endl;

        for (const auto &c : atteignables) {
            cout << "(" << c[0] << "," << c[1] << ") ";
            cout << "\n";
        }

        // cout << "move to? (write xy)";
        // cin >> s;
        //
        // while (s.size() != 2) {
        //     cout << "Incorrect message length" << endl;
        //     cout << "move to? (write xy)";
        //     cin >> s;
        // }
        //
        // mov[0] = s[0] - '0';
        // mov[1] = s[1] - '0';

        mov = players[PlayerTurn]->chooseMovement(atteignables,state);

        if (state.verifyMovementValidity(mov[0], mov[1], atteignables)) {
            players[PlayerTurn]->move(mov[0], mov[1]);

            // Validate the active player's objective
            if (state.obtainTreasure(PlayerTurn)) {
                ++obtainedTreasures[PlayerTurn];

                cout << "\033[1;35mPlayer" << PlayerTurn
                     << " : tresor obtenu : "
                     << treasureName(currentTreasure)
                     << " !\033[0m" << endl;
            }

            if (players[PlayerTurn]->getCurrentTreasure() == Treasure::NONE &&
                players[PlayerTurn]->getPosition() ==
                    startingPositions[PlayerTurn]) {
                board.display({}, getPositions(), Treasure::NONE);

                cout << "Victoire du Player" << PlayerTurn
                     << " ! Les 12 tresors sont obtenus "
                     << "et tu es revenu au depart." << endl;
                break;
            }
        }

        PlayerTurn = (PlayerTurn + 1) % 2;
        cout << endl;
    }
}