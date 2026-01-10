// design the bird
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct IMovement
{
    virtual void mmove() = 0;
    virtual ~IMovement() {}
};

struct Walkable : IMovement
{
    void mmove() override { cout << "Walking..\n"; }
    virtual ~Walkable()
    {
        cout << "IWalkable destructor called\n";
    }
};

struct Flyable : IMovement
{
    void mmove() override { cout << "Flying..\n"; }
    virtual ~Flyable()
    {
        cout << "IFlyable destructor called\n";
    }
};

struct Swimmable : IMovement
{
    void mmove() override { cout << "Swimming..\n"; }
    virtual ~Swimmable()
    {
        cout << "Iswimmable destructor\n";
    }
};

class Bird
{
protected:
    string name;
    int age;
    string color;
    vector<unique_ptr<IMovement>> movements;

public:
    Bird(string nm, int ag, string col, vector<unique_ptr<IMovement>> mm) : name(nm), age(ag), color(col), movements(std::move(mm)) {}

    static unique_ptr<Bird> createBird(string nm, int ag, string col, vector<unique_ptr<IMovement>> mm);
    void performMovement()
    {
        for (auto &m : movements)
        {
            m->mmove();
            cout << endl;
        }
    }
    void getInfo()
    {
        cout << "Name : " << name << "\nAge: " << age << "\nColor : " << color << endl;
    }
    virtual ~Bird()
    {
        cout << "Bird Destructor\n";
    }
};

unique_ptr<Bird> Bird::createBird(string nm, int ag, string col, vector<unique_ptr<IMovement>> mm)
{
    return make_unique<Bird>(nm, ag, col, std::move(mm));
}

int main()
{
    vector<unique_ptr<IMovement>> sparrow_mvmt;
    sparrow_mvmt.push_back(make_unique<Flyable>());
    auto sparrow = Bird::createBird("sparrow", 3, "brown feather", std::move(sparrow_mvmt));

    sparrow->performMovement();
    sparrow->getInfo();
    // delete sparrow;

    cout << "--------------\n";

    vector<unique_ptr<IMovement>> duck_mvmt;
    duck_mvmt.push_back(make_unique<Flyable>());
    duck_mvmt.push_back(make_unique<Swimmable>());
    auto Duck = Bird::createBird("Duck", 2, "white charm", std::move(duck_mvmt));
    Duck->performMovement();
    Duck->getInfo();
    // delete Duck;

    return 0;
}