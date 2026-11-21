#include "heads/mainwindow.h"
#include "heads/ui_mainwindow.h"
#include "heads/normal_mode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    setWindowTitle("Battle Royale");
    resize(800, 600);

    // 设置窗口居中显示
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // 设置窗口背景为清新渐变
    setStyleSheet(
        "QMainWindow {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "                             stop:0 #a8edea, stop:0.5 #fed6e3, stop:1 #f5f7fa);"
        "}"
    );

    // 创建游戏标题
    QLabel* titleLabel = new QLabel("MY GAME", this);
    QFont titleFont("Segoe UI", 36, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  color: #38b6ff;"
        "  padding: 20px;"
        "  background-color: rgba(255, 255, 255, 180);"
        "  border-radius: 15px;"
        "}"
    );

    // 添加阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(5, 5);
    titleLabel->setGraphicsEffect(shadowEffect);

    // 设置标题位置
    titleLabel->setGeometry(200, 80, 400, 100);

    // 美化“开始游戏”按钮
    ui->start->setText("START GAME");
    ui->start->setGeometry(300, 250, 200, 60);
    QFont buttonFont("Segoe UI", 14, QFont::Bold);
    ui->start->setFont(buttonFont);
    ui->start->setCursor(Qt::PointingHandCursor);
    ui->start->setStyleSheet(
        "QPushButton {"
        "  background-color: #4ade80;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #34d399;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #059669;"
        "}"
    );

    // 添加按钮阴影
    QGraphicsDropShadowEffect* buttonShadow = new QGraphicsDropShadowEffect(this);
    buttonShadow->setBlurRadius(15);
    buttonShadow->setColor(QColor(0, 0, 0, 100));
    buttonShadow->setOffset(3, 3);
    ui->start->setGraphicsEffect(buttonShadow);

    // 添加退出按钮
    QPushButton* exitButton = new QPushButton("EXIT", this);
    exitButton->setGeometry(300, 330, 200, 60);
    exitButton->setFont(buttonFont);
    exitButton->setCursor(Qt::PointingHandCursor);
    exitButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #93c5fd;"
        "  color: white;"
        "  border: 2px solid #3b82f6;"
        "  border-radius: 10px;"
        "  padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #60a5fa;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #3b82f6;"
        "}"
    );

    // 添加退出按钮阴影
    QGraphicsDropShadowEffect* exitButtonShadow = new QGraphicsDropShadowEffect(this);
    exitButtonShadow->setBlurRadius(15);
    exitButtonShadow->setColor(QColor(0, 0, 0, 100));
    exitButtonShadow->setOffset(3, 3);
    exitButton->setGraphicsEffect(exitButtonShadow);

    // 连接退出按钮
    connect(exitButton, &QPushButton::clicked, this, &QMainWindow::close);

    // 添加版权信息
    QLabel* copyrightLabel = new QLabel("", this);
    copyrightLabel->setGeometry(200, 520, 400, 30);
    copyrightLabel->setAlignment(Qt::AlignCenter);
    copyrightLabel->setStyleSheet("color: #94a3b8;");

    // 连接开始按钮
    connect(ui->start, &QPushButton::clicked, this, &MainWindow::Startbutclicked);

    // 添加按钮动画效果
    ui->start->installEventFilter(this);
    exitButton->installEventFilter(this);

    // 初始动画
    QPropertyAnimation* titleAnimation = new QPropertyAnimation(titleLabel, "geometry");
    titleAnimation->setDuration(1500);
    titleAnimation->setStartValue(QRect(200, 30, 400, 100));
    titleAnimation->setEndValue(QRect(200, 80, 400, 100));
    titleAnimation->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation* startButtonAnimation = new QPropertyAnimation(ui->start, "geometry");
    startButtonAnimation->setDuration(1000);
    startButtonAnimation->setStartValue(QRect(300, 350, 200, 60));
    startButtonAnimation->setEndValue(QRect(300, 250, 200, 60));
    startButtonAnimation->setEasingCurve(QEasingCurve::OutCubic);

    QPropertyAnimation* exitButtonAnimation = new QPropertyAnimation(exitButton, "geometry");
    exitButtonAnimation->setDuration(1000);
    exitButtonAnimation->setStartValue(QRect(300, 430, 200, 60));
    exitButtonAnimation->setEndValue(QRect(300, 330, 200, 60));
    exitButtonAnimation->setEasingCurve(QEasingCurve::OutCubic);

    QSequentialAnimationGroup* animGroup = new QSequentialAnimationGroup(this);
    animGroup->addAnimation(titleAnimation);
    QParallelAnimationGroup* buttonGroup = new QParallelAnimationGroup(this);
    buttonGroup->addAnimation(startButtonAnimation);
    buttonGroup->addAnimation(exitButtonAnimation);
    animGroup->addAnimation(buttonGroup);
    animGroup->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Startbutclicked(){
    this->hide();

    emit startsignal();
}

