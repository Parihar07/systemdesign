class Base
{
protected:
    int prot = 10;
};

// 1. Public Inheritance (most common)
class D1 : public Base
{
    // prot stays protected in D1
    void test() { prot = 20; } // ✅ OK
};

// 2. Protected Inheritance (rare)
class D2 : protected Base
{
    // prot stays protected in D2
    void test() { prot = 30; } // ✅ OK
};

// 3. Private Inheritance
class D3 : private Base
{
    // prot becomes private in D3
    void test() { prot = 40; } // ✅ OK
};

// Further inheritance:
class D1Child : public D1
{
    void test() { prot = 50; } // ✅ OK: still protected
};

class D3Child : public D3
{
    void test()
    {
        // prot = 60;  // ❌ ERROR: became private in D3
    }
};