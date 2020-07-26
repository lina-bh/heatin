#include "MainWindow.hpp"
#include <qapplication.h>
#include <qsettings.h>
#include <qsize.h>
#include <qvariant.h>

constexpr int DEFAULT_WIDTH = 500;
constexpr int DEFAULT_HEIGHT = 600;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setOrganizationName("flatulation"); // NOLINT(readability-static-accessed-through-instance)
    a.setApplicationName("heatin"); // NOLINT(readability-static-accessed-through-instance)
    QSettings settings;
    const auto size = settings.value("main_size", QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)).value<QSize>();

    MainWindow w;
    w.resize(size);
    w.show();
    auto ret = a.exec(); // NOLINT(readability-static-accessed-through-instance)
    settings.setValue("main_size", w.size());
    return ret;
}
