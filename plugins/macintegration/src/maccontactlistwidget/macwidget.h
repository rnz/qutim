/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Denis Daschenko <daschenko@gmail.com>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QUTIM_END_LICENSE$
**
****************************************************************************/

#ifndef MACWIDGET_H
#define MACWIDGET_H
#include <QMainWindow>
#include <qutim/simplecontactlist/abstractcontactlist.h>
#include <qutim/simplecontactlist/simplecontactlistview.h>
#include <qutim/status.h>

namespace qutim_sdk_0_3
{
class Account;
class Contact;
class ChatSession;
}

class QLineEdit;


namespace Core {
namespace SimpleContactList {
class MacWidgetPrivate;

enum MacMenuId
{
	MacMenuFile,
	MacMenuAccounts,
	MacMenuChats,
	MacMenuRoster,
	MacMenuSize
};

class MacWidget : public QMainWindow, public AbstractContactListWidget
{
	Q_OBJECT
	Q_INTERFACES(Core::SimpleContactList::AbstractContactListWidget)
	Q_CLASSINFO("Uses", "ContactDelegate")
	Q_CLASSINFO("Uses", "ContactModel")
	Q_CLASSINFO("Service", "ContactListWidget")
	Q_DECLARE_PRIVATE(MacWidget)
public:
	MacWidget();
	~MacWidget();
	virtual void addButton(ActionGenerator *generator);
	virtual void removeButton(ActionGenerator *generator);
private slots:
	void showStatusDialog();
	void changeStatusTextAccepted();
	void onAccountCreated(qutim_sdk_0_3::Account *account);
	void onAccountStatusChanged(const qutim_sdk_0_3::Status &status);
	void onAccountDestroyed(QObject *obj);
	void onSessionCreated(qutim_sdk_0_3::ChatSession*);
	void onSessionDestroyed();
	void onActivatedSession(bool state);
	void initMenu();
	void onTextChanged(const QString &text);
protected:
	void loadGeometry();
	void addMenu(const QString &title, MacMenuId id);
	bool eventFilter(QObject *obj, QEvent *ev);
private:
	QScopedPointer<MacWidgetPrivate> d_ptr;
};

} // namespace SimpleContactList
} // namespace Core

#endif // MACWIDGET_H

