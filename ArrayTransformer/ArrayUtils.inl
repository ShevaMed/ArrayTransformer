template<typename ArrayOfContainers>
inline bool readArraysFromFile(const std::string& filePath, ArrayOfContainers& arrays)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        return false;
    }

    using Container = typename ArrayOfContainers::value_type;
    using Value = typename Container::value_type;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        Container array{};
        Value value{};
        while (iss >> value) {
            array.insert(array.end(), value);
            char delimiter = iss.peek();
            while (delimiter == ',' || delimiter == ' ' || delimiter == '\t') {
                iss.ignore();
                delimiter = iss.peek();
            }
        }
        arrays.insert(arrays.end(), array);
    }
    inputFile.close();
    return true;
}

template<typename Container>
inline void printArray(const Container& array)
{
    for (const auto& value : array) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}

template<typename ArrayOfContainers>
inline void printArrays(const ArrayOfContainers& arrays)
{
    for (const auto& array : arrays) {
        printArray(array);
    }
}

template<typename Container>
inline void sortArray(Container& array, const std::string& nameOfSortStrategy)
{
    using Strategy = typename SortTransformer<Container>::SortingStrategy;

    Strategy strategy = Strategy::DefaultSelection;
    if ("DefaultSelection" == nameOfSortStrategy)
        strategy = Strategy::DefaultSelection;
    else if ("ReverseSelection" == nameOfSortStrategy)
        strategy = Strategy::ReverseSelection;
    else if ("DefaultQuick" == nameOfSortStrategy)
        strategy = Strategy::DefaultQuick;
    else if ("ReverseQuick" == nameOfSortStrategy)
        strategy = Strategy::ReverseQuick;

    std::unique_ptr<ArrayTransformer<Container>> sortTransformer(
        new SortTransformer<Container>(strategy));

    sortTransformer->transform(array);
}

template<typename ArrayOfContainers>
inline void sortArrays(ArrayOfContainers& arrays, const std::string& nameOfSortStrategy)
{
    for (auto& array : arrays) {
        sortArray(array, nameOfSortStrategy);
    }
}

template<typename ArrayOfContainers>
inline typename ArrayOfContainers::value_type intersectionArrays(const ArrayOfContainers& arrays,
    const std::string& nameOfIntersectionStrategy)
{
    using Container = typename ArrayOfContainers::value_type;
    using Strategy = typename IntersectionTransformer<ArrayOfContainers>::IntersectionStrategy;

    Strategy strategy = Strategy::TwoLongest;
    if ("TwoLongest" == nameOfIntersectionStrategy)
        strategy = Strategy::TwoLongest;
    else if ("All" == nameOfIntersectionStrategy)
        strategy = Strategy::All;

    std::unique_ptr<ArrayTransformer<Container>> intersectionTransformer(
        new IntersectionTransformer<ArrayOfContainers>(arrays, strategy));

    Container intersectionArray{};
    intersectionTransformer->transform(intersectionArray);
    return intersectionArray;
}

template<typename ArrayOfContainers>
inline typename ArrayOfContainers::value_type symmetricalDifferenceArrays(const ArrayOfContainers& arrays)
{
    using Container = typename ArrayOfContainers::value_type;

    std::unique_ptr<ArrayTransformer<Container>> symmetricalDifferenceTransformer(
        new SymmetricalDifferenceTransformer<ArrayOfContainers>(arrays));

    Container symmetricalDifferenceArray{};
    symmetricalDifferenceTransformer->transform(symmetricalDifferenceArray);
    sortArray(symmetricalDifferenceArray, "ReverseQuick");
    return symmetricalDifferenceArray;
}