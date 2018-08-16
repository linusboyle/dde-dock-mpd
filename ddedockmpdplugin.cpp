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

    if(m_widget->isEnabled())
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

bool DDEDockMPDPlugin::pluginIsDisable(){
    return !m_widget->isEnabled();
}

void DDEDockMPDPlugin::pluginStateSwitched(){
    m_widget->setEnabled(!m_widget->isEnabled());

    if(m_widget->isEnabled()){
        m_proxyInter->itemAdded(this,QString());
        m_widget->show();
    } else {
        m_proxyInter->itemRemoved(this,QString());
        m_widget->hide();
    }
}
