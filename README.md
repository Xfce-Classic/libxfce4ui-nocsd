libxfce4ui-nocsd
================
This is a fork of libxfce4ui with the explicit goal of removing Client-Side Decorations (CSD).

Currently, functions introduced in somewhere between libxfce4ui 4.15 and 4.16 enable
CSD by default for all applications that use the XfceTitledDialog class. This is a
rather invasive UI change and, for some, is entirely unwanted. Since,
[upstream has indicated that they have no intention to allow users to turn CSD off](https://gitlab.xfce.org/xfce/libxfce4ui/-/issues/14),
this fork exists to allow users to disable CSD in any applications that use libxfce4ui.

We implement all CSD-specific functionality as ABI-compatible shims that
simply forward to the relevant GtkDialog methods. This allows upstream applications
built against upstream libxfce4ui to function with no modifications.

**IMPORTANT**: libxfce4ui-nocsd will only remove CSDs for applications that use the XfceTitledDialog class. To remove CSDs from
any applications that use GTK3 Dialogs, you need to set the `DialogsUseHeader` option to `false`:

```
$ xfconf-query -c xsettings -p /Gtk/DialogsUseHeader -s false
```

This can also be done via the GUI under `Settings Editor > xsettings > Gtk`.

Installing
----------
### Repositories

If packages aren't available for your distribution, skip to the Manual Installation section.

**Gentoo**: [Xfce Classic Overlay](https://github.com/Xfce-Classic/gentoo-overlay)

**Manjaro**: In official repository as `libxfce4ui-nocsd`

**Arch**: [AUR](https://aur.archlinux.org/packages/libxfce4ui-nocsd/)

**Ubuntu**: [Xubuntu QA Experimental PPA](https://launchpad.net/~xubuntu-dev/+archive/ubuntu/experimental/+packages)  
*Note: The PPA currently contains builds of libxfce4ui-nocsd with the package name
libxfce4ui-nocsd-2-0. The package name and availability on this PPA is subject to change in the future.*

### Manual Installation

To build libxfce4ui-nocsd from sources, you just need to perform the standard
autotools dance:
```
$ ./autogen.sh # Not requried for tarballs from the Releases tab
$ ./configure --prefix=/opt/libxfce4ui-nocsd # Choose any prefix you'd like
$ make
$ make install
```

Once installed to your chosen prefix, simply add the lib folder to the top of your `LD_LIBRARY_PATH` to ensure that applications dynamically linked against libxfce4ui
will choose this version over any others you may have installed on your system.

For example:
```
export LD_LIBRARY_PATH=/opt/libxfce4ui-nocsd/lib:$LD_LIBRARY_PATH
```
