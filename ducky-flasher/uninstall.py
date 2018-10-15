#Uninstall ducky-flasher
import os
from builtins import input
os.system("clear")
print('Are you sure you want to uninstall ducky-flahser?')
print('1 = yes')
print('2 = no')
question = int(input("Choice: "))

if question == 1:
    os.system("clear")
    print('Uninstalling...')
    status = os.system("sudo rm /usr/bin/ducky-flasher; rm -r /usr/bin/Firmware")
    if status == 0:
        os.system("clear")
        print('ducky-flasher has been uninstalled :(')
    else:
        print('make sure your running as root')
else:
    os.system("clear")
    print('OK, Awesome :P')
