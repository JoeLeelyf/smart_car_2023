#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; // 定义出 MoveBaseClient 别名

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_base_client"); // 初始化ROS节点

    MoveBaseClient ac("move_base", true); // 创建 MoveBaseClient 对象，指定服务名称和是否等待服务器联接

    ROS_INFO("Waiting for the move_base action server to come up");

    ac.waitForServer(); // 等待ActionServer启动

    ROS_INFO("The move_base action server is up");

    // 创建MoveBaseGoal并设置目标位置
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 4.03685092926;
    goal.target_pose.pose.position.y = -2.98988461494;
    goal.target_pose.pose.position.z = 0.0;
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.0;

    ac.sendGoal(goal); // 发送目标位置

    ROS_INFO("Sent goal");

    ac.waitForResult(); // 等待Action完成

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("Hooray, the base moved to the goal");
    }
    else
    {
        ROS_INFO("The base failed to move to the goal");
    }

    return 0;
}
