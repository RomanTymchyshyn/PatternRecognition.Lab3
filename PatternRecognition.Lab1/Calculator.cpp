#include "Calculator.h"

double AverageCalculator::AverageByPatientAndIndicator(const AverageType & typeOfAverage, 
	const int & indicator, const int & patient, IMeasureCalculator* calculator)
{
	int numberOfComparedPatients = 0;

	switch(typeOfAverage)
	{
		case FirstFirst:
			numberOfComparedPatients = _group1.size() - 1;
			break;

		case FirstSecond:
			numberOfComparedPatients = _group2.size();
			break;

		case SecondFirst:
			numberOfComparedPatients = _group1.size();
			break;

		case SecondSecond:
			numberOfComparedPatients = _group2.size() - 1;
			break;
	}

	double sumOfMeasures = 0;
	int comparedToGroupSize = typeOfAverage == FirstFirst || typeOfAverage == SecondFirst ? 
		_group1.size() : _group2.size();

	for (int i = 0; i < comparedToGroupSize; ++i)
	{
		if ((typeOfAverage != FirstFirst && typeOfAverage != SecondSecond) || i != patient)
		{
			sumOfMeasures += Measure(typeOfAverage, indicator, patient, i, calculator);
		}
	}

	return sumOfMeasures / numberOfComparedPatients;
}

std::vector<double> AverageCalculator::AllAverageByPatientAndIndicator(const AverageType & typeOfAverage, 
	const int & indicator, IMeasureCalculator* calculator)
{
	std::vector<double> res;
	int size = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ? 
		_group1.size() : _group2.size();

	for (int i = 0; i < size; ++i)
		res.push_back(AverageByPatientAndIndicator(typeOfAverage, indicator, i, calculator));

	return res;
}

double AverageCalculator::AverageByIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator)
{
	int size = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ?
		_group1.size() : _group2.size();

	double sumOfAverages = 0;

	for (int i = 0; i < size; ++i)
		sumOfAverages += AverageByPatientAndIndicator(typeOfAverage, indicator, i, calculator);

	return sumOfAverages / size;
}

std::vector<std::vector<double>> AverageCalculator::AverageMatrix(const int & numOfIndicators, IMeasureCalculator* measureCalculator)
{
	std::vector<std::vector<double>> res;

	for (int i = 0; i < 4; ++i)
	{
		std::vector<double> row;
		
		for (int j = 0; j < numOfIndicators; ++j)
		{
			row.push_back(AverageByIndicator((AverageType)i, j, measureCalculator));
		}

		res.push_back(row);
	}

	return res;
}