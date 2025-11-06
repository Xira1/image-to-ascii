#include <iostream>

#include "image.h"
#include "print_image.h"

#define DEFAULT_MAX_WIDTH 1024
#define DEFAULT_MAX_HEIGHT 256

int main() {
	size_t max_width = DEFAULT_MAX_WIDTH;
	size_t max_height = DEFAULT_MAX_HEIGHT;

	image_t original = Image::Load("res/test2.jpg");
	image_t resized = Image::Resize(&original, max_width, max_height);

	PrintImage::printImage(&resized, "out/test1.txt");

	return 0;
}