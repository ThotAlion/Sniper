import OSC
import time
from random import randint as randInt

toto = ["BUY_UP","BUY_DOWN","SELL_UP","SELL_DOWN","HOLD_UP","HOLD_DOWN"]

while True:
    speed = randInt(50,100)
    nrobot = randInt(2,11)
    iorder = randInt(0,5)
    balance = randInt(0,255)
    # Init OSC
    client = OSC.OSCClient()
    msg = OSC.OSCMessage()
    msg.setAddress("/ROBOT_"+str(nrobot)+"/CONF")
    msg.append(speed)
    client.sendto(msg, ('192.168.10.255', 8888))
    time.sleep(0.1)
    
    msg = OSC.OSCMessage()
    msg.setAddress("/ROBOT_"+str(nrobot)+"/"+toto[iorder])
    msg.append(balance)
    client.sendto(msg, ('192.168.10.255', 8888))
    time.sleep(0.3)