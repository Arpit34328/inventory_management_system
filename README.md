# Inventory Management System

A simple command-line inventory management application written in C for small-scale retail businesses or personal inventory tracking.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [File Structure](#file-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Data Storage](#data-storage)
- [Development](#development)
- [License](#license)

## Overview

This inventory management system provides a text-based user interface to manage product inventory. It allows users to add new items, check stock levels, sell items to customers, and view detailed reports. The system keeps track of quantities, expiry dates, prices, and provides alerts for expired or low-stock items.

## Features

- **Interactive Menu**: User-friendly menu with keyboard navigation
- **Inventory Management**:
  - View current inventory with detailed information
  - Add new items with quantity, expiry date, and price
  - Sell items with automatic stock updates
  - Check specific item details including expiry status
  - Delete all inventory items
- **Data Persistence**: Save and load inventory data from CSV files
- **Expiry Tracking**: Automatic detection and handling of expired items
- **Stock Level Alerts**: Notifications for low stock items

## File Structure

```
.
├── Makefile
├── data
│   └── inventory.csv
└── src
    ├── include
    │   ├── app.h
    │   ├── manage_data_file.h
    │   └── manage_inventory.h
    ├── library
    │   ├── app.c
    │   ├── display_menu.c
    │   ├── inventory_list.c
    │   ├── manage_data_file.c
    │   ├── manage_inventory.c
    │   └── manage_task.c
    └── main.c
```

## Requirements

- C Compiler (GCC recommended)
- Standard C libraries
- Terminal with ANSI support for menu display

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/inventory_system.git
   cd inventory_system
   ```

2. Compile the code using make:
   ```bash
   make
   ```

   If you don't have make installed, you can compile manually:
   ```bash
   gcc -o inventory_system src/main.c src/library/*.c -Isrc/include
   ```

3. Ensure the `data` directory exists:
   ```bash
   mkdir -p data
   ```

4. Create an empty inventory.csv file (if not already present):
   ```bash
   touch data/inventory.csv
   ```

## Usage

1. Run the application:
   ```bash
   ./inventory_system
   ```

2. Navigate the menu using arrow keys:
   - ↑/↓: Move selection up and down
   - Enter: Select an option

3. Available options:
   - **Show Current Item List**: Displays all items with their details
   - **Add New Item to List**: Add inventory with quantity, expiry date, and price
   - **Sell Item to Customer**: Sell items and generate a receipt
   - **Check Specific Item**: View detailed information about a particular item
   - **Delete All Items**: Clear the entire inventory
   - **Exit from Application**: Save and quit the application

## Data Storage

The inventory data is stored in a CSV file (`data/inventory.csv`) with the following format:

```
ItemID,Description,Quantity,Brand,ExpiryDate,Price
1,Milk 1L,10,Dairy Farm,2025-05-20,45.50
...
```

The system automatically loads this data at startup and saves changes when exiting or after selling items.

## Development

### Adding New Items to the System

The base item catalog is defined in `src/library/inventory_list.c`. To add new product categories:

1. Add entries to the `inventory` array in `inventory_list.c`
2. Increase the array size in `manage_inventory.h` if needed

### Extending Functionality

To add new features:
1. Create appropriate header files in `src/include/`
2. Implement functions in `src/library/`
3. Update the menu in `display_menu.c`
4. Add handling for new options in `perform_task()` function

## License

[MIT License](LICENSE)

---

Created by Arpit Patel
