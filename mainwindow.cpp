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
{
    ui->setupUi(this);

    // Specify the path to the images
    imagePath = "../VideoPlayer/trip/left";
    loadImages();

    // Initialize the progress bar
    ui->progressBar->setRange(0, imageFiles.size() - 1);
    ui->progressBar->setValue(0);

    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::onSpeedChanged);
    
    QIcon playIcon("../VideoPlayer/icon/play.png");
    ui->playButton->setIcon(playIcon);
    ui->playButton->setIconSize(QSize(64, 64)); 
    ui->playButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
 
    QIcon pauseIcon("../VideoPlayer/icon/pause.png");
    ui->pauseButton->setIcon(pauseIcon);
    ui->pauseButton->setIconSize(QSize(64, 64)); 
    ui->pauseButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    ui->pauseButton->setEnabled(false);


    // Set up a timer for updating frames
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);

    // Set up a second timer to calculate FPS every second
    fpsTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &MainWindow::calculateFPS);
    fpsTimer->start(1000);  // Trigger every second


    // Set up the playback speed slider
    ui->speedSlider->setRange(10, 200); // 0.1x to 2.0x speed
    ui->speedSlider->setValue(100);     // Default 1x speed(30 fps)

    // Initialize lastFrameTime and lastSecondTime to the current time
    lastFrameTime = std::chrono::high_resolution_clock::now();


}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::calculateFPS()
{
    calculatedFPS = frameCount;
    frameCount = 0;  
}

void MainWindow::loadImages()
{
    QDir dir(QString::fromStdString(imagePath));
    QStringList qImageFiles = dir.entryList(QStringList() << "*.jpeg", QDir::Files);

    // Convert QStringList to std::vector<std::string>
    for (const QString &filename : qImageFiles) {
        imageFiles.push_back(filename.toStdString());
    }

    // Sort images alphapetically
    // std::sort(imageFiles.begin(), imageFiles.end());


    // Sort images by the numeric index before the last dot
    std::sort(imageFiles.begin(), imageFiles.end(), [](const std::string &a, const std::string &b) {
        std::string numA = a.substr(0, a.rfind('.')); // remove .jpeg
        std::string numB = b.substr(0, b.rfind('.')); // remove .jpeg
        return std::stod(numA) < std::stod(numB); 
    });

    
}


void MainWindow::onPlayButtonClicked()
{
    if (!timer->isActive()) {
        timer->start(1000 / (fps * playbackSpeed));
    }

    if (!fpsTimer->isActive()) {
        fpsTimer->start(1000);
    }
    
    ui->playButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);

}

void MainWindow::onPauseButtonClicked()
{
    if (timer->isActive()) {
        timer->stop();
    }

    if(fpsTimer->isActive()) {
        fpsTimer->stop();
    }

    ui->playButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);


}

// handle the speed changr of the slider
void MainWindow::onSpeedChanged(int value)
{
    playbackSpeed = value / 100.0; // Convert slider value to speed multiplier

    QString speedText = QString("x%1").arg(playbackSpeed, 0, 'f', 1); 
    ui->playbackSpeed->setText(speedText);

    if (timer->isActive()) {
        timer->start(1000 / (fps * playbackSpeed)); // Update the timer interval
    }
}

void MainWindow::updateFrame() {
    // Calculate the time since the last frame
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastFrameTime;
    realFPS = 1.0 / elapsedTime.count();  // Calculate the real FPS based on time between frames

    lastFrameTime = currentTime;  

    // Count the number of frames in one second
    frameCount++;
   
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



    if (!image.empty()) {
        // Display the frame rate on the top-right corner
        cv::putText(image, "Desired FPS: " + std::to_string(fps * playbackSpeed), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        // Display the real FPS on the frame
        cv::putText(image, "FPS: " + std::to_string(realFPS), cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        cv::putText(image, "FPS: " + std::to_string(calculatedFPS), cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);


        // Convert cv::Mat to QImage
        QImage qimage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->frameLabel->setPixmap(QPixmap::fromImage(qimage.rgbSwapped()));
        ui->frameLabel->setScaledContents(true);
    }
}
