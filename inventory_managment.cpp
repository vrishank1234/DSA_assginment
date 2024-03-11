#include <iostream>
#include <string> 
using namespace std;

struct Product {
    int product_id;
    string name;
    int quantity;
};

void displayInventory(const Product inventory[], int numProducts) {
    cout << "Current Inventory:" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < numProducts; ++i) {
        cout << "Product ID: " << inventory[i].product_id << ", Name: " << inventory[i].name<< ", Quantity: " << inventory[i].quantity << endl;
    }

    cout << "------------------" << endl;
}

void addProduct(Product*& inventory, int& numProducts, int productId, string productName, int quantity) {
    for (int i = 0; i < numProducts; ++i) {
        if (inventory[i].product_id == productId) {
            inventory[i].quantity += quantity;
            cout << "Quantity added to existing product (ID: " << productId << "). New Quantity: " << inventory[i].quantity << endl;
            return;
        }
    }

    inventory = (Product*)realloc(inventory, (numProducts + 1) * sizeof(Product));

    if (inventory != nullptr) {
        inventory[numProducts].product_id = productId;
        inventory[numProducts].name = productName;
        inventory[numProducts].quantity = quantity;
        numProducts++;
        cout << "Product added to the inventory (ID: " << productId << ")." << endl;
    } else {
        cout << "Memory reallocation failed. Cannot add more products." << endl;
    }
}

void updateQuantity(Product inventory[], int numProducts) {
    int productId;
    int quantity;
    char task;

    cout << "Enter Product ID: ";
    cin >> productId;

    for (int i = 0; i < numProducts; ++i) {
        if (inventory[i].product_id == productId) {
            cout << "Do you want to perform addition (+) or deletion (-)? ";
            cin >> task;

            cout << "Enter quantity: ";
            cin >> quantity;

            if (task == '+') {
                inventory[i].quantity += quantity;
                cout << "Quantity added. New Quantity: " << inventory[i].quantity << endl;
            } else if (task == '-') {
                if (inventory[i].quantity >= quantity) {
                    inventory[i].quantity -= quantity;
                    cout << "Quantity subtracted. New Quantity: " << inventory[i].quantity << endl;
                } else {
                    cout << "Error: Cannot subtract more quantity than available." << endl;
                }
            } else {
                cout << "Invalid task. Please enter '+' for addition or '-' for deletion." << endl;
            }
            return;
        }
    }

    cout << "Product not found in the inventory (ID: " << productId << ")." << endl;
}

void deleteProduct(Product*& inventory, int& numProducts, int productId) {
    for (int i = 0; i < numProducts; ++i) {
        if (inventory[i].product_id == productId) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < numProducts - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }

            // Decrease the number of products
            numProducts--;

            // Resize the array
            inventory = (Product*)realloc(inventory, numProducts * sizeof(Product));

            cout << "Product deleted from the inventory (ID: " << productId << ")." << endl;
            return;
        }
    }

    cout << "Product not found in the inventory (ID: " << productId << ")." << endl;
}

void checkLowStock(const Product inventory[], int numProducts, int lowStockThreshold) {
    cout << "Low Stock Alert:" << endl;
    cout << "-----------------" << endl;

    for (int i = 0; i < numProducts; ++i) {
        if (inventory[i].quantity < lowStockThreshold) {
            cout << "Product ID: " << inventory[i].product_id << ", Name: " << inventory[i].name<< " is running low on stock. Current Quantity: " << inventory[i].quantity << endl;
        }
    }

    cout << "-----------------" << endl;
}

int main() {
    Product* inventory = nullptr;
    int numProducts = 0;

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Display Inventory" << endl;
        cout << "2. Add Product" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. Check Low Stock" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        int productId, quantity;
        string productName;
        switch (choice) {
            case 1:
                displayInventory(inventory, numProducts);
                break;
            case 2:
                
                cout << "Enter Product ID: ";
                cin >> productId;
                cout << "Enter Product Name: ";
                cin.ignore();
                getline(cin, productName);
                cout << "Enter Quantity: ";
                cin >> quantity;
                addProduct(inventory, numProducts, productId, productName, quantity);
                break;
            case 3:
                updateQuantity(inventory, numProducts);
                break;
            case 4:
                int deleteProductId;
                cout << "Enter Product ID to delete: ";
                cin >> deleteProductId;
                deleteProduct(inventory, numProducts, deleteProductId);
                break;
            case 5:
                int lowStockThreshold;
                cout << "Enter Low Stock Threshold: ";
                cin >> lowStockThreshold;
                checkLowStock(inventory, numProducts, lowStockThreshold);
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    // Cleanup: Free allocated memory
    free(inventory);

    return 0;
}