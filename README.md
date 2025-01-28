# Maguic
A (maybe) future C++ library for GUI using SDL2.

## Requirements
Intall SDL2 dev libraries

### NixOS
```nix
{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    buildInputs = with pkgs; [
      gnumake
      cmake
      glib
      pkg-config

      SDL2
      SDL2_ttf
      SDL2_net
      SDL2_gfx
      SDL2_sound
      SDL2_mixer
      SDL2_image
    ];
    GREETING = "SDL2/CMake env dev started";

    shellHook = ''
      zsh
      echo $GREETING
    '';
}
```