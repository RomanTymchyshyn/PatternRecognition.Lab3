#include "MatrixOperations.h"

std::vector<std::vector<double>> TransposeMatrix(const std::vector<std::vector<double>> &  matrix)
{
	int cols = matrix.size();
	int rows = matrix[0].size();

	std::vector<std::vector<double>> result = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));

	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			result[i][j] = matrix[j][i];
		}
	}

	return result;
}