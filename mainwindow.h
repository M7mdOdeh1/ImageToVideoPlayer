#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onSpeedChanged(int value);
    void updateFrame();
    void calculateFPS();
    

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *fpsTimer;
    std::vector<std::string> imageFiles;
    std::string imagePath;
    int currentFrameIndex;
    int fps;
    double playbackSpeed;
    std::chrono::high_resolution_clock::time_point lastFrameTime;
    double realFPS = 0.0;
    int frameCount = 0;    // Frame counter
    double calculatedFPS = 0.0; // FPS calculated using the second timer


    void loadImages();
    void displayCurrentFrame();
};

#endif // MAINWINDOW_H
