#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "experimental.h"

#ifdef EXPERIMENTAL
class Controller // MVC-Controller
{
public:
    Controller();

    Operator *add(int type);
    void connect(Operator a, Operator b);
    void disconnect(Operator a, Operator b);
    void erase_operator(Operator *a);
    bool compile_model();
    bool save_model(QString path);
    bool load_model(QString path);

};
#endif

#endif // CONTROLLER_H
