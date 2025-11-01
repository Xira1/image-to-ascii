#include <iostream>
#include "image.h"
#include "print_image.h"

#define DEFAULT_MAX_WIDTH 128
#define DEFAULT_MAX_HEIGHT 112

int main() {
	size_t max_width = DEFAULT_MAX_WIDTH;
	size_t max_height = DEFAULT_MAX_HEIGHT;

	image_t original = Image::LoadImage("res/crash.jpg");
	image_t resized = Image::Resize(&original, max_width, max_height);

	PrintImage::printImage(&resized);

	return 0;
}