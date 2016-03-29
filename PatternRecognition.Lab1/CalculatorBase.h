#pragma once

#include <vector>
#include "Patient.h"
#include "IMeasureCalculator.h"
#include "AverageType.h"

class CalculatorBase
{
	protected:

		CalculatorBase(std::vector<Patient> group1, 
			std::vector<Patient> group2) {_group1 = group1, _group2 = group2;};

		std::vector<Patient> _group1;

		std::vector<Patient> _group2;

		std::vector<Patient> GetPatientsPair(const AverageType & typeOfAverage, const int & i, const int & j);
		
		double Measure(const AverageType & typeOfAverage, const int & indicator, const int & firstPatientIndex, const int & secondPatientIndex, IMeasureCalculator* calculator);
};