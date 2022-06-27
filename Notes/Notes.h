#pragma once
#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_Notes.h"
#include <Windows.h>

class Notes : public QMainWindow
{
    Q_OBJECT

public:
    Notes(QMainWindow *parent = Q_NULLPTR);
    ~Notes();

private:
    void InitSystemTrayIcon();
    void CreateAction();
    void CreateMenu();
    void InsertDesktop();
    void InsertDesktop2();
    static bool enumUserWindowsCB(HWND hwnd, LPARAM lParam);
private slots:
    void lockwindow();
    void on_showMainAction();
    void on_exitAppAction();

protected:
    void closeEvent(QCloseEvent* event) override;
private:
    //����ͼ��
    QSystemTrayIcon* m_systemTray;
    //�����Ҽ��˵�
    QMenu* m_menu;
    //�����Ҽ��˵���Ӧ��Action
    QAction* m_lockwindow;
    QAction* m_showMainWindowAction;
    QAction* m_exitAction;

    bool m_lockstatus;
    HWND m_hwndMywindow;
private:
    Ui::NotesClass ui;
};
