#pragma once
#ifndef ADABOOST_H
#define ADABOOST_H
#include "general.h"
#include "StrongClassfier.h"
#include "WeakClassifier.h"

class AdaBoost
{

public:
	AdaBoost();
	AdaBoost(AdaBoostType::C_DATAS& data, AdaBoostType::C_LABELS label) :_data(data), _label(label) { Init(); };
	~AdaBoost();

	void Train(C_UINT32 weakSize);

	void Save(const std::string path);

	void Read(const std::string path);

	UINT32 DimensionSize() const;

	AdaBoostType::LABELS Predict(AdaBoostType::C_DATAS& data) const;
	AdaBoostType::LABEL Predict(AdaBoostType::C_DATA& data) const;
private:

	void Init();
	void ProcessError(WeakClassifier& weakClassifier, AdaBoostType::LABELS& pridect);
	double CalcError(AdaBoostType::C_LABELS& pridect);
	void UpdateWeights(const WeakClassifier& weakClassifier, AdaBoostType::C_LABELS& pridect);

	AdaBoostType::C_DATAS _data;
	AdaBoostType::C_LABELS _label;

	StrongClassfier* _strongClassfier = nullptr;
	std::vector<double>* _dataWeights = nullptr;
	UINT32 _dimensionSize = 0;
	UINT32 _dataSize = 0;

};

#endif // !ADABOOST_H
