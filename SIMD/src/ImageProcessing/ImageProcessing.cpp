#include "ImageProcessing.hpp"

ImageProcessing::ImageProcessing(const std::string& _path)
{
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &channels, 0);

	if(!data)
	{
		std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
		return;
	}

	imageData = new unsigned char[width * height * channels];
	memcpy(imageData, data, width * height * channels);
	stbi_image_free(data);
	std::cout << "Image loaded successfully: " << _path << std::endl;
	std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;
	std::cout << "Image data size: " << width * height * channels << " bytes" << std::endl;

	stbi_image_free(data);
}

ImageProcessing::~ImageProcessing()
{
	if (imageData)
	{
		delete[] imageData;
		imageData = nullptr;
	}
}

void ImageProcessing::ConvertToGrayscale()
{

}
