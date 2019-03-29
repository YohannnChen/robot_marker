#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PolygonStamped.h>
#include <math.h>
visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void Callback(const geometry_msgs::PolygonStampedConstPtr& msg)
{
  double x1,x0,y1,y0;
  ROS_INFO("I heard new position");
  marker.header.frame_id = msg->header.frame_id;
  marker.header.stamp = msg->header.stamp;

  marker.pose.position.x=0;
  marker.pose.position.y=0;
  for(int i=0;i<4;i++)
  {
     marker.pose.position.x += msg->polygon.points[i].x;
     marker.pose.position.y += msg->polygon.points[i].y;
  }
  marker.pose.position.x /= 4;
  marker.pose.position.y /= 4;
  marker.pose.position.z = 0;
  
  x0=msg->polygon.points[0].x;
  x1=msg->polygon.points[1].x;
  y0=msg->polygon.points[0].y;
  y1=msg->polygon.points[1].y;

  marker.pose.orientation.x = 0;
  marker.pose.orientation.y = 0;
  marker.pose.orientation.z = cos(atan((x0-x1)/(y0-y1))/2);
  marker.pose.orientation.w = sin(atan((x0-x1)/(y0-y1))/2);
  marker.lifetime = ros::Duration();
  marker_pub.publish(marker);
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "cube_shape");
  ros::NodeHandle n;
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber pose_sub = n.subscribe("/robot_0/move_base_node/local_costmap/footprint", 1, Callback);
  
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
