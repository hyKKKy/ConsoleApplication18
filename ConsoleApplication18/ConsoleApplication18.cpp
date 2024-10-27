#include <iostream>
#include <string>
#include <fstream>

class Company
{
public:
    Company() : name("empty"), owner("empty"), phoneNumber("empty"), address("empty"), occupation("empty") {}

    Company(const std::string& name, const std::string& owner, const std::string& phoneNumber, const std::string& address, const std::string& occupation)
        : name(name), owner(owner), phoneNumber(phoneNumber), address(address), occupation(occupation)
    {
    }

    std::string getName() const { return name; }
    std::string getOwner() const { return owner; }
    std::string getPhone() const { return phoneNumber; }
    std::string getAddress() const { return address; }
    std::string getOccupation() const { return occupation; }

    void print() const {
        std::cout << "The name of company is: " << name << "\n"
            << "The owner of company is: " << owner << "\n"
            << "The phone number of company is: " << phoneNumber << "\n"
            << "The address of company is: " << address << "\n"
            << "The occupation of company is: " << occupation << "\n";
    }

    void saveCompanyToFile(std::ofstream& outFile) const {
        if (outFile.is_open()) {
            outFile << name << "\n"
                << owner << "\n"
                << phoneNumber << "\n"
                << address << "\n"
                << occupation << "\n"
                << "----------------------\n";
        }
    }

    static Company loadFromFile(std::ifstream& file) {
        std::string name, owner, phoneNumber, address, occupation;

        getline(file, name);
        getline(file, owner);
        getline(file, phoneNumber);
        getline(file, address);
        getline(file, occupation);
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        return Company(name, owner, phoneNumber, address, occupation);
    }

private:
    std::string name;
    std::string owner;
    std::string phoneNumber;
    std::string address;
    std::string occupation;
};

class Dictionary {
public:
    Dictionary() : size(0), capacity(2) {
        companies = new Company * [capacity];
        loadFromFile();
    }

    ~Dictionary() {
        for (int i = 0; i < size; i++) {
            delete companies[i];
        }
        delete[] companies;
    }

    void addCompany(const Company& company) {
        if (size == capacity) {
            resize();
        }
        companies[size++] = new Company(company);
        std::cout << "Company has successfully been added!" << std::endl;
        saveToFile();
    }

    void searchByName(const std::string& name) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (companies[i]->getName() == name) {
                companies[i]->print();
                std::cout << "------------------" << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Nothing is found." << std::endl;
        }
    }

    void searchByOwner(const std::string& owner) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (companies[i]->getOwner() == owner) {
                companies[i]->print();
                std::cout << "------------------" << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Nothing is found." << std::endl;
        }
    }

    void searchByPhoneNumber(const std::string& phonenumber) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (companies[i]->getPhone() == phonenumber) {
                companies[i]->print();
                std::cout << "------------------" << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Nothing is found." << std::endl;
        }
    }

    void searchByOccupation(const std::string& occupation) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (companies[i]->getOccupation() == occupation) {
                companies[i]->print();
                std::cout << "------------------" << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Nothing is found." << std::endl;
        }
    }

    void printAll() const {
        if (size == 0) {
            std::cout << "Dictionary is empty!" << std::endl;
        }
        else {
            for (int i = 0; i < size; i++) {
                companies[i]->print();
                std::cout << "------------------" << std::endl;
            }
        }
    }

private:
    Company** companies;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Company** newCompanies = new Company * [capacity];
        for (int i = 0; i < size; i++) {
            newCompanies[i] = companies[i];
        }
        delete[] companies;
        companies = newCompanies;
    }

    void saveToFile() {
        std::ofstream file("companies.txt", std::ios::app); 
        if (!file) {
            std::cerr << "Error: File could not be opened for saving!" << std::endl;
            return;
        }
        companies[size - 1]->saveCompanyToFile(file);
    }

    void loadFromFile() {
        std::ifstream file("companies.txt");
        if (!file) {
            std::cerr << "File could not be opened for loading!" << std::endl;
            return;
        }

        while (file.peek() != EOF) {
            Company company = Company::loadFromFile(file);
            if (size == capacity) {
                resize();
            }
            companies[size++] = new Company(company);
        }
    }
};

int main() {
    Dictionary d1;
    int user_choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Add company\n"
            << "2. Search by name\n"
            << "3.  Search by owner\n"
            << "4.  Search by phone number\n"
            << "5.  Search by occupation\n"
            << "6.  Print all\n"
            << "0. Exit\n"
            << "Enter your choice: ";
        std::cin >> user_choice;

        switch (user_choice) {
        case 1: {
            std::string name, owner, phone, address, occupation;
            std::cout << "Enter company name: ";
            std::cin >> name;
            std::cout << "Enter owner name: ";
            std::cin >> owner;
            std::cout << "Enter phone number: ";
            std::cin >> phone;
            std::cout << "Enter address: ";
            std::cin >> address;
            std::cout << "Enter occupation: ";
            std::cin >> occupation;

            d1.addCompany(Company(name, owner, phone, address, occupation));
            break;
        }
        case 2: {
            std::string name;
            std::cout << "Enter name to search: ";
            std::cin >> name;
            d1.searchByName(name);
            break;
        }
        case 3: {
            std::string owner;
            std::cout << "Enter owner to search: ";
            std::cin >> owner;
            d1.searchByOwner(owner);
            break;
        }
        case 4: {
            std::string phonenumber;
            std::cout << "Enter phone number to search: ";
            std::cin >> phonenumber;
            d1.searchByPhoneNumber(phonenumber);
            break;
        }
        case 5: {
            std::string occupation;
            std::cout << "Enter occupation to search: ";
            std::cin >> occupation;
            d1.searchByOccupation(occupation);
            break;
        }
        case 6:
            d1.printAll();
            break;
        case 0:
            break;
        default:
            std::cout << "Wrong input!" << std::endl;
            break;
        }
    } while (user_choice != 0);
}