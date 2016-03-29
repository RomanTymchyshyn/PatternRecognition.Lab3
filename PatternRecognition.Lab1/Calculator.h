#pragma once

#include <vector>
#include "IMeasureCalculator.h"
#include "Patient.h"
#include "AverageType.h"
#include "CalculatorBase.h"

class AverageCalculator: public CalculatorBase
{
	public:
		
		AverageCalculator(std::vector<Patient> group1, std::vector<Patient> group2): CalculatorBase(group1, group2) {};

		std::vector<std::vector<double>> AverageMatrix(const int & numOfIndicators, IMeasureCalculator* calculator);

	private:
		
		double AverageByPatientAndIndicator(const AverageType & typeOfAverage, const int & indicator, const int & patient, IMeasureCalculator* calculator);

		std::vector<double> AllAverageByPatientAndIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator);

		double AverageByIndicator(const AverageType & typeOfAverage, const int & indicator, IMeasureCalculator* calculator);
};