#include <QApplication>
#include <QSettings>

#include "MainWindow.hpp"

constexpr int DEFAULT_WIDTH = 500;
constexpr int DEFAULT_HEIGHT = 600;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QApplication::setOrganizationName("flatulation");
    QApplication::setApplicationName("heatin");
    QSettings settings;
    const auto size = settings.value("main_size", QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)).value<QSize>();

    MainWindow w;
    w.resize(size);
    w.show();
    auto ret = QApplication::exec();
    settings.setValue("main_size", w.size());
    return ret;
}
