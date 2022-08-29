#ifndef MYTABPOPUP_H
#define MYTABPOPUP_H

#include <QWidget>

/**
 * @brief 一个容纳tab弹出页的窗口
 */
class MyTabPopup : public QWidget {
    Q_OBJECT
public:
    explicit MyTabPopup(QWidget* parent = nullptr);

    void setContentWidget(QWidget* page);
    QWidget* getContentWidget();

protected:
    //    bool event(QEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void dragRelease(const QPoint& globalPos);
    void backToTabWidget();

private:
    QWidget* content = nullptr;
};

#endif // MYTABPOPUP_H
