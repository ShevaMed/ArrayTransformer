#include <iostream>
#include <vector>
#include <cassert>
#include "ArrayUtils.h"

void runTests();
void testReadArraysFromFile();
void testSortArrays();
void testIntersectionArrays();
void testSymmetricalDifferenceArrays();

int main()
{
    runTests();

    // You can use vector, deque and list both internally and externally
    std::vector<std::vector<int>> arrays;
    std::string filePath = "arrays.txt";

    if (!readArraysFromFile(filePath, arrays)) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    if (arrays.size() < 3) {
        std::cerr << "Error: Need at least 3 arrays in the input file." << std::endl;
        return 1;
    }

    char ch;
    do {
        std::cout << "\n1. Print arrays\n";
        std::cout << "2. Sorting arrays by Selection method (Default)\n";
        std::cout << "3. Sorting arrays by Selection method (Reverse)\n";
        std::cout << "4. Sorting arrays by Quick sort (Default)\n";
        std::cout << "5. Sorting arrays by Quick sort (Reverse)\n";
        std::cout << "6. Print intersection of arrays (Two with the longest length)\n";
        std::cout << "7. Print intersection of arrays (All arrays)\n";
        std::cout << "8. Print symmetrical difference of arrays (Reverse sorting)\n";
        std::cout << "9. Exit\n";
        std::cout << "\nSelect menu item: "; std::cin >> ch;
        system("cls");

        switch (ch) {
        case '1': printArrays(arrays); break;
        case '2': sortArrays(arrays, "DefaultSelection"); break;
        case '3': sortArrays(arrays, "ReverseSelection"); break;
        case '4': sortArrays(arrays, "DefaultQuick"); break;
        case '5': sortArrays(arrays, "ReverseQuick"); break;
        case '6': printArray(intersectionArrays(arrays, "TwoLongest")); break;
        case '7': printArray(intersectionArrays(arrays, "All")); break;
        case '8': printArray(symmetricalDifferenceArrays(arrays)); break;
        case '9': break;
        default: std::cout << "Select the correct menu item!\n" << std::endl; break;
        }
    } while (ch != '9');

    return 0;
}

void runTests()
{
    testReadArraysFromFile();
    testSortArrays();
    testIntersectionArrays();
    testSymmetricalDifferenceArrays();
    std::cout << "All tests passed!" << std::endl;
}

void testReadArraysFromFile()
{
    // Arrange
    std::string testFilePath = "test_input.txt";
    std::ofstream testFile(testFilePath);
    testFile << "11 5, 3,,1 ,6  7  \n";
    testFile << "3  1 ,25, 7,,5, \n";
    testFile << "1, 0  7 ,2 ";
    testFile.close();

    std::vector<std::vector<int>> arrays{};
    std::vector<std::vector<int>> expectedArrays{
        { 11, 5, 3, 1, 6, 7 },
        { 3, 1, 25, 7, 5 },
        { 1, 0, 7, 2 } };

    // Act
    readArraysFromFile(testFilePath, arrays);

    // Assert
    assert(arrays == expectedArrays);
    std::cout << "Read arrays from file test passed!\n";
}

void testSortArrays()
{
    // Arrange
    std::vector<std::vector<int>> arrays{
        { 11, 5, 3, 1, 6, 7 },
        { 3, 1, 25, 7, 5 },
        { 1, 0, 7, 2 } };

    std::vector<std::vector<int>> expectedDefaultArrays{
        { 1, 3, 5, 6, 7, 11 },
        { 1, 3, 5, 7, 25 },
        { 0, 1, 2, 7 } };

    std::vector<std::vector<int>> expectedReverseArrays{
        { 11, 7, 6, 5, 3, 1 },
        { 25, 7, 5, 3, 1 },
        { 7, 2, 1, 0 } };

    // Act
    sortArrays(arrays, "DefaultSelection");
    auto resultDefaultSelection = arrays;
    sortArrays(arrays, "ReverseSelection");
    auto resultReverseSelection = arrays;
    sortArrays(arrays, "DefaultQuick");
    auto resultDefaultQuick = arrays;
    sortArrays(arrays, "ReverseQuick");
    auto resultReverseQuick = arrays;

    // Assert
    assert(resultDefaultSelection == expectedDefaultArrays);
    assert(resultReverseSelection == expectedReverseArrays);
    assert(resultDefaultQuick == expectedDefaultArrays);
    assert(resultReverseQuick == expectedReverseArrays);
    std::cout << "Sort arrays test passed!\n";
}

void testIntersectionArrays()
{
    // Arrange
    std::vector<std::vector<int>> arrays{
        { 11, 5, 3, 1, 6, 7 },
        { 3, 1, 25, 7, 5 },
        { 1, 0, 7, 2 } };

    std::vector<int> expectedTwoLongestIntersection{ 3, 1, 7, 5 };
    std::vector<int> expectedAllIntersection{ 1, 7 };

    // Act
    auto resultTwoLongestIntersection = intersectionArrays(arrays, "TwoLongest");
    auto resultAllIntersection = intersectionArrays(arrays, "All");

    // Assert
    assert(resultTwoLongestIntersection == expectedTwoLongestIntersection);
    assert(resultAllIntersection == expectedAllIntersection);
    std::cout << "Intersection arrays test passed!\n";
}

void testSymmetricalDifferenceArrays()
{
    // Arrange
    std::vector<std::vector<int>> arrays{
        { 11, 5, 3, 1, 6, 7 },
        { 3, 1, 25, 7, 5 },
        { 1, 0, 7, 2 } };

    std::vector<int> expectedSymmetricalDifference{ 25, 11, 6, 2, 0 };

    // Act
    auto resultSymmetricalDifference = symmetricalDifferenceArrays(arrays);

    // Assert
    assert(resultSymmetricalDifference == expectedSymmetricalDifference);
    std::cout << "Symmetrical difference arrays test passed!\n";
}
