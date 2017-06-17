#!/bin/sh

EXIT=0
if lsusb | awk '$6=="03eb:2ff6"{e=1}END{exit e}'; then
    echo "Is your Ducky connected and in DFU mode?  I don't see it.  Try"
    echo "unplugging it, then holding down the button while plugging it back in."
    EXIT=1
fi

FILE=${1:-firmware.hex}		# Where to get our dump.
if test -r "$FILE"; then
    if egrep -vq '^:' "$FILE"; then
	echo "That doesn't look like an ihex file."
	EXIT=1
    fi
else
    echo "No such input file or you don't have permissions to read it."
    EXIT=1
fi

DFU=`which dfu-programmer`
if [ -z "$DFU" ]; then 
    echo "dfu-programmer not found.  Go install it and try again."
    EXIT=1
fi
test $EXIT -eq 1 && exit 1	# Get all the errors at once, then exit

die() {
    echo "$*"
    exit 2
}

echo Erasing...
sudo dfu-programmer at32uc3b1256 erase || die "Failed to erase"
echo Flashing...
sudo dfu-programmer at32uc3b1256 flash --suppress-bootloader-mem "$FILE" \
    || die "Failed to flash"
echo Flash complete.  Resetting your Ducky...
sudo dfu-programmer at32uc3b1256 reset || die "Failed to reset"

