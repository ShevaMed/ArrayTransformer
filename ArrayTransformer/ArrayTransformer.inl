template<typename Container>
inline ArrayTransformer<Container>::~ArrayTransformer()
{
}

template<typename Container>
inline SortTransformer<Container>::
SortTransformer(SortingStrategy strategy) :
	sortingStrategy_(strategy)
{
}

template<typename Container>
inline void SortTransformer<Container>::transform(Container& array)
{
	switch (sortingStrategy_) {
	case SortingStrategy::DefaultSelection:
		selectionSort(array.begin(), array.end()); break;
	case SortingStrategy::ReverseSelection:
		selectionSort(array.rbegin(), array.rend()); break;
	case SortingStrategy::DefaultQuick:
		quickSort(array.begin(), array.end()); break;
	case SortingStrategy::ReverseQuick:
		quickSort(array.rbegin(), array.rend()); break;
	}
}

template<typename ArrayOfContainers>
inline void IntersectionTransformer<ArrayOfContainers>::twoLongestIntersection(Container& array)
{
	array.clear();
	Container longestContainer1{}, longestContainer2{};

	for (const auto& container : arrayOfContainer_) {
		if (container.size() > longestContainer1.size()) {
			longestContainer2 = longestContainer1;
			longestContainer1 = container;
		}
		else if (container.size() > longestContainer2.size()) {
			longestContainer2 = container;
		}
	}

	using Value = typename Container::value_type;
	std::unordered_set<Value> set1(longestContainer1.begin(), longestContainer1.end());
	std::unordered_set<Value> set2(longestContainer2.begin(), longestContainer2.end());

	for (const auto& value : set2) {
		if (set1.count(value) && set2.count(value)) {
			array.insert(array.end(), value);
		}
	}
}

template<typename ArrayOfContainers>
inline void IntersectionTransformer<ArrayOfContainers>::allIntersection(Container& array)
{
	array.clear();
	using Value = typename Container::value_type;

	std::unordered_set<Value> intersection(arrayOfContainer_.front().begin(),
		arrayOfContainer_.front().end());

	for (const auto& container : arrayOfContainer_) {
		std::unordered_set<Value> tempSet(container.begin(), container.end());
		std::unordered_set<Value> tempIntersection{};

		for (const auto& value : tempSet) {
			if (intersection.count(value)) {
				tempIntersection.insert(value);
			}
		}
		intersection = std::move(tempIntersection);
	}
	array.insert(array.end(), intersection.begin(), intersection.end());
}

template<typename ArrayOfContainers>
inline IntersectionTransformer<ArrayOfContainers>::
IntersectionTransformer(const ArrayOfContainers& arrayOfContainer, IntersectionStrategy strategy) :
	arrayOfContainer_(arrayOfContainer),
	intersectionStrategy_(strategy)
{
}

template<typename ArrayOfContainers>
inline void IntersectionTransformer<ArrayOfContainers>::transform(Container& array)
{
	switch (intersectionStrategy_) {
	case IntersectionStrategy::TwoLongest:
		twoLongestIntersection(array); break;
	case IntersectionStrategy::All:
		allIntersection(array); break;
	}
}

template<typename ArrayOfContainers>
inline SymmetricalDifferenceTransformer<ArrayOfContainers>::
SymmetricalDifferenceTransformer(const ArrayOfContainers& arrayOfContainer) :
	arrayOfContainer_(arrayOfContainer)
{
}

template<typename ArrayOfContainers>
inline void SymmetricalDifferenceTransformer<ArrayOfContainers>::transform(Container& array)
{
	array.clear();
	using Value = typename Container::value_type;

	std::multiset<Value> concatenatedSet{};

	for (const auto& container : arrayOfContainer_) {
		for (const auto& value : container) {
			concatenatedSet.insert(value);
		}
	}

	for (const auto& value : concatenatedSet) {
		if (concatenatedSet.count(value) == 1) {
			array.insert(array.end(), value);
		}
	}
}

template<typename Container>
template<typename Iterator>
inline void SortTransformer<Container>::selectionSort(Iterator begin, Iterator end)
{
	for (auto i = begin; i != std::prev(end); ++i) {
		auto minIt = i;
		for (auto j = std::next(i); j != end; ++j) {
			if (*j < *minIt)
				minIt = j;
		}
		std::swap(*i, *minIt);
	}
}

template<typename Container>
template<typename Iterator>
inline void SortTransformer<Container>::quickSort(Iterator begin, Iterator end)
{
	if (std::distance(begin, end) <= 1) {
		return;
	}

	auto pivot = *begin;
	Iterator left = begin;
	Iterator right = std::prev(end);

	while (left != right) {
		while (*right >= pivot && left != right) {
			--right;
		}
		while (*left <= pivot && left != right) {
			++left;
		}
		if (left != right) {
			std::swap(*left, *right);
		}
	}
	std::swap(*begin, *left);

	quickSort(begin, left);
	quickSort(std::next(left), end);
}