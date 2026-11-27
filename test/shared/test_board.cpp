#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Board.h"
#include <memory>
#include "../../src/shared/state/L.h"

using namespace state;

BOOST_AUTO_TEST_CASE(Test_Board_Initializes_All_Tiles)
{
    Board board;
    const auto& playground = board.getPlayground();

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            BOOST_CHECK_MESSAGE(
                playground[i][j] != nullptr,
                "Tuile manquante en (" << i << ", " << j << ")"
            );
        }
    }
}

BOOST_AUTO_TEST_CASE(Test_Board_Insertion_Positions)
{
    Board board;

    for (int i = 1; i <= 5; i += 2) {
        BOOST_CHECK(board.insertPlate(0, i));  // Bord du haut
        BOOST_CHECK(board.insertPlate(i, 0));  // Bord de gauche
        BOOST_CHECK(board.insertPlate(6, i));  // Bord du bas
        BOOST_CHECK(board.insertPlate(i, 6));  // Bord de droite
    }

    BOOST_CHECK(!board.insertPlate(0, 0));   // Coin
    BOOST_CHECK(!board.insertPlate(0, 2));   // Indice pair sur le bord du haut
    BOOST_CHECK(!board.insertPlate(3, 3));   // Centre du plateau
    BOOST_CHECK(!board.insertPlate(-1, 3));  // Ligne hors de la grille
    BOOST_CHECK(!board.insertPlate(3, 7));   // Colonne hors de la grille
}

BOOST_AUTO_TEST_CASE(Test_Board_Insert_From_Top)
{
    Board board;
    auto& plateau = board.getPlayground();

    plateau[0][1]->setTreasure(Treasure::DRAGON);  // En haut de la colonne
    plateau[1][1]->setTreasure(Treasure::NONE);    // Juste en dessous
    plateau[6][1]->setTreasure(Treasure::GHOST);   // En bas de la colonne

    BOOST_CHECK(board.insertPlate(0, 1));

    BOOST_CHECK(board.hasTreasureAt(1, 1, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(0, 1, Treasure::DRAGON));
    BOOST_CHECK(board.getMasterplate().hasTreasure(Treasure::GHOST));
}

BOOST_AUTO_TEST_CASE(Test_Board_Insert_From_Bottom)
{
    Board board;
    auto& plateau = board.getPlayground();

    plateau[6][3]->setTreasure(Treasure::DRAGON);
    plateau[5][3]->setTreasure(Treasure::NONE);
    plateau[0][3]->setTreasure(Treasure::GHOST);

    BOOST_CHECK(board.insertPlate(6, 3));

    BOOST_CHECK(board.hasTreasureAt(5, 3, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(6, 3, Treasure::DRAGON));
    BOOST_CHECK(board.getMasterplate().hasTreasure(Treasure::GHOST));
}

BOOST_AUTO_TEST_CASE(Test_Board_Insert_From_Left)
{
    Board board;
    auto& plateau = board.getPlayground();

    plateau[3][0]->setTreasure(Treasure::DRAGON);
    plateau[3][1]->setTreasure(Treasure::NONE);
    plateau[3][6]->setTreasure(Treasure::GHOST);

    BOOST_CHECK(board.insertPlate(3, 0));

    BOOST_CHECK(board.hasTreasureAt(3, 1, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(3, 0, Treasure::DRAGON));
    BOOST_CHECK(board.getMasterplate().hasTreasure(Treasure::GHOST));
}

BOOST_AUTO_TEST_CASE(Test_Board_Insert_From_Right)
{
    Board board;
    auto& plateau = board.getPlayground();

    plateau[3][6]->setTreasure(Treasure::DRAGON);
    plateau[3][5]->setTreasure(Treasure::NONE);
    plateau[3][0]->setTreasure(Treasure::GHOST);

    BOOST_CHECK(board.insertPlate(3, 6));

    BOOST_CHECK(board.hasTreasureAt(3, 5, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(3, 6, Treasure::DRAGON));
    BOOST_CHECK(board.getMasterplate().hasTreasure(Treasure::GHOST));
}

BOOST_AUTO_TEST_CASE(Test_Board_Turn_MasterPlate)
{
    Board board;
    auto& plateau = board.getPlayground();

    // L'insertion par le haut éjecte la tuile L placée en bas.
    plateau[6][1] = std::make_unique<L>();
    BOOST_REQUIRE(board.insertPlate(0, 1));

    board.turnMasterPlate();
    const Plate tuileLibre = board.getMasterplate();

    BOOST_CHECK(!tuileLibre.getNorth());
    BOOST_CHECK(tuileLibre.getEast());
    BOOST_CHECK(tuileLibre.getSouth());
    BOOST_CHECK(!tuileLibre.getWest());
}

BOOST_AUTO_TEST_CASE(Test_Board_SearchPath_Invalid_Start)
{
    Board board;

    BOOST_CHECK(board.searchPath(-1, 3).empty());
    BOOST_CHECK(board.searchPath(7, 3).empty());
    BOOST_CHECK(board.searchPath(3, -1).empty());
    BOOST_CHECK(board.searchPath(3, 7).empty());

    BOOST_CHECK(!board.searchPath(6, 6).empty());

    board.getPlayground()[6][6].reset();
    BOOST_CHECK(board.searchPath(6, 6).empty());
}

BOOST_AUTO_TEST_CASE(Test_Board_HasTreasureAt)
{
    Board board;
    auto& plateau = board.getPlayground();

    plateau[2][3]->setTreasure(Treasure::DRAGON);
    BOOST_CHECK(board.hasTreasureAt(2, 3, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(2, 3, Treasure::GHOST));

    plateau[2][3]->setTreasure(Treasure::NONE);
    BOOST_CHECK(!board.hasTreasureAt(2, 3, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(2, 3, Treasure::NONE));

    plateau[2][3].reset();
    BOOST_CHECK(!board.hasTreasureAt(2, 3, Treasure::DRAGON));

    BOOST_CHECK(!board.hasTreasureAt(-1, 3, Treasure::DRAGON));
    BOOST_CHECK(!board.hasTreasureAt(2, 7, Treasure::DRAGON));
}

BOOST_AUTO_TEST_CASE(Test_Board_Each_Treasure_Appears_Once)
{
    Board board;

    for (int id = static_cast<int>(Treasure::DRAGON);
         id <= static_cast<int>(Treasure::GEM); ++id) {
        const Treasure tresor = static_cast<Treasure>(id);
        int occurrences = 0;

        for (int ligne = 0; ligne < 7; ++ligne) {
            for (int colonne = 0; colonne < 7; ++colonne) {
                if (board.hasTreasureAt(ligne, colonne, tresor)) {
                    ++occurrences;
                }
            }
        }

        BOOST_CHECK_MESSAGE(occurrences == 1,
            "Le tresor " << id << " apparait " << occurrences << " fois");
    }
}

