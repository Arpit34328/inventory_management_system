/*
 * File Name: manage_inventory.c
 * Author: Arpit Patel
 * Description:
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/app.h"
#include "../include/manage_inventory.h"
#include "../include/manage_data_file.h"


void manage_inventory_sys() {

        load_inventory_from_file();

        display_menu();

}


void read_item_list() {

        printf("+------+-----------------------------+----------+--------------------+------------+------------+\n");
        printf("| ID   | Description                 | Quantity | Brand              | Expiry     | Price      |\n");
        printf("+------+-----------------------------+----------+--------------------+------------+------------+\n");

        uint8_t count = 0;

        for (uint8_t i = 0; i < 100; i++) {

                if (inventory[i].quantity > 0 || (strlen(inventory[i].expiryDate) > 0 && inventory[i].price > 0.0)) {

                        printf("| %-4d | %-27s | %-8d | %-18s | %-10s | ₹%9.2f |\n",
                               inventory[i].itemId, inventory[i].descr, inventory[i].quantity,
                               inventory[i].brand, inventory[i].expiryDate, inventory[i].price);

                        count++;

                }

        }

        if (count == 0) {

                printf("|                                    No items in inventory                                     |\n");

        }

        printf("+------+-----------------------------+----------+--------------------+------------+------------+\n");
        printf("Total items: %d\n", count);

}


void display_inventory_list() {

        printf("+------+------------------------------+\n");
        printf("| ID   | Description                  |\n");
        printf("+------+------------------------------+\n");

        for (int i = 0; i < 100; i++) {
                printf("| %-4d | %-28s |\n", inventory[i].itemId, inventory[i].descr);
        }

        printf("+------+------------------------------+\n");

}


bool is_date_expired(const char* date) {

        if (strlen(date) == 0) return false;

        time_t now = time(NULL);

        time_t expiry = convert_date_to_time(date);

        return difftime(expiry, now) < 0;

}


time_t convert_date_to_time(const char* date_str) {

        struct tm tm_date = {0};

        sscanf(date_str, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);

        tm_date.tm_year -= 1900; // Years since 1900

        tm_date.tm_mon -= 1;     // Months 0-11

        return mktime(&tm_date);

}


void add_item_to_inventory() {

        system("clear");

        printf("==== Add Item to Inventory ====\n\n");

        display_inventory_list();

        int item_id;

        printf("\nEnter Item ID to add (1-100): ");

        scanf("%d", &item_id);

        getchar();

        if (item_id < 1 || item_id > 100) {

                printf("Error: Invalid Item ID. Must be between 1 and 100.\n");

                printf("Press Enter to continue...");

                getchar();

                return;

        }

        int idx = item_id - 1;

        if (inventory[idx].quantity > 0 && !is_date_expired(inventory[idx].expiryDate)) {

                printf("Error: Item already exists in inventory and is not expired.\n");

                printf("Current quantity: %d\n", inventory[idx].quantity);

                printf("Expiry date: %s\n", inventory[idx].expiryDate);

                printf("Press Enter to continue...");

                getchar();

                return;

        }

        if (inventory[idx].quantity > 0 && is_date_expired(inventory[idx].expiryDate)) {

                printf("Warning: Item is expired. Setting quantity to 0.\n");
                inventory[idx].quantity = 0;

        }

        printf("\nAdding Item: %s (Brand: %s)\n", inventory[idx].descr, inventory[idx].brand);

        printf("Enter Quantity: ");

        scanf("%hhu", &inventory[idx].quantity);

        getchar();

        printf("Enter Expiry Date (YYYY-MM-DD): ");

        fgets(inventory[idx].expiryDate, sizeof(inventory[idx].expiryDate), stdin);

        inventory[idx].expiryDate[strcspn(inventory[idx].expiryDate, "\n")] = 0;

        printf("Enter Price (₹): ");

        scanf("%f", &inventory[idx].price);

        getchar();

        printf("\nItem added successfully!\n");

        printf("Press Enter to continue...");

        getchar();

}


void sell_item_to_customer() {
        
	system("clear");        
	
	printf("==== Sell Item to Customer ====\n\n");
                
	display_inventory_list();
                
	int item_id;
        
	printf("\nEnter Item ID to sell (1-100): ");
        
	scanf("%d", &item_id);
        
	getchar();
                
	if (item_id < 1 || item_id > 100) {
        
		printf("Error: Invalid Item ID. Must be between 1 and 100.\n");
        
		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
                
	int idx = item_id - 1;
                
	if (inventory[idx].quantity == 0) {
        
		printf("Error: Item not available in inventory or out of stock.\n");
        
		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
                
	if (is_date_expired(inventory[idx].expiryDate)) {
                
		printf("Error: Item is expired and cannot be sold.\n");
                
		printf("Expiry date: %s\n", inventory[idx].expiryDate);

		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
                
	printf("\nSelling Item: %s (Brand: %s)\n", inventory[idx].descr, inventory[idx].brand);
        
	printf("Available Quantity: %d\n", inventory[idx].quantity);
        
	printf("Price per unit: ₹%.2f\n", inventory[idx].price);
                
	int qty_to_sell;
        
	printf("\nEnter Quantity to sell: ");
        
	scanf("%d", &qty_to_sell);

	getchar();
                
	if (qty_to_sell <= 0) {
        
		printf("Error: Quantity must be greater than 0.\n");
        
		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
        	
	if (qty_to_sell > inventory[idx].quantity) {
        
		printf("Error: Not enough quantity available. Only %d items in stock.\n", inventory[idx].quantity);
        
		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
                
	float total_price = qty_to_sell * inventory[idx].price;
        
	inventory[idx].quantity -= qty_to_sell;
         
	printf("\n=== Sale Receipt ===\n");
        
	printf("Item: %s\n", inventory[idx].descr);
        
	printf("Brand: %s\n", inventory[idx].brand);
        
	printf("Quantity: %d\n", qty_to_sell);
        
	printf("Price per unit: ₹%.2f\n", inventory[idx].price);
        
	printf("Total Amount: ₹%.2f\n", total_price);
        
	printf("Remaining stock: %d\n", inventory[idx].quantity);
                
	printf("\nItem sold successfully!\n");
         
	save_inventory_to_file();
        
	printf("Press Enter to continue...");

	getchar();

}


void check_specific_item() {
        
	system("clear");
        
	printf("==== Check Specific Item ====\n\n");
        
        display_inventory_list();
        
        int item_id;
        
	printf("\nEnter Item ID to check (1-100): ");
        
	scanf("%d", &item_id);
        
	getchar();
                
	if (item_id < 1 || item_id > 100) {
        
		printf("Error: Invalid Item ID. Must be between 1 and 100.\n");
        
		printf("Press Enter to continue...");
        
		getchar();
        
		return;
        
	}
                
	int idx = item_id - 1;
                
	printf("\n=== Item Details ===\n");
        
	printf("Item ID: %d\n", inventory[idx].itemId);
        
	printf("Description: %s\n", inventory[idx].descr);
        
	printf("Brand: %s\n", inventory[idx].brand);
        
	printf("Quantity in Stock: %d\n", inventory[idx].quantity);
                
	if (strlen(inventory[idx].expiryDate) > 0) {
                
		printf("Expiry Date: %s\n", inventory[idx].expiryDate);
                
		if (is_date_expired(inventory[idx].expiryDate)) {
                
			printf("Status: EXPIRED\n");
                
		} 
		
		else {
                
			printf("Status: Valid\n");
                
		}
        
	} 
	
	else {
        
		printf("Expiry Date: Not set\n");
        
		printf("Status: N/A\n");
        
	}
                
	if (inventory[idx].price > 0.0) {
        
		printf("Price: ₹%.2f\n", inventory[idx].price);

	} 
	
	else {

		printf("Price: Not set\n");

	}
                
	if (inventory[idx].quantity == 0) {
        
		printf("\nStock Status: OUT OF STOCK\n");
        
	} 
	
	else if (inventory[idx].quantity < 5) {
        
		printf("\nStock Status: LOW STOCK\n");
        
	} 
	
	else {

		printf("\nStock Status: IN STOCK\n");
 
	}
        
        printf("\nPress Enter to continue...");
 
 	getchar();

}
