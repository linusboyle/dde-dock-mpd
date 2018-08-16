#include "ddedockmpdplugin.h"
#include "ddedockmpdwidget.h"
#include "tipswidget.h"
#include "mpdinterface.h"

DDEDockMPDPlugin::DDEDockMPDPlugin(QObject *parent)
                :QObject(parent)
{
}

const QString DDEDockMPDPlugin::pluginName() const {
    return QStringLiteral("MPDController");
}

const QString DDEDockMPDPlugin::pluginDisplayName() const {
    return QStringLiteral("MPD");
}

void DDEDockMPDPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_widget = new DDEDockMPDWidget();
    m_tipwidget = new TipsWidget();

    proxyInter->itemAdded(this,QString());
}

QWidget *DDEDockMPDPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_widget;
}

QWidget *DDEDockMPDPlugin::itemTipsWidget(const QString &itemKey){
    Q_UNUSED(itemKey);

    return m_tipwidget;
}
