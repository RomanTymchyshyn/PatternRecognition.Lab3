#include "CalculatorBase.h"

std::vector<Patient> CalculatorBase::GetPatientsPair(const AverageType & typeOfAverage, 
	const int & i, const int & j)
{
	std::vector<Patient> res;

	Patient p1 = typeOfAverage == FirstFirst || typeOfAverage == FirstSecond ?
		_group1[i] : _group2[i];
	res.push_back(p1);

	Patient p2 = typeOfAverage == FirstFirst || typeOfAverage == SecondFirst ?
		_group1[j] : _group2[j];
	res.push_back(p2);

	return res;
}

double CalculatorBase::Measure(const AverageType & typeOfAverage, const int & indicator, 
	const int & firstPatientIndex, const int & secondPatientIndex, IMeasureCalculator* calculator)
{
	std::vector<Patient> patients = GetPatientsPair(typeOfAverage, firstPatientIndex, secondPatientIndex);

	bool sameDistribution = typeOfAverage == FirstFirst || typeOfAverage == SecondSecond;

	return calculator->Calculate(patients[0].GetIndicatorSample(indicator), 
								 patients[1].GetIndicatorSample(indicator), sameDistribution);
}