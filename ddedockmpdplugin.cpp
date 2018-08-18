#include "ddedockmpdplugin.h"
#include "ddedockmpdwidget.h"
#include "tipswidget.h"
#include "mpdinterface.h"
#include <QDebug>
#include <QMessageBox>
#include "playlistwidget.h"

#define WIDGET_KEY QString("dde-dock-mpd")

DDEDockMPDPlugin::DDEDockMPDPlugin(QObject *parent)
            :QObject(parent),
             m_setting(new QSettings("deepin","dde-dock-mpd",this))
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
    m_playlist = new PlaylistWidget();

    QTranslator* translator = new QTranslator();
    if(translator->load(":/qm/dde-dock-mpd_" + QLocale::system().name()))
        qApp->installTranslator(translator);
    else {
        qDebug()<<"load translation failed for " <<QLocale::system().name();
        translator->deleteLater();
    }

    if(m_widget->isEnabled() && displayMode() == Dock::DisplayMode::Efficient
            && positionValid() )
        proxyInter->itemAdded(this,WIDGET_KEY);
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

QWidget *DDEDockMPDPlugin::itemPopupApplet(const QString &itemKey){
    Q_UNUSED(itemKey);

    return m_playlist;
}

bool DDEDockMPDPlugin::pluginIsDisable(){
    return !m_widget->isEnabled();
}

void DDEDockMPDPlugin::pluginStateSwitched(){
    m_widget->setEnabled(!m_widget->isEnabled());

    if(m_widget->isEnabled() && displayMode() == Dock::DisplayMode::Efficient && positionValid()){
        m_proxyInter->itemAdded(this,WIDGET_KEY);
        m_widget->show();
    } else if(displayMode() == Dock::DisplayMode::Efficient && positionValid()){
        m_proxyInter->itemRemoved(this,WIDGET_KEY);
        m_widget->hide();
    }
}

const QString DDEDockMPDPlugin::itemContextMenu(const QString &itemKey){
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(2);

    QMap<QString, QVariant> mode;
    mode["itemId"] = "repeatMode";
    if(MPDInterface::instance()->getRepeatMode()){
        mode["itemText"] = tr("Stop Loop");
    } else {
        mode["itemText"]=  tr("Loop Playlist");
    }
    mode["isActive"] = true;
    items.push_back(mode);

    QMap<QString,QVariant> about;
    about["itemId"] = "about";
    about["itemText"] = tr("About");
    about["isActive"] = true;
    items.push_back(about);


    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    return QJsonDocument::fromVariant(menu).toJson();
}

void DDEDockMPDPlugin::invokedMenuItem(const QString &itemkey, const QString &menuId, const bool checked){
    Q_UNUSED(itemkey);
    Q_UNUSED(checked);

    if(menuId == "repeatMode")
        MPDInterface::instance()->switchRepeatMode();
    else if (menuId == "about"){
        QMessageBox aboutMessage(QMessageBox::NoIcon,tr("MPD Control Plugin"),tr("This Plugin is intended for "
                                              "getting information of and controlling MPD"
                                              "from dde-dock\nAuthor:Linus Boyle<linusboyle@gmail.com>\n"
                                              "Licensed under GPLv3,you can find the source code on Github"));
        aboutMessage.setIconPixmap(QPixmap(":/icon/mpd.svg").scaled(48,48,Qt::KeepAspectRatio));
        aboutMessage.exec();
    }
}

void DDEDockMPDPlugin::displayModeChanged(const Dock::DisplayMode displaymode) {
    switch (displaymode) {
        case Dock::DisplayMode::Fashion:
            if(!this->pluginIsDisable() && positionValid())
                m_proxyInter->itemRemoved(this,WIDGET_KEY);
            break;
        case Dock::DisplayMode::Efficient:
            if(!this->pluginIsDisable() && positionValid())
                m_proxyInter->itemAdded(this,WIDGET_KEY);
            break;
        default:
            break;
    }
}

void DDEDockMPDPlugin::positionChanged(const Dock::Position position) {
    switch (position) {
        case Dock::Position::Bottom:
        case Dock::Position::Top:
            if(!this->pluginIsDisable() && displayMode() == Dock::DisplayMode::Efficient){
                m_proxyInter->itemAdded(this,WIDGET_KEY);
            }
            break;
        case Dock::Position::Left:
        case Dock::Position::Right:
            if(!this->pluginIsDisable() && displayMode() == Dock::DisplayMode::Efficient){
                m_proxyInter->itemRemoved(this,WIDGET_KEY);
            }
            break;
        default:
            break;
    }
}

int DDEDockMPDPlugin::itemSortKey(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_setting->value("position",0).toInt();
}

void DDEDockMPDPlugin::setSortKey(const QString &itemKey, const int order) {
    Q_UNUSED(itemKey);

    m_setting->setValue("position",order);
}

bool DDEDockMPDPlugin::positionValid(){
     switch (position()) {
        case Dock::Position::Bottom:
        case Dock::Position::Top:
            return true;
        case Dock::Position::Left:
        case Dock::Position::Right:
            return false;
        default:
            Q_UNREACHABLE();
            break;
    }
}
