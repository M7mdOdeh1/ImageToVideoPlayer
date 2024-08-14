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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<std::string> imageFiles;
    std::string imagePath;
    int currentFrameIndex;
    int fps;
    double playbackSpeed;

    void loadImages();
    void displayCurrentFrame();
};

#endif // MAINWINDOW_H
