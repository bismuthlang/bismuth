{
  description = "The Bismuth Programming language";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }:
    let 
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
#      llvmEnv = pkgs.overrideCC pkgs.stdenv (
#        pkgs.llvmPackages_19.libcxxStdenv.cc.override { 
#           inherit (pkgs.llvmPackages_19) bintools;
#      });
    in {
      devShell.${system} = pkgs.stdenv.mkDerivation {
      name = "bismuth";
        nativeBuildInputs = [
         # pkgs.clang-tools_12
          pkgs.cmake
          pkgs.pkg-config
          pkgs.jdk17
          pkgs.unzip
        ];
        buildInputs = [
       #   pkgs.llvmPackages_19.libcxxClang
          pkgs.llvmPackages_19.libllvm
          pkgs.libossp_uuid
          pkgs.libxml2.dev
          pkgs.zlib.static
            pkgs.libffi
        ]; #  ++ (pkgs.lib.optional pkgs.stdenv.isLinux [ pkgs.glibc.dev pkgs.glibc.static ]);
       #  LLVM_SYS_190_PREFIX = "${pkgs.llvmPackages_19.llvm.dev}";
#       LD_LIBRARY_PATH = "${llvmEnv.cc.cc.lib}/lib";
      };
    };
  
}
