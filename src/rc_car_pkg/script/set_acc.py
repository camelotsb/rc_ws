#!/usr/bin/env python3

import termios
import time
import rospy
#ros msgs
from std_msgs.msg import Int32
from std_msgs.msg import String

rospy.init_node('rc_acc',anonymous=True)

print("node_initiated")

acc_state=Int32(0)
t0=rospy.Time.now()

def set_acc_callback(acc):
    global acc_state, t0

    if acc.data == 0:
        print("recieved 0 from controller")
        t0=rospy.Time.now()
    #elif acc == 1:
    acc_state=acc
    print(acc_state)

rospy.Subscriber("/front_back_selec",Int32, set_acc_callback)
set_acc_pub=rospy.Publisher("/cmd_vel",Int32, queue_size=20)

if __name__ == '__main__':
    
    
    try:
        while not rospy.is_shutdown():
            if acc_state.data == 0 :
                delt=(rospy.Time.now()-t0).to_sec()
                print(delt)
                if  delt> 0.5 :
                    set_acc_pub.publish(0)
                    print("setting acc=0")


            else:
                print("setting acc =",acc_state)
                set_acc_pub.publish(acc_state)
        rospy.spin()
        
                   
            
            
    except KeyboardInterrupt:
        print("interupted!!!")

    except Exception as e:
        print(e)
