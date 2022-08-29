#ifndef ROADTYPELABEL_H
#define ROADTYPELABEL_H

#include <QWidget>

namespace Ui {
class RoadTypeLabel;
}

class RoadTypeLabel : public QWidget {
    Q_OBJECT

public:
    explicit RoadTypeLabel(QWidget* parent = nullptr);
    ~RoadTypeLabel();

public slots:
    void setType(int);

private:
    Ui::RoadTypeLabel* ui;
    QPixmap* roadTypeIcon[3];
};

#endif // ROADTYPELABEL_H
