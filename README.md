# Video Player with Qt and OpenCV

This project is a simple video player built using Qt and OpenCV. The player reads a series of images and plays them as a video, with features such as play/pause, speed control, and a progress bar.

## Features

- **Play/Pause**: Start and stop video playback with the click of a button.
- **Speed Control**: Adjust the playback speed from 0.1x to 2.0x using a slider to controll the frame rate per second (FPS). 
- **Progress Bar**: Track video progress and seek to a specific frame.
- **FPS Display**: Displays the current frame rate in the top-right corner of the video.
- **Loop Playback**: Automatically loops the video when it reaches the end.

## Steps Taken to Complete the Project

### 1. **Setting Up the Qt Project**
   - Created a new Qt Widgets Application project in Qt Creator.
   - Added the necessary UI components (`QPushButton`, `QSlider`, `QLabel`, and `QProgressBar`) to the main window using Qt Designer.
   - Set up the `mainwindow.ui` file with the following elements:
     - `QLabel` named `frameLabel` to display the video frames.
     - `QPushButton` named `playButton` for playing the video.
     - `QPushButton` named `pauseButton` for pausing the video.
     - `QSlider` named `speedSlider` for controlling the playback speed.
     - `QProgressBar` named `progressBar` for showing the progress of the video.
     - `QLabel` named `playbackSpeed` for displaying the current speed of the video.

### 2. **Implementing the Main Window Logic**
   - Created the `MainWindow` class in `mainwindow.h` and `mainwindow.cpp`.
   - Implemented the `loadImages()` function to load images from a specified directory and sort them based on their numeric index.
   - Connected the UI elements (`playButton`, `pauseButton`, `speedSlider`) to their respective slots.
   - Set up a `QTimer` to handle the frame updates at regular intervals based on the playback speed.

### 3. **Adding Icons and Style to Buttons**
   - Loaded icons for the play and pause buttons using `QIcon`.
   - Adjusted the icon size using `setIconSize()`.
   - Applied a transparent background to the buttons using `setStyleSheet()`.

### 4. **Implementing Video Playback Functionality**
   - Created the `updateFrame()` function to display the current frame in the `frameLabel`.
   - Updated the progress bar using `ui->progressBar->setValue(currentFrameIndex)` within `updateFrame()`.
   - Implemented looping functionality by resetting `currentFrameIndex` to `0` when it reaches the end.

### 5. **Handling Playback Speed Changes**
   - Connected the `speedSlider` value changes to the `onSpeedChanged()` function.
   - Updated the playback speed dynamically and reflected it in the `playbackSpeed` label.

### 6. **Final Touches**
   - Added a status bar message to indicate the progress of the video. 
   - Added additional features such as automatically disabling the play button after clicking and enabling it after pause.

## How to Run

1. Clone the repository to your local machine.
2. Open the project in Qt Creator.
3. Build the project using CMake.
4. Run the application.

## Requirements

- Qt 6.x
- OpenCV 4.x
- CMake 3.5 or later

## Demo Video
[Screencast from 08-14-2024 07:51:52 PM.webm](https://github.com/user-attachments/assets/a5bcd8ca-b8de-4368-ab3d-93b77b6f7989)


