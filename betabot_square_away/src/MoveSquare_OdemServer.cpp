#include "ros/ros.h"
#include "betabot_msgs/MoveSquare.h"
#include "betabot_msgs/MoveSquareRequest.h"
#include "betabot_msgs/MoveSquareResponse.h"
#include "nav_msgs/Odometry.h"
#include "iostream"
#include "geometry_msgs/Twist.h"
#include "tf/tf.h"
#include "tf/transform_datatypes.h"
#include <geometry_msgs/Pose2D.h>

class MoveSquareServer
{
    public:
    MoveSquareServer(): x_(0) ,y_(0){};
    
    //Functions for movement
    void forward (ros::Publisher pubMove, int num_seconds)
    {
        geometry_msgs::Twist msg; 
        ros::Rate rate(5);
        //rate is 5Hz so each 5 iterations = 1 sec
        //in order to specify a number of seconds then
        // loop iterator = num_seconds * rate (5 in our case)
        msg.linear.x = 0.5; msg.linear.y =0.0; msg.linear.z =0.0;
        msg.angular.x = 0.0; msg.angular.y = 0.0; msg.angular.z = 0.0;
        ros::Time start = ros::Time::now();
        for (int i=0;i<num_seconds*5;i++) 
            {
                //publish to cmd_vel topic
              pubMove.publish(msg);
              ros::spinOnce();
              rate.sleep(); //this to ensure the time is as we expect
                              //sleep untill next iteration if u finished ur job
            }
    }

    void rotate (ros::Publisher pubMove, int num_seconds)
    {
        geometry_msgs::Twist msg; 
        ros::Rate rate(30);
        //get the pose of the robot again
        msg.linear.y =0.0; msg.linear.z =0.0;
        msg.angular.x = 0.0; msg.angular.y = 0.0; 
        double desired = yaw + 1.5708;
        if (desired > 3.14)
        {
            desired= -1.5708;
        }
        std::cout<<"Current yaw "<< yaw<<std::endl;
        std::cout<<"Desired is "<<desired<<std::endl;
        ros::Time start_turn = ros::Time::now();
        while(abs(desired-yaw)> 0.02)
    {
        //velocity controls
        msg.angular.z = 0.2*(desired-yaw);
        //std::cout<<"yaw is " <<yaw<<std::endl;
        msg.linear.x = 0; //speed value m/s
        pubMove.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }
    }

    void stop_robot(ros::Publisher pubMove)
    {
        geometry_msgs::Twist msg; 
        ros::Rate rate(5);
        ros::Time start2 = ros::Time::now();
        msg.linear.x =0.0; msg.linear.y =0.0; msg.linear.z =0.0;
        msg.angular.x = 0.0; msg.angular.y = 0.0; msg.angular.z = 0.0;
        pubMove.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }
    //////////////////////////////////////////////////////////
    /////////Server Function ////////////
    //////////////////////////////////////////////////////////
    bool MoveSquare (betabot_msgs::MoveSquare::Request &request,
               betabot_msgs::MoveSquare::Response &response)
        {
            ROS_INFO("MoveSquare Service called");
            //Rate = 5 HZ   
            ros::Rate rate(5);
            int side = request.side;
            int repeat = request.repetitions;
            int num_seconds = ceil(side/0.5); 
            geometry_msgs::Twist msg;
            for (int i =0; i<repeat; i++)
            { 
            for (int i =0; i<4; i++)
            {
                forward(pubMove,num_seconds);
                stop_robot(pubMove);
                rotate(pubMove,num_seconds);
                stop_robot(pubMove);
                ros::spinOnce();
                rate.sleep();
            }
            stop_robot(pubMove); //Reset
            }
            response.success = true;
            return true;
        }

    void OdomCallback(const nav_msgs::OdometryConstPtr &msg)
    {
        x_ = msg->pose.pose.position.x;  // get the robot x pose from the odom topic
        y_ = msg->pose.pose.position.y;  // get the robot y pose from the odom topic
        z_ = msg->pose.pose.position.z;
        ori_x = msg->pose.pose.orientation.x;
        ori_y = msg->pose.pose.orientation.y;
        ori_z = msg->pose.pose.orientation.z;
        ori_w = msg->pose.pose.orientation.w;
        double x = 2 * (ori_w * ori_z + ori_x * ori_y);
        double y = 1 - 2 * (ori_y * ori_y + ori_z * ori_z);
        yaw = std::atan2(x, y);

        //tf::Quaternion ori_(ori_x,ori_y,ori_z,ori_w);
        //tf::Matrix3x3 m(ori_);
        //m.getRPY(roll, pitch, yaw);
        //Pose of the robot is now identified :)
        //pose.x = x_; 
        //pose.y = y_;
        //pose.theta = yaw_ini;
        //pubPose2D.publish(pose);
    }

    
    private:
    double x_,y_,z_;
    double ori_x,ori_y,ori_z,ori_w;
    double roll, pitch, yaw;
    //geometry_msgs::Pose2D pose;
    ros::NodeHandle n;
    ros::Publisher pubMove = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
    //ros::Publisher pubPose2D = n.advertise<geometry_msgs::Pose2D>("pose",100);
};
int main(int argc, char **argv)
{
    ros::init(argc, argv, "MoveSquare_Server");
    ROS_INFO("Service is running");
    //Topic cmd_vel for the robot movement
    MoveSquareServer move_square;
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/odom",1,&MoveSquareServer::OdomCallback,&move_square);
    ros::ServiceServer square = nh.advertiseService("square",&MoveSquareServer::MoveSquare,&move_square);
    ros::spin();                                 // Wait for ever for the service request
    return 0;
}
