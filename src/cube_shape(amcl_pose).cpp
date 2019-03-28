#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void Callback(const geometry_msgs::PoseWithCovarianceStampedConstPtr& msg)
{
  ROS_INFO("I heard new position");
  marker.header.frame_id = msg->header.frame_id;
  marker.header.stamp = msg->header.stamp;
  marker.pose.position.x = msg->pose.pose.position.x;
  marker.pose.position.y = msg->pose.pose.position.y;
  marker.pose.position.z = msg->pose.pose.position.z;
  marker.pose.orientation.x = msg->pose.pose.orientation.x;
  marker.pose.orientation.y = msg->pose.pose.orientation.y;
  marker.pose.orientation.z = msg->pose.pose.orientation.z;
  marker.pose.orientation.w = msg->pose.pose.orientation.w;
  marker.lifetime = ros::Duration();
  marker_pub.publish(marker);
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "cube_shape");
  ros::NodeHandle n;
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber pose_sub = n.subscribe("/robot_0/amcl_pose", 1, Callback);
  
    uint32_t shape = visualization_msgs::Marker::CUBE;
    marker.ns = "cube_shape";
    marker.id = 32;
    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.636;
    marker.scale.y = 0.554;
    marker.scale.z = 0.1;
    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    ros::spin();

}
