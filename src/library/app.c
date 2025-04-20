/*
 * File Name: load_sys.c
 * Author: Arpit Patel
 * Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>


#include "../include/app.h"


void load_system() {

	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int width = w.ws_col;
	int height = w.ws_row;

	system("clear");

	const char *messages[] = {
            "-----------------------",
            "|                     |",
            "|    App Loading...   |",
            "|                     |",
            "-----------------------"
	};

	int num_lines = sizeof(messages) / sizeof(messages[0]);
	int total_message_height = num_lines;
	int vertical_padding = (height - total_message_height) / 2;

	for (int i = 0; i < vertical_padding; i++) printf("\n");

	for (int i = 0; i < num_lines; i++) {
	
		int message_length = strlen(messages[i]);
		int horizontal_padding = (width - message_length) / 2;

		for (int j = 0; j < horizontal_padding; j++) printf(" ");

		printf("%s\n", messages[i]);
        
	}

	sleep(3);

	system("clear");

	manage_inventory_sys();

}
