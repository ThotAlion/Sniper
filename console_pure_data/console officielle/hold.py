import OSC
import time
from random import randint as randInt

toto = ["BUY_UP","BUY_DOWN","SELL_UP","SELL_DOWN","HOLD_UP","HOLD_DOWN"]
t0 = time.time()
    
client = OSC.OSCClient()
for i in range(12):
    msg = OSC.OSCMessage()
    msg.setAddress("/ROBOT_"+str(i)+"/HOLD_UP")
    msg.append(0)
    client.sendto(msg, ('192.168.10.255', 8888))
    time.sleep(0.1)