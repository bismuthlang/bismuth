{
  description = "The Bismuth Programming language";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }:
    let 
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      #stdenv = pkgs.llvmPackages_12.stdenv;
    in {
      devShell.${system} = pkgs.llvmPackages_14.libcxxStdenv.mkDerivation {
      name = "bismuth";
      #(pkgs.mkShell.override {
#        stdenv = pkgs.llvmPackages_12.stdenv;
 #     }) {
        nativeBuildInputs = [
          pkgs.stdenv.override {
            LD = pkgs.lld12;
          }
          pkgs.llvmPackages_12.libllvm
          pkgs.lld_12
         # pkgs.llvmPackages_12.libclang
         # pkgs.llvmPackages_12.libstdcxxClang
#          pkgs.llvmPackages_12.libcxxClang
          pkgs.cmake
          pkgs.pkg-config
          pkgs.libossp_uuid
          pkgs.unzip
        ] ++ [
            pkgs.llvmPackages_12.libllvm
        ];
       #  LD_LIBRARY_PATH = "${pkgs.stdenv.cc.cc.lib}/lib";
#        shellHook = ''
#    export LD_LIBRARY_PATH="${pkgs.llvmPackages_12.libstdcxxClang}/lib:${pkgs.libossp_uuid}/lib"
#  '';
       # shellHook = ''
    #export LD_LIBRARY_PATH="${stdenv.cc.cc.lib}/lib/:${pkgs.llvmPackages_12.libclang}/lib:${pkgs.llvmPackages_12.libstdcxxClang}/lib:${pkgs.libossp_uuid}/lib"
#  '';
      };
    };
  
}
