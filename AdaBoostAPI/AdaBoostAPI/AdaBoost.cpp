#include "stdafx.h"
#include "AdaBoost.h"

AdaBoost::AdaBoost()
{
	_strongClassfier = new StrongClassfier();
}

AdaBoost::~AdaBoost()
{
	if (_dataWeights != nullptr)
	{
		delete _dataWeights;
		_dataWeights = nullptr;
	}

	if (_strongClassfier != nullptr)
	{
		delete _strongClassfier;
		_strongClassfier = nullptr;
	}
}

void AdaBoost::Init()
{
	assert(_data.size() > 0 && _data[0].size() > 0);

	_dataSize = _data.size();
	_dimensionSize = _data[0].size();
	_dataWeights = new std::vector<double>(_dataSize, 1.0 / _dataSize);
	_strongClassfier = new StrongClassfier();
}


void AdaBoost::Train(C_UINT32 weakSize)
{
	for (UINT32 index = 0; index < weakSize; index++)
	{
		WeakClassifier weakClassifier;
		AdaBoostType::LABELS pridect;

		ProcessError(weakClassifier, pridect);

		UpdateWeights(weakClassifier, pridect);

		_strongClassfier->Add(weakClassifier);
	}
}

void AdaBoost::Save(const std::string path)
{
	std::ofstream ofstream;

	ofstream.open(path, std::ios::out);


	const std::vector<WeakClassifier>* weakClassifiers = _strongClassfier->GetWeakClassifiers();

	ofstream << "DimensionSize¡G " << _dimensionSize << std::endl;

	for (UINT32 index = 0; index < weakClassifiers->size(); index++)
	{
		ofstream << index << std::endl;
		ofstream << "Dimension¡G " << weakClassifiers->at(index).Dimension() << std::endl;
		ofstream << "Threshold¡G " << weakClassifiers->at(index).Threshold() << std::endl;
		ofstream << "Sign¡G " << weakClassifiers->at(index).Sign() << std::endl;
		ofstream << "Error¡G " << weakClassifiers->at(index).Error() << std::endl;
	}

	ofstream.close();
}

void AdaBoost::Read(const std::string path)
{
	std::ifstream ifstream;

	ifstream.open(path, std::ios::in);


	std::string tag = "";
	UINT32 index = 0;

	ifstream >> tag >> _dimensionSize;
	while (ifstream >> index)
	{
		UINT32 dimension = 0;
		double threshold = 0;
		UINT32 sign = 0;
		double error = 0;

		ifstream >> tag >> dimension;
		ifstream >> tag >> threshold;
		ifstream >> tag >> sign;
		ifstream >> tag >> error;

		WeakClassifier weakClassifier(dimension, threshold, (WeakClassifier::SignType)sign, error);
		_strongClassfier->Add(weakClassifier);
	}

	ifstream.close();
}


void AdaBoost::ProcessError(WeakClassifier& minWeakClassifier, AdaBoostType::LABELS& minPridect)
{
	double minError = 100000;

	/*concurrency::parallel_for(0, static_cast<int>(_dimensionSize), [&](const int& dimension) {
		for (UINT32 index = 0; index < _dataSize; index++)
		{
			const WeakClassifier::SignType signs[] = { WeakClassifier::SignType::BIG
				, WeakClassifier::SignType::SMALL };

			for (UINT32 signIndex = 0; signIndex < sizeof(signs) / sizeof(WeakClassifier::SignType); signIndex++)
			{
				WeakClassifier weakClassifier(dimension, _data[index][dimension], signs[signIndex]);
				const std::vector<__int32> pridect = weakClassifier.Predict(_data, dimension);
				C_DOUBLE error = CalcError(pridect);

				if (error < minError)
				{
					minError = error;
					minWeakClassifier = weakClassifier;
					minPridect = pridect;
				}
			}
		}
	});*/

	C_UINT32 errorSize = _dataSize * 2;
	double* errors = new double[errorSize];
	const WeakClassifier::SignType signs[] = { WeakClassifier::SignType::BIG
		, WeakClassifier::SignType::SMALL };

	for (UINT32 dimension = 0; dimension < _dimensionSize; dimension++)
	{
		concurrency::parallel_for(0, static_cast<int>(_dataSize), [&](const int& index)
		{
			for (UINT32 signIndex = 0; signIndex < 2; signIndex++)
			{
				WeakClassifier weakClassifier(dimension, _data[index][dimension], signs[signIndex]);
				const std::vector<__int32> pridect = weakClassifier.Predict(_data, dimension);
				C_DOUBLE error = CalcError(pridect);
				*(errors + (index << 1) + signIndex) = error;
			}
		});

		for (UINT32 errorIndex = 0; errorIndex < errorSize; errorIndex++)
		{
			if (errors[errorIndex] < minError)
			{
				WeakClassifier weakClassifier(dimension, _data[errorIndex >> 1][dimension], signs[(errorIndex & 1)]);
				const std::vector<__int32> pridect = weakClassifier.Predict(_data, dimension);

				minError = errors[errorIndex];
				minWeakClassifier = weakClassifier;
				minPridect = pridect;
			}
		}
	}
	delete[] errors;
	errors = nullptr;

	minWeakClassifier.Error(minError);
}

double AdaBoost::CalcError(AdaBoostType::C_LABELS& pridect)
{
	assert(pridect.size() == _label.size());

	double error = 0.0;

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		if (pridect[index] != _label[index])
		{
			error += _dataWeights->at(index);
		}
	}

	return error;
}

void AdaBoost::UpdateWeights(const WeakClassifier& weakClassifier, AdaBoostType::C_LABELS& pridect)
{
	double sum = 0;

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		_dataWeights->at(index) *= exp(-weakClassifier.Alpha() * pridect[index] * _label[index]);
		sum += _dataWeights->at(index);
	}

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		_dataWeights->at(index) /= sum;
	}

}

AdaBoostType::LABELS AdaBoost::Predict(AdaBoostType::C_DATAS& data) const
{
	return _strongClassfier->Predict(data);
}

AdaBoostType::LABEL AdaBoost::Predict(AdaBoostType::C_DATA& data) const
{
	return _strongClassfier->Predict(data);
}