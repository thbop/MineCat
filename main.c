#include <raylib.h>
#include <rcamera.h>

// -----------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
// -----------------------------------------------------------------------------------
// Window
#define WIDTH      1200
#define HEIGHT     800
#define HALFWIDTH  WIDTH>>1
#define HALFHEIGHT HEIGHT>>1
#define FPS        60

// Camera
#define CAMERA_SENSITIVITY 0.2f
#define CANERA_MOVE_SPEED  0.1f

// Globals
Camera3D camera;

bool cursorFree;



void Init() {
    InitWindow(WIDTH, HEIGHT, "MineCat");
    SetExitKey(KEY_NULL);
    SetTargetFPS(FPS);
    DisableCursor();
    cursorFree = false;

    camera.position   = (Vector3){ 0.0f, 0.0f, 10.0f };
    camera.target     = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up         = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy       = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

}

void Navigate() {
    if ( !cursorFree ) {
        Vector2 md = GetMouseDelta();
        SetMousePosition(HALFWIDTH, HALFHEIGHT);
        UpdateCameraPro(&camera, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ md.x*CAMERA_SENSITIVITY, md.y*CAMERA_SENSITIVITY, 0.0f }, 0.0f);

        if ( IsKeyDown(KEY_W) ) CameraMoveForward(&camera, CANERA_MOVE_SPEED, false);
        if ( IsKeyDown(KEY_S) ) CameraMoveForward(&camera, -CANERA_MOVE_SPEED, false);

        if ( IsKeyDown(KEY_D) ) CameraMoveRight(&camera, CANERA_MOVE_SPEED, false);
        if ( IsKeyDown(KEY_A) ) CameraMoveRight(&camera, -CANERA_MOVE_SPEED, false);

        if ( IsKeyDown(KEY_SPACE) )      CameraMoveUp(&camera, CANERA_MOVE_SPEED);
        if ( IsKeyDown(KEY_LEFT_SHIFT) ) CameraMoveUp(&camera, -CANERA_MOVE_SPEED);
    }
}

void CursorManger() {
    if ( IsKeyPressed(KEY_ESCAPE) )              { cursorFree = true; EnableCursor(); }
    if ( cursorFree && IsMouseButtonPressed(0) ) { cursorFree = false; DisableCursor(); }
}

void Update() {
    CursorManger();
    Navigate();
}

void Draw() {
    DrawCubeV( (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 4.0f, 4.0f, 4.0f }, GREEN );
}

void Unload() {

    CloseWindow();
}

int main() {
    Init();

    while (!WindowShouldClose()) {
        Update();
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                Draw();
            EndMode3D();
        EndDrawing();
    }

    Unload();
    return 0;
}