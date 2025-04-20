/*
 * File Name: display_menu.c
 * Author: Arpit Patel
 * Description: Interactive menu with keyboard navigation
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <termios.h>


#include "../include/app.h"


// ANSI escape codes for text formatting
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BG_WHITE      "\x1b[47m"
#define ANSI_FG_BLACK      "\x1b[30m"

// Key codes
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_ENTER 10

// Function to get a single character from terminal without echoing
char getch() {

	struct termios old_tio, new_tio;
        char c;

        // Get current terminal settings
        tcgetattr(STDIN_FILENO, &old_tio);

        // Create new settings
        new_tio = old_tio;
        new_tio.c_lflag &= (~ICANON & ~ECHO); // Disable canonical mode and echo

        // Apply new settings
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        // Read character
        c = getchar();

        // Restore old settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

        return c;
}

void display_menu() {

	struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int width = w.ws_col;
        int height = w.ws_row;

        const char *options[] = {
                "Show Current Item List",
                "Add New Item to List",
                "Sell Item to Customer",
                "Check Specific Item",
                "Delete All Items",
                "Exit from Application"
        };

        int num_options = sizeof(options) / sizeof(options[0]);
        int selected = 0; // Default selection
        char c;

        // Hide cursor
        printf("\e[?25l");

        // Loop until Enter is pressed
        while (1) {

                system("clear");

                // Calculate padding for centering
                int total_message_height = num_options + 2; 
                int vertical_padding = (height - total_message_height) / 2;

                // Print vertical padding
                for (int i = 0; i < vertical_padding; i++) printf("\n");

                // Print top border
                int max_length = 0;
                for (int i = 0; i < num_options; i++) {
                        int len = strlen(options[i]);
                        if (len > max_length) {
                                max_length = len;
                        }
                }

                char border[max_length + 7]; 
                memset(border, '-', max_length + 6);
                border[max_length + 6] = '\0';

                int horizontal_padding = (width - (max_length + 6)) / 2;
                for (int j = 0; j < horizontal_padding; j++) printf(" ");
                printf("%s\n", border);

                // Print menu options
                for (int i = 0; i < num_options; i++) {
                        for (int j = 0; j < horizontal_padding; j++) printf(" ");

                        printf("|");

                        // Highlight selected option
                        if (i == selected) {
                                printf("%s%s", ANSI_BG_WHITE, ANSI_FG_BLACK);
                        }

                        // Print option with padding
                        printf(" %-*s ", max_length, options[i]);

                        // Reset formatting
                        if (i == selected) {
                                printf("%s", ANSI_COLOR_RESET);
                        }

                        printf("  |\n");
                }

                // Print bottom border
                for (int j = 0; j < horizontal_padding; j++) printf(" ");
                printf("%s\n", border);

                // Wait for keypress
                c = getch();

                // Handle arrow keys (they come as escape sequences)
                if (c == 27) {
                        getch();
                        c = getch();

                        if (c == KEY_UP && selected > 0) {
                                selected--;
                        } else if (c == KEY_DOWN && selected < num_options - 1) {
                                selected++;
                        }
                } 
		else if (c == KEY_ENTER) {
                        // User pressed Enter, call the appropriate function
                        system("clear");

                        // Show cursor again
                        printf("\e[?25h");

                        // Call perform_task with the selected option
                        perform_task(selected + 1); // +1 assuming your perform_task expects 1-based index
                        return;
                }
	}

}

