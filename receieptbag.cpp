#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

template <typename T>
class ReceiptBag {
public:
    using receipt_type = int;

    ReceiptBag() : next_receipt_id(1) {}

    receipt_type insert(const T& item) {
        items.push_back(item);
        receipts.push_back(next_receipt_id);
        return next_receipt_id++;
    }

    T remove(receipt_type receipt) {
        for (size_t i = 0; i < receipts.size(); ++i) {
            if (receipts[i] == receipt) {
                T removed_item = items[i];
                items.erase(items.begin() + i);
                receipts.erase(receipts.begin() + i);
                return removed_item;
            }
        }
        throw std::out_of_range("Receipt not found.");
    }

    bool empty() const {
        return items.empty();
    }

    size_t size() const {
        return items.size();
    }

private:
    std::vector<T> items;
    std::vector<receipt_type> receipts;
    receipt_type next_receipt_id;
};

int main() {
    ReceiptBag<std::string> shopping_bag;
    std::cout << "Bag is empty: " << (shopping_bag.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Bag size: " << shopping_bag.size() << std::endl;
    std::cout << "---------------------------------" << std::endl;

    auto receipt1 = shopping_bag.insert("Apple");
    std::cout << "Inserted 'Apple' with receipt: " << receipt1 << std::endl;

    auto receipt2 = shopping_bag.insert("Banana");
    std::cout << "Inserted 'Banana' with receipt: " << receipt2 << std::endl;

    auto receipt3 = shopping_bag.insert("Orange");
    std::cout << "Inserted 'Orange' with receipt: " << receipt3 << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::cout << "Current bag size: " << shopping_bag.size() << std::endl;
    std::cout << "---------------------------------" << std::endl;

    try {
        std::string removed_item = shopping_bag.remove(receipt2);
        std::cout << "Removed item with receipt " << receipt2 << ": " << removed_item << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "New bag size: " << shopping_bag.size() << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    try {
        std::cout << "Attempting to remove with an invalid receipt (100)..." << std::endl;
        shopping_bag.remove(100);
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "Bag size: " << shopping_bag.size() << std::endl;

    std::cout << "---------------------------------" << std::endl;

    try {
        std::cout << "Attempting to remove with the already-used receipt (" << receipt2 << ")..." << std::endl;
        shopping_bag.remove(receipt2);
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "Bag size: " << shopping_bag.size() << std::endl;

    return 0;
}
