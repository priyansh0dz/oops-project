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
    static int count;
    Product() { id = 0; name = "None"; price = 0; stock = 0; count++; }
    Product(int i, string n, double p, int s) { id = i; name = n; price = p; stock = s; count++; }
    ~Product() { count--; }
    void display() { cout << id << " | " << name << " | Rs." << price << " | Stock: " << stock << endl; }
    int getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getStock() { return stock; }
    void reduceStock(int q) { stock -= q; }
    friend void showProductCount();
};
int Product::count = 0;

void showProductCount() { cout << "\nTotal Products: " << Product::count << endl; }

class User {
protected:
    string username;
public:
    virtual void menu() = 0;
};

class Admin : public User {
public:
    Admin() { username = "Admin"; }
    void menu() override { cout << "\nAdmin Menu\n"; }
    void addProduct(Product* products[], int &size) {
        if (size >= 50) { cout << "List full!\n"; return; }
        int id, stock; string name; double price;
        cout << "Enter ID: "; cin >> id;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Price: "; cin >> price;
        cout << "Enter Stock: "; cin >> stock;
        products[size++] = new Product(id, name, price, stock);
        cout << "Product Added!\n";
    }
};

class Customer : public User {
public:
    Customer() { username = "Customer"; }
    void menu() override { cout << "\nCustomer Menu\n"; }
};

class Cart {
    Product* items[20];
    int count;
public:
    Cart() { count = 0; }
    void addProduct(Product* p) {
        if (count < 20) items[count++] = p;
        else cout << "Cart Full!\n";
    }
    double total() {
        double sum = 0;
        for (int i = 0; i < count; i++) sum += items[i]->getPrice();
        return sum;
    }
    void show() {
        if (count == 0) cout << "Cart Empty!\n";
        else {
            for (int i = 0; i < count; i++) items[i]->display();
            cout << "Total: Rs." << total() << endl;
        }
    }
};

template <typename T>
T applyDiscount(T amount, T discount) {
    return amount - (amount * discount / 100);
}

bool operator>(Product &a, Product &b) {
    return a.getPrice() > b.getPrice();
}

void saveProducts(Product* products[], int size) {
    ofstream fout("products.txt");
    for (int i = 0; i < size; i++)
        fout << products[i]->getID() << " "
             << products[i]->getName() << " "
             << products[i]->getPrice() << " "
             << products[i]->getStock() << endl;
    fout.close();
}

void loadProducts(Product* products[], int &size) {
    ifstream fin("products.txt");
    if (!fin) return;
    int id, stock; string name; double price;
    while (fin >> id >> name >> price >> stock && size < 50)
        products[size++] = new Product(id, name, price, stock);
    fin.close();
}

int main() {
    Product* products[50];
    int productCount = 0;
    loadProducts(products, productCount);

    Cart cart;
    Admin admin;
    Customer cust;

    int choice;
    while (true) {
        cout << "\n ONLINE SHOPPING SYSTEM \n";
        cout << "1. Admin Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Add to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Checkout\n";
        cout << "6. Compare Two Products\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                admin.menu();
                admin.addProduct(products, productCount);
                saveProducts(products, productCount);
            }
            else if (choice == 2) {
                cust.menu();
                for (int i = 0; i < productCount; i++)
                    products[i]->display();
                showProductCount();
            }
            else if (choice == 3) {
                int pid; cout << "Enter Product ID: "; cin >> pid;
                bool found = false;
                for (int i = 0; i < productCount; i++) {
                    if (products[i]->getID() == pid) {
                        cart.addProduct(products[i]);
                        products[i]->reduceStock(1);
                        found = true;
                        break;
                    }
                }
                if (!found) throw runtime_error("Product not found!");
            }
            else if (choice == 4) {
                cart.show();
            }
            else if (choice == 5) {
                double total = cart.total();
                double discounted = applyDiscount(total, 10.0);
                cout << "\nCheckout: Rs." << total << " -> After 10% Discount: Rs." << discounted << endl;
            }
            else if (choice == 6) {
                int id1, id2;
                cout << "Enter two Product IDs to compare: ";
                cin >> id1 >> id2;
                Product *p1 = nullptr, *p2 = nullptr;
                for (int i = 0; i < productCount; i++) {
                    if (products[i]->getID() == id1) p1 = products[i];
                    if (products[i]->getID() == id2) p2 = products[i];
                }
                if (p1 && p2) {
                    if (*p1 > *p2)
                        cout << p1->getName() << " is costlier.\n";
                    else
                        cout << p2->getName() << " is costlier.\n";
                } else throw runtime_error("Invalid product IDs!");
            }
            else if (choice == 7) {
                cout << "Exiting...\n";
                break;
            }
            else {
                throw invalid_argument("Invalid Choice!");
            }
        }
        catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    for (int i = 0; i < productCount; i++) delete products[i];
    return 0;
}

