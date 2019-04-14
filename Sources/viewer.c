/*

MiBand icon converter viewer.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() {

	// print new line 200 times, better safe than sorry...

	for (int i = 0; i < 200; i++)
		printf("\n");

	return;
}

void test_print(char str[], int line_lenght) {


	// fill a 2D array with the bit as if it was the screen	
	
	int height = strlen(str)/line_lenght;	
	char screen[line_lenght+1][height];
	int str_offset = 0;

	for (int y = 0; y < height; y += 8) { 

		for (int x = 0; x < line_lenght; x++) {

			for (int y_offset = 7;  y_offset >= 0;  y_offset--) {

				screen[x][y+y_offset] = str[str_offset];
				str_offset++;
			}			
		}
	}

	// print the array	

	char char_1 = '#';
	char char_0 = ' ';

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < line_lenght; j++) {

			if (screen[j][i] == '1')
				printf("%c ", char_1);

			else
				printf("%c ", char_0);
		}

		printf("\n");
	}

	return;
}

int main (int argc, char* argv[]) {
	
	// get comand line argument

	char str[strlen(argv[1])*4];

	int line_lenght = 0;

	if (argc > 2)
		line_lenght += atoi(argv[2])-1;

	// convert to binary
	
	char convert_array[16][4] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

	for (int i = 0; i < strlen(argv[1]); i++) {

		for (int j = 0; j < 4; j++) {

			int char_index;

			switch(argv[1][i]) {

				case '1': char_index = 1; break;
				case '2': char_index = 2; break;
				case '3': char_index = 3; break;
				case '4': char_index = 4; break;
				case '5': char_index = 5; break;
				case '6': char_index = 6; break;
				case '7': char_index = 7; break;
				case '8': char_index = 8; break;
				case '9': char_index = 9; break;
				case 'A': char_index = 10; break;
				case 'B': char_index = 11; break;
				case 'C': char_index = 12; break;
				case 'D': char_index = 13; break;
				case 'E': char_index = 14; break;
				case 'F': char_index = 15; break;
				case 'a': char_index = 10; break;
				case 'b': char_index = 11; break;
				case 'c': char_index = 12; break;
				case 'd': char_index = 13; break;
				case 'e': char_index = 14; break;
				case 'f': char_index = 15; break;
				default: char_index = 0; break;

			}

			str[i*4+j] = convert_array[char_index][j];
		}

	}

	// try different line lenght

	int line_lenght_step = 1;

	char console_char;
	
	do {	
		line_lenght += line_lenght_step;

		// cicle checking string boundaries
		
		if (line_lenght < 1)
			line_lenght = strlen(str)/8;

		if (line_lenght > strlen(str)/8)
			line_lenght = 1;
		
		// print a preview with the current line lenght		
		
		clear_screen();
		test_print(str, line_lenght);

		// print the usage instruction to the user

		if (line_lenght_step > 0)
			printf("\n\n\nCurrent line lenght: %d\n\nPress enter to INCREMENT the line lenght, type 's' to switch to decrement mode, type 'q' to quit. ", line_lenght);
		
		else
			printf("\n\n\nCurrent line lenght: %d\n\nPress enter to DECREMENT the line lenght, type 's' to switch to increment mode, type 'q' to quit. ", line_lenght);

		console_char = getchar();

		// if the user type s rever the cicle direction		

		if (console_char == 's') {

			line_lenght += 2*line_lenght_step;
			line_lenght_step *= -1;

		}

	} while (console_char != 'q');
	
	// write a new line and exit

	printf("\n");
	return 0;
}