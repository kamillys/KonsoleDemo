#pragma once

#include <QWidget>
#include <QSplitter>

class SplitTerm : public QWidget
{
    Q_OBJECT
public:
    SplitTerm(QWidget* parent = NULL);
    virtual ~SplitTerm();
private:
    SplitTerm(QWidget* parent, QWidget* konsole);
signals:
    void closed();
private slots:
    void addSplitTerm(Qt::Orientation dir);
    void childClosed();
private:

    QSplitter* s;
    QWidget* k;
};
