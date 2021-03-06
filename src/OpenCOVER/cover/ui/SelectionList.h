#ifndef UI_SELECTIONLIST_H
#define UI_SELECTIONLIST_H

#include "Element.h"

#include <string>
#include <vector>
#include <functional>

namespace opencover {
namespace ui {

//! a graphical Element allowing selection of one item from a list

/** \note QComboBox */
class COVER_UI_EXPORT SelectionList: public Element {

 public:
   SelectionList(Group *parent, const std::string &name);
   SelectionList(const std::string &name, Owner *owner);

   void setList(const std::vector<std::string> items);
   const std::vector<std::string> &items() const;
   void append(const std::string &item);

   void setSelection(const std::vector<bool> selection);
   const std::vector<bool> &selection() const;

   void select(int index);
   int selectedIndex() const;
   std::string selectedItem() const;

    void update() const override;
    void updateChildren() const;

    void setCallback(const std::function<void(int)> &f);
    void triggerImplementation() const override;

 private:
    void shortcutTriggered() override;
    std::vector<std::string> m_items;
    std::vector<bool> m_selection;
    std::function<void(int)> m_callback;
};

}
}
#endif
