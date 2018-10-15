#Make ducky-flasher a default command

import os

permission = os.system("sudo chmod 777 ducky-flasher")

if permission == 0:
    move = os.system("sudo cp ducky-flasher /usr/bin; sudo cp -r Firmware /usr/bin")
    if move == 0:
        print('ducky-flasher is setup!')
        print('To use it, type sudo ducky-flasher')
    else:
        print('Make sure you ran setup.py with sudo')

else:
    print('Make sure you ran setup.py with sudo')
