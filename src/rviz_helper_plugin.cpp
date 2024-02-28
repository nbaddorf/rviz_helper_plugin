#include <rviz_helper_plugin/rviz_helper_panel.hpp>

namespace rviz_helper_plugin

{
MyRvizPanel::MyRvizPanel(QWidget* parent) :
        rviz::Panel(parent)
{
  /*
  qRegisterMetaType<QMessageBox::Icon>();
  connect(this, &MyRvizPanel::displayMessageBox, this, [=]
    (const QString title,
    const QString text,
    const QString info,
    const QMessageBox::Icon icon)
  {
    const bool old_state(isEnabled());
    setEnabled(true);
    QMessageBox msg_box;
    msg_box.setWindowTitle(title);
    msg_box.setText(text);
    msg_box.setInformativeText(info);
    msg_box.setIcon(icon);
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
    setEnabled(true);
  });
  */
  
  connect(this, &MyRvizPanel::enable, this, &MyRvizPanel::setEnabled);
  Q_EMIT enable(true);

  setObjectName("MyRvizPanel");
  setName(objectName());

  QVBoxLayout* layout = new QVBoxLayout();
  setLayout(layout);

  //value_ = new QSpinBox;
  button_ = new QPushButton("STOP NAV");

  //layout->addWidget(new QLabel("button:"));
  //layout->addWidget(value_);
  //layout->addStretch();
  layout->addWidget(button_);

  stop_nav_pub_ = nh_.advertise<actionlib_msgs::GoalID>( "/move_base/cancel", 1 );
  //layout->addStretch();

  //connect(value_, qOverload<int>(&QSpinBox::valueChanged), this, &MyRvizPanel::configChanged);
  connect(button_, &QPushButton::released, this, [=]
    {
      actionlib_msgs::GoalID goal;
      stop_nav_pub_.publish(goal);
      //srv_.request.value = value_->value();
      //QtConcurrent::run(this, &MyRvizPanel::callService);
    }
  );

  //service_ = nh_.serviceClient<simple_node::GetMessage>("get_message");
  //QtConcurrent::run(this, &MyRvizPanel::connectToServices);
}

MyRvizPanel::~MyRvizPanel()
{
}

void MyRvizPanel::stopNav() {

}

void MyRvizPanel::callService()
{
  //Q_EMIT enable(false);

  //const bool rvalue (service_.call(srv_));
  Q_EMIT enable(true);

  /*
  if (!rvalue)
  {
    Q_EMIT displayMessageBox("Failure",
                             "Call to service failed!",
                             "",
                             QMessageBox::Icon::Critical);
    return;
  }
  else if (!srv_.response.return_status)
  {
    Q_EMIT displayMessageBox("Failure",
                             "Service responded with an error:",
                             QString::fromStdString(srv_.response.return_message),
                             QMessageBox::Icon::Warning);
    return;
  }

  Q_EMIT displayMessageBox("Success",
                           "Service responded:",
                           QString::fromStdString(srv_.response.return_message),
                           QMessageBox::Icon::Information);

*/
}

void MyRvizPanel::load(const rviz::Config& config)
{
  rviz::Panel::load(config);
  int tmp_int;

  //if (config.mapGetInt("value", &tmp_int))
  //  value_->setValue(tmp_int);
}

void MyRvizPanel::save(rviz::Config config) const
                 {
  rviz::Panel::save(config);
  //config.mapSetValue("value", value_->value());
}

void MyRvizPanel::connectToService(ros::ServiceClient &client)
{
  while (nh_.ok())
  {
    if (client.waitForExistence(ros::Duration(5)))
    {
      ROS_INFO_STREAM("RViz panel " << getName().toStdString()
                      << " connected to the service " << client.getService());
      break;
    }
  }
}

void MyRvizPanel::connectToServices()
{
  connectToService(service_);
  ROS_INFO_STREAM("RViz panel \'" << getName().toStdString() << "\' services connections have been made");
  Q_EMIT enable(true);
}

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_helper_plugin::MyRvizPanel, rviz::Panel)

