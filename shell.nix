{ pkgs ? import <nixpkgs> {
		localSystem = "x86_64-linux";
		crossSystem = "i686-linux";
	}
}:

pkgs.mkShell {
   nativeBuildInputs = [
    pkgs.grub2        
		pkgs.xorriso     
	];
}

