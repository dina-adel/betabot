#!/usr/bin/env python
import rospy 
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist #to control the speeed/ movement
from std_msgs.msg import Float32

front = Float32()
middle = Float32()
right = Float32()
left = Float32()

def callback(laser):
    print '-------------------------------------------'
    print 'Range data for front:   {}'.format(laser.ranges[179])
    print 'Range data for right:  {}'.format(laser.ranges[269])
    print 'Range data for left: {}'.format(laser.ranges[89])
    print '-------------------------------------------'
    front.data = laser.ranges[179] #front reading
    right.data = laser.ranges[269] #right
    left.data = laser.ranges[89] #left


def move_monitor():
    rospy.init_node('avoid_node',anonymous=True)
    rospy.Subscriber("/scan", LaserScan, callback)
    pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10) 
    move = Twist()
    rate = rospy.Rate(10)
    thr_front = 1.0
    thr_side = 0.5
    while not rospy.is_shutdown():
        if front.data > thr_front and right.data > thr_side and left.data>thr_side: 
        #if no obstacles; move forward
            move.linear.x = 0.3
            move.linear.y = 0.0
            move.linear.z = 0.0 

            move.angular.x =0.0
            move.angular.y =0.0
            move.angular.z = 0.0
            
            pub.publish(move) # publish the move object 
            print ("Moving Forward")
        else:
            move.linear.x = 0.0
            pub.publish(move)
            if right.data > thr_side:
                print ("Rotating right")
                while front.data < thr_front:
                    move.angular.z = -0.3
                    pub.publish(move) 
                move.linear.x = 0.5
                move.linear.y = 0.0
                move.linear.z = 0.0 
                move.angular.x =0.0
                move.angular.y =0.0
                move.angular.z = 0.0
                pub.publish(move)
            elif left.data > thr_side:
                print ("Rotating left")
                while front.data < thr_front:
                    move.angular.z = 0.3
                    pub.publish(move) 
                move.linear.x = 0.5
                move.linear.y = 0.0
                move.linear.z = 0.0 
                move.angular.x =0.0
                move.angular.y =0.0
                move.angular.z = 0.0
                pub.publish(move)   
            #pub.publish(move) # publish the move 
        rate.sleep()


if __name__ == '__main__':
    move_monitor()
    
