{
  description = "The Bismuth Programming language";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs, ... }:
    let 
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      llvmPkgs = nixpkgs.legacyPackages.${system}.pkgsLLVM;
      llvm = pkgs.llvmPackages_19; 
      libllvm = llvm.libllvm.override {
        pkgsBuildBuild.targetPackages.stdenv.cc = pkgs.llvm.libcxxClang;
      }; 
#      llvmEnv = pkgs.overrideCC pkgs.stdenv (
#        pkgs.llvmPackages_19.libcxxStdenv.cc.override { 
#           inherit (pkgs.llvmPackages_19) bintools;
#      });
    in {
#      devShell.${system}
#packages.${system}.default 
#      devShell.${system} 
packages.${system}.default = pkgs.stdenv.mkDerivation {
      name = "bismuth";
      src = self;

      out = [ "install" ];


      Catch2_SOURCE_DIR = "${pkgs.catch2_3.src}";

      nativeBuildInputs = [
          pkgs.cmake
          pkgs.cpm-cmake
          pkgs.pkg-config
          pkgs.jdk17
          pkgs.unzip
          pkgs.catch2_3
          pkgs.lcov
      ];
      buildInputs = [
          pkgs.git
          pkgs.llvmPackages_19.libllvm
          pkgs.libossp_uuid
          pkgs.libxml2.dev
          pkgs.zlib.static
          pkgs.libffi
        ];
      };
    };
}
