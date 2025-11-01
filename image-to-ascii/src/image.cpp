#include "image.h"

#include <iostream>
#include <algorithm>
#include <stb_image.h>

namespace Image {
	image_t LoadImage(const char* filepath) {
		int width, height, nrChannels;
		image_t img;

		
		float* data = stbi_loadf(filepath, &width, &height, &nrChannels, 0);

		size_t total = width * height * nrChannels;
		float* mallocData = (float*)malloc(total * sizeof(float));

		if (mallocData && data) {
			memcpy(mallocData, data, total * sizeof(float));
			stbi_image_free(data);

			img.width = static_cast<size_t>(width);
			img.height = static_cast<size_t>(height);
			img.channel = static_cast<size_t>(nrChannels);
			img.data = mallocData;

			std::cout << "Image load successfully\n";
			std::cout << "Width: " << width << "\n" << "Height: " << height << "\n" << "Num channels: " << nrChannels << "\n";

			return img;
		}
		else {
			std::cout << "Image load failed: " << stbi_failure_reason() << "\n";
			img.data = nullptr;
			stbi_image_free(data);
		}
	}

	image_t Resize(image_t* img, size_t mWidth, size_t mHeight) {
		size_t new_width = mWidth;
		size_t new_height = mHeight;
		size_t channels = img->channel;

		// Allocate new array
		image_t out;
		out.width = new_width;
		out.height = new_height;
		out.channel = channels;

		float* new_data = (float*)malloc(new_width * new_height * channels * sizeof(float));

		if (new_data) {
			out.data = new_data;
		}
		else {
			std::cout << "Failed to allocate new pixel array!" << "\n";
			return out;
		}

		float x_scale = static_cast<float>(img->width) / new_width;
		float y_scale = static_cast<float>(img->height) / new_height;

		for (size_t y_new = 0; y_new < new_height; y_new++) {
			for (size_t x_new = 0; x_new < new_width; x_new++) {
				
				float x_src = x_new * x_scale;
				float y_src = y_new * y_scale;
				
				size_t x1 = std::min((size_t)std::floor(x_src), img->width - 1);
				size_t y1 = std::min((size_t)std::floor(y_src), img->height - 1);
				size_t x2 = std::min(x1 + 1, img->width - 1);
				size_t y2 = std::min(y1 + 1, img->height - 1);

				float xWeight = x_src - x1;
				float yWeight = y_src - y1;

				size_t newIdx = (y_new * new_width + x_new) * channels;

				for (size_t c = 0; c < channels; c++) {
					// Top left x1 y1
					size_t index_11 = (y1 * img->width + x1) * channels + c;
					float Q11_value = img->data[index_11];

					// Top right x2 y1
					size_t index_21 = (y1 * img->width + x2) * channels + c;
					float Q21_value = img->data[index_21];

					// Bottom left x1 y2
					size_t index_12 = (y2 * img->width + x1) * channels + c;
					float Q12_value = img->data[index_12];

					// Bottom right x2 y2
					size_t index_22 = (y2 * img->width + x2) * channels + c;
					float Q22_value = img->data[index_22];

					float P1 = std::lerp(Q11_value, Q21_value, xWeight); // top row
					float P2 = std::lerp(Q12_value, Q22_value, xWeight); // bottom row

					float finalColor = std::lerp(P1, P2, yWeight);

					new_data[newIdx + c] = finalColor;
				}
			}
		}

		std::cout << "\nResized image\n";
		std::cout << "Width: " << new_width << "\n" << "Height: " << new_height << "\n" << "Num channels: " << channels << "\n";

		return out;
	}

	float* GetPixel(image_t* img, size_t x, size_t y) {
		float* data = (float*)img->data;
		size_t idx = (y * img->width + x) * img->channel;

		return &data[idx];
	}

	void SetPixel(image_t* img, size_t x, size_t y, float* newPixel) {
		float* pixel = GetPixel(img, x, y);
		for (size_t i = 0; i < img->channel; i++) {
			pixel[i] = newPixel[i];
		}
	}
}