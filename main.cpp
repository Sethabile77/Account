#include <iostream>
#include <string>
using namespace std;

class Account
{
private:
    float balance;
    string pin;
    string owner;

public:
    Account(float amount, string pinCode, string owner) : balance(amount), pin(pinCode), owner(owner)
    {
    }
    ~Account()
    {
    }
    string getPin()
    {
        return pin;
    }
    void setBalance(float i)
    {
        balance = i;
    }
    float getBalance()
    {
        return balance;
    }
    virtual string encrypt(string proctect);
    virtual Account &operator+=(float amount) = 0;

    virtual Account &operator-=(float amount) = 0;
};
string Account::encrypt(string protect)
{
    cout << "The account is encrypted." << endl;
    return protect + pin;
}

class CreditAccount : public Account
{
private:
    float creditLimit;

public:
    CreditAccount(float amount, string pinCode, string owner, float limit) : Account(amount, pinCode, owner), creditLimit(limit)
    {
    }
    ~CreditAccount()
    {
    }
    virtual CreditAccount &operator+=(float amount);
    virtual CreditAccount &operator-=(float amount);

    virtual string encrypt(string proctect);
};
CreditAccount &CreditAccount::operator+=(float amount)
{
    float temp = getBalance();

    if (amount > 0)
    {
        cout << "Successful deposit into Credit account. " << endl;
        setBalance(temp += amount);
    }
    else
    {
        cout << "Not sucessful" << endl;
    }
    return *this;
}
CreditAccount &CreditAccount::operator-=(float amount)
{
    float temp = getBalance();
    float current = temp - amount;
    if (temp > amount)
    {
        cout << "Transation successful. Sufficient funds." << endl;
        setBalance(temp -= amount);
    }
    else if (current <= creditLimit)
    {
        setBalance(temp -= amount);
        cout << "Transation sucessful " << "you have " << getBalance() << " rand/s as your balance" << endl;
    }
    else
    {
        cout << "DENIED: Amount greater than credit limit!!" << endl;
    }
    return *this;
}
string CreditAccount::encrypt(string protect)
{
    cout << "The CreditAccount is encrypted." << endl;
    return protect + getPin();
}

class ChequeAccount : public Account
{
private:
    double overdraft;

public:
    ChequeAccount(float amount, string pinCode, string owner, double over) : Account(amount, pinCode, owner), overdraft(over)
    {
    }
    ~ChequeAccount()
    {
    }
    virtual ChequeAccount &operator+=(float amount);

    virtual ChequeAccount &operator-=(float amount);

    virtual string encrypt(string proctect);
};
string ChequeAccount::encrypt(string protect)
{
    cout << "The ChequeAccount is encrypted." << endl;
    return protect + getPin();
}
ChequeAccount &ChequeAccount::operator-=(float amount)
{
    float temp = getBalance();
    float current = temp - amount;
    if (temp > amount)
    {
        cout << "Transation successfu. Sufficient funds." << endl;
        setBalance(temp -= amount);
    }

    else if (current < overdraft)
    {
        setBalance(temp -= amount);
        cout << "Transation sucessful. You have  " << getBalance() << " rand/s  as your balance." << endl;
    }
    else
    {
        cout << "DENIED: Amount greater than overdraft!!" << endl;
    }
    return *this;
}
ChequeAccount &ChequeAccount::operator+=(float amount)
{
    float temp = getBalance();

    if (amount > 0)
    {
        setBalance(temp += amount);
        cout << "Successful deposit into Cheque account. " << endl;
    }
    else
    {
        cout << "Not sucessful" << endl;
    }
    return *this;
}

int main()
{
    cout << "Testing starting" << endl;
    cout << endl;
    string pinC;
    cout << "Please Enter your Pin : ";
    cin >> pinC;
    ChequeAccount cheque(10, pinC, "John", 500.50);
    CreditAccount credit(70, "2345", "John", 100.09f);
    // cheque.setBalance(2000);
    // credit.setBalance(2000);
    cheque -= 200;
    cheque.encrypt(pinC);
    cout << endl;
    credit -= 80;
    cheque += 300;
    credit += 4000;
    credit -= 20;
}