

class charge : public SyncActionNode{
    public:
     charge(const std::string& name, const NodeConfig& config)
    : SyncActionNode(name, config)
     { }
    NodeStatus tick() override{

    }

};
class get_blood : public SyncActionNode{
    public:
     get_blood(const std::string& name, const NodeConfig& config)
    : SyncActionNode(name, config)
     { }
     static PortsList providedPorts()
     {
    return { OutputPort<int>("blood") };
  }
  void message_callback(const std_msgs::msg::Int32::SharedPtr msg){
        robot_blood = msg->data;
    }
  NodeStatus tick() override
  {
    rclcpp::Node::SharedPtr node;
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr bs;
        bs=node->reate_subscription<std_msgs::msg::Int32>("blood",10
        std::bind(&get_blood::message_callback, this, _1));
    // the output may change at each tick(). Here we keep it simple.
    setOutput("blood",robot_blood);
    return NodeStatus::SUCCESS;
  }
  private: 
   int robot_blood;
};
class check_blood : public SyncActionNode{
    public:
     check_blood(const std::string& name, const NodeConfig& config)
    : SyncActionNode(name, config)
     { }
    static PortsList providedPorts()
     {
    return { InputPort<int>("blood") };
  }
    NodeStatus tick() override{
        Expected<int> msg = getInput<int>("blood");
        robot_blood = msg.value();
        // Check if expected is valid. If not, throw its error
        if (!msg)
        {
        throw BT::RuntimeError("missing required input [message]: ", 
                                msg.error() );
        }
        if(robot_blood>20)  return NodeStatus::SUCCESS;
        else return NodeStatus::FAILURE;
    }
   private: 
   int robot_blood;
};
class patrol : public SyncActionNode{
    public:
     patrol(const std::string& name, const NodeConfig& config)
    : SyncActionNode(name, config)
     { }
    NodeStatus tick() override{

    }

};
