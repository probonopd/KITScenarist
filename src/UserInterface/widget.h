#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class ScenarioTextEdit;

class Widget : public QWidget
{
	Q_OBJECT
public:
	explicit Widget(QWidget *parent = 0);
	void exec();

signals:

public slots:
	void setStyle();
	void styleChanged();
	void save();
	void load();

private:
	ScenarioTextEdit* m_scenarioEdit;

};

#endif // WIDGET_H
