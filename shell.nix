{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.grub2        
		pkgs.xorriso     
	];
}

