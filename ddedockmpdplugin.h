#ifndef DDEDOCKMPDPLUGIN_H
#define DDEDOCKMPDPLUGIN_H

#include <dde-dock/pluginsiteminterface.h>
#include <qobject.h>

class DDEDockMPDWidget;
class TipsWidget;

class DDEDockMPDPlugin : public QObject,PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "dde-dock-mpd.json")

public:
    explicit DDEDockMPDPlugin(QObject* parent = nullptr);

    const QString pluginName() const override;
    const QString pluginDisplayName() const override;

    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;

private:
    DDEDockMPDWidget* m_widget;
    TipsWidget* m_tipwidget;
};

#endif // DDEDOCKMPDPLUGIN_H