#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// ------------------ Base Product Class ------------------
class Product {
protected:
    string name;
    double price;
    string category;

public:
    Product(string n, double p, string c) : name(n), price(p), category(c) {}
    virtual ~Product() {}

    virtual double getPrice() const {
        return price;
    }

    virtual string getInfo() const {
        return name + " (" + category + ") - ₹" + to_string(price);
    }
};

// ------------------ Derived Product Types ------------------
class Electronics : public Product {
    int warrantyYears;

public:
    Electronics(string n, double p, int w)
        : Product(n, p, "Electronics"), warrantyYears(w) {}
};

class Clothing : public Product {
    string size;

public:
    Clothing(string n, double p, string s)
        : Product(n, p, "Clothing"), size(s) {}
};

class Grocery : public Product {
    string expiryDate;

public:
    Grocery(string n, double p, string e)
        : Product(n, p, "Grocery"), expiryDate(e) {}
};

// ------------------ Discount Strategy Interface ------------------
class DiscountStrategy {
public:
    virtual double applyDiscount(const Product* product) const = 0;
    virtual ~DiscountStrategy() {}
};

class SeasonalDiscount : public DiscountStrategy {
public:
    double applyDiscount(const Product* product) const override {
        return product->getPrice() * 0.90; // 10% off
    }
};

class ClearanceDiscount : public DiscountStrategy {
public:
    double applyDiscount(const Product* product) const override {
        return product->getPrice() * 0.50; // 50% off
    }
};

// ------------------ Inventory Manager ------------------
class InventoryManager {
    vector<shared_ptr<Product>> products;

public:
    void addProduct(shared_ptr<Product> product) {
        products.push_back(product);
    }

    void applyDiscount(const DiscountStrategy& strategy) const {
        for (const auto& product : products) {
            double discountedPrice = strategy.applyDiscount(product.get());
            cout << product->getInfo() << " → Discounted Price: ₹" << discountedPrice << "\n";
        }
    }
};

// ------------------ Main Function ------------------
int main() {
    InventoryManager manager;

    manager.addProduct(make_shared<Electronics>("Laptop", 60000, 2));
    manager.addProduct(make_shared<Clothing>("T-Shirt", 1000, "M"));
    manager.addProduct(make_shared<Grocery>("Rice", 800, "2025-06-01"));

    cout << "\n-- Applying Seasonal Discount --\n";
    SeasonalDiscount seasonal;
    manager.applyDiscount(seasonal);

    cout << "\n-- Applying Clearance Discount --\n";
    ClearanceDiscount clearance;
    manager.applyDiscount(clearance);

    return 0;
}
