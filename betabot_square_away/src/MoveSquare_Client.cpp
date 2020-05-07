#include "ros/ros.h"
#include "betabot_msgs/MoveSquare.h"
#include "betabot_msgs/MoveSquareRequest.h"
#include "betabot_msgs/MoveSquareResponse.h"
#include "iostream"


int main(int argc, char **argv)                // Node Main Function
{
  ros::init(argc, argv, "MoveSquare_Client");   // Initializes Node Name
  ROS_INFO("Client Started");
  ros::NodeHandle nh;                          // Node handle declaration

  // Hook our service clients to the master
  ros::ServiceClient client_small = nh.serviceClient<betabot_msgs::MoveSquare>("square");
  ros::ServiceClient client_large = nh.serviceClient<betabot_msgs::MoveSquare>("square");

  std:: cout <<"okay, service is running :""D" << std::endl;
  // create request and response from GetClosest.srv
  betabot_msgs::MoveSquare::Request cs_ms_req;
  betabot_msgs::MoveSquare::Response cs_ms_res;

  betabot_msgs::MoveSquare::Request cl_ms_req;
  betabot_msgs::MoveSquare::Response cl_ms_res;


  //Read the square side and the number of repetetions
  cs_ms_req.side = atoll(argv[1]);
  cs_ms_req.repetitions = atoll(argv[2]);

  cl_ms_req.side = atoll(argv[3]);
  cl_ms_req.repetitions = atoll(argv[4]);
  
  // Call the service aliased by this handle (nh) with the specified request/response messages
  //move_square.call(ms_req,ms_res);
  client_small.call(cs_ms_req,cs_ms_res);
  client_large.call(cl_ms_req,cl_ms_res);
  
 std::cout <<" The small square robot movement: " << cs_ms_res << std::endl;  
 std::cout <<" The large square robot movement: " << cl_ms_res << std::endl;  


  return 0;
}