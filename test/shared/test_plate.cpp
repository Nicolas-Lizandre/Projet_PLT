#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Plate.h"
#include "../../src/shared/state/L.h"
#include "../../src/shared/state/T.h"
#include "../../src/shared/state/I.h"
#include "../../src/shared/state/Board.h"

using namespace state;

BOOST_AUTO_TEST_CASE(Getter_Plate)
{
    L plate;
    BOOST_CHECK(plate.getNorth());
    BOOST_CHECK(plate.getEast());
    BOOST_CHECK(!plate.getSouth());
    BOOST_CHECK(!plate.getWest());

    T plate2;
    BOOST_CHECK(!plate2.getNorth());
    BOOST_CHECK(plate2.getEast());
    BOOST_CHECK(plate2.getSouth());
    BOOST_CHECK(plate2.getWest());
    
    I plate3;
    BOOST_CHECK(plate3.getNorth());
    BOOST_CHECK(!plate3.getEast());
    BOOST_CHECK(plate3.getSouth());
    BOOST_CHECK(!plate3.getWest()); 
}

BOOST_AUTO_TEST_CASE(TestFourTurnsIsIdentity)
{
  T plate;
 
  for (int k = 0; k < 4; ++k) {
    plate.turnPlate();
  }
  BOOST_CHECK(!plate.getNorth() && plate.getEast() &&
              plate.getSouth() && plate.getWest());
  L plate2;
  for (int k = 0; k < 4; ++k) {
    plate2.turnPlate();
  }
  BOOST_CHECK(plate2.getNorth() && plate2.getEast() &&
              !plate2.getSouth() && !plate2.getWest());

  I plate3;
  for (int k = 0; k < 4; ++k) {
    plate3.turnPlate();
  }
  BOOST_CHECK(plate3.getNorth() && !plate3.getEast() &&
              plate3.getSouth() && !plate3.getWest());
  
}

BOOST_AUTO_TEST_CASE(Test_TurnPlate)
{
  L plate_L;
  plate_L.turnPlate();
  BOOST_CHECK(!plate_L.getNorth() && plate_L.getEast() &&
              plate_L.getSouth() && !plate_L.getWest());
  plate_L.turnPlate();
  BOOST_CHECK(!plate_L.getNorth() && !plate_L.getEast() &&
              plate_L.getSouth() && plate_L.getWest());
  plate_L.turnPlate();
  BOOST_CHECK(plate_L.getNorth() && !plate_L.getEast() &&
              !plate_L.getSouth() && plate_L.getWest());
  T plate_T;
  plate_T.turnPlate();
  BOOST_CHECK(plate_T.getNorth() && !plate_T.getEast() &&
              plate_T.getSouth() && plate_T.getWest());
  plate_T.turnPlate();
  BOOST_CHECK(plate_T.getNorth() && plate_T.getEast() &&
              !plate_T.getSouth() && plate_T.getWest());
  plate_T.turnPlate();
  BOOST_CHECK(plate_T.getNorth() && plate_T.getEast() &&
              plate_T.getSouth() && !plate_T.getWest());
  
  I plate_I;
  plate_I.turnPlate();
  BOOST_CHECK(!plate_I.getNorth() && plate_I.getEast() &&
              !plate_I.getSouth() && plate_I.getWest());
  plate_I.turnPlate();
  BOOST_CHECK(plate_I.getNorth() && !plate_I.getEast() &&
              plate_I.getSouth() && !plate_I.getWest());
  plate_I.turnPlate();
  BOOST_CHECK(!plate_I.getNorth() && plate_I.getEast() &&
              !plate_I.getSouth() && plate_I.getWest());
  
}

BOOST_AUTO_TEST_CASE(Test_showPlate)
{
  std::ostringstream saved; //file in memory where we stock the result of showPlate
  std::streambuf* previous = std::cout.rdbuf(saved.rdbuf()); //Redirect cout into 'saved'

  /*L and its four rotations*/
  Plate L(true, true, false, false);
  L.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "└");

  Plate L_turned_right(false, true, true, false);
  saved.str(""); //Clears the previous output
  L_turned_right.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┌");
  
  Plate L_reversed(false, false, true, true);
  saved.str("");
  L_reversed.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┐");

  Plate L_turned_left(true, false, false, true);
  saved.str("");
  L_turned_left.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┘");
  

  /*I and its four rotations*/
  Plate I(true, false, true, false);
  saved.str("");
  I.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "|");

  Plate I_turned_right(false, true, false, true);
  saved.str("");
  I_turned_right.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "─");

  Plate I_reversed(true, false, true, false);
  saved.str("");
  I_turned_right.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "|");

  Plate I_turned_left(false, true, false, true);
  saved.str("");
  I_turned_left.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "─");

  /*T and its four rotations*/
  Plate T(false, true, true, true);
  saved.str("");
  T.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┬");

  Plate T_turned_right(true, false, true, true);
  saved.str("");
  T_turned_right.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┤");

  Plate T_reversed(true, true, false, true);
  saved.str("");
  T_reversed.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "┴");

  Plate T_turned_left(true, true, true, false);
  saved.str("");
  I_turned_left.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), "├");
  
  /*Illegal Plate*/
  Plate Undefined(false, false, false, false);
  saved.str("");
  Undefined.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  Plate Undefined_2(true, false, false, false);
  saved.str("");
  Undefined_2.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  Plate Undefined_3(false, true, false, false);
  saved.str("");
  Undefined_3.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  Plate Undefined_4(false, false, true, false);
  saved.str("");
  Undefined_4.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  Plate Undefined_5(false, false, false, true);
  saved.str("");
  Undefined_5.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  Plate Undefined_6(true, true, true, true);
  saved.str("");
  Undefined_6.showPlate();
  BOOST_CHECK_EQUAL(saved.str(), " ");

  std::cout.rdbuf(previous); //Cout back to normal
}

BOOST_AUTO_TEST_CASE(Test_getPlateSymbolFromAcesses)
{
  std::string test = "";
  /*L and its four rotations*/
  Plate L(true, true, false, false);
  test = L.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "└");

  Plate L_turned_right(false, true, true, false);
  test = L_turned_right.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┌");
  
  Plate L_reversed(false, false, true, true);
  test = L_reversed.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┐");

  Plate L_turned_left(true, false, false, true);
  test = L_turned_left.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┘");
  

  /*I and its four rotations*/
  Plate I(true, false, true, false);
  test = I.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "|");

  Plate I_turned_right(false, true, false, true);
  test = I_turned_right.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "─");

  Plate I_reversed(true, false, true, false);
  test = I_turned_right.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "|");

  Plate I_turned_left(false, true, false, true);
  test = I_turned_left.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "─");

  /*T and its four rotations*/
  Plate T(false, true, true, true);
  test = T.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┬");

  Plate T_turned_right(true, false, true, true);
  test = T_turned_right.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┤");

  Plate T_reversed(true, true, false, true);
  test = T_reversed.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "┴");

  Plate T_turned_left(true, true, true, false);
  test = I_turned_left.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, "├");
  
  /*Illegal Plate*/
  Plate Undefined(false, false, false, false);
  test = Undefined.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");

  Plate Undefined_2(true, false, false, false);
  test = Undefined_2.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");

  Plate Undefined_3(false, true, false, false);
  test = Undefined_3.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");

  Plate Undefined_4(false, false, true, false);
  test = Undefined_4.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");

  Plate Undefined_5(false, false, false, true);
  test = Undefined_5.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");

  Plate Undefined_6(true, true, true, true);
  test = Undefined_6.getPlateSymbolFromAcesses();
  BOOST_CHECK_EQUAL(test, " ");
}