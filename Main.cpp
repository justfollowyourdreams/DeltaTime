#include <raylib.h>
#include <string>
#include <cmath>

// Easing function for smooth animation.
float EaseOutCubic(float x) 
{ return 1.f - std::pow(1.f - x, 3); }

int main()
{
    // Init and shit
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Delta Time Example");
    unsigned short FPS = 60;
    SetTargetFPS(FPS);
    // ------------------------------

    // Variables for animation
    float   FrameTime = 0.0f, // Frame time is an counter animation time.
            EndTime = .8f;   // End time is the time when the animation should end (animation duration).
    bool Reached = false;   // Flag to know if the animation reached the end.
    // ------------------------------
    bool UseEasing = false; // Flag to use easing function.

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Check if the animation reached the end time. If not, adding delta time to FrameTime.
        if (!Reached)
            FrameTime += GetFrameTime();
            
        // If FrameTime reaches EndTime, set Reached flag to true and FrameTime to EndTime (in case it exceeds to not overflow the ratio).
        if(FrameTime >= EndTime)
        {
            Reached = true;
            FrameTime = EndTime;
        }

        float AnimRatio = FrameTime / EndTime; // Calculate animation ratio (0.0 to 1.0).
        float EasedRatio = EaseOutCubic(AnimRatio); // Calculate eased ratio using easing function.

        // Draw a rectangle moving from position 10 to 510 in EndTime seconds.
        DrawRectangle(10 + (500 * (UseEasing ? EasedRatio : AnimRatio)), 100, 100, 100, LIGHTGRAY);
        // Draw an indicator circle showing the end position of the rectangle.
        DrawCircle(560, 150, 10, {255, 0, 0, 100});
        
        // Draw FPS and FrameTime/EndTime ratio.
        DrawFPS(10, 10); 
        DrawText(("Anim. ratio: " + std::to_string(AnimRatio)).c_str(), 10, 30, 20, Reached ? GREEN : RED);
        DrawText(UseEasing ? ("Easing: ON, Eased Ratio: " + std::to_string(EasedRatio)).c_str() : "Easing: OFF", 10, 50, 20, UseEasing ? GREEN : RED);

        EndDrawing();

        if(IsKeyPressed(KEY_DOWN)) // Decrease target FPS.
        {
            FPS = std::max(10, FPS - 10);
            SetTargetFPS(FPS);
        } 
        else if (IsKeyPressed(KEY_UP)) // Increase target FPS.
        {
            FPS += 10;
            SetTargetFPS(FPS);
        } 
        else if(IsKeyPressed(KEY_SPACE)) // Restart the animation.
        {
            FrameTime = 0.0f;
            Reached = false;
        } 
        else if (IsKeyPressed(KEY_ENTER)) // Toggle easing function.
            UseEasing = !UseEasing;
    }

    CloseWindow();
    return 0;
}