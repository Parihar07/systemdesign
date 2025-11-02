#include <iostream>
using namespace std;

/*
 * VISUAL DEMONSTRATION: vtable and vptr mechanism
 * ================================================
 * This shows EXACTLY how virtual functions work internally
 */

class Shape {
public:
    int id;  // Regular data member
    
    virtual void draw() {
        cout << "Shape::draw()" << endl;
    }
    
    virtual void area() {
        cout << "Shape::area()" << endl;
    }
    
    void regularFunc() {  // NOT virtual
        cout << "Shape::regularFunc()" << endl;
    }
    
    virtual ~Shape() { }
};

class Circle : public Shape {
public:
    double radius;
    
    void draw() override {
        cout << "Circle::draw()" << endl;
    }
    
    void area() override {
        cout << "Circle::area()" << endl;
    }
    
    void regularFunc() {
        cout << "Circle::regularFunc()" << endl;
    }
};

class Rectangle : public Shape {
public:
    double width, height;
    
    void draw() override {
        cout << "Rectangle::draw()" << endl;
    }
    
    void area() override {
        cout << "Rectangle::area()" << endl;
    }
};

void visualizeMemory() {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           VISUAL: HOW vptr AND vtable WORK                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    Circle c;
    Rectangle r;
    
    cout << "\n=== STEP 1: Object Creation ===" << endl;
    cout << "Circle c;      // Creates Circle object" << endl;
    cout << "Rectangle r;   // Creates Rectangle object" << endl;
    
    cout << "\n=== STEP 2: Memory Layout ===" << endl;
    cout << "\nCircle object 'c' in memory:" << endl;
    cout << "┌──────────────────────────────┐  Address: " << &c << endl;
    cout << "│ vptr → Circle's vtable       │  (8 bytes)" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ id (from Shape)              │  (4 bytes)" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ radius (Circle's data)       │  (8 bytes)" << endl;
    cout << "└──────────────────────────────┘" << endl;
    
    cout << "\nRectangle object 'r' in memory:" << endl;
    cout << "┌──────────────────────────────┐  Address: " << &r << endl;
    cout << "│ vptr → Rectangle's vtable    │  (8 bytes)" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ id (from Shape)              │  (4 bytes)" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ width (Rectangle's data)     │  (8 bytes)" << endl;
    cout << "├──────────────────────────────┤" << endl;
    cout << "│ height (Rectangle's data)    │  (8 bytes)" << endl;
    cout << "└──────────────────────────────┘" << endl;
    
    cout << "\n=== STEP 3: vtable Location (ONE per class) ===" << endl;
    cout << "\nCircle's vtable (in read-only memory):" << endl;
    cout << "┌─────────────────────────────┐" << endl;
    cout << "│ [0] → Circle::draw()        │  Function pointer" << endl;
    cout << "│ [1] → Circle::area()        │  Function pointer" << endl;
    cout << "│ [2] → Circle::~Circle()     │  Function pointer" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << "   ↑" << endl;
    cout << "   Circle object's vptr points here" << endl;
    
    cout << "\nRectangle's vtable (in read-only memory):" << endl;
    cout << "┌─────────────────────────────┐" << endl;
    cout << "│ [0] → Rectangle::draw()     │  Function pointer" << endl;
    cout << "│ [1] → Rectangle::area()     │  Function pointer" << endl;
    cout << "│ [2] → Rectangle::~Rectangle│  Function pointer" << endl;
    cout << "└─────────────────────────────┘" << endl;
    cout << "   ↑" << endl;
    cout << "   Rectangle object's vptr points here" << endl;
}

void demonstrateVirtualCall() {
    cout << "\n\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           WHAT HAPPENS DURING VIRTUAL FUNCTION CALL            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    Circle c;
    Shape* s = &c;  // Base pointer to derived object
    
    cout << "\nCode: Shape* s = new Circle();" << endl;
    cout << "      s->draw();" << endl;
    
    cout << "\n=== Runtime Process (Step by Step) ===" << endl;
    cout << "\nStep 1: Compiler sees: s->draw()" << endl;
    cout << "        Compiler knows: draw() is virtual" << endl;
    cout << "        Generates code: 'Look up in vtable'" << endl;
    
    cout << "\nStep 2: At runtime:" << endl;
    cout << "        ┌─────────────────────────────────────┐" << endl;
    cout << "        │ s points to Circle object           │" << endl;
    cout << "        │ Address: " << s << "          │" << endl;
    cout << "        └─────────────────────────────────────┘" << endl;
    cout << "                    ↓" << endl;
    cout << "        ┌─────────────────────────────────────┐" << endl;
    cout << "        │ Circle object:                      │" << endl;
    cout << "        │ vptr → [Circle's vtable]            │" << endl;
    cout << "        └─────────────────────────────────────┘" << endl;
    cout << "                    ↓" << endl;
    cout << "        Follow vptr to Circle's vtable" << endl;
    
    cout << "\nStep 3: Look up 'draw' in vtable:" << endl;
    cout << "        ┌─────────────────────────────────────┐" << endl;
    cout << "        │ Circle's vtable:                    │" << endl;
    cout << "        │ [0] → Circle::draw()  ← Found it!   │" << endl;
    cout << "        │ [1] → Circle::area()                │" << endl;
    cout << "        │ [2] → Circle::~Circle()             │" << endl;
    cout << "        └─────────────────────────────────────┘" << endl;
    
    cout << "\nStep 4: Call the function:" << endl;
    cout << "        Calling: ";
    s->draw();  // Actually calls Circle::draw()
    
    cout << "\n✅ Result: Circle::draw() called (not Shape::draw())" << endl;
}

void showNonVirtualComparison() {
    cout << "\n\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           COMPARISON: Virtual vs Non-Virtual                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    Circle c;
    Shape* s = &c;
    
    cout << "\n=== Virtual Function Call (s->draw()) ===" << endl;
    cout << "Process:" << endl;
    cout << "  1. Look at object's vptr" << endl;
    cout << "  2. Follow to vtable" << endl;
    cout << "  3. Find function pointer" << endl;
    cout << "  4. Call it" << endl;
    cout << "Result: ";
    s->draw();  // Calls Circle::draw()
    
    cout << "\n=== Non-Virtual Function Call (s->regularFunc()) ===" << endl;
    cout << "Process:" << endl;
    cout << "  1. Compiler sees pointer type: Shape*" << endl;
    cout << "  2. Direct call to Shape::regularFunc()" << endl;
    cout << "  3. NO vtable lookup!" << endl;
    cout << "Result: ";
    s->regularFunc();  // Calls Shape::regularFunc() (NOT Circle's!)
}

void showMultipleObjects() {
    cout << "\n\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           MULTIPLE OBJECTS SHARING SAME vtable                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    Circle c1, c2, c3;
    
    cout << "\nCreated 3 Circle objects:" << endl;
    cout << "Circle c1, c2, c3;" << endl;
    
    cout << "\nMemory addresses:" << endl;
    cout << "c1 address: " << &c1 << endl;
    cout << "c2 address: " << &c2 << endl;
    cout << "c3 address: " << &c3 << endl;
    
    cout << "\n╔═══════════════════════════════════════════════════════╗" << endl;
    cout << "║  KEY INSIGHT:                                         ║" << endl;
    cout << "║  • Each object has its OWN vptr                       ║" << endl;
    cout << "║  • But all Circle objects' vptrs point to             ║" << endl;
    cout << "║    THE SAME Circle vtable (shared!)                   ║" << endl;
    cout << "║                                                       ║" << endl;
    cout << "║  Memory saved: Only ONE vtable per class             ║" << endl;
    cout << "║  (not one per object!)                                ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nVisualization:" << endl;
    cout << "c1 → [vptr] ─┐" << endl;
    cout << "c2 → [vptr] ─┼→ Circle's vtable (ONE copy)" << endl;
    cout << "c3 → [vptr] ─┘" << endl;
}

void showSizeComparison() {
    cout << "\n\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           SIZE COMPARISON: With/Without Virtual                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    class NoVirtual {
        int x;
        double y;
    };
    
    class WithVirtual {
        int x;
        double y;
        virtual void func() { }
    };
    
    cout << "\nClass with NO virtual functions:" << endl;
    cout << "sizeof(NoVirtual) = " << sizeof(NoVirtual) << " bytes" << endl;
    cout << "  int x:     4 bytes" << endl;
    cout << "  double y:  8 bytes" << endl;
    cout << "  Total:    12 bytes (+ 4 padding = 16)" << endl;
    
    cout << "\nClass WITH virtual functions:" << endl;
    cout << "sizeof(WithVirtual) = " << sizeof(WithVirtual) << " bytes" << endl;
    cout << "  vptr:      8 bytes ← EXTRA!" << endl;
    cout << "  int x:     4 bytes" << endl;
    cout << "  double y:  8 bytes" << endl;
    cout << "  Total:    20 bytes (+ 4 padding = 24)" << endl;
    
    cout << "\n💡 Cost: Extra 8 bytes per object for vptr" << endl;
}

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║          COMPLETE VISUAL: vptr and vtable MECHANISM            ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    // Show memory layout
    visualizeMemory();
    
    // Demonstrate virtual call
    demonstrateVirtualCall();
    
    // Compare with non-virtual
    showNonVirtualComparison();
    
    // Show multiple objects
    showMultipleObjects();
    
    // Size comparison
    showSizeComparison();
    
    cout << "\n\n";
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                        SUMMARY                                 ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  vptr (Virtual Pointer):                                       ║" << endl;
    cout << "║  • ONE per object (8 bytes)                                    ║" << endl;
    cout << "║  • Points to that class's vtable                               ║" << endl;
    cout << "║  • Set during object construction                              ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  vtable (Virtual Table):                                       ║" << endl;
    cout << "║  • ONE per class (shared by all objects)                       ║" << endl;
    cout << "║  • Array of function pointers                                  ║" << endl;
    cout << "║  • Created at compile time                                     ║" << endl;
    cout << "║  • Stored in read-only memory                                  ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "║  During virtual function call:                                 ║" << endl;
    cout << "║  1. Follow object's vptr → find vtable                         ║" << endl;
    cout << "║  2. Look up function in vtable                                 ║" << endl;
    cout << "║  3. Call the function pointer                                  ║" << endl;
    cout << "║  Result: Runtime polymorphism! ✅                              ║" << endl;
    cout << "║                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}
