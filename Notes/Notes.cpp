#include "Notes.h"

Notes::Notes(QMainWindow *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    //设置无边框
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //设置背景颜色
    this->setStyleSheet("background:#67BBF0");
    //设置透明化
    //this->setWindowOpacity(0.6);


    InitSystemTrayIcon();

}

void Notes::InitSystemTrayIcon()
{
   // this->hide();

    m_systemTray = new QSystemTrayIcon(this);
    QIcon icon = QIcon("test.png");
    m_systemTray->setIcon(icon);

    connect(m_systemTray, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason)
        {
            switch (reason)
            {
            case QSystemTrayIcon::Unknown:
                break;
            case QSystemTrayIcon::Context:
                break;
            case QSystemTrayIcon::DoubleClick:
                this->show();
                break;
            case QSystemTrayIcon::Trigger:
                break;
            case QSystemTrayIcon::MiddleClick:
                break;
            default:
                break;
            }
        });

    CreateAction();
    CreateMenu();
        
    m_systemTray->show();
}

void Notes::CreateAction()
{
    m_showMainWindowAction = new QAction(QStringLiteral("关于系统"), this);
    connect(m_showMainWindowAction, SIGNAL(triggered()), this, SLOT(on_showMainAction()));
    m_exitAction = new QAction(QStringLiteral("退出"), this);
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(on_exitAppAction()));
}

void Notes::CreateMenu()
{
    m_menu = new QMenu(this);
    m_menu->addAction(m_showMainWindowAction);
    m_menu->addSeparator();
    m_menu->addAction(m_exitAction);

    m_systemTray->setContextMenu(m_menu);
}

void Notes::on_showMainAction()
{
    QApplication::setQuitOnLastWindowClosed(false);
    QMessageBox::information(nullptr, QStringLiteral("x"), QStringLiteral("xx"));
}

void Notes::on_exitAppAction()
{
    qApp->exit();
}

void Notes::closeEvent(QCloseEvent* event)
{
    QApplication::setQuitOnLastWindowClosed(true);
    this->hide();
    event->ignore();
}
