#include "CNNFilter.h"

CNNFilter::CNNFilter()
{
	LOG_FILE = "D:\\Log.txt";
	_size = 0;
	_filterHead = nullptr;
	_filterEnd = nullptr;
	_fwLog.open(LOG_FILE, std::ios::app);
}

CNNFilter::~CNNFilter()
{
	while (_filterHead != nullptr)
	{
		FilterMolde* nextMolde = _filterHead->nextMolde;
		Delete(&_filterHead);
		_filterHead = nextMolde;
	}
	_fwLog.close();
	assert(_filterHead == nullptr);
}

const FilterMolde* CNNFilter::GetFilters() const
{
	return _filterHead;
}

void CNNFilter::AddFilter(FilterType type)
{
	FilterMolde* filterMolde = nullptr;

	filterMolde = Create(filterMolde, 3);

	switch (type)
	{
	case Filter3X3_1:
		SetFilter3X3_1(filterMolde->_filter);
		break;
	}

	if (_filterHead == nullptr)
	{
		_filterHead = filterMolde;
		_filterEnd = _filterHead;
	}
	else
	{
		_filterEnd->nextMolde = filterMolde;
		_filterEnd = _filterHead->nextMolde;
	}
	_size++;
}

void CNNFilter::SetFilter3X3_1(int** filter)
{
	filter[0][0] = 0; filter[0][1] = 1; filter[0][2] = 0;
	filter[1][0] = 0; filter[1][1] = 1; filter[1][2] = 0;
	filter[2][0] = 0; filter[2][1] = 1; filter[2][2] = 0;
}

FilterMolde* CNNFilter::Create(FilterMolde* filterMolde,const int size)
{
	int** filter = new int*[size];

	for (int index = 0; index < size; index++)
	{
		filter[index] = new int[size];
	}
	filterMolde = new FilterMolde(filter, size);
	return filterMolde;
}

bool CNNFilter::Delete(FilterMolde** filterMolde)
{
	for (int index = 0; index < (*filterMolde)->_size; index++)
	{
		MNDT::DeleteArray(((*filterMolde)->_filter[index]));
	}

	MNDT::DeleteArray((*filterMolde)->_filter);
	MNDT::DeleteArray((*filterMolde));

	return true;
}

const void CNNFilter::Print(const FilterMolde* filter)
{
	for (int row = 0; row < filter->_size; row++)
	{
		for (int col = 0; col < filter->_size; col++)
		{
			_fwLog << filter->_filter[row][col] << " ";
		}
		_fwLog << std::endl;
	}
}

const void  CNNFilter::PrintAll()
{
	FilterMolde* filter = _filterHead;
	while (filter != nullptr)
	{
		Print(filter);
		filter = filter->nextMolde;
	}
}