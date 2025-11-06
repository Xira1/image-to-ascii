#include "print_image.h"

#include <iostream>
#include <fstream>
#include <cmath>

namespace PrintImage {
	void printImage(image_t* img, const std::string& fileout) {
		const std::string VALUES = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
		size_t RAMP_SIZE = VALUES.length();

		std::ofstream f(fileout);
		if (!f.is_open()) {
			std::cerr << "Failed to open output file " << fileout << "\n";
			return;
		}

		for (size_t y = 0; y < img->height; y++) {
			for (size_t x = 0; x < img->width; x++) {

				size_t newIdx = (y * img->width + x) * img->channel;

				float R = img->data[newIdx + 0];
				float G = img->data[newIdx + 1];
				float B = img->data[newIdx + 2];

				float l = 0.2126f * R + 0.7152f * G + 0.0722f * B;

				int index = static_cast<int>(std::floor((1.0f - l) * (RAMP_SIZE - 1)));

				// Clamp index
				if (index < 0) index = 0;
				if (index >= RAMP_SIZE) index = RAMP_SIZE - 1;

				f << VALUES[index];
			}

			f << "\n";
		}

		f.close();
	}
}