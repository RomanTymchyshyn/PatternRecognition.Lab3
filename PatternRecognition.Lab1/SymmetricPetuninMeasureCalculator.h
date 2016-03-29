#pragma once

#include <vector>
#include <algorithm>
#include "IMeasureCalculator.h"
#include "PetuninMeasureCalculator.h"

class SymmetricPetuninMeasureCalculator: public IMeasureCalculator
{
	public:

		SymmetricPetuninMeasureCalculator()
		{
			_petuninMeasureCalculator = new PetuninMeasureCalculator();
		};

		virtual double Calculate(std::vector<double> sample1, std::vector<double> sample2, bool sameDistribution = false) const;

		virtual bool IsSymmetric() const { return true; }

		~SymmetricPetuninMeasureCalculator()
		{
			delete _petuninMeasureCalculator;
		};

	private:

		IMeasureCalculator* _petuninMeasureCalculator;

};