#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
//#include "output_node.h"
//#include "input_node.h"
//#include "edge.h"
//#include "graphicsceneitem.h"
#include "labels.h"
#include "operators.h"
#include "graphicslineitem.h"
#include "graphicsscene.h"
#include "verilog_parser.h"
#include "experimental.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#ifndef EXPERIMENTAL

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void setDrawingObject(QString itemtype);
    void stopDrawingObject();
    void zoom(int zoomin = 0);
    void save();
    void load();
    void eraser();
    void eraseAll();
    void loadAxes();
    void resetSettings();
    void setAutoSave();
    void setShowAxes();
    void newDocument();
    void setUpdatedFlag();
    void setNotUpdatedFlag();
    void about();
    void debug();
    bool check();

public:
   // MainWindow(QWidget *parent = nullptr);
   // ~MainWindow();

    static MainWindow* instance();
    int popUpDialog(const QString &name,
                           const QString &text,
                           QMessageBox::Icon icon,
                           QMessageBox::StandardButtons buttons
                           );
    ~MainWindow();

    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(const MainWindow&) = delete;

    int NextID() { return ++m_objectCount; }
    QGraphicsView* View() const { return m_View; }
    GraphicsScene* Scene() const { return m_Scene; }
    QGraphicsItem* Center() const { return m_Center; }
    static Qt::GlobalColor WireColor();

protected:
    static MainWindow* m_instance;
    static bool autoSave;
    static bool showAxes;
    static Qt::GlobalColor wireColor;

    int m_objectCount = 0;
    QGraphicsView* m_View = nullptr;
    GraphicsScene* m_Scene = nullptr;
    QGraphicsItem* m_Center = nullptr;

    QToolBar* m_toolbar_operators = nullptr;
    QToolBar* m_toolbar_tools = nullptr;

    QAction* autoSaveAction = nullptr;
    QAction* showAxesAction = nullptr;

    QString currentPath = "";
    bool updated = false;

    virtual void closeEvent(QCloseEvent* event) override;
    MainWindow(QWidget *parent = nullptr);
    void setToolBar();
    void setMenuBar();
    void loadSettings();
};

#else


class MainWindow : public QMainWindow // MVC-View
{
    Q_OBJECT
    friend class Controller;
public slots:
    void setDrawingObject(QString itemtype);
    void stopDrawingObject();
    void zoom(int zoomin = 0);
    void save();
    void load();
    void eraser();
    void eraseAll();
    void resetSettings();
    void setAutoSave();
    void setShowAxes();
    void newDocument();
    void about();
    void debug();
    bool check();

public:
    static MainWindow* instance();
    int popUpDialog(const QString &name,
                    const QString &text,
                    QMessageBox::Icon icon,
                    QMessageBox::StandardButtons buttons
                    );
    ~MainWindow();
    QGraphicsView* View() const { return m_View; }
    GraphicsScene* Scene() const { return m_Scene; }
    QGraphicsItem* Center() const { return m_Center; }
    static Qt::GlobalColor WireColor();

private:
    static MainWindow* m_instance;
    static bool autoSave;
    static bool showAxes;
    static Qt::GlobalColor wireColor;

    int m_objectCount = 0; // TODO:  make it size_t
    QGraphicsView* m_View = nullptr;
    GraphicsScene* m_Scene = nullptr;
    QGraphicsItem* m_Center = nullptr;

    QToolBar* m_toolbar_operators = nullptr;
    QToolBar* m_toolbar_tools = nullptr;

    QAction* autoSaveAction = nullptr;
    QAction* showAxesAction = nullptr;

    QString currentPath = "";
    bool updated = false;

    MainWindow(QWidget *parent = nullptr);
    virtual void closeEvent(QCloseEvent* event) override;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(const MainWindow&) = delete;

private: //  helpers
    void setToolBar();
    void setMenuBar();
    void loadSettings();
    void loadAxes();
    void setUpdatedFlag();
    void setNotUpdatedFlag();
};


#endif

#endif // MAINWINDOW_H
