#!/usr/bin/env bash

FILE=$1

java -jar ./out/artifacts/old_USB_Rubber_Ducky_jar/USB-Rubber-Ducky.jar -i Encoder/test-files/inputs/$FILE.txt -o Encoder/test-files/outputs/$FILE.bin
