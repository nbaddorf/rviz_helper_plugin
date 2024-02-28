#ifndef RVIZ_HELPER_PLUGIN_RVIZ_HELPER_PANEL_HPP
#define RVIZ_HELPER_PLUGIN_RVIZ_HELPER_PANEL_HPP

#include <QFuture>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QtConcurrent/QtConcurrentRun>
#include <QVBoxLayout>
#include <ros/ros.h>
#include <ros/service.h>
#include <rviz/panel.h>

namespace rviz_helper_panel
{

class MyRvizPanel : public rviz::Panel
{
Q_OBJECT

public:
  MyRvizPanel(QWidget* parent = 0);
  virtual ~MyRvizPanel();

Q_SIGNALS:
  void enable(const bool);
  void displayMessageBox(const QString,
                         const QString,
                         const QString,
                         const QMessageBox::Icon);

protected Q_SLOTS:
  virtual void load(const rviz::Config &config);
  virtual void save(rviz::Config config) const;

private:
  void connectToService(ros::ServiceClient &client);
  void connectToServices();
  virtual void callService();

  //QSpinBox *value_;
  QPushButton* button_;

  ros::NodeHandle nh_;
  ros::ServiceClient service_;
  simple_node::GetMessage srv_;
};

}

#endif
