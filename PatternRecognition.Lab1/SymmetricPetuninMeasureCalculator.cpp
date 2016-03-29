#include "SymmetricPetuninMeasureCalculator.h"

double SymmetricPetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y, bool sameDistribution) const
{
	double distance = _petuninMeasureCalculator->Calculate(x, y);

	if (!sameDistribution)
	{
		distance += _petuninMeasureCalculator->Calculate(y, x);
		distance /= 2.0;
	}

	return distance;
}