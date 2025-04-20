/*
 * File Name: manage_data_file.c
 * Author: Arpit Patel
 * Description: Functions for managing inventory data files
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/manage_data_file.h"
#include "../include/manage_inventory.h"


void load_inventory_from_file() {

        FILE* data_ptr = fopen("data/inventory.csv", "r");

        if (data_ptr == NULL) {

                printf("Warning: Could not Open inventory file. Starting with empty inventory.\n");
                return;

        }

        char buffer[256];

        if (fgets(buffer, sizeof(buffer), data_ptr) == NULL) {

                printf("Warning: File is empty or could not be read\n");
                fclose(data_ptr);

                return;

        }

        while (fgets(buffer, sizeof(buffer), data_ptr) != NULL) {

                char *token;
                token = strtok(buffer, ",");

                if (token == NULL) continue;

                int item_id = atoi(token);

                if (item_id < 1 || item_id > 100) continue;

                token = strtok(NULL, ",");

                if (token == NULL) continue;

                token = strtok(NULL, ",");

                if (token == NULL) continue;

                inventory[item_id - 1].quantity = atoi(token);

                token = strtok(NULL, ",");

                if (token == NULL) continue;

                token = strtok(NULL, ",");

                if (token == NULL) continue;

                strncpy(inventory[item_id - 1].expiryDate, token, sizeof(inventory[item_id - 1].expiryDate));

                inventory[item_id - 1].expiryDate[sizeof(inventory[item_id - 1].expiryDate) - 1] = '\0';

                token = strtok(NULL, ",");

                if (token == NULL) continue;

                inventory[item_id - 1].price = atof(token);

                if (is_date_expired(inventory[item_id - 1].expiryDate)) {

                        printf("Warning: Item ID %d (%s) is expired. Setting quantity to 0.\n", item_id, inventory[item_id - 1].descr);
                        inventory[item_id - 1].quantity = 0;

                }
        }

        fclose(data_ptr);

}


void save_inventory_to_file() {

        FILE* data_ptr = fopen("data/inventory.csv", "w");

        if (data_ptr == NULL) {

                printf("Error: Could not open inventory file for writing\n");
                return;

        }

        fprintf(data_ptr, "ItemID,Description,Quantity,Brand,ExpiryDate,Price\n");

        for (uint8_t i = 0; i < 100; i++) {

                if (inventory[i].quantity > 0 || (strlen(inventory[i].expiryDate) > 0 && inventory[i].price > 0.0)) {

                        fprintf(data_ptr, "%u,%s,%u,%s,%s,%.2f\n", inventory[i].itemId, inventory[i].descr, inventory[i].quantity, inventory[i].brand, inventory[i].expiryDate, inventory[i].price);

                }

        }

        fclose(data_ptr);

        printf("Inventory saved successfully.\n");

}
