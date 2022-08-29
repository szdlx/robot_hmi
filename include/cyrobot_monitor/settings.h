#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMessageBox>
#include <QSettings>
#include <QWidget>
namespace Ui {
class Settings;
}

class Settings : public QWidget {
    Q_OBJECT

public:
    explicit Settings(QWidget* parent = 0);
    ~Settings();
public slots:
    void slot_ok_btn_click();
    void slot_cancel_btn_click();

Q_SIGNALS:
    void button_name_changed();
    void rviz_topic_changed();

private:
    Ui::Settings* ui;
};

#endif // SETTINGS_H
