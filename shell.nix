{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell rec {
  buildInputs = with pkgs; [
    stdenv
    clang-tools
    gnumake
    valgrind
  ];
}
