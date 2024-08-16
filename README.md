# Video Player with Qt and OpenCV

This project is a video player built using Qt and OpenCV. It reads a series of images and plays them as a video, with features such as play/pause, speed control, grayscale conversion, rotation, and a progress bar.

## Features

- **Play/Pause**: Start and stop video playback with the click of a button.
- **Speed Control**: Adjust the playback speed from 0.1x to 2.0x using a slider, controlling the frame rate per second (FPS).
- **Progress Bar**: Track video progress and seek to a specific frame.
- **FPS Display**: Displays both real-time FPS and calculated FPS in the top-right corner of the video.
- **Loop Playback**: Automatically loops the video when it reaches the end.
- **Grayscale and Red Channel Modes**: Toggle grayscale and red-channel-only modes using keyboard arrow keys.
- **Rotation**: Rotate the video in 90-degree increments with the left and right arrow keys.

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

### 2. **Refactoring for Clean Code**
   - Extracted the image loading logic into a dedicated `ImageLoader` class for better separation of concerns.
   - Created a `FrameProcessor` class to handle grayscale conversion, red-channel manipulation, and rotation functionality, decoupling image processing from the main window logic.
   - Added an `FPSCalculator` class to manage FPS calculations, including both real-time and average FPS calculation approaches.

### 3. **Modularization and Code Clean-Up**
   - Refactored `MainWindow` to utilize the newly introduced classes, making the code more modular and easier to maintain.
   - Removed redundant logic from `MainWindow` and moved it to the appropriate classes.
   - Enhanced the readability and maintainability of the code by dividing functionality into single-purpose classes.

### 4. **Implementing the Main Window Logic**
   - Implemented the `loadImages()` function in `ImageLoader` to load images from a specified directory and sort them based on their numeric index.
   - Connected the UI elements (`playButton`, `pauseButton`, `speedSlider`) to their respective slots in the main window.
   - Set up a `QTimer` to handle the frame updates at regular intervals based on the playback speed.
   - Added key press handling for toggling grayscale, red-channel-only modes, and rotating the video.

### 5. **Enhancing User Experience**
   - Added icons for the play and pause buttons using `QIcon`.
   - Adjusted the icon size using `setIconSize()` and applied a transparent background using `setStyleSheet()`.
   - Ensured smooth playback and seamless transitions between different playback speeds.
   - Displayed FPS information on the video frames to give users real-time performance feedback.

### 6. **Implementing Video Playback Functionality**
   - Created the `updateFrame()` function to display the current frame in the `frameLabel`.
   - Updated the progress bar in real-time using `ui->progressBar->setValue(currentFrameIndex)` within `updateFrame()`.
   - Implemented looping functionality by resetting `currentFrameIndex` to `0` when it reaches the end of the video.

### 7. **Handling Playback Speed Changes**
   - Connected the `speedSlider` value changes to the `onSpeedChanged()` function.
   - Updated the playback speed dynamically and reflected it in the `playbackSpeed` label.
   - Ensured that the FPS calculation and video frame timing adjusted appropriately to the new speed.

### 8. **Final Touches**
   - Added status bar messages to indicate the progress of the video.
   - Enhanced the user experience by automatically disabling the play button after clicking and enabling it after pausing.
   - Ensured that keypress events work across different UI elements by setting the appropriate focus policies.

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


