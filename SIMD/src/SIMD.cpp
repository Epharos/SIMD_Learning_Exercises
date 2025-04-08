#include <iostream>

#include "Profiler.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "pch.hpp"

// Exercises part 1 - Begginer
#include "LoadAndSave/LoadAndSave.hpp"
#include "BasicArithmetic/BasicArithmetic.hpp"
#include "DotProduct/DotProduct.hpp"

// Exercises part 2 - Intermediate
#include "Min_Max/Min_Max.hpp"
#include "MatMulVec/MatrixMultiplyVector.hpp"

// Exercices part 3 - Advanced
#include "Matrix/MatrixMultiplication.hpp"

int main()
{
	int choice;
	std::cout << "Choose an exercise to run" << std::endl;

	std::cout << "1. Load and Save" << std::endl;
	std::cout << "2. Basic Arithmetic" << std::endl;
	std::cout << "3. Dot Product" << std::endl;
	std::cout << "--------" << std::endl;
	std::cout << "4. Min and max" << std::endl;
	std::cout << "5. 4x4 Matrix and 4x1 Vector multiplication" << std::endl;
	std::cout << "--------" << std::endl;
	std::cout << "6. 4x4 Matrix multiplication" << std::endl;

	std::cin >> choice;
	if (choice == 1)
	{
		LoadAndSave loadAndSave(400000000);
		loadAndSave.Do();
	}
	else if (choice == 2)
	{
		BasicArithmetic basicArithmetic(400000000);
		basicArithmetic.Do();
	}
	else if (choice == 3)
	{
		DotProduct dotProduct(40000000);
		dotProduct.Do();
	}
	else if (choice == 4)
	{
		MinMax minMax(400000000);
		minMax.Do();
	}
	else if (choice == 5)
	{
		MatrixMultiplyVector matrixMultiplyVector(40000000, true);
		matrixMultiplyVector.Do();
	}
	else if (choice == 6)
	{
		MatrixMultiplication matrixMultiplication(40000000, true);
		matrixMultiplication.Do();
	}
	else
	{
		std::cout << "Invalid choice" << std::endl;
		return 1;
	}

	return 0;
}
