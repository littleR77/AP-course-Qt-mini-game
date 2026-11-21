#include "heads/main_ui.h"
#include <QPushButton>
#include <QVBoxLayout>
main_ui::main_ui() {
    // 设置窗口属性
    setWindowTitle("Battle Royale");
    setMinimumSize(800, 600);

    // 获取屏幕尺寸并居中显示
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // 设置窗口样式
    setStyleSheet(
        "main_ui {"
        "  background-color: #1a1a2e;"
        "  border: 1px solid #333;"
        "}"
    );

    // 创建主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(30);

    // 添加游戏标题
    QLabel* titleLabel = new QLabel("BATTLE ROYALE", this);
    QFont titleFont("Arial", 36, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel {"
        "  color: #e94560;"
        "  padding: 20px;"
        "  background-color: rgba(26, 26, 46, 180);"
        "  border-radius: 15px;"
        "}"
    );

    // 添加阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 180));
    shadowEffect->setOffset(5, 5);
    titleLabel->setGraphicsEffect(shadowEffect);

    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();

    // 创建按钮容器
    QWidget* buttonContainer = new QWidget(this);
    buttonContainer->setStyleSheet(
        "QWidget {"
        "  background-color: rgba(26, 26, 46, 0);"
        "}"
    );
    QVBoxLayout* buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->setSpacing(20);

    // 创建开始按钮
    QPushButton* startButton = new QPushButton("START GAME", this);
    startButton->setFixedSize(240, 60);
    QFont buttonFont("Arial", 14, QFont::Bold);
    startButton->setFont(buttonFont);
    startButton->setCursor(Qt::PointingHandCursor);
    startButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #e94560;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #ff6b81;"
        "  transform: scale(1.05);"
        "}"
        "QPushButton:pressed {"
        "  background-color: #c23855;"
        "}"
    );

    // 添加按钮阴影
    QGraphicsDropShadowEffect* buttonShadow = new QGraphicsDropShadowEffect(this);
    buttonShadow->setBlurRadius(15);
    buttonShadow->setColor(QColor(0, 0, 0, 150));
    buttonShadow->setOffset(3, 3);
    startButton->setGraphicsEffect(buttonShadow);

    buttonLayout->addWidget(startButton, 0, Qt::AlignCenter);

    // 创建退出按钮
    QPushButton* exitButton = new QPushButton("EXIT", this);
    exitButton->setFixedSize(240, 60);
    exitButton->setFont(buttonFont);
    exitButton->setCursor(Qt::PointingHandCursor);
    exitButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #16213e;"
        "  color: white;"
        "  border: 2px solid #e94560;"
        "  border-radius: 10px;"
        "  padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #1f2b49;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #0f172a;"
        "}"
    );

    // 添加按钮阴影
    QGraphicsDropShadowEffect* exitButtonShadow = new QGraphicsDropShadowEffect(this);
    exitButtonShadow->setBlurRadius(15);
    exitButtonShadow->setColor(QColor(0, 0, 0, 150));
    exitButtonShadow->setOffset(3, 3);
    exitButton->setGraphicsEffect(exitButtonShadow);

    buttonLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    mainLayout->addWidget(buttonContainer);
    mainLayout->addStretch();

    // 添加版权信息
    QLabel* copyrightLabel = new QLabel("© 2023 Battle Royale Game. All rights reserved.", this);
    copyrightLabel->setAlignment(Qt::AlignCenter);
    copyrightLabel->setStyleSheet("color: #888;");
    mainLayout->addWidget(copyrightLabel);

    // 设置布局
    setLayout(mainLayout);

    // 创建游戏实例
    normalgame = new Normal_mode();

    // 连接按钮信号
    connect(startButton, &QPushButton::clicked, this, &main_ui::normal_modebuttonclicked);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    // 连接游戏信号
    connect(this, &main_ui::normalsignal, normalgame, &Normal_mode::start);

    // 添加按钮悬停动画效果
    startButton->installEventFilter(this);
    exitButton->installEventFilter(this);
}


void main_ui::Hstartsignal(){
    this->show();
}

void main_ui::normal_modebuttonclicked(){
    this->hide();
    emit normalsignal();
}
