#include "quetzalprotocol.h"
#include "quetzalaccount.h"
#include <qutim/debug.h>

QuetzalProtocol::QuetzalProtocol(const QuetzalMetaObject *meta, PurplePlugin *plugin)
{
	QObject::d_ptr->metaObject = const_cast<QuetzalMetaObject *>(meta);
	m_plugin = plugin;
	protocols().insert(m_plugin, this);
}

QList<Account *> QuetzalProtocol::accounts() const
{
	QList<QuetzalAccount *> accounts = m_accounts.values();
	return *reinterpret_cast<QList<Account *> *>(&accounts);
}

Account *QuetzalProtocol::account(const QString &id) const
{
	return m_accounts.value(id);
}

void QuetzalProtocol::loadAccounts()
{
	QStringList accounts = config("general").value("accounts", QStringList());
	debug() << id() << accounts;
	foreach(const QString &id, accounts)
		m_accounts.insert(id, new QuetzalAccount(id, this));
}

QByteArray quetzal_fix_protocol_name(const char *name)
{
	if (!qstrcmp(name, "XMPP"))
		return "jabber";
	return QByteArray(name).toLower();
}

QuetzalMetaObject::QuetzalMetaObject(PurplePlugin *protocol)
{
	QByteArray stringdata_b = "Quetzal::";
	stringdata_b += protocol->info->id;
	stringdata_b += '\0';
	stringdata_b.replace('-', '_');
	int value = stringdata_b.size();
	stringdata_b += quetzal_fix_protocol_name(protocol->info->name);
	stringdata_b += '\0';
	int key = stringdata_b.size();
	stringdata_b.append("Protocol\0", 9);

	char *stringdata = (char*)qMalloc(stringdata_b.size() + 1);
	uint *data = (uint*) calloc(17, sizeof(uint));
	qMemCopy(stringdata, stringdata_b.constData(), stringdata_b.size() + 1);
	data[0] = 4;
	data[2] = 1;
	data[3] = 14;
	data[14] = key;
	data[15] = value;

	d.superdata = &QuetzalProtocol::staticMetaObject;
	d.stringdata = stringdata;
	d.data = data;
	d.extradata = 0;
}
