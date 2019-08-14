#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "utility.h"

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QDateTime>
#include <QDebug>

class ConfigParams;

class SettingsDialog: public QDialog
{
	Q_OBJECT
public:
	SettingsDialog(ConfigParams* params, QWidget* p = nullptr);

	// QWidget interface
protected:
	void showEvent(QShowEvent* event) override;

private:
	void setInfoLabels();

private:
	ConfigParams* params_;

	QSpinBox* spinWork, *spinShort, *spinLong, *spinReps;

	QCheckBox* pchturnLongRest, *pchshowAgain;

	QPushButton* pcmdOk, *pcmdCancel;

	QLabel* next_tomato_completion;

	QLabel* max_tomatoes_label;

private slots:
	void slotAccept();

	void slotReject();

	void slotParametersChanged();

};

#endif // SETTINGSDIALOG_H
