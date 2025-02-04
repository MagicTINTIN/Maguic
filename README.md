# Maguic
A (maybe) future C++ library for GUI using SDL3 ???.

## Requirements
Install SDL3 dev libraries

### Arch Linux
```
sudo pacman -Sy sdl3 sdl_ttf
```

### NixOS
```nix
{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    buildInputs = with pkgs; [
      gnumake
      cmake
      glib
      pkg-config

      sdl3
    ];
    GREETING = "SDL3/CMake env dev started";

    shellHook = ''
      zsh
      echo $GREETING
    '';
}
```