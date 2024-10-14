#include "verilog_parser.h"

Verilog_Parser::Verilog_Parser(QString& path)
{
    m_path = path;
}


Verilog_Operand* Verilog_Parser::operand(SceneItem* it)
{
    if(m_operands.find(it) == m_operands.end())
        m_operands[it] = new Verilog_Operand(it);

    return m_operands[it];
}

Verilog_Wire* Verilog_Parser::wire(SceneItem* it)
{
    if(m_wires.find(it) == m_wires.end())
        m_wires[it] = new Verilog_Wire(it);

    return m_wires[it];
}

Verilog_Label* Verilog_Parser::input(SceneItem* it)
{
    if(m_inputs.find(it) == m_inputs.end())
        m_inputs[it] = new Verilog_Label(it);

    return m_inputs[it];
}

Verilog_Label* Verilog_Parser::output(SceneItem* it)
{
    if(m_outputs.find(it) == m_outputs.end())
        m_outputs[it] = new Verilog_Label(it);

    return m_outputs[it];
}



void Verilog_Parser::parse()
{
    QFile f(m_path.split(".")[0]+".v");

    f.open(QIODevice::WriteOnly);
    if(!f.isOpen())
    {
        qDebug() << "cannot open file" << f.fileName();
        return;
    }


    QTextStream out(&f);

    out << "module (input ";

    for(auto* i : m_inputs)
    {
        out << i->toString() << ", ";
    }
    out << "\n        output ";

    for(auto* i : m_outputs)
    {
        if(i != m_outputs.last())
            out << i->toString() << ", ";
    }
    out << m_outputs.last()->toString() << ");\n\n";

    for(auto* i: m_wires)
    {
        out << "\twire " << i->toString() << ";\n";
    }
    out << "\n";

    for(auto it = m_operands.begin(); it != m_operands.end(); it++)
    {
        SceneItem* i = it.key();
        out << "\t" << it.value()->toString() << "(" << m_wires[i]->toString() << ", ";


        for(auto* j: i->inputs())
        {
            if(j!=i->inputs().last())
            {
                if(m_inputs.find(j) != m_inputs.end())
                    out << m_inputs[j]->toString() << ", ";
                else
                    out << m_wires[j]->toString() << ", ";
            }
        }
        SceneItem* last_neighbour = i->inputs().last();

        if(m_inputs.find(last_neighbour) != m_inputs.end())
            out << m_inputs[last_neighbour]->toString() << ");\n";
        else
            out << m_wires[last_neighbour]->toString() << ");\n";
    }
    out <<"\n";

    for(auto it = m_outputs.begin(); it != m_outputs.end(); it++)
    {
        if(m_wires.find(it.key()->inputs()[0]) != m_wires.end())
            out << "\tassign " << it.value()->toString() << " = " << m_wires[it.key()->inputs()[0]]->toString() <<";\n";
        else
            out << "\tassign " << it.value()->toString() << " = " << m_inputs[it.key()->inputs()[0]]->toString() <<";\n";
    }

    out << "\nendmodule\n";


    QMessageBox mb(QMessageBox::Question, "Editor", "Verilog saved in " + m_path+".v");
    mb.exec();
}






