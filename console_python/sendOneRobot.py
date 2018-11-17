import OSC
import time
from random import randint as randInt

toto = ["BUY_UP","BUY_DOWN","SELL_UP","SELL_DOWN","HOLD_UP","HOLD_DOWN"]

speed = 100
nrobot = 9
iorder = randInt(0,5)
balance = randInt(0,255)
# Init OSC
client = OSC.OSCClient()
msg = OSC.OSCMessage()
msg.setAddress("/ROBOT_"+str(nrobot)+"/CONF")
msg.append(0)
client.sendto(msg, ('192.168.10.255', 8888))
time.sleep(1.0)



msg = OSC.OSCMessage()
msg.setAddress("/ROBOT_"+str(nrobot)+"/"+toto[iorder])
msg.append(balance)
client.sendto(msg, ('192.168.10.255', 8888))
time.sleep(1.0)

for i in range(150):
    msg = OSC.OSCMessage()
    msg.setAddress("/ROBOT_"+str(nrobot)+"/CONF")
    msg.append(i)
    client.sendto(msg, ('192.168.10.255', 8888))
    time.sleep(0.1)
    
time.sleep(10.0)
msg = OSC.OSCMessage()
msg.setAddress("/ROBOT_"+str(nrobot)+"/CONF")
msg.append(0)
client.sendto(msg, ('192.168.10.255', 8888))
time.sleep(1.0)
    