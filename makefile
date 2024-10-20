.RECIPEPREFIX = >

.PHONY: default
default: mkdir build/kernel

.PHONY: build/kernel
build/kernel: build/libk.a
> make -C kernel/arch/i386
> grub-file --is-x86-multiboot build/kernel

.PHONY: build/libk.a
build/libk.a:
> make -C libc

.PHONY: grub-iso
grub-iso: build/kernel
> mkdir -p build/iso
> mkdir -p build/iso/boot
> mkdir -p build/iso/boot/grub
>
> cp build/kernel build/iso/boot/kernel
> cp grub.cfg     build/iso/boot/grub/grub.cfg
>
> grub-mkrescue -o build/lake.iso build/iso

.PHONY: mkdir
mkdir:
> mkdir -p build

.PHONY: clean
clean:
> rm -rf build/

