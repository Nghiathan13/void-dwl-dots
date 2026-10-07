# void-dwl-dots
Minimal Void musl + dwl setup - Nghiathan
- WM: dwl + dwlb + slstatus (~/src/suckless)
- scale eDP-1: 1.5-2, fonts: Noto + Hack
- services: dbus elogind iwd rtkit socklog dcron tlp-off

## Backup (manual copy, no symlinks)
```bash
cp ~/src/suckless/dwl/config.h ~/Projects/void-dwl-dots/dwl/
cp ~/src/suckless/dwlb/config.h ~/Projects/void-dwl-dots/dwlb/
cp ~/src/suckless/slstatus/config.h ~/Projects/void-dwl-dots/slstatus/
cp ~/.local/bin/dwl-start ~/Projects/void-dwl-dots/bin/
cp ~/.local/bin/vol ~/Projects/void-dwl-dots/bin/
cd ~/Projects/void-dwl-dots && git add -A && git commit -m "backup theme..."
```
