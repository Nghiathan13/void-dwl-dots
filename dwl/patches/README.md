# dwl patches (base: e203845, wlroots 0.20)

Apply order:
  git apply patches/autostart_main-5fd19fe.patch
  git apply patches/dragmfact-v0.9.patch

Then copy config.h over, build:
  sudo make clean install

1. autostart_main-5fd19fe - spawn autostart[] after socket ready, kill on quit
2. dragmfact-v0.9 - Mod+middle drag resizes mfact (rebinds togglefloating,
   use Mod+Shift+Space instead)
