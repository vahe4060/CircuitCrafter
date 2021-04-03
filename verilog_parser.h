#ifndef VERILOG_PARSER_H
#define VERILOG_PARSER_H
#include "graphicssceneitem.h"
#include <QMessageBox>

class Verilog_Object
{
public:
    Verilog_Object(int id) { m_id = id; }

    virtual int id() const { return m_id; }
    QString toString() const { return m_value; }
    virtual QString parse() const = 0;

protected:
    int m_id;
    QString m_value = "";
};

class Verilog_Wire: public Verilog_Object
{
public:
    Verilog_Wire(SceneItem* item): Verilog_Object(item->id())
    {
        m_value = "m_wire" + QString::number(m_id);
    }
    ~Verilog_Wire() {}

    QString parse() const override
    {
        return "wire " + m_value + ";";
    }
};

class Verilog_Operand: public Verilog_Object
{
public:
    Verilog_Operand(SceneItem* item): Verilog_Object(item->id())
    {
        m_value = item->toString().toLower();
    }
    ~Verilog_Operand(){}

    QString parse() const override
    {
        return "";
    }
};


class Verilog_Label: public Verilog_Object
{
public:
    Verilog_Label(SceneItem* item): Verilog_Object(item->id())
    {
        m_value = "label_"+QString::number(m_id);
    }
    ~Verilog_Label(){}

    QString parse() const override
    {
        return "";
    }
};

class Verilog_Parser
{
public:
    Verilog_Parser(QString& path);

    Verilog_Operand* operand(SceneItem* it);
    Verilog_Wire* wire(SceneItem* it);
    Verilog_Label* input(SceneItem* it);
    Verilog_Label* output(SceneItem* it);

    void parse();

protected:
    QString m_final;
    QString m_path;

    QMap<SceneItem*, Verilog_Wire*> m_wires;
    QMap<SceneItem*, Verilog_Operand*> m_operands;
    QMap<SceneItem*, Verilog_Label*> m_inputs;
    QMap<SceneItem*, Verilog_Label*> m_outputs;
};



#endif // VERILOG_PARSER_H
