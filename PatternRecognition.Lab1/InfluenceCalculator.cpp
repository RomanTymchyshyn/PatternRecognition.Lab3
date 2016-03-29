#include "InfluenceCalculator.h"

void InfluenceCalculator::CalculateInfluenceSet(
	IMeasureCalculator* measureCalculator,
	const int & numberOfIndicators,
	const int & numberOfGroup,
	const std::string & nameOfFile)
{
	std::vector<Patient>& groupRef = numberOfGroup == 1 ? _group1: _group2;

	std::vector<std::vector<double>> delta(numberOfIndicators, std::vector<double>(groupRef.size(), 0));

	CalculateAllDeltaForGroup(delta, numberOfIndicators, numberOfGroup, measureCalculator);
	
	WriteResultsForGroup(delta, numberOfIndicators, nameOfFile);
}

void InfluenceCalculator::CalculateAllDeltaForGroup(
	std::vector<std::vector<double>> & deltaMatrix,
	const int & numberOfIndicators,
	const int & numberOfGroup,
	IMeasureCalculator* measureCalculator)
{
	int gSize = numberOfGroup == 1 ? _group1.size() : _group2.size();
	int oppositeGroupSize = numberOfGroup == 1 ? _group2.size() : _group1.size();

	std::vector<double> inGroupDistance(gSize, 0);
	std::vector<double> interGroupDistance(oppositeGroupSize, 0);

	double ms = 0.0;

	for (int indicator = 0; indicator < numberOfIndicators; ++indicator)
	{
		for (int i = 0; i < gSize; ++i)
		{
			for (int j = 0; j < gSize; ++j)
			{
				if (i == j)
				{
					inGroupDistance[j] = 1.0;
				}
				else
				{
					AverageType typeOfAverage = numberOfGroup == 1 ? FirstFirst : SecondSecond;
					inGroupDistance[j] = Measure(typeOfAverage, indicator, i, j, measureCalculator);
				}
			}

			for (int j = 0; j < oppositeGroupSize; ++j)
			{
				AverageType typeOfAverage = numberOfGroup == 1 ? FirstSecond : SecondFirst;
				interGroupDistance[j] = Measure(typeOfAverage, indicator, i, j, measureCalculator);
			}

			double maxInGroup = 
				*std::max_element(inGroupDistance.begin(),
								 inGroupDistance.end());

			double minTnterGroup = 
				*std::min_element(interGroupDistance.begin(),
								 interGroupDistance.end());

			deltaMatrix[indicator][i] = std::abs(maxInGroup - minTnterGroup);
		}
	}
}

void InfluenceCalculator::WriteResultsForGroup(std::vector<std::vector<double>> delta,
	const int & numberOfIndicators,
	const std::string & nameOfFile)
{
	std::ofstream fout(nameOfFile);

	for (int i = 0; i < numberOfIndicators; ++i)
	{
		WriteResultsByIndicator(delta[i], i, fout);
	}

	fout.close();
}

void InfluenceCalculator::WriteResultsByIndicator(
	std::vector<double> delta,
	const int & indicator,
	std::ofstream & fout)
{
	const int numOfGroups = 13;

	double deltas[numOfGroups] = {2.0, 1.0, 0.95, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0};

	std::vector<std::vector<int>> groups(numOfGroups - 1, std::vector<int>());

	int size = delta.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < numOfGroups - 1; ++j)
		{
			if (delta[i] < deltas[j] && delta[i] >= deltas[j + 1])
				groups[j].push_back(i + 1);
		}
	}

	for (int i = 0; i < numOfGroups - 1; ++i)
	{
		fout.width(5);
		fout << std::left << indicator + 1;
		fout.precision(2);
		fout.width(6);
		fout << std::right << deltas[i] << " > delta >= ";
		fout.width(10);
		fout << std::left << deltas[i + 1];
		fout.width(10);
		fout << std::right << groups[i].size();
		for (int j = 0; j < groups[i].size(); ++j)
		{
			fout.width(4);
			fout << std::right << groups[i][j];
		}
		fout << std::endl;
	}
}