//
// Created by tompi on 08/10/2026.
//

#include "Board.h"
#include "L.h"
#include "T.h"
#include "I.h"

#include <iostream>
#include <memory>
#include <queue>
#include <array>
#include <algorithm>
#include <utility>
#include <ctime>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <random>

using namespace state;

state::Board::Board(): playground{}, masterplate{} {
    this->shuffle();
}


bool state::Board::verifyInsertValidity(int i, int j) {
     int legal_inserts[12][2] = {
        {0, 1}, {0, 3}, {0, 5},
        {6, 1}, {6, 3}, {6, 5},
        {1, 0}, {3, 0}, {5, 0},
        {1, 6}, {3, 6}, {5, 6}
    };

    for ( auto& pos : legal_inserts) {
        if (pos[0] == i && pos[1] == j) {
            return true;
        }
    }
    return false;
}

bool state::Board::insertPlate(int i, int j) {
    if (verifyInsertValidity(i,j)) {
        auto tempPlate = std::move(masterplate);
        switch (i) {
            case 0:
                masterplate = std::move(playground[6][j]);
                for (int l = 6; l > 0; --l) {
                    playground[l][j] = std::move(playground[l - 1][j]);
                }
                playground[0][j] = std::move(tempPlate);
                return true;

            case 6:
                masterplate = std::move(playground[0][j]);
                for (int l = 0;  l<6 ; l++) {
                    playground[l][j] = std::move(playground[l + 1][j]);
                }
                playground[6][j]=std::move(tempPlate);
                return true;
        }

        switch (j) {
            case 0:
                masterplate = std::move(playground[i][6]);
                for (int l = 6;  l>0 ; l--) {
                    playground[i][l] = std::move(playground[i][l-1]);
                }
                playground[i][0]=std::move(tempPlate);
                return true;

            case 6:
                masterplate = std::move(playground[i][0]);
                for (int l = 0;  l<6 ; l++) {
                    playground[i][l] = std::move(playground[i][l+1]);
                }
                playground[i][6]=std::move(tempPlate);
                return true;
        }
    }
    return false;
}


void state::Board::turnMasterPlate(){
    masterplate->turnPlate();
}


/*void state::Board::display(
    const std::vector<std::array<int, 2>>& reachable,
    const std::vector<std::array<int, 2>>& playerPositions)
{
    const char* const RESET = "\033[0m";
    const char* const YELLOW = "\033[1;33m";

    const char* const PLAYER_COLORS[2] = {
        "\033[1;37;42m", // White text, green background
        "\033[1;37;41m"  // White text, red background
    };

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            const char* couleur = RESET;

            // Highlight reachable cells
            for (const auto& c : reachable) {
                if (c[0] == i && c[1] == j) {
                    couleur = YELLOW;
                    break;
                }
            }

            // Player colors take priority
            for (std::size_t k = 0; k < playerPositions.size(); ++k) {
                if (playerPositions[k][0] == i &&
                    playerPositions[k][1] == j) {
                    couleur = PLAYER_COLORS[k % 2];
                }
            }

            std::cout << couleur;

            if (playground[i][j]) {
                playground[i][j]->showPlate();
            } else {
                std::cout << '?';
            }

            std::cout << RESET;
        }

        std::cout << '\n';
    }
}*/

void Board::displayMasterplate() {
    masterplate->display();
}

void state::Board::display(
    const std::vector<std::array<int, 2>>& reachable,
    const std::vector<std::array<int, 2>>& playerPositions,
    Treasure expected)
{
    const char* reset = "\033[0m";
    const char* reachableColor = "\033[1;33m";
    const char* treasureColor = "\033[1;30;105m";
    const std::array<const char*, 4> playerColors = {
        "\033[1;37;42m", "\033[1;37;41m",
        "\033[1;37;44m", "\033[1;37;46m"
    };

    std::cout << "\n     ";
    for (int j = 0; j < 7; ++j) {
        std::cout << j << "   ";
    }
    std::cout << '\n';

    for (int i = 0; i < 7; ++i) {
        std::cout << " " << i << "  ";
        for (int j = 0; j < 7; ++j) {
            const std::array<int, 2> position = {i, j};
            Plate* plate = playground[i][j].get();
            const bool isReachable =
                std::find(reachable.begin(), reachable.end(), position) !=
                reachable.end();
            const bool isObjective =
                expected != Treasure::NONE && plate &&
                plate->hasTreasure(expected);
            const char* color = isObjective ? treasureColor :
                (isReachable ? reachableColor : reset);

            for (std::size_t k = 0;
                 k < playerPositions.size() && k < playerColors.size(); ++k) {
                if (playerPositions[k] == position) {
                    color = playerColors[k];
                    break;
                }
            }

            std::cout << color;
            if (plate) {
                plate->display();
            } else {
                std::cout << '?';
            }
            if (isObjective) {
                const int id = static_cast<int>(expected);
                std::cout << treasureColor << (id < 10 ? "0" : "") << id;
            } else {
                std::cout << "  ";
            }
            std::cout << reset << ' ';
        }
        std::cout << '\n';
    }

    std::cout << reachableColor << " Case atteignable " << reset << '\n';
}

/*void state::Board::createPlayground() {
    for (auto& row : playground) {
        for (auto& plate : row) {
            plate = std::make_unique<state::L>();
            plate->setTreasure(Treasure::NONE);
        }
    }
    masterplate = std::make_unique<state::T>();
    masterplate->setTreasure(Treasure::NONE);

    std::vector<std::array<int, 2>> treasurePositions;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            const bool isCorner =
                (i == 0 || i == 6) && (j == 0 || j == 6);
            if (!isCorner) {
                treasurePositions.push_back({i, j});
            }
        }
    }

    std::mt19937 generator(std::random_device{}());
    std::shuffle(treasurePositions.begin(), treasurePositions.end(), generator);
    for (int id = 1; id <= static_cast<int>(Treasure::GEM); ++id) {
        const auto& position = treasurePositions[id - 1];
        playground[position[0]][position[1]]->setTreasure(
            static_cast<Treasure>(id));
    }
}*/

std::vector<std::array<int, 2>> state::Board::searchPath (int i, int j)
{
    std::vector<std::array<int, 2>> reachable;

    if (i < 0 || i >= 7 || j < 0 || j >= 7) return reachable;

    if (!playground[i][j]) return reachable;

    const int di[4] = { -1, 0, 1, 0 };
    const int dj[4] = { 0, 1, 0, -1 };

    auto isOpen = [this](int a, int b, int dir) {
        const std::unique_ptr<Plate>& plate = playground[a][b];
        if (!plate) return false;
        switch (dir) {
        case 0:  return plate->getNorth();
        case 1:  return plate->getEast();
        case 2:  return plate->getSouth();
        case 3:  return plate->getWest();
        default: return false;
        }
    };

    bool visited[7][7] = {};
    std::queue<std::array<int, 2>> file;

    visited[i][j] = true;
    file.push({ i, j });

    while (!file.empty()) {
        std::array<int, 2> courante = file.front();
        file.pop();
        reachable.push_back(courante);

        for (int dir = 0; dir < 4; ++dir) {
            int ni = courante[0] + di[dir];
            int nj = courante[1] + dj[dir];

            if (ni < 0 || ni >= 7 || nj < 0 || nj >= 7) continue;
            if (visited[ni][nj]) continue;

            if (isOpen(courante[0], courante[1], dir) &&
                isOpen(ni, nj, (dir + 2) % 4)) {
                visited[ni][nj] = true;
                file.push({ ni, nj });
            }
        }
    }
    return reachable;
}

bool state::Board::hasTreasureAt(
    int i, int j, Treasure expected) const
{
    if (i < 0 || i >= 7 || j < 0 || j >= 7 || !playground[i][j]) {
        return false;
    }
    return playground[i][j]->hasTreasure(expected);
}
// Helpers :

std::string defaultFilename(const std::string& prefix = "SavedGame") {
    std::time_t t = std::time(nullptr);
    char time_in_char[32];
    std::strftime(time_in_char, sizeof(time_in_char), "%Y-%m-%d_%H-%M-%S", std::localtime(&t));
    return prefix + "_" + time_in_char + ".json";
}

static Json::Value toJson(const Plate& plate) {
    Json::Value value;
    value["north"] = plate.getNorth();
    value["south"] = plate.getSouth();
    value["east"] = plate.getEast();
    value["west"] = plate.getWest();
    return value;
}

static std::unique_ptr<Plate> fromJson(const Json::Value& SavedPlate) {
    std::unique_ptr<Plate> plate;
    auto nb_access = SavedPlate["north"].asBool() + SavedPlate["south"].asBool() + SavedPlate["east"].asBool() + SavedPlate["west"].asBool();
    if(nb_access == 3) {
        plate = std::make_unique<T>();

    } else if (nb_access == 2 && ((SavedPlate["north"].asBool() && SavedPlate["south"].asBool()) || (SavedPlate["east"].asBool() && SavedPlate["west"].asBool()))) {
        plate = std::make_unique<I>();
    } else  if(nb_access == 2) {
        plate = std::make_unique<L>();
    }else{
        std::cerr << "Invalid plate configuration in JSON." << std::endl;
        return nullptr;
    }

    for (int k =0; k < 4 && (plate->getNorth() != SavedPlate["north"].asBool() || plate->getEast() != SavedPlate["east"].asBool() || plate->getSouth() != SavedPlate["south"].asBool() || plate->getWest() != SavedPlate["west"].asBool()); k++) {
            plate->turnPlate();
        }
    return plate;
}

void state::Board::save(std::string name) {
    if (name.empty()) {
        name = defaultFilename();
    }
    Json::Value root;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (playground[i][j]) {
                root["playground"][i][j] = toJson(*playground[i][j]);
            }
        }

    }

    if (masterplate) {
        root["masterplate"] = toJson(*masterplate);
    }

    std::ofstream file(name);
    if (!file.is_open()) {
        std::cerr << "Could not open file for saving: " << name << std::endl;
        return;
    }
    file << root.toStyledString();
}

void state::Board::load(std::string path) {
    // Implementation for loading the board from a file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file for loading: " << path << std::endl;
        return;
    }
    Json::Value LoadedBoard;
    Json::CharReaderBuilder reader;
    std::string errors;
    if (!Json::parseFromStream(reader, file, &LoadedBoard, &errors)) {
        std::cerr << "Error parsing JSON from file: " << errors << std::endl;
        return;
    }
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 7; ++j) {
            if (LoadedBoard["playground"][i][j].isObject()) {
                playground[i][j] = fromJson(LoadedBoard["playground"][i][j]);
            }
            else {
                playground[i][j] = nullptr;
            }
        }
    }
    if(LoadedBoard["masterplate"].isObject()) {
            masterplate = fromJson(LoadedBoard["masterplate"]);
    } else {
        masterplate = nullptr;
    }
}

void state::Board::shuffle() {
    int num_I = 13;
    int num_T = 6;
    int num_L = 15;
    std::vector<int> available; //indicates which type of plates can be placed.

    //Alea
    std::random_device randomDevice; // seed
    std::mt19937 generator(randomDevice()); //Mersenne Twister

    int choice = 0;
    int rotation = 0;

    // Corners
    playground.at(0).at(0) = std::make_unique<state::L>();
    playground.at(0).at(0)->turnPlate();

    playground.at(0).at(6) = std::make_unique<state::L>();
    playground.at(0).at(6)->turnPlate();
    playground.at(0).at(6)->turnPlate();

    playground.at(6).at(0) = std::make_unique<state::L>();

    playground.at(6).at(6) = std::make_unique<state::L>();
    for (int k = 0; k < 3; ++k) {
        playground.at(6).at(6)->turnPlate();
    }
    // Top, bottom edges
    for (auto j : { 2, 4}) {
        playground.at(0).at(j) = std::make_unique<state::T>();
        playground.at(6).at(j) = std::make_unique<state::T>();
        for(int k = 0; k < 2; ++k) {
            playground.at(6).at(j)->turnPlate();
        }
    }

    // Left and right edges
    for (auto i : {2, 4}) {
        playground.at(i).at(0) = std::make_unique<state::T>();
        for(int k = 0; k < 3; ++k) {
            playground.at(i).at(0)->turnPlate();
        }
        playground.at(i).at(6) = std::make_unique<state::T>();
        playground.at(i).at(6)->turnPlate();
    }

    //Center
    playground.at(2).at(4) = std::make_unique<state::T>();
    playground.at(4).at(4) = std::make_unique<state::T>();
    playground.at(4).at(4)->turnPlate();
    playground.at(4).at(2) = std::make_unique<state::T>();
    for(int k = 0; k < 2; ++k) {
        playground.at(4).at(2)->turnPlate();
    }
    playground.at(2).at(2) = std::make_unique<state::T>();
    for(int k = 0; k < 3; ++k) {
        playground.at(2).at(2)->turnPlate();
    }


    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 7; ++j) {
            if (!playground.at(i).at(j)) {
                std::uniform_int_distribution<int> rotationDistribution(0, 3); // uniform distribution for rotation
                rotation = rotationDistribution(generator);
                available.clear();
                if (num_I > 0) {available.push_back(0);}
                if (num_T > 0) {available.push_back(1);}
                if (num_L > 0) {available.push_back(2);}
                std::uniform_int_distribution<int> distribution(0, available.size()-1); // uniform distribution over available indices
                choice = available[distribution(generator)];
                switch (choice) {
                    case 0:
                        playground.at(i).at(j) = std::make_unique<state::I>();
                        for(int k = 0; k < rotation; ++k) {
                            playground.at(i).at(j)->turnPlate();
                        }
                        num_I--;
                        break;
                    case 1:
                        playground.at(i).at(j) = std::make_unique<state::T>();
                        for(int k = 0; k < rotation; ++k) {
                            playground.at(i).at(j)->turnPlate();
                        }
                        num_T--;
                        break;
                    case 2:
                        playground.at(i).at(j) = std::make_unique<state::L>();
                        for(int k = 0; k < rotation; ++k) {
                            playground.at(i).at(j)->turnPlate();
                        }
                        num_L--;
                        break;
                }
            }
        }
    }
    //It supposed to be one plate left.
    if (num_I > 0) {
            masterplate = std::make_unique<state::I>();
    } else if (num_T > 0) {
            masterplate = std::make_unique<state::T>();
    } else if (num_L > 0) {
            masterplate = std::make_unique<state::L>();
    }

    std::vector<std::array<int, 2>> treasurePositions;

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            playground.at(i).at(j)->setTreasure(Treasure::NONE);

            const bool isCorner =
                (i == 0 || i == 6) && (j == 0 || j == 6);

            if (!isCorner) {
                treasurePositions.push_back({i, j});
            }
        }
    }

    masterplate->setTreasure(Treasure::NONE);

    // Place each treasure exactly once
    std::shuffle(
        treasurePositions.begin(),
        treasurePositions.end(),
        generator
    );

    for (int id = 1; id <= static_cast<int>(Treasure::GEM); ++id) {
        const auto& position = treasurePositions[id - 1];

        playground.at(position[0]).at(position[1])->setTreasure(
            static_cast<Treasure>(id)
        );
    }

}


std::array<std::array<std::unique_ptr<state::Plate>, 7>, 7> &state::Board::getPlayground() {
    return playground;
}

state::Plate state::Board::getMasterplate() {
    return *masterplate;
}
