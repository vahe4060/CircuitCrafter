#ifndef TOOLBOXITEM_H
#define TOOLBOXITEM_H
#include <QtWidgets>


namespace Ui{
 class ToolBoxItem;
}

class ToolBoxItem : public QWidget
{
    Q_OBJECT
public:
    ToolBoxItem() {}
    virtual ~ToolBoxItem() {}
};

#endif // TOOLBOXITEM_H
