#include "../include/imageloader.h"
#include <QDir>
#include <algorithm>

ImageLoader::ImageLoader(const std::string directory)
    : directoryPath(directory) {}

std::vector<std::string> ImageLoader::loadImages() {
    QDir dir(QString::fromStdString(directoryPath));
    QStringList qImageFiles = dir.entryList(QStringList() << "*.jpeg" << "*.jpg" << "*.png", QDir::Files);

    std::vector<std::string> imageFiles;
    for (const QString& filename : qImageFiles) {
        imageFiles.push_back(filename.toStdString());
    }

    // Sort images by the numeric index before the last dot
    std::sort(imageFiles.begin(), imageFiles.end(), [](const std::string& a, const std::string& b) {
        std::string numA = a.substr(0, a.rfind('.'));
        std::string numB = b.substr(0, b.rfind('.'));
        return std::stod(numA) < std::stod(numB);
    });

    return imageFiles;
}

void ImageLoader::setDirectory(const std::string directory) {
    directoryPath = directory;
}
