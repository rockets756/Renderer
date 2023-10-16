#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H
void update_camera(unsigned int shaderProgram, float deltaTime);

void move_forward();
void move_left();
void move_backwards();
void move_right();
void move_up();
void move_down();
void stop_move_forwards();
void stop_move_left();
void stop_move_backwards();
void stop_move_right();
void stop_move_up();
void stop_move_down();

#endif //RENDERER_CAMERA_H
