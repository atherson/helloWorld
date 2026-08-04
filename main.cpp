#include <QApplication>
#include <QLabel>
#include <QFont>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set application metadata
    QApplication::setApplicationName("HelloWorldApp");

    // Create the main window widget
    QLabel window("Hello, World!");
    window.setWindowTitle("Hello world app in qt framework");
    window.resize(400, 250);
    window.setAlignment(Qt::AlignCenter);

    // Enhance typography
    QFont font = window.font();
    font.setPointSize(18);
    font.setBold(true);
    window.setFont(font);

    window.show();

    return app.exec();
}
