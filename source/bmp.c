
/**
 * @brief Pure C Bitmap writer
 *
 * Based on: https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
 */

#include "bmp.h"

#define BMP_FILE_HEADER_SIZE		14
#define BMP_INFO_HEADER_SIZE		40

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int bmp_create(char* filename, uint32_t w, uint32_t h, bool* data) {

	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	unsigned char bmppad[3] = {0, 0, 0};
	FILE *f;

	uint32_t filesize = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE + w * h * 3;

	int index = 0;
	uint8_t* filedata = (uint8_t*)malloc(filesize);

	//Write file header
	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize >> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize >> 16);
	bmpfileheader[ 5] = (unsigned char)(filesize >> 24);

	memcpy(filedata + index, bmpfileheader, sizeof(bmpfileheader));
	index += sizeof(bmpfileheader);

	//Write info header
	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w >> 8);
	bmpinfoheader[ 6] = (unsigned char)(w >> 16);
	bmpinfoheader[ 7] = (unsigned char)(w >> 24);
	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	memcpy(filedata + index, bmpinfoheader, sizeof(bmpinfoheader));
	index += sizeof(bmpinfoheader);

	//Write data
	for (int i = h - 1; i >= 0; i--) {
		for (int j = 0; j < w; j++) {
			if (data[i * w + j] == false) {
				filedata[index + 0] = 0x00;
				filedata[index + 1] = 0x00;
				filedata[index + 2] = 0x00;
			} else {
				filedata[index + 0] = 0xFF;
				filedata[index + 1] = 0xFF;
				filedata[index + 2] = 0xFF;
			}
			index += 3;
		}

		//Padding should ensure each section is word aligned
		//TODO: this is broken
		index += (w % 4 != 0) ? 4 - (w % 4) : 0;
	}

	f = fopen(filename, "w");

	fwrite(filedata, 1, filesize, f);

	fclose(f);

	free(filedata);

	return 0;
}
