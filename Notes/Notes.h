#pragma once
#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_Notes.h"

class Notes : public QMainWindow
{
    Q_OBJECT

public:
    Notes(QMainWindow *parent = Q_NULLPTR);


private:
    void InitSystemTrayIcon();
    void CreateAction();
    void CreateMenu();
private slots:
    void on_showMainAction();
    void on_exitAppAction();

protected:
    void closeEvent(QCloseEvent* event) override;
private:
    QSystemTrayIcon* m_systemIcon;
    QSystemTrayIcon* m_systemTray;
    QMenu* m_menu;
    QAction* m_showMainWindowAction;
    QAction* m_exitAction;

private:
    Ui::NotesClass ui;
};
