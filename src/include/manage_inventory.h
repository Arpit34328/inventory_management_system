/*
 * File Name: manage_inventory.h
 * Authors: Arpit Patel
 * Description:
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#pragma pack(push,1)
typedef struct {

        uint8_t itemId;
        char descr[100];
        uint8_t quantity;
        char brand[50];
        char expiryDate[11];
        float price;

} item;
#pragma pack(pop)

extern item inventory[100];

void read_item_list();

void display_inventory_list();

bool is_date_expired(const char* date);

time_t convert_date_to_time(const char* date_str);

void add_item_to_inventory();

void sell_item_to_customer();

void check_specific_item();

#endif // INVENTORY_H
