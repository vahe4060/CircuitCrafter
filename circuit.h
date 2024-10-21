#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "experimental.h"

#ifdef EXPERIMENTAL

class Circuit // MVC-Model
{
    friend class Controller;
public:
    Circuit();
    bool compile();
    bool load(QString path);
    bool save(QString path);
    void add_operator(int type);
    void erase(int id);
    void connect(int id1, int id2);
    void disconnect(int id1, int id2);

    int NextID() { return ++m_objectCount; }
protected:
    int m_objectCount;

};
#endif

#endif // CIRCUIT_H
