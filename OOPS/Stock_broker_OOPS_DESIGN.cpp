#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Class representing individual stocks
class Stock
{
public:
    string symbol; // Stock symbol (e.g., AAPL for Apple)
    double price;  // Current price of the stock
    Stock(string symbol, double price) : symbol(symbol), price(price) {}
};

// Wallet class to handle adding and withdrawing balance
class Wallet
{
private:
    double balance;

public:
    Wallet() : balance(0.0) {}

    // Add funds to the wallet
    void addBalance(double amount)
    {
        balance += amount;
        cout << "Added Rs." << amount << " to wallet. Current balance: Rs." << balance << endl;
    }

    // Withdraw funds from the wallet (if enough balance)
    bool withdrawBalance(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrew Rs." << amount << " from wallet. Current balance: Rs." << balance << endl;
        return true;
    }

    // Show wallet balance
    void showBalance() const
    {
        cout << "Current wallet balance: Rs." << balance << endl;
    }
};

// Portfolio class to manage stocks bought by the user
class Portfolio
{
private:
    unordered_map<string, int> holdings; // Maps stock symbol to quantity

public:
    // Buy a stock (add to holdings)
    void buyStock(const Stock &stock, int quantity)
    {
        holdings[stock.symbol] += quantity;
        cout << "Bought " << quantity << " shares of " << stock.symbol << endl;
    }

    // Sell a stock (remove from holdings)
    bool sellStock(const Stock &stock, int quantity)
    {
        if (holdings[stock.symbol] < quantity)
        {
            cout << "Not enough shares to sell!" << endl;
            return false;
        }
        holdings[stock.symbol] -= quantity;
        if (holdings[stock.symbol] == 0)
        {
            holdings.erase(stock.symbol); // Remove stock from portfolio if all shares are sold
        }
        cout << "Sold " << quantity << " shares of " << stock.symbol << endl;
        return true;
    }

    // Show current portfolio
    void showPortfolio() const
    {
        if (holdings.empty())
        {
            cout << "Portfolio is empty." << endl;
            return;
        }

        cout << "Current portfolio:" << endl;
        for (const auto &holding : holdings)
        {
            cout << holding.first << ": " << holding.second << " shares" << endl;
        }
    }
};

// Demat Account class for holding user info and managing wallet and portfolio
class Account
{
private:
    string accountHolderName;
    string accountNumber;
    Wallet wallet;
    Portfolio portfolio;

public:
    Account(string name, string accNum) : accountHolderName(name), accountNumber(accNum) {}

    // Add funds to the wallet
    void addFunds(double amount)
    {
        wallet.addBalance(amount);
    }

    // Withdraw funds from the wallet
    bool withdrawFunds(double amount)
    {
        return wallet.withdrawBalance(amount);
    }

    // Buy stock if enough balance
    bool buyStock(const Stock &stock, int quantity)
    {
        double totalCost = stock.price * quantity;
        if (wallet.withdrawBalance(totalCost))
        {
            portfolio.buyStock(stock, quantity);
            return true;
        }
        return false;
    }

    // Sell stock and add funds to wallet
    bool sellStock(const Stock &stock, int quantity)
    {
        if (portfolio.sellStock(stock, quantity))
        {
            double totalSale = stock.price * quantity;
            wallet.addBalance(totalSale);
            return true;
        }
        return false;
    }

    // Show portfolio of an account
    void showPortfolio() const
    {
        portfolio.showPortfolio();
    }

    // Show wallet balance
    void showBalance() const
    {
        wallet.showBalance();
    }
};

// StockBroker class to manage user accounts and stock trading
class StockBroker
{
private:
    unordered_map<string, Account *> accounts;   // Maps account number to account
    unordered_map<string, Stock *> listedStocks; // Maps stock symbol to Stock object

public:
    StockBroker()
    {
        // Initialize with some predefined stocks (e.g., NIFTY 50)
        listedStocks["RELIANCE"] = new Stock("RELIANCE", 2500.0);
        listedStocks["TCS"] = new Stock("TCS", 3500.0);
        listedStocks["INFY"] = new Stock("INFY", 1500.0);
        listedStocks["HDFCBANK"] = new Stock("HDFCBANK", 1600.0);
        listedStocks["HDFC"] = new Stock("HDFC", 2700.0);
        listedStocks["ICICIBANK"] = new Stock("ICICIBANK", 700.0);
        listedStocks["KOTAKBANK"] = new Stock("KOTAKBANK", 1800.0);
        listedStocks["SBIN"] = new Stock("SBIN", 450.0);
        // Add more stocks as needed
    }

    ~StockBroker()
    {
        // Cleanup dynamically allocated memory
        for (auto &account : accounts)
        {
            delete account.second;
        }
        for(auto &stock : listedStocks){
            delete stock.second;
        }
    }

    // Create a new account
    void createAccount(string name, string accNum)
    {
        if (accounts.find(accNum) != accounts.end())
        {
            cout << "Account already exists!" << endl;
            return;
        }
        accounts[accNum] = new Account(name, accNum);
        cout << "Account created for " << name << " with account number " << accNum << endl;
    }

    // Add funds to an account
    void addFundsToAccount(string accNum, double amount)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        accounts[accNum]->addFunds(amount);
    }

    // Withdraw funds from an account
    void withdrawFundsFromAccount(string accNum, double amount)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        accounts[accNum]->withdrawFunds(amount);
    }

    // Buy stock for an account
    void buyStockForAccount(string accNum, const string &symbol, int quantity)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        if (listedStocks.find(symbol) == listedStocks.end())
        {
            cout << "Stock not listed!" << endl;
            return;
        }
        accounts[accNum]->buyStock(*listedStocks[symbol], quantity);
    }

    // Sell stock for an account
    void sellStockForAccount(string accNum, const string &symbol, int quantity)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        if (listedStocks.find(symbol) == listedStocks.end())
        {
            cout << "Stock not listed!" << endl;
            return;
        }
        accounts[accNum]->sellStock(*listedStocks[symbol], quantity);
    }

    // Show portfolio of an account
    void showPortfolio(string accNum)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        accounts[accNum]->showPortfolio();
    }

    // Show wallet balance of an account
    void showBalance(string accNum)
    {
        if (accounts.find(accNum) == accounts.end())
        {
            cout << "Account not found!" << endl;
            return;
        }
        accounts[accNum]->showBalance();
    }
    void displayListedStocks()
    {
        for (auto &stock : listedStocks)
        {
            cout << stock.first << endl;
        }
    }
};

// Menu class to interact with the user
class Menu
{
private:
    StockBroker broker;

public:
    void displayMenu()
    {
        int choice;
        do
        {
            cout << "\n=== Stock Broker Menu ===" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Add Funds to Account" << endl;
            cout << "3. Withdraw Funds from Account" << endl;
            cout << "4. Buy Stock" << endl;
            cout << "5. Sell Stock" << endl;
            cout << "6. Show Portfolio" << endl;
            cout << "7. Show Wallet Balance" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            string accNum, name, symbol;
            double amount;
            int quantity;

            switch (choice)
            {
            case 1:
                cin.ignore(); // Clear buffer before getline
                cout << "Enter account holder name: ";
                getline(cin, name);
                cout << "Enter account number: ";
                getline(cin, accNum);
                broker.createAccount(name, accNum);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount to add: ";
                cin >> amount;
                broker.addFundsToAccount(accNum, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                broker.withdrawFundsFromAccount(accNum, amount);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> accNum;
                broker.displayListedStocks();
                cout << "Enter stock symbol to buy: ";
                cin >> symbol;
                cout << "Enter quantity to buy: ";
                cin >> quantity;
                broker.buyStockForAccount(accNum, symbol, quantity);
                break;
            case 5:
                cout << "Enter account number: ";
                cin >> accNum;
                broker.displayListedStocks();
                cout << "Enter stock symbol to sell: ";
                cin >> symbol;
                cout << "Enter quantity to sell: ";
                cin >> quantity;
                broker.sellStockForAccount(accNum, symbol, quantity);
                break;
            case 6:
                cout << "Enter account number: ";
                cin >> accNum;
                broker.showPortfolio(accNum);
                break;
            case 7:
                cout << "Enter account number: ";
                cin >> accNum;
                broker.showBalance(accNum);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        } while (choice != 0);
    }
};

// Main function to start the program
int main()
{
    Menu menu;
    menu.displayMenu();
    return 0;
}
