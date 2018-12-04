[简体中文](https://github.com/linusboyle/dde-dock-mpd/blob/master/README_zh_CN.md)

# Caution: dde-dock has updated and api changed, chances are that this plugin no longer works!

# dde-dock-mpd

![screenshot](https://raw.githubusercontent.com/linusboyle/dde-dock-mpd/master/img/showcase.png)
![screenshot](https://raw.githubusercontent.com/linusboyle/dde-dock-mpd/master/img/showcase2.png)

This is a plugin of [dde-dock](https://github.com/linuxdeepin/dde-dock) to facilitate user's control of MPD.

It shows the current state of the player and information about the currently played song. With this plugin user can:

- Control the player to play or pause,switch mode(random or list) , goto next or previous song,by just a click on the panel.
- Hover over the plugin to see the current playing progress of the song.
- Left click on the title to popup the playlist.You can select a song to jump to it
- right click to switch if enable list loop mode(a.k.a. MPD's *repeat* mode)

**NOTE**: 

- This plugin does not support fashion mode,'Cause the author think it's unnecessary to control MPD from it
- when dock changed to left/right side,plugin will disable automatically
- User has to spare enough (about 200 pix) space for this plugin,so make your dock tidy :)

## Dependencies

### Compilation 
- Qt5 (>=5.6)
- libmpd (development package)
- [dde-dock](https://github.com/linuxdeepin/dde-dock) (development package)
- [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit) (development package)

### Runtime
- Qt5
- libmpd
- mpd
- [dde-dock](https://github.com/linuxdeepin/dde-dock) 
- [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit)
