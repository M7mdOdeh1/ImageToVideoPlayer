#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentFrameIndex(0)
    , fps(30)
    , playbackSpeed(1.0)
    , isGrayscale(false)
    , isRedChannel(false)
    , rotationAngle(0.0)
{
    ui->setupUi(this);

    // Specify the path to the images
    imagePath = "../VideoPlayer/trip/left";
    ImageLoader imageLoader(imagePath);
    imageFiles = imageLoader.loadImages();

    if (imageFiles.empty()) {
        // Handle error: No images found
        qWarning("No images found in the specified path.");
        return;
    }


    // Initialize FPS calculator and frame processor
    fpsCalculator = std::make_unique<FPSCalculator>();
    frameProcessor = std::make_unique<FrameProcessor>();

    // Initialize the progress bar
    ui->progressBar->setRange(0, imageFiles.size() - 1);
    ui->progressBar->setValue(0);

    // Connect UI components to respective slots
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::onSpeedChanged);

    // Set up UI for buttons
    QIcon playIcon("../VideoPlayer/icon/play.png");
    ui->playButton->setIcon(playIcon);
    ui->playButton->setIconSize(QSize(64, 64));
    ui->playButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");

    QIcon pauseIcon("../VideoPlayer/icon/pause.png");
    ui->pauseButton->setIcon(pauseIcon);
    ui->pauseButton->setIconSize(QSize(64, 64));
    ui->pauseButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    ui->pauseButton->setEnabled(false);

    // Set up the playback speed slider
    ui->speedSlider->setRange(10, 200); // 0.1x to 2.0x speed
    ui->speedSlider->setValue(100);     // Default 1x speed (30 fps)

    // Set focus policy to handle key events
    this->setFocusPolicy(Qt::StrongFocus);

    // Set up the timer to update the frame
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);


}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            isGrayscale = !isGrayscale;
            break;
        case Qt::Key_Down:
            isRedChannel = !isRedChannel;
            break;
        case Qt::Key_Left:
            rotationAngle += 90.0;
            break;
        case Qt::Key_Right:
            rotationAngle -= 90.0;
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }

    displayCurrentFrame();
}

void MainWindow::onPlayButtonClicked()
{
    if (!timer->isActive()) {
        timer->start(1000 / (fps * playbackSpeed));
    }
    
    ui->playButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
}

void MainWindow::onPauseButtonClicked()
{
    if (timer->isActive()) {
        timer->stop();
    }


    ui->playButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
}

void MainWindow::onSpeedChanged(int value)
{
    playbackSpeed = value / 100.0; // Convert slider value to speed multiplier

    QString speedText = QString("x%1").arg(playbackSpeed, 0, 'f', 1);
    ui->playbackSpeed->setText(speedText);

    if (timer->isActive()) {
        timer->start(1000 / (fps * playbackSpeed)); // Update the timer interval
    }
}

void MainWindow::updateFrame()
{
    realFPS = fpsCalculator->calculateRealTimeFPS();
    fpsCalculator->countFrame();

    if (currentFrameIndex < imageFiles.size()) {
        displayCurrentFrame();
        currentFrameIndex++;
    } else {
        currentFrameIndex = 0; // Reset to the beginning
        displayCurrentFrame();
    }
    ui->progressBar->setValue(currentFrameIndex);
}

void MainWindow::displayCurrentFrame()
{
    QString currentImagePath = QString::fromStdString(imagePath) + "/" + QString::fromStdString(imageFiles[currentFrameIndex]);
    cv::Mat image = cv::imread(currentImagePath.toStdString());

    cv::Mat processedFrame = frameProcessor->processFrame(image, isGrayscale, isRedChannel, rotationAngle);

    if (!processedFrame.empty()) {
        // Display FPS on the top-right corner
        cv::putText(processedFrame, "Desired FPS: " + std::to_string(fps * playbackSpeed), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        cv::putText(processedFrame, "Real FPS (between 2 frames): " + std::to_string(realFPS), cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        cv::putText(processedFrame, "Real FPS (over 1 seconds): " + std::to_string(fpsCalculator->getFpsCount()), cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        // Convert cv::Mat to QImage
        QImage qimage(processedFrame.data, processedFrame.cols, processedFrame.rows, processedFrame.step, QImage::Format_RGB888);
        ui->frameLabel->setPixmap(QPixmap::fromImage(qimage.rgbSwapped()));
        ui->frameLabel->setScaledContents(true);
    }
}
