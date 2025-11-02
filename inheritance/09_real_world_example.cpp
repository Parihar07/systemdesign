#include <iostream>
#include <vector>
#include <string>

// =================================================================================
// Part 9: Real-World Example of Inheritance (GUI Toolkit)
// =================================================================================

/*
 * This example models a simple Graphical User Interface (GUI) toolkit.
 *
 * System-Level View:
 *
 * 1.  The Abstract Contract (`UIWidget`): We define an abstract base class that represents
 *     any widget that can be drawn on the screen. It enforces a contract that any
 *     concrete widget MUST know how to `draw()` itself. This is the core of the
 *     polymorphic interface.
 *
 * 2.  Concrete Implementations (`Button`, `TextField`): These are the specific widgets.
 *     They fulfill the `UIWidget` contract by providing their own `draw()` logic.
 *     From a memory perspective, each of these objects will contain a `vptr` pointing
 *     to their respective `vtable`.
 *
 * 3.  The Rendering Engine (`render` function): This is the core of the system. It's
 *     designed to be completely decoupled from the specific widget types. It operates
 *     on a collection of `UIWidget*` pointers. When it calls `widget->draw()`, the
 *     `vptr` -> `vtable` mechanism ensures the correct, specific `draw()` function is
 *     executed at runtime.
 *
 * This design is incredibly extensible. To add a new widget (e.g., a `Checkbox`), we
 * simply create a new class that inherits from `UIWidget`. The `render` function
 * doesn't need to be changed at all.
 */

// --- 1. The Abstract Contract ---
class UIWidget {
public:
    virtual void draw() const = 0; // Pure virtual function
    virtual ~UIWidget() = default;   // Always have a virtual destructor in a base class
};

// --- 2. Concrete Implementations ---
class Button : public UIWidget {
private:
    std::string m_label;

public:
    Button(const std::string& label) : m_label(label) {}

    void draw() const override {
        std::cout << "Drawing a Button: [" << m_label << "]" << std::endl;
    }
};

class TextField : public UIWidget {
private:
    std::string m_text;

public:
    TextField(const std::string& initial_text = "") : m_text(initial_text) {}

    void setText(const std::string& text) {
        m_text = text;
    }

    void draw() const override {
        std::cout << "Drawing a TextField: |" << m_text << "|" << std::endl;
    }
};

// --- 3. The Rendering Engine ---
// This function knows how to render any collection of UIWidgets.
// It is completely decoupled from the concrete types like Button or TextField.
void render(const std::vector<UIWidget*>& widgets) {
    std::cout << "\n--- SCREEN REFRESH ---" << std::endl;
    for (const auto* widget : widgets) {
        if (widget) {
            widget->draw(); // Dynamic dispatch happens here!
        }
    }
    std::cout << "----------------------" << std::endl;
}

int main() {
    Button ok_button("OK");
    Button cancel_button("Cancel");
    TextField name_field("Enter name");

    // Create a window's widget list. The list holds pointers to the base class.
    // This is the core of polymorphism in action.
    std::vector<UIWidget*> widget_list;
    widget_list.push_back(&ok_button);
    widget_list.push_back(&cancel_button);
    widget_list.push_back(&name_field);

    // Render the entire screen.
    render(widget_list);

    // Simulate a user typing in the text field.
    std::cout << "\n...User types 'System Programmer' into the text field...\n";
    name_field.setText("System Programmer");

    // Render the screen again to see the update.
    // The render function itself is unchanged.
    render(widget_list);

    return 0;
}
