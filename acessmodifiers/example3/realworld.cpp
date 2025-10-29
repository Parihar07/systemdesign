class BankAccount
{
protected:
    double balance = 1000.0;

    void setBalance(double b)
    {
        balance = b;
    }
};

class CheckingAccount : public BankAccount
{
public:
    void deposit(double amount)
    {
        balance += amount; // ✅ OK: accessing own balance
    }

    void transferFrom(CheckingAccount &other, double amount)
    {
        other.balance -= amount; // ✅ OK: other is CheckingAccount
        this->balance += amount;
    }

    // This would be DANGEROUS if allowed:
    void dangerousHack(BankAccount &anyAccount)
    {
        // anyAccount.balance = 0;  // ❌ ERROR: can't access through Base&
        // Good! We shouldn't be able to mess with arbitrary accounts
    }
};

class SavingsAccount : public BankAccount
{
    // Has different rules for withdrawals
};

int main()
{
    CheckingAccount checking;
    SavingsAccount savings;

    // If CheckingAccount could access BankAccount's protected through Base&,
    // it could bypass SavingsAccount's withdrawal rules!
}