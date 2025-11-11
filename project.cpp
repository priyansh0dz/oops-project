#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Product {
    int id;
    string name;
    double price;
    int stock;
public:
    Product() : id(0), name("None"), price(0.0), stock(0) {}
    Product(int pid, string pname, double pprice, int pstock) {
        id = pid;
        name = pname;
        price = pprice;
        stock = pstock;
    }

    void display() const {
        cout << id << " | " << name << " | Rs." << price << " | Stock: " << stock << endl;
    }

    int getID() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void reduceStock(int qty) { stock -= qty; }
};

class Cart {
    Product items[20];
    int count;
public:
    Cart() { count = 0; }

    void addProduct(const Product &p) {
        if (count < 20) {
            items[count++] = p;
            cout << p.getName() << " added to cart!\n";
        } else {
            cout << "Cart is full!\n";
        }
    }

    double getTotal() const {
        double total = 0;
        for (int i = 0; i < count; i++)
            total += items[i].getPrice();
        return total;
    }

    void showCart() const {
        if (count == 0) {
            cout << "\nCart is empty!\n";
            return;
        }
        cout << "\n--- Cart Items ---\n";
        for (int i = 0; i < count; i++)
            items[i].display();
        cout << "Total Amount: Rs." << getTotal() << endl;
    }
};

class Admin {
public:
    void addProduct(Product products[], int &size) {
        if (size >= 50) {
            cout << "Product list full!\n";
            return;
        }
        int id, stock;
        string name;
        double price;
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Stock: ";
        cin >> stock;
        products[size++] = Product(id, name, price, stock);
        cout << "Product added successfully!\n";
    }
};

void saveProducts(Product products[], int size) {
    ofstream fout("products.txt");
    for (int i = 0; i < size; i++)
        fout << products[i].getID() << " "
             << products[i].getName() << " "
             << products[i].getPrice() << " "
             << products[i].getStock() << endl;
    fout.close();
}

void loadProducts(Product products[], int &size) {
    ifstream fin("products.txt");
    if (!fin) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }
    int id, stock;
    string name;
    double price;
    size = 0;
    while (fin >> id >> name >> price >> stock) {
        products[size++] = Product(id, name, price, stock);
    }
    fin.close();
}

int main() {
    Product products[50];
    int productCount = 0;
    loadProducts(products, productCount);

    Cart cart;
    Admin admin;
    int choice;

    while (true) {
        cout << "\n=== ONLINE SHOPPING SYSTEM ===\n";
        cout << "1. Admin Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Add to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Checkout\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            admin.addProduct(products, productCount);
            saveProducts(products, productCount);
        }
        else if (choice == 2) {
            for (int i = 0; i < productCount; i++)
                products[i].display();
        }
        else if (choice == 3) {
            int pid;
            cout << "Enter Product ID to add: ";
            cin >> pid;
            bool found = false;
            for (int i = 0; i < productCount; i++) {
                if (products[i].getID() == pid) {
                    cart.addProduct(products[i]);
                    products[i].reduceStock(1);
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Product not found!\n";
        }
        else if (choice == 4) {
            cart.showCart();
        }
        else if (choice == 5) {
            cout << "\nCheckout complete! Total Bill: Rs." << cart.getTotal() << endl;
        }
        else if (choice == 6) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
