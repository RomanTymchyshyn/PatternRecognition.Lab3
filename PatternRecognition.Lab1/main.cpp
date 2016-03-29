#include <vector>
#include <iostream>
#include <time.h> 
#include "IFileReader.h"
#include "IFileWriter.h"
#include "Patient.h"
#include "PokFileReader.h"
#include "FileWriter.h"
#include "Helper.h"
#include "IMeasureCalculator.h"
#include "PetuninMeasureCalculator.h"
#include "SymmetricPetuninMeasureCalculator.h"
#include "Calculator.h"
#include "MatrixOperations.h"
#include "InfluenceCalculator.h"

int main()
{
	clock_t time = clock();

	IFileReader* reader = new PokFileReader();
	IFileWriter* writer = new FileWriter();

	Helper* helper = new Helper(reader, writer);

	std::vector<Patient> group1 = helper->ReadGroup("ALLD2", "D2", ".POK", 60);
	std::vector<Patient> group2 = helper->ReadGroup("ALLD3", "D3", ".POK", 42);

	IMeasureCalculator* nonSymmetricCalculator = 
		new PetuninMeasureCalculator();
	IMeasureCalculator* symmetricCalculator = 
		new SymmetricPetuninMeasureCalculator();

	InfluenceCalculator* calculator = new InfluenceCalculator(group1, group2);
	calculator->CalculateInfluenceSet(symmetricCalculator, 15, 1, 
		"influence_set1.txt");

	calculator->CalculateInfluenceSet(symmetricCalculator, 15, 2, 
		"influence_set2.txt");

	time = clock() - time;

	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << "Finished!\nTime elapsed: " << ms << " ms" << std::endl << std::endl;
	
	delete calculator;
	delete nonSymmetricCalculator;
	delete symmetricCalculator;
	delete helper;
	delete reader;
	delete writer;

	std::cout << "Press any key.\n";
	std::cin.get();

	return 0;
}
