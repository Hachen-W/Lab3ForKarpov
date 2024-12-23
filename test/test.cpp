#define CATCH_CONFIG_MAIN
#include "../lib/Catch2/src/catch2/catch_test_macros.hpp"
#include "../lib/matrix/matrix.hpp"
#include "../lib/table/table.hpp"
#include "../lib/landscape/landscape.hpp"
#include "../lib/entity/castle.hpp"


TEST_CASE("Class Matrix") {
    Matrix<int> matrix;
    size_t count_strings;
    size_t count_columns;
    SECTION("Check Resize and []") {
        matrix.resize(5, 7);
        count_strings = matrix.getStringsCount();
        count_columns = matrix.getColumnsCount();
        REQUIRE(count_strings == 5);
        REQUIRE(count_columns == 7);
        for (int i = 0; i < count_strings; i++)
            for (int j = 0; j < count_columns; j++)
                REQUIRE(matrix[i][j] == 0);
        REQUIRE(count_strings == 5);
        for (int i = 0; i < count_strings; i++) {
            int index = count_columns - i - 1 > 0 ? count_columns - i - 1 : 0;
            matrix[i][index] = 9;
            REQUIRE(matrix[i][index] == 9);
        }
    }
}

TEST_CASE("Class Table") {
    Table<unsigned int, char> table;
    TableCeil<unsigned int, char> tableCeil;
    for (unsigned int index = 0; index < 4; index++) {
        tableCeil.key = 5 + index;
        tableCeil.value = 'a' + index;
        table.push(tableCeil);
        REQUIRE(table.getElement(5 + index) == 'a' + index);
    }
    REQUIRE_THROWS(table.getElement(9));
    table.removeElement(5);
    REQUIRE_THROWS(table.getElement(5));
    for (unsigned int index = 1; index < 4; index++)
        REQUIRE(table.getElement(5 + index) == 'a' + index);
}

TEST_CASE("Class Landscape") {
    unsigned int countStrings = 5, countColumns = 7;

    Landscape landscape;
    SECTION("Testing Playground") {
        landscape.getPlayground().resize(countStrings, countColumns);
        for (unsigned int i = 0; i < countStrings; i++) {
            for (unsigned int j = 0; j < countColumns; j++) {
                REQUIRE(landscape.getPlayground()[i][j] == 0);
            }
        }
        for (unsigned int i = 0; i < countStrings; i++) {
            for (unsigned int j = 0; j < countColumns; j++) {
                LandscapeType temp = LandscapeType(rand() % 2);
                landscape.getPlayground()[i][j] = temp;
                REQUIRE(landscape.getPlayground()[i][j] == temp);
            }
        }
    }
    SECTION("Testing Table") {
        unsigned int countCastles = 5;
        double HEALTH_BY_DEFAULT = 7.5;
        unsigned int GOLD_BY_DEFAULT = 70;
        Castle* castle;
        Entity* entity;

        TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil;
        for (unsigned int i = 0; i < countCastles; i++) {
            castle = new Castle{HEALTH_BY_DEFAULT, GOLD_BY_DEFAULT, CastleType};
            tableCeil.key = {7,i};
            tableCeil.value = castle;
            landscape.getTable().push(tableCeil);
        }
        for (unsigned int i = 0; i < countCastles; i++) {
            castle = static_cast<Castle*>(landscape.getTable().getElement({7,i}));
            REQUIRE(castle->getHealth() == HEALTH_BY_DEFAULT);
            REQUIRE(castle->getGold() == GOLD_BY_DEFAULT);
        }
    }
}