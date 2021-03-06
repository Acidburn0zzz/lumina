//===========================================
//  Lumina-DE source code
//  Copyright (c) 2014, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
//  This panel plugin allows the user to quickly access user favorites and applications
//===========================================
#ifndef _LUMINA_PANEL_USER_BUTTON_WIDGET_H
#define _LUMINA_PANEL_USER_BUTTON_WIDGET_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QHash>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDateTime>
#include <QTransform>
#include <QMouseEvent>
#include <QTabWidget>

#include <LuminaXDG.h>
#include <LuminaOS.h>
#include "UserItemWidget.h"

#define SSAVER QString("xscreensaver-demo")

namespace Ui{
	class UserWidget;
};

class UserWidget : public QTabWidget{
	Q_OBJECT
public:
	UserWidget(QWidget *parent=0);
	~UserWidget();

public slots:
	void UpdateMenu();

private:
	Ui::UserWidget *ui;
	QHash<QString, QList<XDGDesktop> > *sysapps;
	QDateTime lastUpdate;
	int cfav; //current favorite category
	void ClearScrollArea(QScrollArea *area);
	QIcon rotateIcon(QIcon);

private slots:
	void LaunchItem(QString path, bool fix = true);

	//Favorites Tab
	void FavChanged(); //for ensuring radio-button-like behaviour
	void updateFavItems();

	//Apps Tab
	void updateAppCategories();
	void updateApps();

	//Home Tab
	void updateHome();
	void slotGoToDir(QString dir);
	void slotGoHome();
	void slotOpenDir();

	//Slots for the special buttons
	void openStore(){
	  LaunchItem(LOS::AppStoreShortcut());
	}
	void openControlPanel(){
	  LaunchItem(LOS::ControlPanelShortcut());
	}
	void openDeskSettings(){
	  LaunchItem("lumina-config", false);
	}
	void openQtConfig(){
	  LaunchItem( LOS::QtConfigShortcut(), false);
	}
	void openScreenSaverConfig(){
	  LaunchItem(SSAVER, false);
	}

protected:
	void mouseMoveEvent( QMouseEvent *event);

signals:
	void CloseMenu();

};

#endif
