/*
Description: The Inventory Control System is a program designed to simplify inventory management for store owners. It enables users to efficiently view and oversee their store's inventory. Detailed information about each item, including its name, ID Number, cost, current stock quantity, and total value, can be easily accessed. Additionally, users can record sales, automatically update stock levels, and calculate profits using this system. The program provides valuable insights into store performance by displaying the quantity sold, total profit for each item, and overall store profit. With a limit of ten distinct items, the program also facilitates restocking existing items and adding new ones. The system supports loading and saving data from a permanent file.

Programmer: HELI JITENDRAKUMAR PATEL
Date: December 07, 2023
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Inventory                              // defines a structure for storing details of a product
{
    char itemName[50];
    int idNum;
    float unitCost;
    int stock;
    int unitsSold;
    float profit;
};

// Function declarations
void explainTheProgram(void);
void displayDetails(void);
void displayStock(struct Inventory items[], int totalItems);
void recordSale(struct Inventory items[], int totalItems);
void computeProfit(struct Inventory items[], int totalItems);
void addItem(struct Inventory items[], int totalItems);
void addNewItem(struct Inventory items[], int* totalItems);
void saveStockData(struct Inventory items[], int totalItems);
void loadStockData(struct Inventory items[], int* totalItems);

int main(void)
{
    struct Inventory items[12];               // declares an array with capacity of 12 items
    int totalItems = 0;
    char userChoice;

    explainTheProgram();
    getchar();

    loadStockData(items, &totalItems);         // load initial stock from file
   
    do
    {
        system("cls"); 

        displayDetails();                      

        printf("\nPlease enter your choice: ");
        scanf(" %c", &userChoice);

        userChoice = tolower(userChoice);           // to convert into lowercase

        switch (userChoice)
        {
        case 'a':
            displayStock(items, totalItems);        // calls a function to display current inventory details
            break;
        case 'b':
            recordSale(items, totalItems);          // calls a function to record a product sale
            break;
        case 'c':
            computeProfit(items, totalItems);       // calls a function to show profit 
            break;
        case 'd':
            addItem(items, totalItems);             // calls a function to restock an existing item
            break;
        case 'e':
            addNewItem(items, &totalItems);         // calls a function to add a new item to the inventory
            break;
        case 'f':
            saveStockData(items, totalItems);
            printf("Exiting...\n");
            break;
        default:
            printf("Please enter a valid input.\n");
        }

        if (userChoice != 'f')
        {
            printf("\nPress Enter to continue......");
            getchar();                                     // Wait for user input
            getchar();                                     
        }

    } while (userChoice != 'f');

    return 0;
}

void explainTheProgram(void)
{
    printf("\n1.This is a program designed to simplify inventory management for store owners.\n2.It enables users to efficiently view and oversee their store's inventory. \n3.Detailed information about each item, including its name, ID Number, cost, current stock quantity, and total value, can be easily accessed.\n4.Additionally, users can record sales, automatically update stock levels, and calculate profits using this system. \n5.The program provides valuable insights into store performance by displaying the quantity sold, total profit for each item, and overall store profit. \n6.With a limit of ten distinct items, the program also facilitates restocking existing items and adding new ones. \n7.The system supports loading and saving data from a permanent file.\n\n");
    return;
}

void displayDetails(void)
{
    printf("\n\tInventory Control System\n\nTo choose a function, enter its letter label:\n\na) Display current inventory details.\nb) Record a product sale.\nc) Show profit and sales data.\nd) Restock an existing item.\ne) Add a new item to the inventory.\nf) Exit the program.\n");
    return;
}

void displayStock(struct Inventory items[], int totalItems)  //this function is to provide a clear and formatted display of the inventory details
{
    printf("\n\tInventory Information:\n\n");
    printf("Item Name\tID Number\tQuantity\tCost\t\tValue\n\n");

    for (int index = 0; index < totalItems; index++)
    {
        printf("%s\t\t%d\t\t%d\t\t$%.2f\t\t%.2f\n", items[index].itemName, items[index].idNum, items[index].stock, items[index].unitCost, items[index].unitCost * items[index].stock);
    }
}

void recordSale(struct Inventory items[], int totalItems)  //this function is to record a sale by updating the stock, units sold, and profit for                                                                           a specific product
{
    int product_id, unitsSold;
    printf("\nEnter the ID Number of the product sold: ");
    scanf("%d", &product_id);

    int itemIndex = -1;                                  //value to check whether an item was found or not 
    for (int index = 0; index < totalItems; index++)   
    {
        if (items[index].idNum == product_id)            //searches for the product with the entered ID
        {
            itemIndex = index;                           //the index is stored in the variable index
            break;
        }
    }

    if (itemIndex != -1)
    {
        printf("Enter the number of units sold: ");
        scanf("%d", &unitsSold);

        items[itemIndex].stock -= unitsSold;
        items[itemIndex].unitsSold += unitsSold;
        items[itemIndex].profit += unitsSold * items[itemIndex].unitCost;

        printf("\nSale processed!!!\n");                  //stock, units sold, and profit for the product are updated
    }
    else
    {
        printf("\nID Number of the product not found.\n");
    }
}

void computeProfit(struct Inventory items[], int totalItems)   // this function is to display detailed profit information for each item and the                                                                                 overall profit across the entire inventory
{
    float total_Profit = 0;                                    // initializing variable to keep track of the overall profit.
    printf("\nProfit Details:\n");
    printf("Item Name\tID Number\tQuantity Sold\tItem Profit\n\n");

    for (int index = 0; index < totalItems; index++)
    {
        printf("%s\t\t%d\t\t%d\t\t%.2f\n", items[index].itemName, items[index].idNum, items[index].unitsSold, items[index].profit);
        total_Profit += items[index].profit;                   //updates the overall profit by adding the profit of the each item
    }
    printf("\nTotal Profit: $%.2f\n", total_Profit);       
}

void addItem(struct Inventory items[], int totalItems)          //this function is to restock a specific item in the inventory by updating its stock 
{
    int product_id, itemToStock;
    printf("\nEnter the product ID to restock: ");
    scanf("%d", &product_id);

    int itemIndex = -1;
    for (int index = 0; index < totalItems; index++)                  
    {
        if (items[index].idNum == product_id)                         //searches for the item with the entered ID
        {
            itemIndex = index;                                        // the index is stored in the variable
            break;
        }
    }

    if (itemIndex != -1)
    {
        printf("\nEnter the quantity to add to stock: ");
        scanf("%d", &itemToStock);

        items[itemIndex].stock += itemToStock;

        printf("\nStock updated!!!\n");                                 //stock for the item is updated
    }
    else
    {
        printf("\nItem not found!\n");
    }
}

void addNewItem(struct Inventory items[], int* totalItems)  //this function is to add a new item to the inventory, if space available
{
    if (*totalItems < 10)                                   //checks if the total number of items in the inventory is less than 12
    {
        printf("\nEnter the name of the new item: ");
        scanf("%s", items[*totalItems].itemName);

        printf("\nEnter the ID Number of item: ");
        scanf("%d", &items[*totalItems].idNum);

        printf("\nEnter the price of the item: ");
        scanf("%f", &items[*totalItems].unitCost);

        printf("\nEnter the initial stock quantity: ");
        scanf("%d", &items[*totalItems].stock);

        items[*totalItems].unitsSold = 0;
        items[*totalItems].profit = 0;

        (*totalItems)++;                                     //increases the total number of items in the inventory

        printf("\nNew item is added to inventory!\n");
    }
    else
    {
        printf("\nNot able to add the new item!! Inventory is full...\n");
    }
}

void saveStockData(struct Inventory items[], int totalItems)  //this function is responsible for exporting the stock data of items to a text file
{
    FILE* file = fopen("AddDatatoStock.txt", "wb");            //open existing binary file, for writing
    if (file != NULL)                                         //checks if the file was successfully opened
    {
        fprintf(file, "%d\n", totalItems);                    //writes the total number of items to the file 

        for (int index = 0; index < totalItems; index++)
        {
            fprintf(file, "%s %d %.2f %d %d %.2f\n", items[index].itemName, items[index].idNum, items[index].unitCost, items[index].stock, items[index].unitsSold, items[index].profit);        //writes details to the file
        }
        fclose(file);
    }
    else
    {
        printf("\nFailed to export the stock data.\n");
    }
}

void loadStockData(struct Inventory items[], int* totalItems)       //function is responsible for importing stock data from a text file
{
    FILE* file = fopen("AddDatatoStock.txt", "rb");                  //open an existing binary file for reading
    if (file != NULL)
    {
        fscanf(file, "%d", totalItems);                             //reads the total number of items from the file
        for (int index = 0; index < *totalItems; index++)
        {
            fscanf(file, "%s %d %f %d %d %f", items[index].itemName, &items[index].idNum, &items[index].unitCost, &items[index].stock, &items[index].unitsSold, &items[index].profit);                                          //reads its detail from the file
        }
        fclose(file);
        printf("\nStock data loaded!!\n");
    }
    else
    {
        printf("\nNo existing stock data found.\n");
    }
}
