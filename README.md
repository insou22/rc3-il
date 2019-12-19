## rc3-il
Quick patch for `NPEA00387` UYA to add some IL practice features:

- No autosave
- Ammo doesn't decrease
- Single-screen interplanetary loads
- Save/load position hotkey
- Instant savefile reloading

A timer is planned; I'll do it at some point.

### Usage
#### Hotkeys
- `L2 + R2` held, then `SQUARE` pressed: save position
- `L2 + R2` held, then `CIRCLE` pressed: load position
- `L2 + R2` held, then `CROSS` pressed: reload planet
- `L2 + R2 + R1` held, then `CIRCLE` pressed: reload the set-aside savefile
- `L2 + R2 + R1` held, then `SQUARE` pressed: set aside current savefile, then reload it

If no savefile has been set aside and you attempt to reload it, it will work like you also had `Up` held.

### Compiling and installing
0) Make sure your `make.sh` has LF line endings
1) Install `binutils-powerpc64-linux-gnu`. I use WSL. (e.g. `sudo apt install binutils-powerpc64-linux-gnu`)
2) Install `gcc-powerpc64-linux-gnu`. (e.g. `sudo apt install gcc-powerpc64-linux-gnu`)
3) Move a decrypted `EBOOT.BIN` of the game to this directory, and rename it to `EBOOT.ELF.bak`
4) `./make.sh` to compile/assemble the patches
5) `python3 apply.py` to apply the patches to the executable, saving to `EBOOT.ELF`
6) Resign `EBOOT.ELF` such that your platform of choice accepts it.
7) Replace `EBOOT.BIN` in the game