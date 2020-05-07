#include "ros/ros.h"
#include "betabot_msgs/MoveSquare.h"
#include "betabot_msgs/MoveSquareRequest.h"
#include "betabot_msgs/MoveSquareResponse.h"
#include "nav_msgs/Odometry.h"
#include "iostream"
#include "geometry_msgs/Twist.h"
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
        
        for (int i=0;i<num_seconds*5;i++) 
            {
                //publish to cmd_vel topic
              pubMove.publish(msg);
              rate.sleep(); //this to ensure the time is as we expect
                              //sleep untill next iteration if u finished ur job
            }
    }

    void rotate (ros::Publisher pubMove, int num_seconds)
    {
        geometry_msgs::Twist msg; 
        ros::Rate rate(5);
        msg.linear.x =0.0; msg.linear.y =0.0; msg.linear.z =0.0;
        msg.angular.x = 0.0; msg.angular.y = 0.0; msg.angular.z = 1.57/num_seconds;
        for (int i=0;i <num_seconds*5;i++) 
            {
                pubMove.publish(msg);
                rate.sleep();
            }
    }

    void stop_robot(ros::Publisher pubMove)
    {
        geometry_msgs::Twist msg; 
        ros::Rate rate(5);
        msg.linear.x =0.0; msg.linear.y =0.0; msg.linear.z =0.0;
        msg.angular.x = 0.0; msg.angular.y = 0.0; msg.angular.z = 0.0;
        pubMove.publish(msg);
        rate.sleep();
    }
    //////////////////////////////////////////////////////////
    /////////Server Function ////////////
    //////////////////////////////////////////////////////////
    bool MoveSquare (betabot_msgs::MoveSquare::Request &request,
               betabot_msgs::MoveSquare::Response &response)
        {
            ROS_INFO("MoveSquare Service called");
            ros::NodeHandle n;
            ros::Publisher pubMove = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
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
                //stop_robot(pubMove);
                rotate(pubMove,num_seconds);
                //stop_robot(pubMove);
                rate.sleep();
            }
            stop_robot(pubMove); //Reset
            }
            stop_robot(pubMove);
            //rate.sleep();
            response.success = true;
            return true;

        }
    
    private:
    double x_;
    double y_;
};
int main(int argc, char **argv)
{
    ros::init(argc, argv, "MoveSquare_Server");
    ROS_INFO("Service is running");
    //Topic cmd_vel for the robot movement
    MoveSquareServer move_square;
    ros::NodeHandle nh;
    ros::ServiceServer square = nh.advertiseService("square",&MoveSquareServer::MoveSquare,&move_square);
    ros::spin();                                 // Wait for ever for the service request
    return 0;
}