#pragma once

#include <unordered_set>
#include <set>

template <typename Container>
class ArrayTransformer
{
public:
	virtual ~ArrayTransformer();
	virtual void transform(Container& array) = 0;
};

template <typename Container>
class SortTransformer : public ArrayTransformer<Container> 
{
public:
	enum class SortingStrategy {
		DefaultSelection,
		ReverseSelection,
		DefaultQuick,
		ReverseQuick
	};

private:
	template<typename Iterator>
	void selectionSort(Iterator begin, Iterator end);
	template<typename Iterator>
	void quickSort(Iterator begin, Iterator end);

public:
	SortTransformer(SortingStrategy strategy);

	void transform(Container& array) override;

private:
	SortingStrategy sortingStrategy_;
};

template <typename ArrayOfContainers>
class IntersectionTransformer : public ArrayTransformer<typename ArrayOfContainers::value_type>
{
public:
	using Container = typename ArrayOfContainers::value_type;

	enum class IntersectionStrategy {
		TwoLongest,
		All
	};

private:
	void twoLongestIntersection(Container& array);
	void allIntersection(Container& array);

public:
	IntersectionTransformer(const ArrayOfContainers& arrayOfContainer, IntersectionStrategy strategy);

	void transform(Container& array) override;

private:
	const ArrayOfContainers& arrayOfContainer_;
	IntersectionStrategy intersectionStrategy_;
};

template <typename ArrayOfContainers>
class SymmetricalDifferenceTransformer : public ArrayTransformer<typename ArrayOfContainers::value_type>
{
public:
	using Container = typename ArrayOfContainers::value_type;

	SymmetricalDifferenceTransformer(const ArrayOfContainers& arrayOfContainer);

	void transform(Container& array) override;

private:
	const ArrayOfContainers& arrayOfContainer_;
};

#include "ArrayTransformer.inl"
