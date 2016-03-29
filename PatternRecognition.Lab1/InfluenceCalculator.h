#pragma once

#include <vector>
#include <cmath>
#include "IMeasureCalculator.h"
#include "Patient.h"
#include "AverageType.h"
#include "CalculatorBase.h"
#include "MatrixOperations.h"
#include <fstream>
#include <time.h>

class InfluenceCalculator : public CalculatorBase
{
	public:

		InfluenceCalculator(std::vector<Patient> group1, 
			std::vector<Patient> group2): CalculatorBase(group1, group2) {};

		void CalculateInfluenceSet(IMeasureCalculator* measureCalculator,
			const int & numberOfIndicators,
			const int & numberOfGroup,
			const std::string & nameOfFile);

	private:

		void CalculateAllDeltaForGroup(
			std::vector<std::vector<double>> & deltaMatrix,
			const int & numberOfIndicators, 
			const int & numberOfGroup, 
			IMeasureCalculator* calculator);

		void WriteResultsForGroup(std::vector<std::vector<double>> delta,
			const int & numberOfIndicators,
			const std::string & nameOfFile);

		void WriteResultsByIndicator(std::vector<double> delta,
			const int & indicator, 
			std::ofstream & fout);
};