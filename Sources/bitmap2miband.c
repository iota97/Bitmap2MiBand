/*

Bitmap to MiBand icon converter.

Works only with 24 BPP bitmap.
Any non black pixel (#000000) will be considered on.
Image will be cropped to get a height multiple of 8.

*/

#include <stdio.h>
#include <stdlib.h>
  
int main(int argc, char *argv[]) {

	// Check argument number

	if (argc < 2) {
		
		printf("Please provide the Bitmap path as argument.\n");
		return -1;
	
	}
	
	// Open the file
	
	FILE *fp;

	fp = fopen(argv[1], "r");	

	// Get the pixels array offset

	fseek(fp, 10, SEEK_SET);

	int32_t pixel_start = fgetc(fp) | fgetc(fp) << 8 | fgetc(fp) << 16 | fgetc(fp) << 24;

	// Get image height and width

	fseek(fp, 18, SEEK_SET);
	
	int32_t width = fgetc(fp) | fgetc(fp) << 8 | fgetc(fp) << 16 | fgetc(fp) << 24;

	int32_t height = fgetc(fp) | fgetc(fp) << 8 | fgetc(fp) << 16 | fgetc(fp) << 24;

	// Check the pixels order

	int8_t topdown_order;

	if (height < 0) {

		topdown_order = 1;
		height *= -1;
	}
	
	else {

		topdown_order = 0;

	}

	// Floor the height to a multiple of 8
	
	height -= height % 8;

	// Get to the pixels data

	fseek(fp, pixel_start, SEEK_SET);

	// Put the pixels color into an array

	u_int8_t parsed_bmp[width*height];

	u_int32_t counter = 0;

	for (int32_t row = 0; row < height; row++) {

		for (int32_t col = 0; col < width; col++) {
	
			if (fgetc(fp) | fgetc(fp) | fgetc(fp)) {
				
				parsed_bmp[counter] = 1;
			}

			else {
				
				parsed_bmp[counter] = 0;
			}

			counter++;
		}
		
		// Skip padding pixels

		fseek(fp, 4 + (width * -3) % 4, SEEK_CUR);

	}
	
	// Close the file

	fclose(fp);

	
	// Sort pixels into an array matching the MiBand pattern

	u_int8_t sorted_bmp[width*height];

	if (topdown_order == 1) {

		counter = 0;

		for (int32_t y = 0; y < height; y+=8) {

			for (int32_t x = 0; x < width; x++) {

				for (int32_t y_bias = 7; y_bias >= 0; y_bias--) {

					sorted_bmp[counter] = parsed_bmp[x+(y+y_bias)*width];

					counter++;
	
				}
			}
		}	
	}

	else {
		counter = width*height-1;

		for (int32_t y = 0; y < height; y+=8) {

			for (int32_t x = width-1; x >= 0; x--) {

				for (int32_t y_bias = 7; y_bias >= 0; y_bias--) {

					sorted_bmp[counter] = parsed_bmp[x+(y+y_bias)*width];

					counter--;	
				}
			}
		}	
		
	}
	
	// Convert to hex

	char hex_bmp[width*height/4+1];

	for (int32_t i = 0; i < width*height/4; i++) {

		hex_bmp[i] = *((char*) "0123456789ABCDEF" + sorted_bmp[i*4]*8+sorted_bmp[i*4+1]*4+sorted_bmp[i*4+2]*2+sorted_bmp[i*4+3]);
	
	}

	// Add null terminator and print

	hex_bmp[width*height/4] = '\0'; 
	printf("%s\n", (char*) hex_bmp);

	// Exit

	return 0;
}
