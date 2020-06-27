#include "TestWidget.h"
#include "ui_TestWidget.h"

#include <fstream>

#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QList>

#include "OpenGLDisplay.h"

namespace
{
    // any file from http://trace.eas.asu.edu/yuv/
    const char* YUV_FILE_PATH = "test.yuv";
    const unsigned FRAME_WIDTH = 352; //video frame width, hardcoded for PoC
    const unsigned FRAME_HEIGHT = 288; //video frame width, hardcoded for PoC
    const unsigned FRAME_SIZE = FRAME_WIDTH * FRAME_HEIGHT * 3/2;
}

struct TestWidget::TestWidgetImpl
{
    TestWidgetImpl()
        : ui(new Ui::TestWidget)
    {}

    Ui::TestWidget*             ui;
    unsigned char*              mBuffer;
    unsigned                    mSize;

    QList<OpenGLDisplay*>       mPlayers;
};

TestWidget::TestWidget(QWidget *parent)
    : QWidget(parent)
    , impl(new TestWidgetImpl)
{
    impl->ui->setupUi(this);
    impl->ui->playAllButton->setEnabled(false);

    QGridLayout* wallLayout = new QGridLayout;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            OpenGLDisplay* player = new OpenGLDisplay(this);
            wallLayout->addWidget(player, i, j);
            impl->mPlayers.append(player);
        }
    }

    wallLayout->setSpacing(2);
    wallLayout->setMargin(0);

    impl->ui->videoWall->setLayout(wallLayout);
    connect(impl->ui->playAllButton, &QPushButton::clicked, this, &TestWidget::playVideoWall);
}

TestWidget::~TestWidget()
{
    delete[] impl->mBuffer;
}

void TestWidget::readAllSampleFile()
{
    if (!QFile::exists(YUV_FILE_PATH))
    {
        qDebug() << "No sample File!";
        return;
    }

    impl->mSize = QFile(YUV_FILE_PATH).size();
    impl->mBuffer = new unsigned char[impl->mSize];

    std::ifstream yuv_file(YUV_FILE_PATH, std::ios::binary);
    yuv_file.read(reinterpret_cast<char*>(impl->mBuffer), impl->mSize);

    if (yuv_file.tellg() < impl->mSize)
        qWarning() << "YUV file read error, could read only: " << yuv_file.tellg();

    impl->ui->playAllButton->setEnabled(true);
}

void TestWidget::playVideoWall()
{
    const int SKIP_COUNT = 3;

    impl->ui->playAllButton->setEnabled(false);

    int frameNumber = 0;
    int frameCount = impl->mSize  / FRAME_SIZE;

    for (int i = 0; i < impl->mPlayers.count(); ++i)
        impl->mPlayers[i]->InitDrawBuffer(FRAME_SIZE);

    while (frameNumber < frameCount)
    {
        unsigned char* runner = impl->mBuffer;
        runner += frameNumber * FRAME_SIZE;
        for (int i = 0; i < impl->mPlayers.count(); ++i)
        {
            if (i * SKIP_COUNT < frameNumber)
            {
                impl->mPlayers[i]->DisplayVideoFrame(runner, FRAME_WIDTH, FRAME_HEIGHT);
            }
        }
        frameNumber++;

        QThread::msleep(40);
        qApp->processEvents();
    }

    impl->ui->playAllButton->setEnabled(true);
}
