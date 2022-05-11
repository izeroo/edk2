qemu-system-x86_64 \
	-m 256 -net none \
	-drive if=pflash,format=raw,unit=0,file=/home/zero/ovmf/OVMF_CODE.fd,readonly=on \
	-drive if=pflash,format=raw,unit=1,file=/home/zero/ovmf/OVMF_VARS.fd \
	-drive file=fat:rw:/home/zero/ovmf/esp,format=raw,
