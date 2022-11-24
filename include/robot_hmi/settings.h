#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

Q_SIGNALS:
    void velRangChanged(float vel, float ang);
    void testEnable(bool t);

private:
    void connect_init();
    void ReadSettings();
    void WriteSettings();

private:
    float angmax=100, velmax=100;
    bool tenable=false;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
