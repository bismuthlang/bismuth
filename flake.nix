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
        pkgs.llvmPackages_14.libcxxStdenv.cc.override { 
          inherit (pkgs.llvmPackages_14) bintools;
      });
    in {
      devShell.${system} = llvmEnv.mkDerivation {
      name = "bismuth";
        nativeBuildInputs = [
          pkgs.clang-tools_12 
          pkgs.cmake
          pkgs.pkg-config
          pkgs.libossp_uuid
          pkgs.unzip
          pkgs.libxml2
        ] ++ [
pkgs.llvmPackages_12.libllvm
        ];
         LDFLAGS = [ "-L${pkgs.llvmPackages_12.libllvm.dev}/lib" ];
       #  LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib";
        shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.llvmPackages_12.libstdcxxClang}/lib:${pkgs.libossp_uuid}/lib"
  '';
       # shellHook = ''
    #export LD_LIBRARY_PATH="${stdenv.cc.cc.lib}/lib/:${pkgs.llvmPackages_12.libclang}/lib:${pkgs.llvmPackages_12.libstdcxxClang}/lib:${pkgs.libossp_uuid}/lib"
#  '';
      };
    };
  
}
