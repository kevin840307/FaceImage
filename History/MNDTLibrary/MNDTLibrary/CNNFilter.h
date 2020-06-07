#pragma once
#ifndef CNNFILTER_H
#define CNNFILTER_H

#include "MNDTLibrary.h"

enum FilterType
{
	Filter3X3_1
};

struct FilterMolde
{
	FilterMolde* nextMolde;
	int** _filter;
	int _size;

	FilterMolde(int** filter, const int size)
	{
		_filter = filter;
		_size = size;
		nextMolde = nullptr;
	}
};

class CNNFilter
{
public:
	CNNFilter();
	~CNNFilter();
	void AddFilter(FilterType type);
	const FilterMolde* GetFilters() const;
	const void PrintAll();
	const void Print(const FilterMolde* filter);
private:
	const char* LOG_FILE;
	std::fstream _fwLog;

	int _size;
	FilterMolde* _filterHead;
	FilterMolde* _filterEnd;

	FilterMolde* Create(FilterMolde* filterMolde, const int size);
	bool Delete(FilterMolde** filter);


	void SetFilter3X3_1(int** filter);
};
#endif // !CNNFILTER_H

