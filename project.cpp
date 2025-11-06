#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    int id;
    string name;
    float price;

    Product() {}
    Product(int i, string n, float p) {
        id = i;
        name = n;
        price = p;
    }

    void display() {
        cout << id << "  " << name << "  Rs." << price << endl;
    }
};

class Cart {
public:
    Product items[10];  
    int itemCount;

    Cart() {
        itemCount = 0;
    }

    void addProduct(Product p) {
        if (itemCount < 10) {
            items[itemCount] = p;
            itemCount++;
            cout << p.name << " added to cart!" << endl;
        } else {
            cout << "Cart full! Cannot add more items.\n";
        }
    }

    void showCart() {
        if (itemCount == 0) {
            cout << "Cart is empty!\n";
            return;
        }

        cout << "\nYour Cart:\n";
        float total = 0;
        for (int i = 0; i < itemCount; i++) {
            items[i].display();
            total += items[i].price;
        }
        cout << "\nTotal = Rs." << total << endl;
    }
};


int main() {
    Product products[5] = {
        Product(1, "Shirt", 599),
        Product(2, "Jeans", 899),
        Product(3, "Shoes", 1299),
        Product(4, "Watch", 999),
        Product(5, "Cap", 299)
    };

    Cart cart;
    int choice;

    do {
        cout << "\n Online Shopping Menu \n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            for (int i = 0; i < 5; i++)
                products[i].display();
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Product ID to add: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < 5; i++) {
                if (products[i].id == id) {
                    cart.addProduct(products[i]);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid Product ID!\n";
        }
        else if (choice == 3) {
            cart.showCart();
        }
        else if (choice == 4) {
            cout << "Thank you for shopping! \n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
