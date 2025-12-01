// Display inventory after insertion (for verification) 

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure to store product details
struct Product {
    string sku;
    string name;
    int quantity;
};

// Global inventory vector
vector<Product> inventory;

// Function to check if a string contains only digits
bool isNumeric(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Function to insert a new product
void insertProduct() {
    string sku, name, quantityStr;
    int quantity;
    
    cout << "Enter SKU: ";
    getline(cin, sku);
    
    // Check for duplicate SKU
    for (const auto& item : inventory) {
        if (item.sku == sku) {
            cout << "Product with this SKU already exists!" << endl;
            return;
        }
    }
    
    cout << "Enter Product Name: ";
    getline(cin, name);
    
    // Validate: product name cannot be empty
    if (name.empty()) {
        cout << "Error: Product name cannot be empty." << endl;
        return;
    }
    
    cout << "Enter Quantity: ";
    getline(cin, quantityStr);
    
    // Validate: quantity must be numeric
    if (!isNumeric(quantityStr)) {
        cout << "Invalid input. Quantity must be a number." << endl;
        return;
    }
    
    quantity = stoi(quantityStr);
    
    // Validate: quantity must be positive
    if (quantity < 0) {
        cout << "Error: Quantity must be positive." << endl;
        return;
    }
    
    // Create product and add to inventory
    Product product = {sku, name, quantity};
    inventory.push_back(product);
    cout << "Product inserted successfully." << endl;
}

// Function to display all products in inventory
void displayInventory() {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }
    
    cout << "\nCurrent Inventory:" << endl;
    cout << setw(15) << left << "SKU" 
         << setw(25) << left << "Product Name" 
         << setw(15) << left << "Quantity" << endl;
    cout << "-----------------------------------------------" << endl;
    
    for (const auto& item : inventory) {
        cout << setw(15) << left << item.sku 
             << setw(25) << left << item.name 
             << setw(15) << left << item.quantity << endl;
    }
    cout << endl;
}

// Function to search product by SKU
void searchBySKU() {
    string sku;
    cout << "Enter SKU to search: ";
    getline(cin, sku);
    
    for (const auto& item : inventory) {
        if (item.sku == sku) {
            cout << "\nProduct Found:" << endl;
            cout << "SKU: " << item.sku << endl;
            cout << "Name: " << item.name << endl;
            cout << "Quantity: " << item.quantity << endl;
            return;
        }
    }
    
    cout << "Product with SKU " << sku << " not found." << endl;
}

// Function to search product by Name
void searchByName() {
    string name;
    cout << "Enter Product Name to search: ";
    getline(cin, name);
    
    bool found = false;
    for (const auto& item : inventory) {
        if (item.name == name) {
            if (!found) {
                cout << "\nProducts Found:" << endl;
                found = true;
            }
            cout << "SKU: " << item.sku << ", Name: " << item.name 
                 << ", Quantity: " << item.quantity << endl;
        }
    }
    
    if (!found) {
        cout << "Product with name " << name << " not found." << endl;
    }
}

// Function to update quantity of existing product
void updateQuantity() {
    string sku, quantityStr;
    int newQuantity;
    
    cout << "Enter SKU to update: ";
    getline(cin, sku);
    
    for (auto& item : inventory) {
        if (item.sku == sku) {
            cout << "Current Quantity: " << item.quantity << endl;
            cout << "Enter new Quantity: ";
            getline(cin, quantityStr);
            
            if (!isNumeric(quantityStr)) {
                cout << "Invalid input. Quantity must be a number." << endl;
                return;
            }
            
            newQuantity = stoi(quantityStr);
            
            if (newQuantity < 0) {
                cout << "Error: Quantity must be positive." << endl;
                return;
            }
            
            item.quantity = newQuantity;
            cout << "Quantity updated successfully." << endl;
            return;
        }
    }
    
    cout << "Product with SKU " << sku << " not found." << endl;
}

// Function to delete product by SKU
void deleteProduct() {
    string sku;
    cout << "Enter SKU to delete: ";
    getline(cin, sku);
    
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->sku == sku) {
            cout << "Product " << it->name << " removed from inventory." << endl;
            inventory.erase(it);
            return;
        }
    }
    
    cout << "Product with SKU " << sku << " not found." << endl;
}

// Program entry point
int main() {
    int choice;
    
    while (true) {
        cout << "\n========== Inventory Stock Manager ==========" << endl;
        cout << "1. Insert New Product" << endl;
        cout << "2. Display Inventory" << endl;
        cout << "3. Search Product by SKU" << endl;
        cout << "4. Search Product by Name" << endl;
        cout << "5. Update Product Quantity" << endl;
        cout << "6. Delete Product" << endl;
        cout << "7. Exit" << endl;
        cout << "============================================" << endl;
        cout << "Enter your choice (1-7): ";
        
        string input;
        getline(cin, input);
        
        if (!isNumeric(input)) {
            cout << "Invalid choice. Please select from 1 to 7." << endl;
            continue;
        }
        
        choice = stoi(input);
        
        switch (choice) {
            case 1:
                insertProduct();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                searchBySKU();
                break;
            case 4:
                searchByName();
                break;
            case 5:
                updateQuantity();
                break;
            case 6:
                deleteProduct();
                break;
            case 7:
                cout << "Exiting Inventory Manager." << endl;
                break;
            default:
                cout << "Invalid choice. Please select from 1 to 7." << endl;
        }
    }
    
    return 0;
}7