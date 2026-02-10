#ifndef ORTHO_VIEW_CONTROLLER_ORTHO_VIEW_CONTROLLER_H
#define ORTHO_VIEW_CONTROLLER_ORTHO_VIEW_CONTROLLER_H

#include <rviz_common/frame_position_tracking_view_controller.hpp>
#include <rviz_common/properties/enum_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/quaternion_property.hpp>
#include <rviz_common/properties/vector_property.hpp>
#include <rviz_rendering/objects/shape.hpp>

#include <memory>

namespace ortho_view_controller {
/// An orthographic view controller which can be optionally locked to a plane.
class OrthoViewController
    : public rviz_common::FramePositionTrackingViewController {
  Q_OBJECT

public:
  OrthoViewController();
  ~OrthoViewController();

  void onInitialize() override;

  void handleMouseEvent(rviz_common::ViewportMouseEvent &e) override;

  void lookAt(const Ogre::Vector3 &p) override;

  void reset() override;

  void mimic(rviz_common::ViewController *source) override;

  void update(float dt, float ros_dt) override;

private slots:
  void onPlaneChanged();

private:
  enum Plane { PLANE_NONE = 0, PLANE_XY, PLANE_XZ, PLANE_YZ };

  static Ogre::Vector3 planeNormal(Plane plane);

  /// Gets the plane this view controller is currently locked to.
  Plane getPlane() const;

  Ogre::SceneNode *getCameraParent(Ogre::Camera *camera);

  std::unique_ptr<rviz_common::properties::EnumProperty> plane_property_;
  std::unique_ptr<rviz_common::properties::VectorProperty> centre_property_;
  std::unique_ptr<rviz_common::properties::QuaternionProperty>
      orientation_property_;
  std::unique_ptr<rviz_common::properties::FloatProperty> scale_property_;

  bool dragging_ = false;

  std::unique_ptr<rviz_rendering::Shape> centre_shape_;
};
} // namespace ortho_view_controller

#endif // ORTHO_VIEW_CONTROLLER_ORTHO_VIEW_CONTROLLER_H
