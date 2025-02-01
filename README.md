# Maguic
A (maybe) future C++ library for GUI using SDL3 ???.

## Requirements
Intall SDL3 dev libraries

### Arch Linux
```
sudo pacman -Sy sdl3
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