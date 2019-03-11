//
// Created by Lucas Amorim on 3/11/2019.
//

#ifndef INC_3DMODELING_DOOR_HPP
#define INC_3DMODELING_DOOR_HPP



class Doorr {
private:
  int state = 0;
  int angle = 0;
  void* camera;
  bool cameraIsInsideRange();
public:
  explicit Doorr(void* camera);
  void draw();
  void update();
};


#endif //INC_3DMODELING_DOOR_HPP
