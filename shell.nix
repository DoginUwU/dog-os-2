{ pkgs ? import <nixpkgs> {
		# localSystem = "x86_64-linux";
		# crossSystem = "i686-linux";
	}
}:

pkgs.mkShell {
   nativeBuildInputs = [
	 		pkgs.bochs
	 		pkgs.gdb
	 		pkgs.nasm
			pkgs.grub2
			pkgs.xorriso
			pkgs.qemu
	];
}
