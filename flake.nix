{
  description = "The Bismuth Programming language";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }:
    let 
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      llvmEnv = pkgs.overrideCC pkgs.stdenv (
        pkgs.llvmPackages_12.libcxxStdenv.cc.override { 
           inherit (pkgs.llvmPackages_12) bintools;
      });
    in {
      devShell.${system} = llvmEnv.mkDerivation {
      name = "bismuth";
        nativeBuildInputs = [
          pkgs.ninja
          pkgs.clang-tools_12
          pkgs.cmake
          pkgs.pkg-config
          pkgs.jdk17
          pkgs.unzip
        ];
        buildInputs = [
          pkgs.llvmPackages_12.libllvm
          pkgs.libossp_uuid
          pkgs.libxml2
          pkgs.zlib
        ];
       # LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath [ pkgs.llvmPackages_12.libllvm ]}";
      };
    };
  
}
