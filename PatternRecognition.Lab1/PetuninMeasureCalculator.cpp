#include "PetuninMeasureCalculator.h"

double PetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y, bool sameDistribution) const
{
	sort(x.begin(), x.end());
	double count = 0;
	double n = x.size();
	double m = y.size();
	double N = n * (n - 1) / 2;
	const double g = 3.0;
	double h, p1, p2, p;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			h = 0;
			for (int k = 0; k < m; k++)
				if (x[i] < y[k] && y[k] <= x[j])
					h++;
			h /= m;

			p1 = (h * m + g * g / 2 - g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			p2 = (h * m + g * g / 2 + g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			p = (j - i) / (n + 1.0);
			
			if (p1 < p && p <= p2)
				count++;
		}
	}
	return count / N;
}