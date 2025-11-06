#pragma once

typedef struct {
	size_t width;
	size_t height;
	size_t channel;
	float* data;
} image_t;

namespace Image {
	image_t Load(const char* filepath);
	image_t Resize(image_t* img, size_t mWidth, size_t mHeight); // Billinear interpolation
	/*float* GetPixel(image_t* img, size_t x, size_t y);
	void SetPixel(image_t* img, size_t x, size_t y, float* newPixel);*/
}