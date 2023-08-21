#pragma once

#include <fstream>
#include <sstream>
#include <memory>
#include "ArrayTransformer.h"

template <typename ArrayOfContainers>
bool readArraysFromFile(const std::string& filePath, ArrayOfContainers& arrays);

template <typename Container>
void printArray(const Container& array);

template <typename ArrayOfContainers>
void printArrays(const ArrayOfContainers& arrays);

template <typename Container>
void sortArray(Container& array, const std::string& nameOfSortStrategy);

template <typename ArrayOfContainers>
void sortArrays(ArrayOfContainers& arrays, const std::string& nameOfSortStrategy);

template <typename ArrayOfContainers>
typename ArrayOfContainers::value_type intersectionArrays(const ArrayOfContainers& arrays, 
                                                          const std::string& nameOfIntersectionStrategy);

template <typename ArrayOfContainers>
typename ArrayOfContainers::value_type symmetricalDifferenceArrays(const ArrayOfContainers& arrays);

#include "ArrayUtils.inl"
