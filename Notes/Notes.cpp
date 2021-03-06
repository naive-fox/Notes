#include "Notes.h"


Notes::Notes(QMainWindow *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_lockstatus = false;

    this->setWindowTitle("MyNotes");

    //设置无边框
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //设置背景颜色
    this->setStyleSheet("background:#67BBF0");
    //设置托盘图标
    InitSystemTrayIcon();
    
}

Notes::~Notes()
{
    if (nullptr != m_systemTray)
        delete m_systemTray;
    if (nullptr != m_menu)
        delete m_menu;
    if (nullptr != m_lockwindow)
        delete  m_lockwindow;
    if (nullptr != m_showMainWindowAction)
        delete m_showMainWindowAction;
    if (nullptr != m_exitAction)
        delete m_exitAction;
}

void Notes::InitSystemTrayIcon()
{
   // this->hide();

    m_systemTray = new QSystemTrayIcon(this);
    QIcon icon = QIcon("mars_1.png");
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
    m_transparent = new QAction(QStringLiteral("透明化"), this);
    connect(m_transparent, SIGNAL(triggered()), this, SLOT(transparent()));
    m_exitAction = new QAction(QStringLiteral("退出"), this);
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(on_exitAppAction()));
    m_lockwindow = new QAction(QStringLiteral("取消锁定"), this);
    connect(m_lockwindow, SIGNAL(triggered()), this, SLOT(lockwindow()));
}

void Notes::CreateMenu()
{
    m_menu = new QMenu(this);
    m_menu->addAction(m_showMainWindowAction);
    m_menu->addAction(m_transparent);
    m_menu->addAction(m_lockwindow);
    m_menu->addSeparator();
    m_menu->addAction(m_exitAction);

    m_systemTray->setContextMenu(m_menu);
}

void Notes::InsertDesktop()
{
   
    if (m_lockstatus)
    {
       // InsertDesktop2();



    //    HWND hwndWorkerW = nullptr;
    //    HWND hwndDefView = nullptr;

    //    hwndWorkerW = FindWindowEx(NULL, NULL, L"WorkerW", NULL);
    //    while ((!hwndDefView) && hwndWorkerW)
    //    {
    //        hwndDefView = FindWindowEx(NULL, NULL, L"SHELLDLL_DefView", NULL);
    //        hwndWorkerW = FindWindowEx(NULL, hwndWorkerW, L"WorkerW", NULL);
    //    }

    //    SetParent((HWND)this->winId(), (HWND)0x00010184);

    //    ShowWindow(hwndWorkerW, 0);
        SetParent((HWND)this->winId(), NULL);
        setWindowFlags(!Qt::FramelessWindowHint);
        this->show();
    }
    else
    {
        SetParent((HWND)this->winId(), (HWND)(0x000500EA));
        setWindowFlags(Qt::FramelessWindowHint);
        this->show();
        //this->setWindowFlags(Qt::FramelessWindowHint);
    }
    
    m_lockstatus = !m_lockstatus;
}
void Notes::InsertDesktop2()
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    HWND desktopHwnd = resultHwnd; //findDesktopIconWnd();
    if (desktopHwnd)
        SetParent((HWND)this->winId(), desktopHwnd);
}
bool CALLBACK Notes::enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) {
        return TRUE;
    };

    HWND sndWnd;
    if (!(sndWnd = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL))) {
        return TRUE;
    }
    HWND targetWnd;
    if (!(targetWnd = FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView"))) {
        return TRUE;
    }

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}
void Notes::lockwindow()
{
    InsertDesktop();
}

void Notes::transparent()
{
    // method 1  调用windows系统函数
    // 对整体窗口有效，主窗口内的某个窗口或者控件无效
    //::SetWindowLong((HWND)this->winId(), GWL_EXSTYLE, GetWindowLong((HWND)this->winId(), GWL_EXSTYLE) ^ WS_EX_LAYERED);
    //::SetLayeredWindowAttributes((HWND)this->winId(), 0, 128, 2);
    //this->show();

    // method 2  
    // 整体透明化，包含子控件。如果透明度设成0.0，将会显示黑背景
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(0.5);
    setGraphicsEffect(opacityEffect);
    this->show();

    // method 3 
    // 设置整体透明度，包括子控件。如果透明度设成0.0，将会“消失”
    //setWindowOpacity(0.5);

    // method 4 
    // 未成功，仅仅看到下述函数将窗口背景设成了黑色
    // 该函数形参为true时，会将窗口背景设置为黑色。
    //setAttribute(Qt::WA_TranslucentBackground, true); 
    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, QColor(155, 155, 255, 45));
    //setPalette(pal);

    // method 5
    // 未成功
    //QPalette palette;
    //palette.setColor(QPalette::Background, QColor(255, 0, 0, 127));
    //this->setPalette(palette);
}

void Notes::on_showMainAction()
{
    QApplication::setQuitOnLastWindowClosed(false);
    QMessageBox::information(nullptr, QStringLiteral("x"), QStringLiteral("xx"));
}

void Notes::on_exitAppAction()
{
    //delete m_systemTray;
    qApp->exit();
}

void Notes::closeEvent(QCloseEvent* event)
{
    QApplication::setQuitOnLastWindowClosed(true);
    this->hide();
    event->ignore();
}

