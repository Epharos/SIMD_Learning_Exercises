#include <iostream>

#include "Profiler.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "pch.hpp"

// Exercises part 1 - Begginer
#include "LoadAndSave/LoadAndSave.hpp"
#include "BasicArithmetic/BasicArithmetic.hpp"
#include "Min_Max/Min_Max.hpp"

// Exercises part 2 - Intermediate
#include "DotProduct/DotProduct.hpp"
#include "MatMulVec/MatrixMultiplyVector.hpp"

// Exercices part 3 - Advanced
#include "Matrix/MatrixMultiplication.hpp"

int main()
{
	int choice;
	std::cout << "Choose an exercise to run" << std::endl;

	std::cout << "1. Load and Save" << std::endl;
	std::cout << "2. Basic Arithmetic" << std::endl;
	std::cout << "3. Min and max" << std::endl;
	std::cout << "--------" << std::endl;
	std::cout << "4. Dot Product" << std::endl;
	std::cout << "5. 4x4 Matrix and 4x1 Vector multiplication" << std::endl;
	std::cout << "--------" << std::endl;
	std::cout << "6. 4x4 Matrix multiplication" << std::endl;

	Exercise* exercise = nullptr;

	std::cin >> choice;

	switch (choice)
	{
	case 1:
		exercise = new LoadAndSave(400000000); // 400M loads and saves
		break;
	case 2:
		exercise = new BasicArithmetic(400000000); // 400M values
		break;
	case 3:
		exercise = new MinMax(400000000); // 400M values
		break;
	case 4:
		exercise = new DotProduct(400000000); // 400M values
		break;
	case 5:
		exercise = new MatrixMultiplyVector(40000000, true); // 40M values as it takes a bit more time
		break;
	case 6:
		exercise = new MatrixMultiplication(40000000, true); // 40M values as it takes a bit more time
		break;
	default:
		std::cout << "Invalid choice" << std::endl;
		return 1;
	}

	if (exercise)
	{
		exercise->ProcessAll();
		delete exercise;
	}

	return 0;
}
