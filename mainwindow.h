#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <vector>
#include <string>
#include <QKeyEvent>
#include <memory>
#include "include/imageloader.h"
#include "include/frameprocessor.h"
#include "include/fpscalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onSpeedChanged(int value);
    void updateFrame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<std::string> imageFiles;
    std::string imagePath;
    int currentFrameIndex;
    int fps;
    double playbackSpeed;
    
    std::unique_ptr<FrameProcessor> frameProcessor;
    std::unique_ptr<FPSCalculator> fpsCalculator;

    bool isGrayscale;
    bool isRedChannel;
    double rotationAngle;

    double realFPS;

    void displayCurrentFrame();
};

#endif // MAINWINDOW_H
