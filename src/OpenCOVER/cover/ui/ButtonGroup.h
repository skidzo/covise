#ifndef UI_BUTTONGROUP_H
#define UI_BUTTONGROUP_H

#include "Element.h"
#include "Container.h"
#include <string>
#include <functional>

namespace opencover {
namespace ui {

class Button;

//! Container of Buttons where just a single one can be in pressed state

/** \note QActionGroup */
class COVER_UI_EXPORT ButtonGroup: public Element, public Container {

 public:
    ButtonGroup(const std::string &name, Owner *owner);
    ButtonGroup(Group *parent, const std::string &name);

    void enableDeselect(bool flag);

    //! value assigned to active (=pressed) Button
    int value() const;
    //! pointer to active Button
    Button *activeButton() const;

    //! add Button to this ButtonGroup, toggling its state to fulfill constraint that exactly one button be active
    virtual bool add(Element *elem) override;
    //! remove Button from this ButtonGroup, toggling other Button's state to fulfill constraint that exactly one button be active
    virtual bool remove(Element *elem) override;

    void setCallback(const std::function<void(int)> &f);
    std::function<void(int)> callback() const;

    //! if required, toggle state of @param b so that exactly one button is active
    void toggle(const Button *b);

    void triggerImplementation() const override;

private:
    bool m_allowDeselect = false;
    std::function<void(int)> m_callback;
};

}
}
#endif
