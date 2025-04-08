#pragma once

#include "../pch.hpp"

class ImageProcessing
{
protected:
	unsigned char* imageData;
	int width;
	int height;
	int channels;

public:
	ImageProcessing(const std::string& _path);
	~ImageProcessing();
	void ConvertToGrayscale();
	/*void ApplyGaussianBlur();
	void ApplySobelEdgeDetection();*/
};