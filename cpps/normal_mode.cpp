#include "heads/normal_mode.h"
#include "heads/mainwindow.h"
Normal_mode::Normal_mode(QWidget* parent)
    : Game_mode{parent}
{
    active = false;
    // 设置窗口属性
    setWindowTitle("Normal Mode");

}
void Normal_mode::start() {
    //播放器
    startTime = QTime::currentTime();  // 记录开始时间
    bgm = new QMediaPlayer(this);
    bgmout = new QAudioOutput(this);
    bgm->setAudioOutput(bgmout);
    bgmout->setVolume(0.1);
    bgm->setSource(QUrl("qrc:/resources/BGM.mp3"));
    bgm->play();
    bgm->setLoops(-1);
    fire = new QMediaPlayer(this);
    fireout = new QAudioOutput(this);
    fire->setAudioOutput(fireout);
    fireout->setVolume(1.0);
    fire->setSource(QUrl("qrc:/resources/fire.wav"));
    aaa = new QMediaPlayer(this);
    aaaout = new QAudioOutput(this);
    aaa->setAudioOutput(aaaout);
    aaaout->setVolume(0.5);
    aaa->setSource(QUrl("qrc:/resources/aaa.m4a"));
    fei = new QMediaPlayer(this);
    feiout = new QAudioOutput(this);
    fei->setAudioOutput(feiout);
    feiout->setVolume(0.5);
    fei->setSource(QUrl("qrc:/resources/feiqilai.m4a"));
    man = new QMediaPlayer(this);
    manout = new QAudioOutput(this);
    man->setAudioOutput(manout);
    manout->setVolume(0.5);
    man->setSource(QUrl("qrc:/resources/man.m4a"));
    amns = new QMediaPlayer(this);
    amnsout = new QAudioOutput(this);
    amns->setAudioOutput(amnsout);
    amnsout->setVolume(0.5);
    amns->setSource(QUrl("qrc:/resources/amns.m4a"));
    biu = new QMediaPlayer(this);
    biuout = new QAudioOutput(this);
    biu->setAudioOutput(biuout);
    biuout->setVolume(0.5);
    biu->setSource(QUrl("qrc:/resources/biu.m4a"));
    over = new QMediaPlayer(this);
    overout = new QAudioOutput(this);
    over->setAudioOutput(overout);
    overout->setVolume(1.0);
    over->setSource(QUrl("qrc:/resources/gameover.wav"));
    tool = new QMediaPlayer(this);
    toolout = new QAudioOutput(this);
    tool->setAudioOutput(toolout);
    toolout->setVolume(1.0);
    tool->setSource(QUrl("qrc:/resources/tool.wav"));

    srand(time(0));
    active = true;
    moveTimer = new QTimer(this);
    moveTimer->start(16);
    connect(moveTimer, &QTimer::timeout, this, &Normal_mode::updatePlayerPosition);
    EnemymoveTimer = new QTimer(this);
    EnemymoveTimer->start(16);
    connect(moveTimer, &QTimer::timeout, this, &Normal_mode::updateEnemyPosition);
    checkTimer = new QTimer(this);
    checkTimer->start(100);
    connect(checkTimer, &QTimer::timeout, this, &Normal_mode::checkdeath);
    dodgeTimer = new QTimer(this);
    dodgeTimer->start(100);
    connect(dodgeTimer, &QTimer::timeout, this, &Normal_mode::dodgerecovery);
    rspeedTimer = new QTimer(this);
    rspeedTimer->start(2500);
    connect(rspeedTimer, &QTimer::timeout, this, &Normal_mode::updaterandomspeed);
    //myscene = new QGraphicsScene();
    //QPixmap* pixmap = new QPixmap(scenepos);
    //if (pixmap->isNull()) {
    //    qDebug() << "Failed to load background from:" << scenepos;
    //    // 添加一个彩色矩形作为备用背景
    //    myscene->addRect(0, 0, 1280, 720, QPen(), QBrush(Qt::darkGreen));
    //    delete pixmap;
    //}
    //else {
    //    // 图片加载成功，添加到场景中
    //    qDebug() << "Image loaded successfully, size:" << pixmap->width() << "x" << pixmap->height();
    //    const int bgSize = 2560;
    //    QPixmap scaledBg = pixmap->scaled(bgSize, bgSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    //    // 创建一个圆形背景图像
    //    QPixmap circularBg(bgSize, bgSize);
    //    circularBg.fill(Qt::transparent);

    //    // 使用 QPainter 绘制圆形背景
    //    QPainter painter(&circularBg);
    //    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //    painter.setClipRegion(QRegion(0, 0, bgSize, bgSize, QRegion::Ellipse));  // 设置圆形裁剪区域
    //    painter.drawPixmap((bgSize - scaledBg.width()) / 2,
    //        (bgSize - scaledBg.height()) / 2, scaledBg);  // 将图像绘制到圆形区域中

    //    // 将圆形背景添加到场景
    //    background = myscene->addPixmap(circularBg);
    //    background->setPos(0, 0);  // 设置背景位置
    //    myscene->setSceneRect(0, 0, bgSize, bgSize);
    //}
    myscene = new QGraphicsScene();
    bgSize = 2560;

    // 1. 绘制地图图像
    mapImage=QPixmap(bgSize, bgSize);
    mapImage.fill(Qt::transparent);

    QPainter painter(&mapImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // 草地背景
    painter.setBrush(QColor("#d0f0c0"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, bgSize, bgSize);

    // 河流
    painter.setBrush(QColor("#a2d5f2"));
    painter.drawRoundedRect(200, 400, 2160, 200, 60, 60);

    // 树木
    auto drawTree = [&](int x, int y) {
        painter.setBrush(QColor("#4caf50"));
        painter.drawEllipse(x, y, 80, 80);
        painter.setBrush(QColor("#8d6e63"));
        painter.drawRect(x + 35, y + 70, 10, 30);
        };
    drawTree(300, 500);
    drawTree(2200, 300);
    drawTree(1000, 1600);
    drawTree(1800, 2000);

    // 石头
    auto drawRock = [&](int x, int y) {
        painter.setBrush(QColor("#b0bec5"));
        painter.drawEllipse(x, y, 60, 40);
        };
    drawRock(900, 900);
    drawRock(1600, 1300);
    drawRock(2200, 2000);

    // 🌸 花丛装饰
    auto drawFlower = [&](int x, int y) {
        painter.setBrush(QColor("#ffb6c1"));
        for (int i = 0; i < 5; ++i)
            painter.drawEllipse(x + qCos(i * 72 * M_PI / 180) * 10, y + qSin(i * 72 * M_PI / 180) * 10, 8, 8);
        painter.setBrush(QColor("#ffd700"));
        painter.drawEllipse(x, y, 6, 6);  // 中心
        };
    drawFlower(400, 1800);
    drawFlower(2000, 800);
    drawFlower(1800, 1600);

    // 🛖 木屋装饰
    auto drawHut = [&](int x, int y) {
        painter.setBrush(QColor("#a1887f"));  // 屋体
        painter.drawRect(x, y, 80, 60);
        painter.setBrush(QColor("#6d4c41"));  // 屋顶
        QPointF roof[3] = { QPointF(x - 10, y), QPointF(x + 40, y - 40), QPointF(x + 90, y) };
        painter.drawPolygon(roof, 3);
        };
    drawHut(700, 700);
    drawHut(2000, 1700);

    // 🪵 栅栏装饰
    auto drawFence = [&](int x, int y, int count) {
        painter.setBrush(QColor("#deb887"));
        for (int i = 0; i < count; ++i)
            painter.drawRect(x + i * 20, y, 10, 40);
        };
    drawFence(1600, 300, 8);
    drawFence(300, 2100, 10);

    // 2. 圆形裁剪图像
    QPixmap circularBg(bgSize, bgSize);
    circularBg.fill(Qt::transparent);

    QPainter circlePainter(&circularBg);
    circlePainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    circlePainter.setClipRegion(QRegion(0, 0, bgSize, bgSize, QRegion::Ellipse));
    circlePainter.drawPixmap(0, 0, mapImage);

    // 3. 添加到场景
    background = myscene->addPixmap(circularBg);
    background->setPos(0, 0);
    myscene->setSceneRect(0, 0, bgSize, bgSize);

    view = new QGraphicsView(myscene, this);
    view->setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
    view->setRenderHint(QPainter::SmoothPixmapTransform);  // 平滑变换
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->resize(1280, 720);
    // 将窗口居中显示在屏幕上
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(1280, 720),
            QGuiApplication::primaryScreen()->geometry()
        )
    );
    // 显示窗口
    this->show();
    // 生成草丛
    spawngrass();
    //添加玩家
    this->setplayer(1);
    initaspeed = player->aspeed;
    playerLabel = new QLabel(nullptr);
    playerLabel->setAttribute(Qt::WA_TranslucentBackground); // 使背景透明
    playerMovie = new QMovie(player->ppos);
    playerMovieLeft = new QMovie(player->lpos);
    playerMovieRight = new QMovie(player->ppos); 
    playerMovieMoving = new QMovie(player->mpos);
    playerMovieMovingL = new QMovie(player->lmpos);
    playerDodgeMovie = new QMovie(player->dpos);
    playerDodgeMovieL = new QMovie(player->ldpos);
    
    enemymovieL = new QMovie(enemyl);
    enemymovieR = new QMovie(enemyr);
    if (playerMovieLeft->isValid()) {
        playerMovieLeft->setScaledSize(QSize(72, 130));
    }
    if (playerMovieRight->isValid()) {
        playerMovieRight->setScaledSize(QSize(72, 130));
    }
    if (playerMovieMoving->isValid()) {
        playerMovieMoving->setScaledSize(QSize(72, 130));
    }
    if (playerMovieMovingL->isValid()) {
        playerMovieMovingL->setScaledSize(QSize(72, 130));
    }
    if (playerDodgeMovie->isValid()) {
        playerDodgeMovie->setScaledSize(QSize(72, 130));
    }
    if (playerDodgeMovieL->isValid()) {
        playerDodgeMovieL->setScaledSize(QSize(72, 130));
    }
    if (enemymovieL->isValid()) {
        enemymovieL->setScaledSize(QSize(72, 65));
    }
    if (enemymovieR->isValid()) {
        enemymovieR->setScaledSize(QSize(72, 65));
    }
    
    playerMovieLeft->setCacheMode(QMovie::CacheAll);
    playerMovieRight->setCacheMode(QMovie::CacheAll);
    playerMovieMoving->setCacheMode(QMovie::CacheAll);
    playerMovieMovingL->setCacheMode(QMovie::CacheAll);
    playerDodgeMovie->setCacheMode(QMovie::CacheAll);
    playerDodgeMovieL->setCacheMode(QMovie::CacheAll);
    playerMovie->setCacheMode(QMovie::CacheAll);
    enemymovieL->setCacheMode(QMovie::CacheAll);
    enemymovieR->setCacheMode(QMovie::CacheAll);

    playerLabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
    if (playerMovie->isValid()) {
        qDebug() << "Character animation loaded successfully";
        qDebug() << "Movie size:" << playerMovie->currentImage().size();
        // 设置动画大小
        playerMovie->setScaledSize(QSize(72,130));
        playerLabel->setMovie(playerMovie);
        playerMovie->setCacheMode(QMovie::CacheAll); // 缓存所有帧以提高性能
        playerMovie->setSpeed(100); // 设置播放速度为正常速度
        playerMovie->start();
        playerProxyWidget = myscene->addWidget(playerLabel);
        // 设置玩家位置始终居中
        playerProxyWidget->setPos(myscene->width() / 2 - playerLabel->width() / 2,
            myscene->height() / 2 - playerLabel->height() / 2);
        // 视图居中显示玩家
        view->centerOn(playerProxyWidget);
        // 生成武器
        spawnfire();
        //加载玩家血条,头像
        initHp = player->Hp;
        initmaxv = player->maxspeed;
        initaspeed = player->aspeed;
        originalmyblood=QPixmap(myblood);
        headpicture = QPixmap(headpic);
        if(!(originalmyblood.isNull())){ qDebug() << "myblood loaded successfully"; }
        if (!(headpicture.isNull())) { qDebug() << "headpicture loaded successfully"; }
        mybloodItem = new QGraphicsPixmapItem(originalmyblood);
        myheadpic = new QGraphicsPixmapItem(headpicture);
        mybloodItem->setScale(0.05);
        myheadpic->setScale(0.5);
        myscene->addItem(mybloodItem);
        myscene->addItem(myheadpic);
        mybloodH = originalmyblood.height();
        mybloodW = originalmyblood.width();
        //左上角提示(手雷，烟雾)
        QPixmap minigrenade(grenadepic);
        grenadeamount = new QGraphicsPixmapItem(minigrenade);
        qDebug() << "grenadeamount loaded";
        QPixmap minismoke(smokegrenadepic);
        smokeamount = new QGraphicsPixmapItem(minismoke);
        qDebug() << "smokeamount loaded";
        QPixmap minispeedy(speedy);
        speedyamount = new QGraphicsPixmapItem(minispeedy);
        grenadeamount->setScale(0.1);
        smokeamount->setScale(0.1);
        speedyamount->setScale(0.3);
        myscene->addItem(grenadeamount);
        myscene->addItem(smokeamount);
        myscene->addItem(speedyamount);
        grenadeText = new QGraphicsTextItem();
        grenadeText->setDefaultTextColor(Qt::black);
        grenadeText->setFont(QFont("Arial", 10, QFont::Bold));
        grenadeText->setZValue(1);
        myscene->addItem(grenadeText);
        smokeText = new QGraphicsTextItem();
        smokeText->setDefaultTextColor(Qt::black);
        smokeText->setFont(QFont("Arial", 10, QFont::Bold));
        smokeText->setZValue(1);
        myscene->addItem(smokeText);
        mybloodTimer = new QTimer(this);
        mybloodTimer->start(16);
        connect(mybloodTimer, &QTimer::timeout, this, &Normal_mode::updatemybloodpos);
        //生成按钮
        spawn = new QPushButton(this);
        spawn->setFixedSize(60, 40);
        QIcon icon(enemypic);
        spawn->setIcon(icon);
        spawn->setIconSize(QSize(60, 40));
        spawn->setFlat(true);
        spawn->show();
        spawn->setStyleSheet("QPushButton {"
            "background-color: transparent;"
            "border: none;"
            "}");
        spawnwidget = myscene->addWidget(spawn);
        spawnwidget->setZValue(1000);
        connect(spawn, &QPushButton::clicked, this, &Normal_mode::spawnenemy);
        //敌人血条初始化
        originalblood = QPixmap(blood);
        //添加敌人生成计时器并连接
        /*enemyTimer = new QTimer(this);
        enemyTimer->start(1000);
        connect(enemyTimer, &QTimer::timeout, this, &Normal_mode::spawnenemy);*/
        for (size_t i = 0;i < 5;i++) {
            spawnenemy();
        }
        enemyattackTimer = new QTimer(this);
        enemyattackTimer->start(1000);
        connect(enemyattackTimer, &QTimer::timeout, this, &Normal_mode::enemyattack);
    //随时检查
        connect(checkTimer, &QTimer::timeout, this, &Normal_mode::checkpertime);
        
        connect(mybloodTimer, &QTimer::timeout, this, &Normal_mode::updatebloodspos);
        toolTimer = new QTimer(this);
        toolTimer->start(3000);
        connect(toolTimer, &QTimer::timeout, this, &Normal_mode::spawntool);
        stateTimer = new QTimer(this);
        stateTimer->start(16);
        connect(stateTimer, &QTimer::timeout, this, &Normal_mode::updataplayerstate);
        connect(stateTimer, &QTimer::timeout, this, &Normal_mode::updateenemystate);
        faTimer = new QTimer(this);
        faTimer->start(16);
        connect(faTimer, &QTimer::timeout, this, &Normal_mode::updatefa);
        circleTimer = new QTimer(this);
        circleTimer->start(16);
        connect(circleTimer, &QTimer::timeout, this, &Normal_mode::updatecirclepos);
        bulletTimer = new QTimer(this);
        bulletTimer->start(16);
        connect(bulletTimer, &QTimer::timeout, this, &Normal_mode::updatefirebullets);
        connect(bulletTimer, &QTimer::timeout, this, &Normal_mode::updateenemybullets);
        defenseTimer = new QTimer(this);
        defenseTimer->start(500);
        connect(defenseTimer, &QTimer::timeout, this, &Normal_mode::checkdefense);
        bombTimer = new QTimer(this);
        bombTimer->start();
        connect(bombTimer, &QTimer::timeout, this, &Normal_mode::updatebombspos);
        
        cursorpic = QPixmap(round);
        transparentPixmap=QPixmap(1, 1);
        transparentPixmap.fill(Qt::transparent);//填充为透明
        cursoritem = new QGraphicsPixmapItem(cursorpic);
        myscene->addItem(cursoritem);
        cursorTimer = new QTimer(this);
        cursorTimer->start(16);
        connect(cursorTimer, &QTimer::timeout, this, &Normal_mode::updatecursorpos);
        liziTimer = new QTimer(this);
        liziTimer->start(100);
        /*connect(liziTimer, &QTimer::timeout, this, &Normal_mode::updatelizipos);*/
        sizeTimer = new QTimer(this);
        sizeTimer->start(16);
        connect(sizeTimer, &QTimer::timeout, this, &Normal_mode::updatesize);
        for (int i = 0;i < 16;i++) {
            rx.push_back(cos(2 * M_PI * i / 16) * enemies[0]->aspeed);
            ry.push_back(sin(2 * M_PI * i / 16) * enemies[0]->aspeed);
        }
    }
}
void Normal_mode::end() {
    QPointF mypos = playerProxyWidget->scenePos();
    active = false;
    int rank = enemies.size() + 1;
    if (playerMovie) {
        disconnect(playerMovie, nullptr, this, nullptr);
        playerMovie->stop();
    }
    if (playerProxyWidget) {
        myscene->removeItem(playerProxyWidget);
        delete playerProxyWidget;
        playerProxyWidget = nullptr;
    }
    if (playerMovie) {
        playerMovie->stop();
        delete playerMovie;
        playerMovie = nullptr;
    }
    delete player;
    player = nullptr;
    qDebug() << "Player has died and been removed from the scene";
    // 停止所有计时器
    if (moveTimer) moveTimer->stop();
    if (EnemymoveTimer) EnemymoveTimer->stop();
    if (bulletTimer) bulletTimer->stop();
    if (enemyattackTimer) enemyattackTimer->stop();
    if (checkTimer) checkTimer->stop();
    if (enemyTimer) enemyTimer->stop();
    if (toolTimer) toolTimer->stop();
    if (mybloodTimer) mybloodTimer->stop();
    if (orbitTimer) orbitTimer->stop();
    if (spawnbuTimer) spawnbuTimer->stop();
    if (stateTimer) stateTimer->stop();
    if (faTimer) faTimer->stop();
    if (circleTimer) circleTimer->stop();
    if (defenseTimer) defenseTimer->stop();
    if (bombTimer) bombTimer->stop();
    if (cursorTimer) cursorTimer->stop();
    if (liziTimer) liziTimer->stop();
    if (rspeedTimer) rspeedTimer->stop();
    if (dodgeTimer) dodgeTimer->stop();
    if (playerMovie) {
        playerMovie->stop();
        delete playerMovie;
        playerMovie = nullptr;
    }
    if (playerProxyWidget) {
        myscene->removeItem(playerProxyWidget);
        delete playerProxyWidget;
        playerProxyWidget = nullptr;
    }
    
    for (auto bullet : enemybullets) {
        myscene->removeItem(bullet);
        delete bullet;
    }
    enemybullets.clear();
    //敌人(先清除子弹)
    for (size_t i = 0;i < enemybullets.size();i++) {
        myscene->removeItem(enemybullets[i]);
        delete enemybullets[i];
        delete weaponbullets[i];
    }
    for (size_t i = 0; i < enemies.size(); i++) {
        for (size_t w = 0; w < enemies[i]->weaponwidget.size(); w++) {
            if (enemies[i]->weaponwidget[w]) {
                myscene->removeItem(enemies[i]->weaponwidget[w]);
                delete enemies[i]->weaponwidget[w];
            }
            if (w < enemies[i] ->weapons.size() && enemies[i]->weapons[w]) {
                delete enemies[i]->weapons[w];
            }

        }
        myscene->removeItem(enemywidgets[i]);
        /*delete enemywidgets[i];
        delete enemies[i];*/
        delete enemybloods[i];
    }
    enemybloods.clear();
    /*enemies.clear();
    enemywidgets.clear();*/
    //道具
    for (auto tool : tools) {
        myscene->removeItem(tool);
        delete tool;
    }
    tools.clear();
    //草丛
    for (auto grass : grassItems) {
        myscene->removeItem(grass);
        delete grass;
    }
    grassItems.clear();
    //子弹
    for (auto widget : fireWidgets) {
        if (widget) {
            myscene->removeItem(widget);
            delete widget;
        }
    }
    fireWidgets.clear();
    for (auto firebu : firebullets) {
        myscene->removeItem(firebu);
        delete firebu;
    }
    
    firebullets.clear();
    qDebug() << 1;
    myscene->removeItem(mybloodItem);
    myscene->removeItem(myheadpic);
    myscene->removeItem(smokeamount);
    myscene->removeItem(smokeText);
    myscene->removeItem(grenadeamount);
    myscene->removeItem(grenadeText);
    myscene->removeItem(spawnwidget);
    delete spawnwidget;
    delete  spawn;
    myscene->removeItem(cursoritem);
    delete cursoritem;
    //展示游戏结束(隔一秒),得分，排名
    //QTimer::singleShot(2000, [this,rank,mypos]() {
    //    if (myscene) {
    //        QGraphicsTextItem* gameOverText = nullptr;
    //        if (rank == 1) {
    //            gameOverText= myscene->addText("Victory");
    //        }
    //        else{gameOverText= myscene->addText("Game Over");
    //        }
    //        gameOverText->setDefaultTextColor(Qt::red);
    //        // 设置字体
    //        QFont font;
    //        font.setPointSize(30);
    //        font.setBold(true);
    //        gameOverText->setFont(font);

    //        // 居中显示
    //        QRectF gameoverRect = gameOverText->sceneBoundingRect();
    //        QRectF sceneRect = myscene->sceneRect();
    //        gameOverText->setPos(
    //            mypos.x() - gameoverRect.width()/2,
    //            mypos.y() - gameoverRect.height()/2);
    //        view->centerOn(gameOverText);
    //        int margin = 20;
    //        //得分
    //        gameoverRect = gameOverText->sceneBoundingRect();
    //        QString scoreText = QString("Score: %1").arg(score);
    //        QGraphicsTextItem* scoreItem = myscene->addText(scoreText);
    //        scoreItem->setDefaultTextColor(Qt::white);
    //        scoreItem->setFont(font);
    //        QRectF scoreRect = scoreItem->sceneBoundingRect();
    //        scoreItem->setPos(gameoverRect.x() + gameoverRect.width() / 2 - scoreRect.width() / 2,
    //            gameoverRect.y() + gameoverRect.height() + margin);
    //        //排名
    //        scoreRect = scoreItem->sceneBoundingRect();
    //        QString rankText = QString("Rank: %1").arg(rank);
    //        QGraphicsTextItem* rankItem = myscene->addText(rankText);
    //        rankItem->setDefaultTextColor(Qt::white);
    //        rankItem->setFont(font);
    //        QRectF rankRect = rankItem->sceneBoundingRect();
    //        rankItem->setPos(scoreRect.x(), scoreRect.y() + scoreRect.height() + margin);
    //        gameOverText->setZValue(1);
    //        scoreItem->setZValue(1);
    //        rankItem->setZValue(1);
    //        qDebug() << "GameOver Pos:" << gameOverText->pos();
    //        qDebug() << "Score Pos:" << scoreItem->pos();
    //        qDebug() << "Rank Pos:" << rankItem->pos();
    //        //按钮
    //        QPushButton* restartButton = new QPushButton("Retry",nullptr);
    //        restartButton->setFixedSize(80, 40);
    //        restartButton->show();
    //        restartButton->setFlat(true);
    //        QGraphicsProxyWidget* retrywidget=myscene->addWidget(restartButton);
    //        retrywidget->setPos(rankRect.x() - 80, rankRect.y() + rankRect.height() + margin);
    //        connect(restartButton, &QPushButton::clicked, [this]() {
    //            Normal_mode* ngame = new Normal_mode();
    //            ngame->start();
    //            });
    //        QPushButton* quitButton = new QPushButton("Exit", nullptr);
    //        quitButton->setFixedSize(80, 40);
    //        quitButton->show();
    //        QGraphicsProxyWidget* exitwidget=myscene->addWidget(quitButton);
    //        exitwidget->setPos(rankRect.x() + 40, rankRect.y() + rankRect.height() + margin);
    //    }
    //    });
    QTimer::singleShot(2000, [this, rank, mypos]() {
        if (!myscene) return;
        qDebug() << 1;
        // 创建半透明背景d
        QGraphicsRectItem* overlay = new QGraphicsRectItem(myscene->sceneRect());
        overlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
        overlay->setPen(Qt::NoPen);
        overlay->setZValue(1000);
        myscene->addItem(overlay);
        qDebug() << 1;
        // 创建游戏结束文本
        QGraphicsTextItem* gameOverText = nullptr;
        if (rank == 1) {
            gameOverText = myscene->addText("Victory");
            gameOverText->setDefaultTextColor(Qt::green);
        }
        else {
            gameOverText = myscene->addText("Game Over");
            gameOverText->setDefaultTextColor(Qt::red);
        }

        // 设置字体
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        gameOverText->setFont(font);

        // 居中显示
        QRectF gameoverRect = gameOverText->sceneBoundingRect();
        gameOverText->setPos(
            mypos.x() - gameoverRect.width() / 2,
            mypos.y() - gameoverRect.height() / 2);
        view->centerOn(gameOverText);

        int margin = 20;
        // 得分
        QString scoreText = QString("Score: %1").arg(score);
        QGraphicsTextItem* scoreItem = myscene->addText(scoreText);
        scoreItem->setDefaultTextColor(Qt::white);
        scoreItem->setFont(font);
        QRectF scoreRect = scoreItem->sceneBoundingRect();
        scoreItem->setPos(
            gameOverText->pos().x() + gameoverRect.width() / 2 - scoreRect.width() / 2,
            gameOverText->pos().y() + gameoverRect.height() + margin);

        // 排名
        QString rankText = QString("Rank: %1").arg(rank);
        QGraphicsTextItem* rankItem = myscene->addText(rankText);
        rankItem->setDefaultTextColor(Qt::white);
        rankItem->setFont(font);
        QRectF rankRect = rankItem->sceneBoundingRect();
        rankItem->setPos(
            scoreItem->pos().x(),
            scoreItem->pos().y() + scoreRect.height() + margin);
        // 设置Z值确保显示在最上层
        gameOverText->setZValue(1001);
        scoreItem->setZValue(1001);
        rankItem->setZValue(1001);
        // 创建按钮样式
        QString buttonStyle =
            "QPushButton {"
            "  background-color: rgba(60, 60, 60, 200);"
            "  color: white;"
            "  border: 2px solid #aaaaaa;"
            "  border-radius: 5px;"
            "  font-size: 16px;"
            "  font-weight: bold;"
            "  padding: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: rgba(80, 80, 80, 220);"
            "  border: 2px solid #cccccc;"
            "}"
            "QPushButton:pressed {"
            "  background-color: rgba(100, 100, 100, 240);"
            "}";
        // 重试按钮
        QPushButton* restartButton = new QPushButton("Retry");
        restartButton->setFixedSize(100, 40);
        restartButton->setStyleSheet(buttonStyle);
        QGraphicsProxyWidget* retryWidget = myscene->addWidget(restartButton);
        retryWidget->setPos(
            rankItem->pos().x() + rankRect.width() / 2 - 110,
            rankItem->pos().y() + rankRect.height() + margin * 1.5);
        retryWidget->setZValue(1001);
        // 退出按钮
        QPushButton* quitButton = new QPushButton("Exit");
        quitButton->setFixedSize(100, 40);
        quitButton->setStyleSheet(buttonStyle);
        QGraphicsProxyWidget* exitWidget = myscene->addWidget(quitButton);
        exitWidget->setPos(
            rankItem->pos().x() + rankRect.width() / 2 + 10,
            rankItem->pos().y() + rankRect.height() + margin * 1.5);
        exitWidget->setZValue(1001);
        qDebug() << 1;
        //存活时间
        QTime endTime = QTime::currentTime();
        int survivalSeconds = startTime.secsTo(endTime);
        int minutes = survivalSeconds / 60;
        int seconds = survivalSeconds % 60;
        QString timeText = QString("Survival Time: %1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));

        QGraphicsTextItem* timeItem = myscene->addText(timeText);
        timeItem->setDefaultTextColor(Qt::white);
        timeItem->setFont(font);
        QRectF timeRect = timeItem->sceneBoundingRect();
        timeItem->setPos(
            rankItem->pos().x(),
            rankItem->pos().y() + rankRect.height() + margin);
        timeItem->setZValue(1001);

        // 按钮位置
        retryWidget->setPos(
            rankItem->pos().x() + rankRect.width() / 2 - 110,
            timeItem->pos().y() + timeRect.height() + margin * 1.5);

        exitWidget->setPos(
            rankItem->pos().x() + rankRect.width() / 2 + 10,
            timeItem->pos().y() + timeRect.height() + margin * 1.5);
        // 连接按钮信号
        connect(restartButton, &QPushButton::clicked, [this, overlay, gameOverText, scoreItem, rankItem, retryWidget, exitWidget]() {
            // 清理游戏结束界面
            myscene->removeItem(overlay);
            myscene->removeItem(gameOverText);
            myscene->removeItem(scoreItem);
            myscene->removeItem(rankItem);
            myscene->removeItem(retryWidget);
            myscene->removeItem(exitWidget);

            qDebug() << 1;
            // 重新开始游戏
            QTimer::singleShot(100, [this]() {
                // 创建新游戏
                qDebug() << 2;
                Normal_mode* ngame = new Normal_mode();
                qDebug() << 3;
                ngame->start();
                qDebug() << 4;
                // 关闭当前窗口
                this->close();
                qDebug() << 5;
                });
            });
        connect(quitButton, &QPushButton::clicked, [this, overlay, gameOverText, scoreItem, rankItem, retryWidget, exitWidget, timeItem]() {
            myscene->removeItem(overlay);
            myscene->removeItem(gameOverText);
            myscene->removeItem(scoreItem);
            myscene->removeItem(rankItem);
            myscene->removeItem(retryWidget);
            myscene->removeItem(exitWidget);
            myscene->removeItem(timeItem);

            QTimer::singleShot(100, [this]() {
                MainWindow* startW = new MainWindow();
                Normal_mode* nm = new Normal_mode();
                QObject::connect(startW, &MainWindow::startsignal, nm, &Normal_mode::start);
                startW->show();
                this->close();
                });
            });
        });
}

void Normal_mode::checkpertime() {
    qDebug() << 1;
    if (!player || !playerProxyWidget) return; //安全检查

    //检查草丛
    for (QGraphicsPixmapItem* g : grassItems) {
        checkplayeringrass();
    }
}
void Normal_mode::spawngrass() {
    QPixmap grasspixmap(grasspic);
    if (grasspixmap.isNull()) {
        qDebug() << "Failed to load grass image!";
        return;
    }
    const int grasscount = 6;
    for (int i = 0;i < grasscount;i++) {
        int x = rand() % (static_cast<int>(myscene->width()) - grasspixmap.width());
        int y = rand() % (static_cast<int>(myscene->height()) - grasspixmap.height());
        // 创建草丛项
        QGraphicsPixmapItem* grassItem = new QGraphicsPixmapItem(grasspixmap);
        grassItem->setPos(x, y);
        grassItem->setScale(1.1);
        grassItem->setZValue(3);
        myscene->addItem(grassItem);
        grassItems.push_back(grassItem);//加入容器中
    }
}
void Normal_mode::checkplayeringrass() {
    qDebug() << 2;
    if (!player || !playerProxyWidget) return; //安全检查
    QRectF pRect = playerProxyWidget->sceneBoundingRect();
    for (auto grass : grassItems) {
        //计算重叠（50%）
        QRectF gRect = grass->sceneBoundingRect();
        if (pRect.intersects(gRect)) {
            QRectF intersection = pRect.intersected(gRect);
            qreal overlap = intersection.width() * intersection.height() / (pRect.width() * pRect.height());
            if (overlap > 0.5) { player->invisible = true;return; }
        }
    }
    for (auto smoke : smokes) {
        QRectF srect = smoke->sceneBoundingRect();
        if (pRect.intersects(srect)) {
            QRectF intersection = pRect.intersected(srect);
            qreal overlap = intersection.width() * intersection.height() / (pRect.width() * pRect.height());
            if (overlap > 0.5) { player->invisible = true;return; }
        }
    }
    player->invisible = false;
}
void Normal_mode::spawnenemy() {
    Enemy* enemy = new Enemy();
    QLabel* enemylabel = new QLabel(nullptr);
    enemylabel->setAttribute(Qt::WA_TranslucentBackground); // 使背景透明
    enemy->myLable = enemylabel;
    if (enemymovieL->isValid()) {
        qDebug() << "enemy animation loaded successfully";
        qDebug() << "Movie size:" << enemymovieL->currentImage().size();
    }
    enemylabel->setMovie(enemymovieL);
    enemymovieL->setSpeed(100);
    enemymovieL->start();
    //血条
    QPixmap enemyblood(blood);
    if (enemyblood.isNull()) {
        qDebug() << "failed to load enemy blood";
    }
    else { qDebug() << "enemy blood load successfully"; }
    QGraphicsPixmapItem* enemybloodItem = new QGraphicsPixmapItem(enemyblood);
    enemybloodItem->setScale(0.05);
    QGraphicsProxyWidget* enemywidget = myscene->addWidget(enemylabel);
    int x = rand() % (static_cast<int>(myscene->width() - enemywidget->sceneBoundingRect().width()));
    int y = rand() % (static_cast<int>(myscene->height() - enemywidget->sceneBoundingRect().height()));
    enemywidget->setPos(x, y);
    QRectF enemyRect = enemywidget->sceneBoundingRect();
    qreal bgsize = myscene->sceneRect().width();
    QPointF center(bgsize / 2, bgsize / 2);
    QPointF nw(enemyRect.x(), enemyRect.y());
    qreal nwdis = sqrt((nw.x() - center.x()) * (nw.x() - center.x()) + (nw.y() - center.y()) * (nw.y() - center.y()));
    QPointF sw(enemyRect.x(), enemyRect.y() + enemyRect.height());
    qreal swdis = sqrt((sw.x() - center.x()) * (sw.x() - center.x()) + (sw.y() - center.y()) * (sw.y() - center.y()));
    QPointF ne(enemyRect.x() + enemyRect.width(), enemyRect.y());
    qreal nedis = sqrt((ne.x() - center.x()) * (ne.x() - center.x()) + (ne.y() - center.y()) * (ne.y() - center.y()));
    QPointF se(enemyRect.x() + enemyRect.width(), enemyRect.y() + enemyRect.height());
    qreal sedis = sqrt((se.x() - center.x()) * (se.x() - center.x()) + (se.y() - center.y()) * (se.y() - center.y()));
    bool outofBounds = false;

    if (nwdis >= bgsize / 2 || swdis >= bgsize / 2 || nedis >= bgsize / 2 || sedis >= bgsize / 2) {
        outofBounds = true;
    }
    if (!checkenemycollides(enemywidget)&&!outofBounds) {
        myscene->addItem(enemywidget);
        myscene->addItem(enemybloodItem);
        enemies.push_back(enemy);
        enemywidgets.push_back(enemywidget);
        enemybloods.push_back(enemybloodItem);
        enemybloodItem->setData(0, enemy->Hp);//储存原始血量
        enemybloodItem->setData(1, enemyblood.width());//储存宽高
        enemybloodItem->setData(2, enemyblood.height());
    }
    else { 
        myscene->removeItem(enemywidget);
        spawnenemy(); }
}
Enemy* Normal_mode::checkcollides() {
    qDebug() << 28;
    if (!player || !playerProxyWidget)return nullptr;
    for (size_t i = 0;i < enemies.size();i++) {
        if (playerProxyWidget->collidesWithItem(enemywidgets[i])) {
            return enemies[i];
        }
    }
    return nullptr;
}
Enemy* Normal_mode::checkenemycollides(QGraphicsProxyWidget* enemywidget) {
    qDebug() << 29;
    if (!player || !playerProxyWidget)return nullptr;
    for (size_t i = 0;i < enemies.size();i++) {
        if (enemywidget == enemywidgets[i]) { continue; }
        if (enemywidget->collidesWithItem(enemywidgets[i])) {
            return enemies[i];
        }
    }
    return nullptr;
}
bool Normal_mode::checkcollideswithme(QGraphicsProxyWidget* enemywidget) {
    qDebug() << 30;
    if (!player || !playerProxyWidget)return false;
    if (enemywidget->collidesWithItem(playerProxyWidget)) {
        return true;
    }
    return false;
}
void Normal_mode::keyPressEvent(QKeyEvent* event) {
    if (!player || !playerProxyWidget) return; //安全检查
    switch (event->key()) {
    case Qt::Key_W:
        keyW = true;
        break;
    case Qt::Key_A:
        keyA = true;
        break;
    case Qt::Key_S:
        keyS = true;
        break;
    case Qt::Key_D:
        keyD = true;
        break;
    case Qt::Key_Space: {
        if (dodgeCD == 0) {
            dodgeCD = 5;
            dodge();
        }
        break;
    }
    case Qt::Key_X: {
        keyX = true;
        break;
    }
    case Qt::Key_V: {
        keyV = true;
        break;
    }
    default:
        QWidget::keyPressEvent(event);
    }
}
void Normal_mode::keyReleaseEvent(QKeyEvent* event) {
    if (!player || !playerProxyWidget) return; //安全检查
    switch (event->key()) {
    case Qt::Key_W:
        keyW = false;
        break;
    case Qt::Key_A:
        keyA = false;
        break;
    case Qt::Key_S:
        keyS = false;
        break;
    case Qt::Key_D:
        keyD = false;
        break;
    case Qt::Key_X:
        keyX = false;
        break;
    case Qt::Key_V:
        keyV = false;
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}
void Normal_mode::mousePressEvent(QMouseEvent* event) {
    if (!player || !playerProxyWidget) return; //安全检查
    if (event->button() == Qt::LeftButton) {
        mousePos = view->mapToScene(event->pos());
        if (keyX) {
            spawngrenade(mousePos);
        }
        else if (keyV) {
            spawnsmokegrenade(mousePos);
        }
        else {
            MousePressed = true;
        }  
    }
    if (event->button() == Qt::RightButton) {
        // 将鼠标点击位置转换为场景坐标
        QPointF clickPos = view->mapToScene(event->pos());
        targetEnemy(clickPos);
    }
}
void Normal_mode::mouseReleaseEvent(QMouseEvent* event) {
    if (!player || !playerProxyWidget) return; //安全检查
    if (event->button() == Qt::LeftButton&&MousePressed) {
        MousePressed = false;
        shoot();
    }
}
void Normal_mode::mouseMoveEvent(QMouseEvent* event) {
    //鼠标移动时更新位置
    if (MousePressed) {
        mousePos = view->mapToScene(event->pos());
    }
}
//void Normal_mode::shoot() {
//    if (!player || !playeritem) return; //安全检查
//
//    QPixmap bulletpixmap(player->weapon->ppos);
//    QGraphicsPixmapItem* bullet = new QGraphicsPixmapItem(bulletpixmap);
//    bullet->setScale(1);
//    bullet->setPos(playeritem->pos());
//    //计算方向
//    QPointF direction = mousePos - playeritem->pos();
//    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
//    if (length > 0) {
//        direction.rx() = direction.x() / length;
//        direction.ry() = direction.y() / length;
//        myscene->addItem(bullet);
//        bullets.push_back(bullet);
//        bullet->setData(0, direction.x());  // 存储x方向
//        bullet->setData(1, direction.y());  // 存储y方向
//    }
//}

//void Normal_mode::updatebulletspos() {
//    for (auto it = bullets.begin(); it != bullets.end();) {
//        QGraphicsPixmapItem* bu = *it;
//        qreal dx = bu->data(0).toDouble();
//        qreal dy = bu->data(1).toDouble();
//        bu->moveBy(dx * bulletSpeed, dy * bulletSpeed);
//        //检查命中
//        QRectF buRect = bu->sceneBoundingRect();
//        bool shouldRemove = false;
//        if (!myscene->sceneRect().contains(buRect)) {
//            shouldRemove = true;
//        }
//        for (size_t i = 0;i < enemyItems.size();i++) {
//            if (i >= enemies.size()) break;
//            if (bu->collidesWithItem(enemyItems[i])) {
//                shouldRemove = true;
//                enemies[i]->Hp -= player->damage;
//                break;
//            }  
//        }
//        if (shouldRemove) {
//            myscene->removeItem(bu);
//            delete bu;
//            it = bullets.erase(it);
//        }
//        else {
//            ++it;
//        }
//    }
//}
void Normal_mode::updatePlayerPosition() {
    qDebug() << 3;
    if (!player || !playerProxyWidget) return; //安全检查
    QPointF currentpos = playerProxyWidget->pos();
    qreal ax = 0, ay = 0;
    static QElapsedTimer timer;
    static bool firstFrame = true;
    if (firstFrame) {
        timer.start();
        firstFrame = false;
        return;
    }
    qreal t = timer.elapsed() / 1000.0; // 转换为秒
    timer.restart();
    // 限制时间步长，防止大延迟导致的跳跃
    if (t > 0.1) t = 0.1;
    if (keyW) ay -= player->aspeed;
    if (keyA) ax -= player->aspeed;
    if (keyS) ay += player->aspeed;
    if (keyD) ax += player->aspeed;
    // 如果是斜向移动，标准化加速度
    int ea = ax;int nor = ay;
    if (ax != 0 && ay != 0) {
        qreal length = sqrt(ax * ax + ay * ay);
        ax = ax / length * player->aspeed;
        ay = ay / length * player->aspeed;
    }
    //阻力,计算速度
    ax += xfa;
    ay += yfa;
    player->xspeed += ax * t;
    player->yspeed += ay * t;
    // 限制最大速度
    const qreal maxSpeed = 500.0; 
    qreal speed = sqrt(player->xspeed * player->xspeed + player->yspeed * player->yspeed);
    /*qDebug() << "speed:" << speed;*/
    if (speed > maxSpeed) {
        player->xspeed = player->xspeed / speed * maxSpeed;
        player->yspeed = player->yspeed / speed * maxSpeed;
    }
    // 如果速度非常小，设为0
    const qreal minSpeed = 5;
    if (fabs(player->xspeed) < minSpeed) player->xspeed = 0;
    if (fabs(player->yspeed) < minSpeed) player->yspeed = 0;
    qreal dx = player->xspeed * t;
    qreal dy = player->yspeed * t;
    QPointF originalpos = playerProxyWidget->scenePos();
    if (dx != 0 || dy != 0) {
        playerProxyWidget->moveBy(dx, dy);
    }
    //// 检查碰撞和边界
    /*QRectF sceneRect = myscene->sceneRect();*/
    QRectF playerRect = playerProxyWidget->sceneBoundingRect();
    QRectF sceneRect = myscene->sceneRect();
    QPointF center = sceneRect.center();
    QPointF nw(playerRect.topLeft());
    QPointF sw(playerRect.bottomLeft());
    QPointF ne(playerRect.topRight());
    QPointF se(playerRect.bottomRight());

    qreal nwdis = QLineF(nw, center).length();
    qreal swdis = QLineF(sw, center).length();
    qreal nedis = QLineF(ne, center).length();
    qreal sedis = QLineF(se, center).length();
    qreal radius = sceneRect.width() / 2;
    bool outofBounds = nwdis >= radius || swdis >= radius || nedis >= radius || sedis >= radius;
    if (checkcollides() || outofBounds) {
        // 如果碰撞或超出边界，恢复位置
        playerProxyWidget->setPos(currentpos);
        if (checkcollides()) {
            /*playerProxyWidget->setPos(originalpos);*/
            /*qDebug() << "collide!";
            Enemy* other = checkcollides();
            qreal tx = player->xspeed;
            player->xspeed = other->xspeed;
            other->xspeed = tx;
            qreal ty = player->yspeed;
            player->yspeed = other->yspeed;
            other->yspeed = ty;*/
            //音效
            
        }
        //边界反弹
        if (outofBounds) {
            qDebug() << "player out!";
            player->xspeed *= -0.5;
            player->yspeed *= -0.5;
        }
    }
    view->centerOn(playerProxyWidget);
    
    if (ea == 0 && nor == 0) {
        if (player->dodgestate) {
            if (currentPlayerMovie == playerMovieMoving || currentPlayerMovie == playerMovieRight) {
                switchanime(playerDodgeMovie);
            }
            else { switchanime(playerDodgeMovieL); }
        }
        else {
            if (currentPlayerMovie == playerMovieMoving) {
                switchanime(playerMovieRight);
            }
            else if (currentPlayerMovie == playerMovieMovingL) { switchanime(playerMovieLeft); }
        }
    }
    else {
        if (player->dodgestate) {
            if (ea > 0) { switchanime(playerDodgeMovie); }
            else if(ea<0){ switchanime(playerDodgeMovieL); }
        }
        else {
            if (ea > 0) { switchanime(playerMovieMoving); }
            else if (ea < 0) {
                switchanime(playerMovieMovingL);
            }
        }
    }
}
//敌人朝着玩家移动
void Normal_mode::updateEnemyPosition() {
    qDebug() << 4;
    if (enemies.empty() || !player || !playerProxyWidget) return;//安全检查
    QPointF playerPos = playerProxyWidget->pos();
    static QElapsedTimer timer;
    static bool firstFrame = true;
    if (firstFrame) {
        timer.start();
        firstFrame = false;
        return;
    }
    qreal t = timer.elapsed() / 1000.0; // 转换为秒
    timer.restart();
    for (size_t i = 0; i < enemywidgets.size();) {
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        Enemy* enemy = enemies[i];
        QGraphicsPixmapItem* blood = enemybloods[i];
        //死亡清除
        if (enemy->Hp <= 0) {
            qDebug() << "enemy died";
            //死亡动画
            deathanime(0,enemywidget->scenePos(),enemywidget->sceneBoundingRect().width(),enemywidget->sceneBoundingRect().height());
            for (size_t w = 0; w < enemy->weaponwidget.size(); w++) {
                if (enemy->weaponwidget[w]) {
                    myscene->removeItem(enemy->weaponwidget[w]);
                    delete enemy->weaponwidget[w];
                }
                if (w < enemy->weapons.size() && enemy->weapons[w]) {
                    delete enemy->weapons[w];
                }
                
            }
            for (size_t j = 0; j < weaponbullets.size();) {
                if (weaponbullets[j]->master == enemy) {
                    myscene->removeItem(enemybullets[j]);
                    weaponbullets.erase(weaponbullets.begin() + j);
                    enemybullets.erase(enemybullets.begin() + j);
                }
                else {
                    j++;
                }
            }
            // 如果是目标敌人，清除目标
            if (target == enemy) {
                target = nullptr;
                delete circleitem;
                targetEnemywidget = nullptr;
                circleitem = nullptr;
            }
            myscene->removeItem(enemywidget);
            enemies.erase(enemies.begin() + i);
            enemywidgets.erase(enemywidgets.begin() + i);
            enemybloods.erase(enemybloods.begin() + i);
            delete enemywidget;
            delete enemy;
            delete blood;

            continue;
        }
        else { i++; }
        QPointF currentPos = enemywidget->pos();
        QPointF direction = playerPos - currentPos;
        qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {//避免除0
            qreal ax = 0;qreal ay = 0;
            QGraphicsPixmapItem* tool = nullptr;
            qreal minlen = 250;
            qreal tax = 00;
            qreal tay = 0;
            for (auto it : tools) {
                if (QLineF(enemywidget->sceneBoundingRect().center(), it->sceneBoundingRect().center()).length() > 200) {
                    continue;
                }
                else {
                    QPointF d = it->sceneBoundingRect().center() - enemywidget->sceneBoundingRect().center();
                    qreal len = sqrt(d.x() * d.x() + d.y() * d.y());
                    if (len > 0&&len<minlen) {
                        minlen = len;
                        tool = it;
                        tax = enemy->aspeed * d.x() / len;
                        tay = enemy->aspeed * d.y() / len;
                        break;
                    }
                }
            }
            if (tool) {
                ax = tax;
                ay = tay;
            }
            else if (!(player->invisible)&&QLineF(enemywidget->sceneBoundingRect().center(),playerProxyWidget->sceneBoundingRect().center()).length()<400) {
                ax= enemy->aspeed *direction.x() / length;
                ay= enemy->aspeed *direction.y() / length;

            }
            else {
                ax = rx[(i+randnum)%16];
                ay = ry[(i+randnum)%16];
            }
            //阻力
            qreal u = 0.5;
            ax -= enemy->xspeed * u;
            
            ay -= enemy->yspeed * u;
            enemy->xspeed += ax * t;
            enemy->yspeed += ay * t;
            // 限制最大速度
            const qreal maxSpeed = 200.0;
            qreal speed = sqrt(enemy->xspeed * enemy->xspeed + enemy->yspeed * enemy->yspeed);
            if (speed > maxSpeed) {
                enemy->xspeed = enemy->xspeed / speed * maxSpeed;
                enemy->yspeed = enemy->yspeed / speed * maxSpeed;
            }

            // 如果速度非常小，设为0
            const qreal minSpeed = 5;
            if (fabs(enemy->xspeed) < minSpeed) enemy->xspeed = 0;
            if (fabs(enemy->yspeed) < minSpeed) enemy->yspeed = 0;
            QPointF originalpos = enemywidget->pos();
            qDebug() << "enemy pos:" << originalpos.x() << " " << originalpos.y();
            enemywidget->moveBy(enemy->xspeed*t, enemy->yspeed *t);
            //面朝方向
            enemy->myLable->setMovie(direction.x() >= 0 ? enemymovieR : enemymovieL);
            enemy->myLable->movie()->start();
            /*qDebug() << "敌人在移动" << direction.rx() * moveSpeed << direction.ry() * moveSpeed;*/
            // 检查碰撞和边界
            QRectF enemyRect = enemywidget->sceneBoundingRect();
            qreal bgsize = myscene->sceneRect().width();
            QPointF center=myscene->sceneRect().center();
            QPointF nw(enemyRect.x(), enemyRect.y());
            qreal nwdis = sqrt((nw.x() - center.x()) * (nw.x() - center.x()) + (nw.y() - center.y()) * (nw.y() - center.y()));
            QPointF sw(enemyRect.x(), enemyRect.y() + enemyRect.height());
            qreal swdis = sqrt((sw.x() - center.x()) * (sw.x() - center.x()) + (sw.y() - center.y()) * (sw.y() - center.y()));
            QPointF ne(enemyRect.x() + enemyRect.width(), enemyRect.y());
            qreal nedis = sqrt((ne.x() - center.x()) * (ne.x() - center.x()) + (ne.y() - center.y()) * (ne.y() - center.y()));
            QPointF se(enemyRect.x() + enemyRect.width(), enemyRect.y() + enemyRect.height());
            qreal sedis = sqrt((se.x() - center.x()) * (se.x() - center.x()) + (se.y() - center.y()) * (se.y() - center.y()));
            bool outofBounds = false;
         
            if (nwdis >= bgsize / 2 || swdis >= bgsize / 2 || nedis >= bgsize / 2 || sedis >= bgsize / 2) {
                outofBounds = true;
            }
            if (outofBounds) {
                qDebug() << "out!";
                enemy->xspeed *= -0.5;
                enemy->yspeed *= -0.5;
                enemywidget->setPos(originalpos);
            }
            if (checkenemycollides(enemywidget)) {
                /*enemywidget->setPos(originalpos);*/
                Enemy* other = checkenemycollides(enemywidget);
                qreal tx = enemy->xspeed;
                enemy->xspeed = other->xspeed;
                other->xspeed = tx;
                qreal ty = enemy->yspeed;
                enemy->yspeed = other->yspeed;
                other->yspeed = ty;
            }
            if (checkcollideswithme(enemywidget)) {
                enemywidget->setPos(originalpos);
                qreal tx = player->xspeed;
                player->xspeed = enemy->xspeed;
                enemy->xspeed = tx;
                qreal ty = player->yspeed;
                player->yspeed = enemy->yspeed;
                enemy->yspeed = ty;
                if (randnum % 2 == 0) {
                    man->play();
                }
                if (randnum % 2 == 1) {
                    fei->play();
                }
            }
        }
    }
}
void Normal_mode::enemyattack() {
    if (!player || !playerProxyWidget) return; //安全检查
    for (size_t i = 0;i < enemies.size();i++) {
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        Enemy* enemy = enemies[i];
        if (!enemywidget || !enemy || enemy->weaponwidget.empty())continue;
        //寻敌
        qreal minDistance = 5000;
        int t = -1;
        bool targetIsPlayer = false;
        QPointF center = enemywidget->sceneBoundingRect().center();
        for (size_t j = 0;j < enemies.size();j++) {
            QGraphicsProxyWidget* it = enemywidgets[j];
            if (it == enemywidget)continue;
            QPointF enemycenter = it->sceneBoundingRect().center();
            qreal dis = QLineF(center,enemycenter).length();
            if (dis < minDistance) {
                minDistance = dis;
                t = j;
            }
        }
        QPointF mycenter = playerProxyWidget->sceneBoundingRect().center();
        if (QLineF(center, mycenter).length() < minDistance&&!player->invisible) {
            minDistance = QLineF(center, mycenter).length();
            targetIsPlayer = true;
        }
        const qreal maxTargetDistance = 400.0;
        if (minDistance <= maxTargetDistance) {
            //攻击
            if (enemy->weaponwidget.empty() || enemy->weapons.empty()) continue;
            if (targetIsPlayer) {
                QGraphicsProxyWidget* weaponWidget = enemy->weaponwidget.back();
                Weapon* weapon = enemy->weapons.back();
                if (!weaponWidget || !weapon) continue;
                weapon->target = nullptr;
                weapon->targetwidget = playerProxyWidget;
                weapon->master = enemy;
                QPointF direction = playerProxyWidget->sceneBoundingRect().center() - enemywidget->sceneBoundingRect().center();
                qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
                if (length > 0) {
                    QRectF rect = enemywidget->sceneBoundingRect();
                    const qreal centerX = rect.x() + rect.width() / 2;
                    const qreal centerY = rect.y() + rect.height() / 2;
                    direction.rx() = direction.x() / length;
                    direction.ry() = direction.y() / length;
                    enemy->weapons.pop_back();enemy->weaponwidget.pop_back();
                    qreal rad = direction.y() >= 0 ? acos(direction.x()) : 2 * M_PI - acos(direction.x());
                    weaponWidget->setPos(centerX, centerY);
                    QRectF weaponRect = weaponWidget->boundingRect();
                    weaponWidget->setTransformOriginPoint(weaponRect.width() / 2, weaponRect.height() / 2);
                    weaponWidget->setRotation(rad * 180 / M_PI);
                    weaponWidget->setData(0, direction.x());
                    weaponWidget->setData(1, direction.y());
                    enemybullets.push_back(weaponWidget);
                    weaponbullets.push_back(weapon);
                    qDebug() << "Player is closest target for enemy" << i;
                }
            }
            else if (t >= 0 && t < enemies.size() && t < enemywidgets.size()) {
                QGraphicsProxyWidget* weaponWidget = enemy->weaponwidget.back();
                Weapon* weapon = enemy->weapons.back();
                if (!weaponWidget || !weapon) continue;
                weapon->target = enemies[t];
                weapon->targetenemy = enemywidgets[t];
                weapon->targetwidget = nullptr;
                weapon->master = enemy;
                QGraphicsProxyWidget* targetenemy = weapon->targetenemy;
                QPointF direction = targetenemy->sceneBoundingRect().center() - enemywidget->sceneBoundingRect().center();
                qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
                if (length > 0) {
                    QRectF rect = enemywidget->sceneBoundingRect();
                    const qreal centerX =rect.x() + rect.width() / 2 ;
                    const qreal centerY = rect.y() + rect.height() / 2 ;
                    direction.rx() = direction.x() / length;
                    direction.ry() = direction.y() / length;
                    enemy->weapons.pop_back();enemy->weaponwidget.pop_back();
                    qreal rad = direction.y() >= 0 ? acos(direction.x()) : 2 * M_PI - acos(direction.x());
                    weaponWidget->setPos(centerX, centerY);
                    QRectF firerect = weaponWidget->sceneBoundingRect();
                    weaponWidget->setTransformOriginPoint(firerect.center());
                    weaponWidget->setRotation(rad * 180 / M_PI);
                    weaponWidget->setData(0, direction.x());
                    weaponWidget->setData(1, direction.y());
                    enemybullets.push_back(weaponWidget);
                    weaponbullets.push_back(weapon);
                    qDebug() << "target is other enemy";
                }
            }
            
        }
    }
}
void Normal_mode::updateenemybullets() {
    qDebug() << 5;
    if (!player || !playerProxyWidget) return; //安全检查
    for (size_t i = 0;i < weaponbullets.size() && i < enemybullets.size();) {
        QGraphicsProxyWidget* weaponWidget = enemybullets[i];
        Weapon* weapon = weaponbullets[i];
        if (!weaponWidget || !weapon) {
            // 安全移除无效子弹
            if (i < enemybullets.size()) enemybullets.erase(enemybullets.begin() + i);
            if (i < weaponbullets.size()) weaponbullets.erase(weaponbullets.begin() + i);
            continue;
        }
        QPointF direction(0,0);
        bool hasValidTarget = false;
        if (weapon->targetwidget) {
            QPointF playerCenter = playerProxyWidget->sceneBoundingRect().center();
            QPointF weaponCenter = weaponWidget->sceneBoundingRect().center();
            direction = playerCenter - weaponCenter;
            hasValidTarget = true;
       
        }
        else if (weapon->targetenemy) {
            bool found = false;
            for (size_t j = 0; j < enemywidgets.size(); j++) {
                if (enemywidgets[j] == weapon->targetenemy) {
                    found = true;
                    break;
                }
            }
            if (found) {
                QPointF targetCenter = weapon->targetenemy->sceneBoundingRect().center();
                QPointF weaponCenter = weaponWidget->sceneBoundingRect().center();
                direction = targetCenter - weaponCenter;
                hasValidTarget = true;
            }
        }
        if (!hasValidTarget) {
     
            if (weaponWidget->data(0).isValid() && weaponWidget->data(1).isValid()) {
                direction.setX(weaponWidget->data(0).toDouble());
                direction.setY(weaponWidget->data(1).toDouble());
            }
            else {
                qreal angle = weaponWidget->rotation() * M_PI / 180.0;
                direction.setX(cos(angle));
                direction.setY(sin(angle));
            }
        }
        qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            direction.rx() = direction.x() / length;
            direction.ry() = direction.y() / length;
        }
        weaponWidget->moveBy(direction.x() * bulletSpeed, direction.y() * bulletSpeed);
        QRectF weaponrect = weaponWidget->sceneBoundingRect();
        bool shouldRemove = false;
        //检查命中
        if (!myscene->sceneRect().contains(weaponrect)) {
            shouldRemove = true;
        }
        for (size_t j = 0;j < enemywidgets.size();j++) {
            if (j >= enemies.size()) break;
            if (enemies[j] == weapon->master)continue;
            if (weaponWidget->collidesWithItem(enemywidgets[j])) {
                shouldRemove = true;
                if (weapon->master) {
                    if (!enemies[j]->weaponwidget.empty()) {
                        QGraphicsProxyWidget* widget = enemies[j]->weaponwidget.back();
                        myscene->removeItem(widget);
                        enemies[j]->weapons.pop_back();enemies[j]->weaponwidget.pop_back();
                        delete widget;
                    }
                    else { enemies[j]->Hp -= player->damage; }
                }
                break;
            }
        }
        if (!shouldRemove && weapon->master && weaponWidget->collidesWithItem(playerProxyWidget)) {
            shouldRemove = true;
            if (weapon->master) {
                if (!fireWidgets.empty()) {
                    QGraphicsProxyWidget* widget = fireWidgets.back();
                    myscene->removeItem(widget);
                    fireWidgets.pop_back();
                    delete widget;
                }
                else { player->Hp -= weapon->master->damage; qDebug() << "my Hp:" << player->Hp; }
            }
        }
        if (shouldRemove) {
            myscene->removeItem(weaponWidget);
            enemybullets.erase(enemybullets.begin() + i);
            weaponbullets.erase(weaponbullets.begin() + i);
            delete weaponWidget;
            delete weapon;
        }
        else {
            i++;
        }
    }
}
void Normal_mode::checkdeath() {
    qDebug() << 6;
    if (player && player->Hp <= 0) {
        deathanime(1,playerProxyWidget->scenePos(),playerProxyWidget->sceneBoundingRect().width(),playerProxyWidget->sceneBoundingRect().height());
        checkTimer->stop();
        over->play();
        end();
        
    }
    if (enemies.empty()) {
        checkTimer->stop();
        end();
    }
}
void Normal_mode::spawntool(){
    qDebug() << 7;
    int t = rand() % 4;
    QPixmap tool;
    switch (t)
    {
    case(0): { tool.load(heart);break; }
    case(1): { tool.load(speedy);break; }
    case(2): { tool.load(heal);break; }
    case(3): { tool.load(addweapon); }
    default:
        break;
    }
    int x = rand() % (static_cast<int>(myscene->width()) - tool.width());
    int y = rand() % (static_cast<int>(myscene->height()) - tool.height());
    QGraphicsPixmapItem* toolItem = new QGraphicsPixmapItem(tool);
    toolItem->setPos(x, y);
    toolItem->setScale(0.1);
    QRectF toolrect = toolItem->sceneBoundingRect();
    qreal bgsize = myscene->sceneRect().width();
    QPointF center=myscene->sceneRect().center();
    QPointF nw(toolrect.x(), toolrect.y());
    qreal nwdis = sqrt((nw.x() - center.x()) * (nw.x() - center.x()) + (nw.y() - center.y()) * (nw.y() - center.y()));
    QPointF sw(toolrect.x(), toolrect.y() + toolrect.height());
    qreal swdis = sqrt((sw.x() - center.x()) * (sw.x() - center.x()) + (sw.y() - center.y()) * (sw.y() - center.y()));
    QPointF ne(toolrect.x() + toolrect.width(), toolrect.y());
    qreal nedis = sqrt((ne.x() - center.x()) * (ne.x() - center.x()) + (ne.y() - center.y()) * (ne.y() - center.y()));
    QPointF se(toolrect.x() + toolrect.width(), toolrect.y() + toolrect.height());
    qreal sedis = sqrt((se.x() - center.x()) * (se.x() - center.x()) + (se.y() - center.y()) * (se.y() - center.y()));
    bool outofBounds = false;

    if (nwdis >= bgsize / 2 || swdis >= bgsize / 2 || nedis >= bgsize / 2 || sedis >= bgsize / 2) {
        outofBounds = true;
    }
    if (outofBounds) {
        spawntool();
    }
    else {
        myscene->addItem(toolItem);
        toolItem->setData(0, t);//存储类型
        tools.push_back(toolItem);
    }
}
void Normal_mode::updateenemystate() {
    if (!player || enemies.empty())return;
    for (size_t i = 0;i < enemies.size();i++) {
        Enemy* enemy = enemies[i];
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        for (auto it = tools.begin();it != tools.end();) {
            QGraphicsPixmapItem* toolItem = *it;
            if (enemywidget->collidesWithItem(toolItem)) {
                switch (toolItem->data(0).toInt())
                {
                case(0): {
                    enemy->Hp += 10;
                    qDebug() << "enemy picked up health, new HP:" << player->Hp;
                    break;
                }
                case(3): {
                    for (size_t i = 0;i < 5;i++) {
                        spawnweapon(enemywidget,enemy);
                    }
                }
                default:
                    break;
                }
                myscene->removeItem(toolItem);
                it = tools.erase(it);
                delete toolItem;
            }
            else { ++it; }
        }
    }
}
void Normal_mode::updataplayerstate() {
    qDebug() << 8;
    if (!player || !playerProxyWidget) return; //安全检查
    for (auto it = tools.begin();it != tools.end();) {
        QGraphicsPixmapItem* toolItem = *it;
        if (playerProxyWidget->collidesWithItem(toolItem)) {
            switch (toolItem->data(0).toInt())
            {
            case(0): {
                player->Hp += 10;
                qDebug() << "Player picked up health, new HP:" << player->Hp;
                break;
            }
            case(1): {
                mygrenade++;
                mysmokegrenade++;
                qDebug() << "Player picked up a grenade and a smokegrenade" << player->damage;
                break;
            }
            case(2): {
                speedybuffs.push_back("speedyrun");
                qDebug() << "Player picked up speed boost";
                QTimer::singleShot(3000, [this]() {//一段时间后移除buff
                    for (auto it = speedybuffs.begin(); it != speedybuffs.end(); ++it) {
                        if (!player || !playerProxyWidget) return;
                        if (*it == "speedyrun") {
                            speedybuffs.erase(it);
                            checkbuff();
                            break;  // 只移除一个buff
                        }
                    }
                    });
                break;
            }
            //加5个武器
            case(3): {
                for (size_t i = 0;i < 5;i++) {
                    spawnweapon(playerProxyWidget,nullptr);
                }
            }
            default:
                break;
            }
            myscene->removeItem(toolItem);
            it=tools.erase(it);
            delete toolItem;
            tool->play();
        }
        else { ++it; }
    }
}
void Normal_mode::checkbuff() {
    qDebug() << 9;
    if (!player || !playerProxyWidget) return; //安全检查
    int countspeed = 0;//加速个数
    for (auto buff : speedybuffs) {
        if (buff == "speedyrun") {
            countspeed++;
        }
    }
    player->aspeed = initaspeed + countspeed * 40;
    player->maxspeed = initmaxv + countspeed * 70;
}
void Normal_mode::spawnfire() {
    qDebug() << 10;
    if (!player)return;
    const int amount = 4;
    for (size_t i = 0;i < enemies.size();i++) {
        QGraphicsProxyWidget* enemywidget= enemywidgets[i];
        Enemy* enemy = enemies[i];
        QRectF rect = enemywidget->sceneBoundingRect();
        const qreal r = rect.height();
        const qreal centerX = rect.x() + rect.width() / 2;
        const qreal centerY = rect.y() + rect.height() / 2;
        for (size_t i = 0;i < amount;i++) {
            QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
            firelabel->setAttribute(Qt::WA_TranslucentBackground);
            firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
            QMovie* firegif = new QMovie(firepos);
            firegif->setCacheMode(QMovie::CacheAll);
            if (firegif->isValid()) {
                qDebug() << "Weapon GIF loaded successfully";
            }
            else {
                qDebug() << "Failed to load fire GIF!";
                delete firegif;
                delete firelabel;
                continue;
            }
            firegif->setScaledSize(QSize(30, 30));
            firelabel->setMovie(firegif);
            firegif->start();
            QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
            //设置角度位置
            qreal angle = i * 360 / amount;
            QRectF firerect = fireWidget->sceneBoundingRect();
            qreal rad = angle * (2 * M_PI) / 360;
            qreal distance =r;/**(1 + sin(rad))*///函数图像
            qreal x = centerX + distance * cos(rad) - firelabel->width() / 2;
            qreal y = centerY + distance * sin(rad) - firelabel->height() / 2;
            fireWidget->setPos(x, y);
            fireWidget->setTransformOriginPoint(firerect.center());
            fireWidget->setRotation(angle);
            Weapon* weapon = new Weapon();
            enemy->weapons.push_back(weapon);
            enemy->weaponwidget.push_back(fireWidget);
        }
    }
    QRectF rect = playerProxyWidget->sceneBoundingRect();
    const qreal r = rect.height();
    const qreal centerX = rect.x() + rect.width() / 2;
    const qreal centerY = rect.y() + rect.height() / 2;
    for (int i = 0;i < amount;i++) {
        QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
        firelabel->setAttribute(Qt::WA_TranslucentBackground);
        firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
        QMovie* firegif = new QMovie(firepos);
        firegif->setCacheMode(QMovie::CacheAll);
        if (firegif->isValid()) {
            qDebug() << "Fire GIF loaded successfully";
        }
        else {
            qDebug() << "Failed to load fire GIF!";
            delete firegif;
            delete firelabel;
            continue;
        }
        firegif->setScaledSize(QSize(30, 30));
        firelabel->setMovie(firegif);
        firegif->start();
        QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
        //设置角度位置
        qreal angle = i * 360 / amount;
        QRectF firerect = fireWidget->sceneBoundingRect();
        qreal rad = angle * (2 * M_PI) / 360;
        qreal distance = r;/**(1 + sin(rad))*///函数图像
        qreal x = centerX + distance * cos(rad) - firelabel->width() / 2;
        qreal y = centerY + distance * sin(rad) - firelabel->height() / 2;
        fireWidget->setPos(x,y);
        fireWidget->setTransformOriginPoint(firerect.center());
        fireWidget->setRotation(angle);
        fireWidgets.push_back(fireWidget);
    }
    orbitTimer = new QTimer(this);
    orbitTimer->start(16);
    connect(orbitTimer, &QTimer::timeout, this, &Normal_mode::updatefirepos);
    spawnbuTimer = new QTimer(this);
    spawnbuTimer->start(1500);
    connect(spawnbuTimer, &QTimer::timeout, this, &Normal_mode::spawnfireps);
}
void Normal_mode::updatefirepos(){
    qDebug() << 11;
    if (!playerProxyWidget) return;
    static qreal orbitAngle = 0.0;
    orbitAngle += 1;
    if (orbitAngle >= 360)orbitAngle -= 360;
    int amount = fireWidgets.size();
    QRectF rect = playerProxyWidget->sceneBoundingRect();
    const qreal r = rect.height();
    const qreal centerX = rect.x() + rect.width() / 2;
    const qreal centerY = rect.y() + rect.height() / 2;
    for (int i = 0;i <amount;i++) {
        if (i >= fireWidgets.size()) break;  // 安全检查
        qreal angle = i * 360 / amount+orbitAngle;
        QGraphicsProxyWidget* fireWidget = fireWidgets[i];
        QRectF firerect = fireWidget->sceneBoundingRect();
        qreal rad = angle * (2 * M_PI) / 360;
        qreal distance = r*sqrt(amount)/2;
        player->myr = distance;
        qreal x = centerX + distance * cos(rad) - firerect.width() / 2;
        qreal y = centerY + distance * sin(rad) - firerect.height() / 2;
        fireWidget->setPos(x, y);
    }
    for (size_t i = 0;i < enemies.size();i++) {
        QGraphicsProxyWidget* enemywidget =enemywidgets[i];
        Enemy* enemy = enemies[i];
        int amount = enemy->weapons.size();
        QRectF rect = enemywidget->sceneBoundingRect();
        const qreal r = rect.height();
        const qreal centerX = rect.x() + rect.width() / 2;
        const qreal centerY = rect.y() + rect.height() / 2;
        for (int i = 0;i < amount;i++) {
            if (i >= enemy->weapons.size()) break;  // 安全检查
            qreal angle = i * 360 / amount + orbitAngle;
            QGraphicsProxyWidget* fireWidget = enemy->weaponwidget[i];
            QRectF firerect = fireWidget->sceneBoundingRect();
            qreal rad = angle * (2 * M_PI) / 360;
            qreal distance = r*sqrt(enemy->weapons.size())/2;
            enemy->enemyr = distance;
            qreal x = centerX + distance * cos(rad) - firerect.width() / 2;
            qreal y = centerY + distance * sin(rad) - firerect.height() / 2;
            fireWidget->setPos(x, y);
        }
    }
}
void Normal_mode::spawnfireps() {
    qDebug() << 12;
    if (fireWidgets.size() < 10) {
        QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
        firelabel->setAttribute(Qt::WA_TranslucentBackground);
        firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
        QMovie* firegif = new QMovie(firepos);
        firegif->setCacheMode(QMovie::CacheAll);
        if (firegif->isValid()) {
            qDebug() << "Fire GIF loaded successfully";
        }
        else {
            qDebug() << "Failed to load fire GIF!";
        }
        firegif->setScaledSize(QSize(30, 30));
        firelabel->setMovie(firegif);
        firegif->start();
        QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
        fireWidgets.push_back(fireWidget);
    }
    for (size_t i = 0;i < enemies.size();i++) {
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        Enemy* enemy = enemies[i];
        if (enemy->weaponwidget.size() >= 10)continue;
        QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
        firelabel->setAttribute(Qt::WA_TranslucentBackground);
        firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
        QMovie* firegif = new QMovie(firepos);
        firegif->setCacheMode(QMovie::CacheAll);
        if (firegif->isValid()) {
            qDebug() << "Weapon GIF loaded successfully";
        }
        else {
            qDebug() << "Failed to load fire GIF!";
        }
        firegif->setScaledSize(QSize(30, 30));
        firelabel->setMovie(firegif);
        firegif->start();
        QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
        enemy->weaponwidget.push_back(fireWidget);
        Weapon* weapon = new Weapon();
        enemy->weapons.push_back(weapon);
    }
}
void Normal_mode::spawnweapon(QGraphicsProxyWidget* character,Enemy* enemy) {
    qDebug() << 13;
    if (!player || enemies.empty())return;
    if (!character)return;
    if (character == playerProxyWidget) {
        QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
        firelabel->setAttribute(Qt::WA_TranslucentBackground);
        firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
        QMovie* firegif = new QMovie(firepos);
        firegif->setCacheMode(QMovie::CacheAll);
        if (firegif->isValid()) {
            qDebug() << "Fire GIF loaded successfully";
        }
        else {
            qDebug() << "Failed to load fire GIF!";
        }
        firegif->setScaledSize(QSize(30, 30));
        firelabel->setMovie(firegif);
        firegif->start();
        QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
        fireWidgets.push_back(fireWidget);
    }
    else {
        QGraphicsProxyWidget* enemywidget = character;
        QLabel* firelabel = new QLabel(nullptr); // 设置为顶层窗口部件
        firelabel->setAttribute(Qt::WA_TranslucentBackground);
        firelabel->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除
        QMovie* firegif = new QMovie(firepos);
        firegif->setCacheMode(QMovie::CacheAll);
        if (firegif->isValid()) {
            qDebug() << "Weapon GIF loaded successfully";
        }
        else {
            qDebug() << "Failed to load fire GIF!";
        }
        firegif->setScaledSize(QSize(30, 30));
        firelabel->setMovie(firegif);
        firegif->start();
        QGraphicsProxyWidget* fireWidget = myscene->addWidget(firelabel);
        enemy->weaponwidget.push_back(fireWidget);
        Weapon* weapon = new Weapon();
        enemy->weapons.push_back(weapon);
    }
}
void Normal_mode::shoot() {
    if (!player || !playerProxyWidget) return; //安全检查
    if (fireWidgets.empty())return;
    QGraphicsProxyWidget* fireWidget = fireWidgets[fireWidgets.size() - 1];
    if (target) {
        QPointF direction =targetEnemywidget->sceneBoundingRect().center() - playerProxyWidget->pos();
        qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            QRectF rect = playerProxyWidget->boundingRect();
            const qreal centerX = playerProxyWidget->pos().x() + rect.width() / 2 * playerProxyWidget->scale();
            const qreal centerY = playerProxyWidget->pos().y() + rect.height() / 2 * playerProxyWidget->scale();
            direction.rx() = direction.x() / length;
            direction.ry() = direction.y() / length;
            fireWidgets.pop_back();
            qreal rad = direction.y() >= 0 ? acos(direction.x()) : 2 * M_PI - acos(direction.x());
            fireWidget->setPos(centerX, centerY);
            QRectF firerect = fireWidget->boundingRect();
            fireWidget->setTransformOriginPoint(firerect.center());
            fireWidget->setRotation(rad * 180 / M_PI);
            firebullets.push_back(fireWidget);
            fireWidget->setData(0, direction.x());
            fireWidget->setData(1, direction.y());
            fireWidget->setData(2, 1);
        }
    }
    else {
        QPointF direction = mousePos - playerProxyWidget->pos();
        qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            QRectF rect = playerProxyWidget->boundingRect();
            const qreal centerX = playerProxyWidget->pos().x() + rect.width() / 2 * playerProxyWidget->scale();
            const qreal centerY = playerProxyWidget->pos().y() + rect.height() / 2 * playerProxyWidget->scale();
            direction.rx() = direction.x() / length;
            direction.ry() = direction.y() / length;
            fireWidgets.pop_back();
            qreal rad = direction.y() >= 0 ? acos(direction.x()) : 2 * M_PI - acos(direction.x());
            fireWidget->setPos(centerX, centerY);
            QRectF firerect = fireWidget->boundingRect();
            fireWidget->setTransformOriginPoint(firerect.center());
            fireWidget->setRotation(rad * 180 / M_PI);
            firebullets.push_back(fireWidget);
            fireWidget->setData(0, direction.x());
            fireWidget->setData(1, direction.y());
            fireWidget->setData(2, 0);
        }
    }
    //音效
    biu->play();
}
void Normal_mode::updatefirebullets() {
    qDebug() << 14;
    for (auto it = firebullets.begin();it != firebullets.end();) {
        QGraphicsProxyWidget* firebullet = *it;
        bool shouldRemove = false;
        if (firebullet->data(2) == 0) {
            qreal dx = firebullet->data(0).toDouble();
            qreal dy = firebullet->data(1).toDouble();
            firebullet->moveBy(dx * bulletSpeed, dy * bulletSpeed);
        }
        if (firebullet->data(2) == 1) {
            if (targetEnemywidget) {
                QPointF direction = targetEnemywidget->sceneBoundingRect().center() - firebullet->pos();
                qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
                direction.rx() = direction.x() / length;
                direction.ry() = direction.y() / length;
                firebullet->moveBy(direction.x() * bulletSpeed, direction.y() * bulletSpeed);
            }
            //目标已死亡先删除
            else {
                shouldRemove = true;
            }
        }
        //检查命中
        QRectF fireRect = firebullet->sceneBoundingRect();
        if (!myscene->sceneRect().contains(fireRect)) {
            shouldRemove = true;
        }
        for (size_t i = 0;i < enemywidgets.size();i++) {
            if (i >= enemies.size()) break;
            if (firebullet->collidesWithItem(enemywidgets[i])) {
                shouldRemove = true;
                //音效
                amns->play();
                if (!enemies[i]->weaponwidget.empty()) {
                    QGraphicsProxyWidget* widget = enemies[i]->weaponwidget.back();
                    myscene->removeItem(widget);
                    enemies[i]->weapons.pop_back();enemies[i]->weaponwidget.pop_back();
                    delete widget;
                }
                else { 
                    enemies[i]->Hp -= player->damage;
                    if (enemies[i]->Hp <= 0) {
                        score++;
                    }
                }
                break;
            }
        }
        if (shouldRemove) {
            myscene->removeItem(firebullet);
            delete firebullet;
            it = firebullets.erase(it);
        }
        else {
            ++it;
        }
    }
}
void Normal_mode::checkdefense() {
    qDebug() << 15;
    if (!playerProxyWidget)return;
    QRectF playerrect = playerProxyWidget->sceneBoundingRect();
    QPointF mycenter = playerrect.center();
    qreal myr = player->myr;
    for (size_t i = 0;i < enemies.size();i++) {
        Enemy* enemy = enemies[i];
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        QRectF enemyrect = enemywidget->sceneBoundingRect();
        QPointF enemycenter = enemyrect.center();
        qreal enemyr = enemy->enemyr;
        qreal distance = QLineF(mycenter, enemycenter).length();
        //相撞抵消（分类）
        bool collide = false;
        if (!fireWidgets.empty() && !enemy->weaponwidget.empty() && distance <= myr + enemyr) {
            collide = true;
        }
        if (fireWidgets.empty() && !enemy->weaponwidget.empty() && distance <= enemyr) {
            collide = true;
        }
        if (!fireWidgets.empty() && enemy->weaponwidget.empty() && distance <= myr) {
            collide = true;
        }
        if (collide) {
            if (!fireWidgets.empty()) {
                QGraphicsProxyWidget* widget = fireWidgets.back();
                myscene->removeItem(widget);
                fireWidgets.pop_back();
                delete widget;
            }
            else { player->Hp -= enemy->damage;qDebug() << "my Hp:" << player->Hp; }
            if (!enemy->weaponwidget.empty()) {
                QGraphicsProxyWidget* enemyWeapon = enemy->weaponwidget.back();
                myscene->removeItem(enemyWeapon);
                enemy->weapons.pop_back();enemy->weaponwidget.pop_back();
                delete enemyWeapon;
            }
            else { enemy->Hp -= player->damage; }
        }
    }
}
void Normal_mode::dodge() {
    qDebug() << 16;
    player->dodgestate = true;
    player->aspeed += 40;
    player->maxspeed += 500;
    player->untouchable = true;
    QTimer::singleShot(3000, [this]() {
        player->dodgestate = false;
        player->aspeed -= 40;
        player->maxspeed -= 500;
        player->untouchable = false;
        qDebug() << "dodge finishes";
        });
    qDebug() << "dodge successfully";
}
void Normal_mode::dodgerecovery() {
    if (!player)return;
    if (dodgeCD == 0) {
        return;
    }
    if (dodgeCD > 0)dodgeCD-=0.1;
}
void Normal_mode::switchanime(QMovie* newMovie) {
    if (currentPlayerMovie == newMovie||!player) {
        return; 
    }
    if (currentPlayerMovie) {
        currentPlayerMovie->stop();
    }
    currentPlayerMovie = newMovie;
    playerLabel->setMovie(currentPlayerMovie);
    currentPlayerMovie->start();
}
void Normal_mode::updatemybloodpos() {
    qDebug() << 17;
    if (!player)return;
    qreal bloodRatio = static_cast<qreal>(player->Hp) / initHp;
    if (bloodRatio > 1)bloodRatio = 1;
    qreal cWidth = mybloodW * bloodRatio;
    //裁剪
    QPixmap croppedmyblood = originalmyblood.copy(0, 0, cWidth, mybloodH);
    mybloodItem->setPixmap(croppedmyblood);

    QPointF viewTopLeft = view->mapToScene(0, 0);
    int margin = 30;
    myheadpic->setPos(viewTopLeft.x() + margin, viewTopLeft.y() + margin);
    mybloodItem->setPos(myheadpic->x()+myheadpic->sceneBoundingRect().width() + margin, myheadpic->y());
    /*QPointF playerPos = playerProxyWidget->pos();
    mybloodItem->setPos(playerPos.x(),playerPos.y());*/
    
    //道具提示
    grenadeamount->setPos(mybloodItem->x(), mybloodItem->y() + mybloodItem->sceneBoundingRect().height() + margin);
    smokeamount->setPos(grenadeamount->x() + grenadeamount->sceneBoundingRect().width() + margin, grenadeamount->y());
    if (!speedybuffs.empty()) {
        speedyamount->setVisible(true);
        speedyamount->setPos(smokeamount->x() + smokeamount->sceneBoundingRect().width() + margin, smokeamount->y());
    }
    else { speedyamount->setVisible(false); }
    grenadeText->setPlainText(QString::number(mygrenade));
    smokeText->setPlainText(QString::number(mysmokegrenade));
    grenadeText->setPos(grenadeamount->x() + grenadeamount->sceneBoundingRect().width() - grenadeText->sceneBoundingRect().width(),
        grenadeamount->y() + grenadeamount->sceneBoundingRect().height() - grenadeText->sceneBoundingRect().height());
    smokeText->setPos(smokeamount->x() + smokeamount->sceneBoundingRect().width() - smokeText->sceneBoundingRect().width(),
        smokeamount->y() + smokeamount->sceneBoundingRect().height() - smokeText->sceneBoundingRect().height());

    //按钮
    spawnwidget->setPos(mybloodItem->scenePos().x() + mybloodItem->sceneBoundingRect().width()+20,
        mybloodItem->scenePos().y());
}
void Normal_mode::updatebloodspos() {
    qDebug() << 18;
    if (!player)return;
    for (size_t i = 0;i < enemybloods.size();i++) {
        QGraphicsPixmapItem* blood = enemybloods[i];
        Enemy* enemy = enemies[i];
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        qreal bloodRatio = static_cast<qreal>(enemy->Hp) / blood->data(0).toDouble();
        if (bloodRatio > 1)bloodRatio = 1;
        qreal cWidth = blood->data(1).toDouble() * bloodRatio;
        QPixmap croppedblood = originalblood.copy(0, 0, cWidth, blood->data(2).toDouble());
        blood->setPixmap(croppedblood);
        int margin = 30;
        blood->setPos(enemywidget->x(), enemywidget->y() - margin);
    }
}
void Normal_mode::updatefa() {
    qDebug() << 19;
    if (!player)return;
    xfa = -player->xspeed*0.5;
    yfa = -player->yspeed*0.5;
}
void Normal_mode::targetEnemy(const QPointF& clickPos) {
    if (enemies.empty() || enemywidgets.empty()||!player) {
        qDebug() << "No enemies to target";
        return;
    }
    qreal minDistance = 5000;
    int t = -1;
    QPointF playercenter = playerProxyWidget->sceneBoundingRect().center();
    //找最近的敌人
    for (size_t i = 0;i < enemies.size();i++) {
        QGraphicsProxyWidget* enemywidget = enemywidgets[i];
        if (!enemywidget) continue;
        QPointF enemyCenter = enemywidget->sceneBoundingRect().center();
        qreal dis= QLineF(playercenter, enemyCenter).length();
        //如果点击到敌人直接锁定
        if (enemywidget->contains(clickPos)) {
            t=i;
            break;
        }
        if (dis < minDistance) {
            minDistance = dis;
            t = i;
        }
    }
    //距离限制
    const qreal maxTargetDistance = 500.0;
    if (t >= 0 && t < enemies.size() && t < enemywidgets.size() && minDistance < maxTargetDistance) {
        target = enemies[t];
        targetEnemywidget = enemywidgets[t];
        isTargeting = true;
        QPixmap circle(round);
        if (circle.isNull()) {
            qDebug() << "Failed to load circle image!";
            return;
        }
        if (circleitem) {
            delete circleitem;
            circleitem = nullptr;
        }
        circleitem = new QGraphicsPixmapItem(circle);
        QRectF circlrrect = circleitem->sceneBoundingRect();
        QRectF enemyrect = targetEnemywidget->sceneBoundingRect();
        circleitem->setPos(enemyrect.x(), enemyrect.y() + enemyrect.width() - circlrrect.width());
        circleitem->setScale(0.5);
        myscene->addItem(circleitem);
    }  
}
void Normal_mode::updatecirclepos() {
    qDebug() << 21;
    if (!target||!circleitem||!player)return;
    QRectF enemyrect = targetEnemywidget->sceneBoundingRect();
    QRectF circlrrect = circleitem->sceneBoundingRect();
    circleitem->setPos(enemyrect.x(), enemyrect.y() + enemyrect.width() - circlrrect.width());
}
void Normal_mode::updaterandomspeed() {
    qDebug() << 22;
    if (enemies.empty())return;
    int amount = 16;
    randnum = rand() % amount;
}
void Normal_mode::spawngrenade(QPointF destination) {
    if (!player||mygrenade<=0)return;
    QPixmap g(grenadepic);
    QGraphicsPixmapItem* grenadeitem = new QGraphicsPixmapItem(g);
    QRectF playerrect = playerProxyWidget->sceneBoundingRect();
    grenadeitem->setPos(playerrect.center());
    grenadeitem->setScale(0.3);
    myscene->addItem(grenadeitem);
    bombs.push_back(grenadeitem);
    //计算方向(初始速度)
    QPointF direction = destination - playerrect.center();
    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    qreal xs = direction.x() * bombspeed / length;
    qreal ys = direction.y() * bombspeed / length;
    grenadeitem->setData(0, xs);
    grenadeitem->setData(1, ys);
    grenadeitem->setData(2, destination.x());//存储目标位置
    grenadeitem->setData(3, 0);
    mygrenade--;
}
void Normal_mode::spawnsmokegrenade(QPointF destination) {
    if (!player||mysmokegrenade<=0)return;
    QPixmap sg(smokegrenadepic);
    if (!sg.isNull()) {
        qDebug() << "spawn smokegrenade ";
    }
    QGraphicsPixmapItem* smokegrenadeitem = new QGraphicsPixmapItem(sg);
    QRectF playerrect = playerProxyWidget->sceneBoundingRect();
    smokegrenadeitem->setPos(playerrect.center());
    smokegrenadeitem->setScale(0.3);
    myscene->addItem(smokegrenadeitem);
    bombs.push_back(smokegrenadeitem);
    //计算方向(初始速度)
    QPointF direction = destination - playerrect.center();
    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    qreal xs = direction.x() * bombspeed / length;
    qreal ys = direction.y() * bombspeed / length;
    smokegrenadeitem->setData(0, xs);
    smokegrenadeitem->setData(1, ys);
    smokegrenadeitem->setData(2, destination.x());//存储目标位置
    smokegrenadeitem->setData(3, 1);//类型
    mygrenade--;
}
void Normal_mode::updatebombspos() {
    if (!player||bombs.empty())return;
    qreal deviation = 5;
    static QElapsedTimer timer;
    static bool firstFrame = true;
    if (firstFrame) {
        timer.start();
        firstFrame = false;
        return;
    }
    qreal t = timer.elapsed() / 1000.0; // 转换为秒
    timer.restart();
    if (t > 0.1) t = 0.1;
    for (auto bomb : bombs) {
        //爆炸检测
        QRectF bombrect = bomb->sceneBoundingRect();
        if (abs(bombrect.x() - bomb->data(2).toDouble()) < deviation || bomb->data(0) == 0) {
            if (bomb->data(3) == 0) {
                grenadeexplosion(bomb);
            }
            if (bomb->data(3) == 1) {
                smokerelease(bomb);
            }
        }
        //减速移动
        qreal xs = bomb->data(0).toDouble();
        qreal ys = bomb->data(1).toDouble();
        qreal fa = 10;
        qreal len = sqrt(xs * xs + ys * ys);
        xs -= fa * t * xs / len;
        ys -= fa * t * ys / len;
        const qreal minSpeed = 5;
        if (fabs(xs) < minSpeed) xs = 0;
        if (fabs(ys) < minSpeed) ys = 0;
        bomb->setData(0, xs);
        bomb->setData(1, ys);
        bomb->moveBy(xs * t, ys * t);
    }
}
void Normal_mode::grenadeexplosion(QGraphicsPixmapItem* grenade) {
    //删除
    for (auto it = bombs.begin();it != bombs.end();it++) {
        if (*it == grenade) {
            bombs.erase(it);
            break;
        }
    }
    QPointF center = grenade->sceneBoundingRect().center();
    myscene->removeItem(grenade);
    //爆炸特效和伤害
    QLabel* grenadeL = new QLabel(nullptr);
    grenadeL->setAttribute(Qt::WA_TranslucentBackground);
    QMovie* speffect = new QMovie(explode);
    if (speffect->isValid()) {
        qDebug() << "explode!";
        speffect->setCacheMode(QMovie::CacheAll);
        grenadeL->setMovie(speffect);
        speffect->start();
        QGraphicsProxyWidget* explodewidget = myscene->addWidget(grenadeL);
        explodewidget->setPos(center.x() - grenadeL->width() / 2, center.y() - grenadeL->height() / 2);
        QPointF excenter = explodewidget->sceneBoundingRect().center();
        qreal range = explodewidget->sceneBoundingRect().height();
        qreal damage = 15;
        for (size_t i = 0;i < enemies.size();i++) {
            Enemy* enemy = enemies[i];
            QGraphicsProxyWidget* enemywidget = enemywidgets[i];
            QPointF enemycenter = enemywidget->sceneBoundingRect().center();
            if (QLineF(excenter, enemycenter).length() <= range) {
                enemy->Hp -= damage;
            }
        }
        //音效
        if (fire && fire->playbackState() != QMediaPlayer::PlayingState) {
            fire->play();
            qDebug() << "play";
        }
        QTimer::singleShot(1000, [this,explodewidget,speffect]() {
            myscene->removeItem(explodewidget);
            speffect->deleteLater();
            });
    }
}
void Normal_mode::smokerelease(QGraphicsPixmapItem* smokegrenade) {
    for (auto it = bombs.begin();it != bombs.end();it++) {
        if (*it == smokegrenade) {
            bombs.erase(it);
            break;
        }
    }
    //烟雾生成
    QPointF center = smokegrenade->sceneBoundingRect().center();
    myscene->removeItem(smokegrenade);
    QLabel* smokegrenadeL = new QLabel(nullptr);
    smokegrenadeL->setAttribute(Qt::WA_TranslucentBackground);
    QMovie* smoke = new QMovie(smokegif);
    if (smoke->isValid()) {
        qDebug() << "release smoke!";
        smoke->setCacheMode(QMovie::CacheAll);
        smokegrenadeL->setMovie(smoke);
        smoke->start();
        QGraphicsProxyWidget* smokewidget = myscene->addWidget(smokegrenadeL);
        smokewidget->setPos(center.x() - smokegrenadeL->width() / 2, center.y() - smokegrenadeL->height() / 2);
        smokes.push_back(smokewidget);
        //固定
        QTimer::singleShot(1500, [this,smoke]() {
            smoke->stop();
            });
        //消散
        QTimer::singleShot(20000, [this,smoke,smokewidget]() {
            myscene->removeItem(smokewidget);
            smoke->deleteLater();
            });
    }
}
void Normal_mode::updatecursorpos() {
    qDebug() << 24;
    if ((!keyX && !keyV)||(mygrenade<=0&&mysmokegrenade<=0)) {
        cursoritem->setPixmap(transparentPixmap);
        return;
    }
    cursoritem->setPixmap(cursorpic);
    qDebug() << "cursor generated";
    QPoint viewPos = view->mapFromGlobal(QCursor::pos());     //从全局坐标转为视图坐标
    QPointF scenePos = view->mapToScene(viewPos);
    cursoritem->setPos(scenePos.x() - cursoritem->sceneBoundingRect().width() / 2,
        scenePos.y() - cursoritem->sceneBoundingRect().height() / 2);
    cursoritem->setScale(0.5);
}
void Normal_mode::updatelizipos() {
    if (!player)return;
    if (!player->dodgestate)return;
    QMovie* liziMovie = new QMovie(lizi);
    if (liziMovie->isValid()) {
        qDebug() << "lizi generated";
        liziMovie->setScaledSize(QSize(72, 130));
    }
    liziMovie->setCacheMode(QMovie::CacheAll);
    QLabel* lizilabel = new QLabel(nullptr);
    lizilabel->setMovie(liziMovie);
    lizilabel->setAttribute(Qt::WA_TranslucentBackground); // 使背景透明
    liziMovie->setSpeed(100);
    liziMovie->start();
    QGraphicsProxyWidget* liziwidget = myscene->addWidget(lizilabel);
    QPointF center = playerProxyWidget->sceneBoundingRect().center();
    liziwidget->setPos(center.x() - liziwidget->sceneBoundingRect().width() / 2,
        center.y() - liziwidget->sceneBoundingRect().height() / 2);
    qreal duration = liziMovie->frameCount() * liziMovie->nextFrameDelay();
    QTimer::singleShot(duration, [this, liziwidget, lizilabel,liziMovie]() {
        myscene->removeItem(liziwidget);
        });
}
void Normal_mode::deathanime(int n, QPointF pos, int width, int height) {
    if (n == 0) {
        QLabel* deathlabel = new QLabel(nullptr);
        QMovie* dying = new QMovie(enemydying);
        if (dying->isValid()) {
            qDebug() << "enemy is dying";
        }
        dying->setScaledSize(QSize(144, 72));
        deathlabel->setMovie(dying);
        deathlabel->setAttribute(Qt::WA_TranslucentBackground);
        dying->start();
        QGraphicsProxyWidget* deathwidget = myscene->addWidget(deathlabel);
        deathwidget->setPos(pos.x() + width - deathwidget->sceneBoundingRect().width(),
           pos.y() + height - deathwidget->sceneBoundingRect().height());
        //音效
        aaa->play();
        //只播放一次
        QTimer::singleShot(dying->nextFrameDelay()*dying->frameCount(), [this, dying, deathwidget]() {
            dying->stop();
            myscene->removeItem(deathwidget);
            delete deathwidget;
            });
    }
    if (n == 1) {
        QLabel* deathlabel = new QLabel(nullptr);
        QMovie* dying = new QMovie(mydying);
        if (dying->isValid()) {
            qDebug() << "player is dying";
        }
        dying->setScaledSize(QSize(220, 130));
        deathlabel->setMovie(dying);
        deathlabel->setAttribute(Qt::WA_TranslucentBackground);
        dying->start();
        QGraphicsProxyWidget* deathwidget = myscene->addWidget(deathlabel);
        deathwidget->setPos(pos.x(), pos.y());
        QTimer::singleShot(dying->nextFrameDelay() * dying->frameCount(), [this, dying, deathwidget]() {
            dying->stop();
            myscene->removeItem(deathwidget);
            delete deathwidget;
            });
    }

}
void Normal_mode::updatesize() {
    if (!player) return;
    qreal ds = 0.4;
    qreal os = bgSize;
    bgSize -= ds;
    if (bgSize < 200) return;
    qreal scale = bgSize / 2560;
    background->setScale(scale);
    qreal offset = (1.0 - scale) * 2560 / 2.0;
    background->setPos(offset, offset);
    myscene->setSceneRect(offset, offset, bgSize, bgSize);
    QRectF playerRect = playerProxyWidget->sceneBoundingRect();
    QRectF sceneRect = myscene->sceneRect();
    QPointF center = sceneRect.center();
    QPointF nw(playerRect.topLeft());
    QPointF sw(playerRect.bottomLeft());
    QPointF ne(playerRect.topRight());
    QPointF se(playerRect.bottomRight());
    qreal nwdis = QLineF(nw, center).length();
    qreal swdis = QLineF(sw, center).length();
    qreal nedis = QLineF(ne, center).length();
    qreal sedis = QLineF(se, center).length();
    qreal radius = sceneRect.width() / 2;
    bool outofBounds = nwdis >= radius || swdis >= radius || nedis >= radius || sedis >= radius;
    if (outofBounds) {
        qreal nx = playerRect.x() - center.x();
        nx *= bgSize / (os+1);
        nx += center.x();
        qreal ny = playerRect.y() - center.y();
        ny *= bgSize / (os+1);
        ny += center.y();
        playerProxyWidget->setPos(nx, ny);
    }
    for (int i = 0;i < enemies.size();i++) {
        QRectF enemyrect = enemywidgets[i]->sceneBoundingRect();
        QPointF nw(enemyrect.topLeft());
        QPointF sw(enemyrect.bottomLeft());
        QPointF ne(enemyrect.topRight());
        QPointF se(enemyrect.bottomRight());
        qreal nwdis = QLineF(nw, center).length();
        qreal swdis = QLineF(sw, center).length();
        qreal nedis = QLineF(ne, center).length();
        qreal sedis = QLineF(se, center).length();
        qreal radius = sceneRect.width() / 2;
        bool outofBounds = nwdis >= radius || swdis >= radius || nedis >= radius || sedis >= radius;
        if (outofBounds) {
            qreal nx = enemyrect.x() - center.x();
            nx *= bgSize / (os + 1);
            nx += center.x();
            qreal ny = enemyrect.y() - center.y();
            ny *= bgSize / (os + 1);
            ny += center.y();
            enemywidgets[i]->setPos(nx, ny);
        }
    }
    for (auto it = tools.begin();it != tools.end();) {
        QGraphicsPixmapItem* tool = *it;
        QRectF toolrect = tool->sceneBoundingRect();
        QPointF nw(toolrect.topLeft());
        QPointF sw(toolrect.bottomLeft());
        QPointF ne(toolrect.topRight());
        QPointF se(toolrect.bottomRight());
        qreal nwdis = QLineF(nw, center).length();
        qreal swdis = QLineF(sw, center).length();
        qreal nedis = QLineF(ne, center).length();
        qreal sedis = QLineF(se, center).length();
        qreal radius = sceneRect.width() / 2;
        bool outofBounds = nwdis >= radius || swdis >= radius || nedis >= radius || sedis >= radius;
        if (outofBounds) {
            myscene->removeItem(tool);
            it=tools.erase(it);
            delete tool;
        }
        else { it++; }
    }
}

