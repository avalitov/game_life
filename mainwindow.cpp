#include "mainwindow.h"

const int   N   =   40/*+40*/;
const int   M   =   70/*+40*/;
const int   sizeN   =   800/N/2;
const int   sizeM   =   sizeN;
const int   speed_decrease  =   50;
const int   speed_increase  =   17;
int mas[N][M] = {0};
int mas1[N][M] = {0};
int mas2[N][M] = {0};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    const int w = 80;
    const int h = 30;
    const int between = 15;
    
    start = new QPushButton(this);
    start->setGeometry(between, N*sizeN + between, w, h);
    start->setText("старт");
    
    pause = new QPushButton(this);
    pause->setGeometry(between*2 + w, N*sizeN + between, w, h);
    pause->setText("пауза");
    
    pause->setEnabled(false);
    start->setEnabled(true);
    
    one_step = new QPushButton(this);
    one_step->setGeometry(between*3 + 2*w, N*sizeN + between, w, h);
    one_step->setText("один шаг");
    
    clear = new QPushButton(this);
    clear->setGeometry(between*4 + 3*w, N*sizeN + between, w, h);
    clear->setText("очистить");
    
    random = new QPushButton(this);
    random->setGeometry(between*5 + 4*w, N*sizeN + between, w*2, h);
    random->setText("заполнить ячейки рандомно");
    
    QPushButton* plain = new QPushButton(this);
    plain->setGeometry(M*sizeM + between, between, w, h);
    plain->setText("plain");
    
    QPushButton* glider = new QPushButton(this);
    glider->setGeometry(M*sizeM + between, 2*between + h, w, h);
    glider->setText("glider");
    
    QPushButton* relay = new QPushButton(this);
    relay->setGeometry(M*sizeM + between, 3*between + 2*h, w, h);
    relay->setText("relay");
    
    QPushButton* gosper_gun = new QPushButton(this);
    gosper_gun->setGeometry(M*sizeM + between, 4*between + 3*h, w, h);
    gosper_gun->setText("gosper gun");
    
    QPushButton* fountain = new QPushButton(this);
    fountain->setGeometry(M*sizeM + between, 5*between + 4*h, w, h);
    fountain->setText("fountain");
    
    QPushButton* popower = new QPushButton(this);
    popower->setGeometry(M*sizeM + between, 6*between + 5*h, w, h);
    popower->setText("popower");
    
    increase = new QPushButton(this);
    increase->setGeometry(M*sizeM + between, N*sizeN - 2*between, w, h);
    increase->setText("быстро");
    
    decrease = new QPushButton(this);
    decrease->setGeometry(M*sizeM + between, N*sizeN + between, w, h);
    decrease->setText("медленно");
    
    resize(M*sizeM + 2*between + w, N*sizeN + 2*between + h);
    
    ptmr    = new QTimer(this);
    speed   = true;
    decrease->setEnabled(false);
    ptmr1   = new QTimer(this);
    srand(time(NULL));
    
    connect(start,      SIGNAL(clicked()),  SLOT(slot_ok()));
    connect(pause,      SIGNAL(clicked()),  SLOT(slot_pause()));
    connect(one_step,   SIGNAL(clicked()),  SLOT(slot_one_step()));
    connect(clear,      SIGNAL(clicked()),  SLOT(slot_clear()));
    connect(random,     SIGNAL(clicked()),  SLOT(slot_random()));
    
    connect(plain,      SIGNAL(clicked()),  SLOT(slot_plain()));
    connect(glider,     SIGNAL(clicked()),  SLOT(slot_glider()));
    connect(relay,      SIGNAL(clicked()),  SLOT(slot_relay()));
    connect(gosper_gun, SIGNAL(clicked()),  SLOT(slot_gosper_gun()));
    connect(fountain,   SIGNAL(clicked()),  SLOT(slot_fountain()));
    connect(popower,    SIGNAL(clicked()),  SLOT(slot_popower()));
    
    connect(increase,   SIGNAL(clicked()),  SLOT(slot_increase()));
    connect(decrease,   SIGNAL(clicked()),  SLOT(slot_decrease()));
    
    connect(ptmr,       SIGNAL(timeout()),  SLOT(MySlot()));
    connect(ptmr1,      SIGNAL(timeout()),  SLOT(slot_random1()));
    
    setMouseTracking(true);
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    
    painter.setBrush(QBrush(Qt::red, Qt::HorPattern));
    painter.setPen(QPen(Qt::blue, 0.1));

    for (int n = 0;  n <= N*sizeN;  n += sizeN)
        painter.drawLine(0, n, sizeM*M, n);
    for (int m = 0;  m <= M*sizeM;  m += sizeM)
        painter.drawLine(m, 0, m, sizeN*N);
        
    for (int n = 0;  n < N;  ++n)
        for (int m = 0;  m < M;  ++m)
            if (mas[n][m]   ==  1) {
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                   
                int w = sizeM;
                int h = sizeN;
                
                int x = sizeM*m;
                int y = sizeN*n;
                
                painter.drawRect(x, y, w, h);
                
            } else if (mas[n][m]   ==  2) {
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                
                int w = sizeM/2;
                int h = sizeN/2;
                
                int x = sizeM*m*2;
                int y = sizeN*n*2;
                
                painter.drawEllipse(x - (x - w)/2, y - (y - h)/2, w, h);
            }
    
    
    for (int n = 0;  n < N;  ++n)
        for (int m = 0;  m < M;  ++m)
            if (mas2[n][m]   ==  1) {
                int w = sizeM;
                int h = sizeN;
                
                int x = sizeM*m;
                int y = sizeN*n;
                painter.drawRect(x, y, w, h);
                QPainter painter(this);
                
                QBrush brush(Qt::blue, Qt::SolidPattern);
                
                painter.fillRect(x, y, w, h, brush);
                int q = 1;
                
                if (mas[n][m] == 1) {
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    painter.drawRect(x + q, y + q, w - q*2, h - q*2);
                    
                } else if (mas[n][m] == 2) {
                    int w = sizeM/2;
                    int h = sizeN/2;
                    
                    int x = sizeM*m*2;
                    int y = sizeN*n*2;
                    
                    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                    painter.eraseRect(x + q, y + q, w - q*2, h - q*2);
                    painter.drawEllipse(x - (x - w)/2, y - (y - h)/2, w, h);
                    //qDebug() << m << " " << n;
                } else {
                    painter.eraseRect(x + q, y + q, w - q*2, h - q*2);
                }
            }
}

int MainWindow::buttonsInfo(QMouseEvent* pe)
{
    int strButtons = 0;

    if(pe->buttons() & Qt::LeftButton) {
        strButtons += 1;//"Left ";
    }
    if(pe->buttons() & Qt::RightButton) {
        strButtons += 2;//"Right ";
    }
    if(pe->buttons() & Qt::MidButton) {
        strButtons += 3;//"Middle";
    }
    return strButtons;        
}

void MainWindow::my_mouse(QMouseEvent* pe)
{
    if (buttonsInfo(pe) != 0) {
        int x = pe->x();
        int y = pe->y();
        
        if (x >= 0 && x < M*sizeM && y >= 0 && y < N*sizeN) {
            
            int y1 = (x/sizeN);
            int x1 = (y/sizeM);
            
            if (mas[x1][y1] == 1)
                mas[x1][y1] = 0;
            else
                mas[x1][y1] = 1;
        }
    }
    {
        int x = pe->x();
        int y = pe->y();
        
        if (x >= 0 && x < M*sizeM && y >= 0 && y < N*sizeN) {
            
            int y1 = (x/sizeN);
            int x1 = (y/sizeM);
            
            for (int n = 0;  n < N;  ++n)
                for (int m = 0;  m < M;  ++m)
                    mas2[n][m]  = 0;
            
            mas2[x1][y1] =  1;
        } else {
            for (int n = 0;  n < N;  ++n)
                for (int m = 0;  m < M;  ++m)
                    mas2[n][m]  = 0;
        }
    }
    
    repaint();
}

void MainWindow::mouseMoveEvent (QMouseEvent* pe)
{
    my_mouse(pe);
}

void MainWindow::mousePressEvent (QMouseEvent* pe)
{
    my_mouse(pe);
}

int sosedi(int n, int m)
{
    int counter = 0;
    
    int minN = (n - 1 < 0) ? 0 : n - 1;
    int minM = (m - 1 < 0) ? 0 : m - 1;
    
    int maxN = (n + 1 >= N) ? N - 1 : n + 1;
    int maxM = (m + 1 >= M) ? M - 1 : m + 1;;
    
    for (int i = minN; i <= maxN; ++i)
        for (int j = minM; j <= maxM; ++j)
            if ((i != n) || (j != m)) {
                if (mas[i][j] == 1)
                    counter++;
            }
    return counter;
}

void MainWindow::MySlot()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            mas1[i][j] = mas[i][j];
    
    for (int n = 0;  n < N;  ++n)
        for (int m = 0;  m < M;  ++m) {
            if ((mas[n][m] == 2) && (sosedi(n, m) == 3))
                mas1[n][m] = 1;
            if ((mas[n][m] == 0) && (sosedi(n, m) == 3))
                mas1[n][m] = 1;
            if ((mas[n][m] == 1) && (sosedi(n, m) != 3) && (sosedi(n, m) != 2))
                mas1[n][m] = 2;
        }
    
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            mas[i][j] = mas1[i][j];
    
    repaint();
}

void MainWindow::slot_ok()
{
    if (speed) {
        ptmr->start(speed_decrease);
        increase->setEnabled(true);
    } else {
        ptmr->start(speed_increase);
        decrease->setEnabled(true);
    }
    
    start->setEnabled(false);
    pause->setEnabled(true);
}

void MainWindow::slot_pause()
{
    ptmr->stop();
    pause->setEnabled(false);
    start->setEnabled(true);
    increase->setEnabled(false);
    decrease->setEnabled(false);
}

void MainWindow::slot_one_step()
{
    ptmr->stop();
    slot_pause();
    MySlot();
}

void MainWindow::slot_clear()
{
    for (int n = 0;  n < N;  ++n)
        for (int m = 0;  m < M;  ++m)
            mas[n][m] = 0;
    repaint();
}

void MainWindow::slot_random()
{
    slot_clear();
    clear->setEnabled(false);
    one_step->setEnabled(false);
    slot_pause();
    start->setEnabled(false);
    
    increase->setEnabled(false);
    decrease->setEnabled(false);
    random->setEnabled(false);
    
    ptmr1->start(2);
}

void MainWindow::slot_random1()
{
    static int sum = 0;
    int i = rand() % N;
    int j = rand() % M;
    
    do {
        i = rand() % N;
        j = rand() % M;
    } while (mas[i][j] == 1);
    
    mas[i][j]   =   1;
    ++sum;
    
    repaint();
    
    if (sum >= N*M/8) {
        ptmr1->stop();
        sum = 0;
        clear->setEnabled(true);
        one_step->setEnabled(true);
        start->setEnabled(true);
        pause->setEnabled(false);
        
        random->setEnabled(true);
    }
}

void MainWindow::zapolnenie(QString &s, bool nach)
{
    slot_clear();
    
    int counter = 0;
    int start = INT_MAX;
    int end = 0;
    int index = 0;
    
    for (int k = 0; k < s.size(); ++k) {
        index++;
        if (s[k] == '\n') {
            index = 0;
            counter++;
        }
        
        if (s[k] == 'O') {
            if (index < start)
                start   = index;
            if (index > end)
                end     = index;
        }
    }
    
    int i = 0;
    int j = 0;
    
    if (nach == 1) {
        i = N/2 - counter/2;
        j = M/2 - (start + end)/2;
    } else {
        i = 0;
        j = -1;
    }
    
    for (int k = 0; k < s.size(); ++k) {
        j++;
        if (s[k] == '\n') {
            if (nach == 1)
                j = M/2 - (start + end)/2;
            else
                j = -1;
            i++;
        }
        if (s[k] == 'O') {
            mas[i][j] = 1;
        }
    }
    repaint();
}

void MainWindow::slot_plain()
{
    QString s = "...............................OO.............................\n"
                "..............................O...O...........................\n"
                "...................OO........O.....O...OO.....................\n"
                "...................OO........O...O.OO..OO.....................\n"
                ".............................O.....O..........................\n"
                "..............................O...O...........................\n"
                "...............................OO.............................\n";
    zapolnenie(s);
    
}

void MainWindow::slot_glider()
{
    slot_clear();
    
    mas[0][1] = 1;
    mas[1][2] = 1;
    mas[2][0] = 1;
    mas[2][1] = 1;
    mas[2][2] = 1;
    
    repaint();
}

void MainWindow::slot_relay()
{
    QString s = "........................................OO......OO............\n"
                ".......................................O..O....O..O...........\n"
                "......................................OOOOOO..OOOOOO..........\n"
                ".......................................O..O....O..O...........\n"
                "...............OO......OO...............OO......OO............\n"
                "..............O..O....O..O....................................\n"
                ".............OOOOOO..OOOOOO...O...............................\n"
                "..............O..O....O..O....O.O.............................\n"
                "...............OO......OO.....OO..............................\n";
    zapolnenie(s);
    
}

void MainWindow::slot_gosper_gun()
{
    QString s = "..............................................................\n"
                "..............................................................\n"
                ".........................O.O..................................\n"
                ".........................O..O.................................\n"
                "..........O......O..........OO................................\n"
                ".........O.O.....O........O...OO....OO........................\n"
                "........O.OO......O.........OO......OO........................\n"
                "..OO...OO.OO.........OO..O..O.................................\n"
                "..OO....O.OO.....OOO..O..O.O..................................\n"
                ".........O.O.......OOOO.......................................\n"
                "..........O.........OO........................................\n";
    zapolnenie(s, 0);
    
}

void MainWindow::slot_fountain()
{
    QString s = ".........................OO.........OO........................\n"
                ".........................O..OOOOOOO..O........................\n"
                "..........................O...OOO...O.........................\n"
                "...........................O..O.O..O..........................\n"
                "..............................................................\n"
                "......................OO....OOO.OOO....OO.....................\n"
                "......................O..OO..O.O.O..OO..O.....................\n"
                ".......................OOO.OOO...OOO.OOO......................\n"
                "............................OO.O.OO...........................\n"
                ".........................OO.........OO........................\n"
                ".........................O...........O........................\n"
                "...........................O.......O..........................\n"
                "..........................OO.......OO.........................\n";
    zapolnenie(s);
    
}

void MainWindow::slot_popower()
{
    QString s = "....................................O.........................\n"
                "...................................O.O........................\n"
                "..............................................................\n"
                "............................OO...O...OO.......................\n"
                "............................OO..O.....O.......................\n"
                ".................................O.O..........................\n"
                "...................................OO.........................\n"
                ".............................OO...............................\n"
                "..................OO........O..O..............................\n"
                "................O.O.........O.O....O..........................\n"
                "...............O.....O.......O.....O..........................\n"
                "................O...OO..OOO..OO....O..........................\n"
                ".............................OO.......O.......................\n"
                "..................O.O.......O.O......O....OO..................\n"
                "...................O........O........O...O.O..................\n"
                ".......................O....O.O.......OOOOO...................\n"
                "......................O.O....OO........OOO....................\n"
                "..................OO..O..O................O...................\n"
                "..................OO...OO................O.O..................\n"
                "..............................................................\n"
                "..........................O........OOO..OO...O................\n"
                "..........................O.....O.......O.....O...............\n"
                "..........................O....O.O.........O.O................\n"
                "..............................O..O........OO..................\n"
                "...............................OO.............................\n"
                ".........................OO...................................\n"
                "..........................O.O.................................\n"
                ".......................O.....O..OO............................\n"
                ".......................OO...O...OO............................\n"
                "..............................................................\n"
                "........................O.O...................................\n"
                ".........................O....................................\n";
    zapolnenie(s);
}

void MainWindow::slot_increase()
{
    speed =  false;
    increase->setEnabled(false);
    decrease->setEnabled(true);
    ptmr->setInterval(speed_increase);
}

void MainWindow::slot_decrease()
{
    speed =  true;
    decrease->setEnabled(false);
    increase->setEnabled(true);
    ptmr->setInterval(speed_decrease);
}

MainWindow::~MainWindow()
{
}
