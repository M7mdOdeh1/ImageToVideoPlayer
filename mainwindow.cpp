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

    statusBar()->showMessage("Ready");


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

    // Set up the playback speed slider
    ui->speedSlider->setRange(10, 200); // 0.1x to 2.0x speed
    ui->speedSlider->setValue(100);     // Default 1x speed (30 fps)
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::loadImages()
{
    QDir dir(QString::fromStdString(imagePath));
    QStringList qImageFiles = dir.entryList(QStringList() << "*.jpeg", QDir::Files);

    // Convert QStringList to std::vector<std::string>
    for (const QString &filename : qImageFiles) {
        imageFiles.push_back(filename.toStdString());
    }

    // Sort images by the numeric index between the last underscore and the last dot
    std::sort(imageFiles.begin(), imageFiles.end(), [](const std::string &a, const std::string &b) {
        std::string numA = a.substr(a.rfind('_') + 1, a.rfind('.') - a.rfind('_') - 1);
        std::string numB = b.substr(b.rfind('_') + 1, b.rfind('.') - b.rfind('_') - 1);
        return std::stod(numA) < std::stod(numB);
    });
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

void MainWindow::updateFrame()
{
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
        cv::putText(image, "FPS: " + std::to_string(fps * playbackSpeed), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        // Convert cv::Mat to QImage
        QImage qimage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->frameLabel->setPixmap(QPixmap::fromImage(qimage.rgbSwapped()));
        ui->frameLabel->setScaledContents(true);
    }
}
