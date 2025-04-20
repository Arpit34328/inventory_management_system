/*
 * File Name: manage_task.c
 * Author: Arpit Patel
 * Description: Implementation of task management functions
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/app.h"
#include "../include/manage_inventory.h"
#include "../include/manage_data_file.h"


void perform_task(uint8_t option) {

        system("clear");

        switch (option) {

                case 1:

                        printf("==== Current Inventory ====\n\n");

                        read_item_list();

                        printf("\nPress Enter to continue...");

                        getchar();

                        break;

                case 2:

                        add_item_to_inventory();

                        break;

                case 3:

                        sell_item_to_customer();

                        break;

                case 4:

                        check_specific_item();

                        break;

                case 5:

                        printf("==== Delete All Items ====\n");

                        printf("Are you sure you want to delete all items? (y/n): ");

                        char confirm;

                        scanf("%c", &confirm);

                        getchar();

                        if (confirm == 'y' || confirm == 'Y') {

                                for (int i = 0; i < 100; i++) {

                                        inventory[i].quantity = 0;

                                        strcpy(inventory[i].expiryDate, "");

                                        inventory[i].price = 0.0;

                                }

                                printf("All items deleted successfully.\n");

                        }
                        else {

                                printf("Delete operation cancelled.\n");

                        }

                        printf("Press Enter to continue...");

                        getchar();

                        break;

                case 6:

                        printf("==== Exiting Application ====\n");

                        printf("Saving inventory data...\n");

                        save_inventory_to_file();

                        printf("Thank you for using the Inventory Management System!\n");

                        exit(0);

                        break;

                default:

                        printf("Invalid option selected.\n");

                        printf("Press Enter to continue...");

                        getchar();

                        break;

        }

        display_menu();

}
