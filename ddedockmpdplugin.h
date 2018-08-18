/*
 *  Author: Linus Boyle <linusboyle@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DDEDOCKMPDPLUGIN_H
#define DDEDOCKMPDPLUGIN_H

#include <dde-dock/pluginsiteminterface.h>
#include <qobject.h>

class DDEDockMPDWidget;
class TipsWidget;
class QSettings;
class PlaylistWidget;

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
    QWidget *itemPopupApplet(const QString &itemKey) override;

    void pluginStateSwitched() override;
    bool pluginIsAllowDisable() override {
        return true;
    }
    bool pluginIsDisable() override;

    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString& itemkey,const QString& menuId,const bool checked) override;

    void displayModeChanged(const Dock::DisplayMode displaymode) override;
    void positionChanged(const Dock::Position position) override;

    int itemSortKey(const QString &itemKey) override;
    void setSortKey(const QString &itemKey, const int order) override;

private:
    DDEDockMPDWidget* m_widget;
    TipsWidget* m_tipwidget;
    QSettings* m_setting;
    PlaylistWidget* m_playlist;

    bool positionValid();
};

#endif // DDEDOCKMPDPLUGIN_H
