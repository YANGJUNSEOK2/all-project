/*
junseok.yang
sketch_lap
cs230
spring 2019
Demo.cpp
*/
#include "Demo.hpp"
#include <CS230/graphics/GL.hpp>
#include <CS230/math/angles.hpp>
#include <CS230/window/WindowEventHandler.hpp>
#include <CS230/util/Random.hpp>
#include "Application.hpp"

bool Demo::StartUpWasSuccessful()
{
    sketch.SetOutlineColor(255);
    sketch.SetupSketch(width, height);
    sketch.SetFrameOfReference(CS230::CameraView::LeftHanded_OriginTopLeft);
    return true;
}

bool Demo::ShouldClose() const { return isDone; }

void Demo::Update(float delta_time_seconds)
{
    delta_time_seconds;

}

void Demo::Draw()
{
    CS230::GL::begin_drawing();
    sketch.ClearScreen();
    sketch.PushMatrix();
    //use draw text() functions so Insert the desired text in the desired position.
    sketch.DrawText("Junseok.Yang", float(width/2), float(height/2));

    CS230::vector2 p0 = { 0,-321 };
    CS230::vector2 p = { 0,200 };
    CS230::vector2 p1 = { 278,160 };
    CS230::vector2 p2 = { -278,160 };

    sketch.ApplyTranslate({ float(width / 2), float(height / 2) });
    sketch.ApplyRotate(CS230::PI);

    koch(p0, p1, 5);
    koch(p1, p2, 5);
    koch(p2, p0, 5);

    tree(p0, p, 5);

    sketch.FinishSketchingFrame();
    sketch.PopMatrix();
    CS230::GL::end_drawing();
}

void Demo::ShutDown() {}

void Demo::HandleMouseMove(int mouse_x, int mouse_y)
{
    mouseX = mouse_x;
    mouseY = mouse_y;
}

void Demo::HandleResizeEvent(CS230::window::size size)
{
    width = size.width;
    height = size.height;
    sketch.SetCameraViewSize(width, height);
}
//use draw shape line functions made the desired shape by putting the desired lines in the desired position.
void Demo::koch(CS230::vector2 p0, CS230::vector2 p1, float limit)
{

    float dx = (p1.x - p0.x);
    float dy = (p1.y - p0.y);
    float dist = sqrt(dx*dx + dy * dy);
    float unit = (dist / 3)* my_random(0, 1.5f);
    float angle = atan2(dy, dx);
    CS230::vector2 pA = { p0.x + dx / 3,p0.y + dy / 3 };
    CS230::vector2 pC = { p1.x - dx / 3,p1.y - dy / 3 };
    CS230::vector2 pB = { pA.x + cos(angle - CS230::PI / 3)*unit,pA.y + sin(angle - CS230::PI / 3)*unit };

    if (limit > 0)
    {
        koch(p0, pA, limit - 1);
        koch(pA, pB, limit - 1);
        koch(pB, pC, limit - 1);
        koch(pC, p1, limit - 1);
    }
    else
    {
        sketch.DrawLine({ p0.x, p0.y }, { pA.x, pA.y });
        sketch.DrawLine({ pA.x, pA.y }, { pB.x, pB.y });
        sketch.DrawLine({ pB.x, pB.y }, { pC.x, pC.y });
        sketch.DrawLine({ pC.x, pC.y }, { p1.x, p1.y });
    }
}
//use draw shape line functions made the desired shape by putting the desired lines in the desired position.
void Demo::tree(CS230::vector2 p0, CS230::vector2 p1, float limit)
{
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;
    float dist = sqrt(dx*dx + dy * dy);
    float angle = atan2(dy, dx);
    float branchAngleA = my_random(-float(CS230::PI / 2), float(CS230::PI/2));
    float branchAngleB = my_random(-float(CS230::PI / 2), float(CS230::PI / 2));
    float trunkRatio = my_random(float(0.25), float(0.75));
    float branchLength = dist * (1 - trunkRatio);
    CS230::vector2 pA = { p0.x + dx * trunkRatio,p0.y + dy * trunkRatio };
    CS230::vector2 pC = { pA.x + cos(angle + branchAngleA)*branchLength,pA.y + sin(angle + branchAngleA)*branchLength };
    CS230::vector2 pB = { pA.x + cos(angle + branchAngleB)*branchLength,pA.y + sin(angle + branchAngleB)*branchLength };

    sketch.DrawLine({ p0.x,p0.y }, { pA.x,pA.y });
    sketch.DrawLine({ pA.x,pA.y }, { p0.x,p0.y });
    
    if(limit>0)
    {
        tree(pA, pC, limit - 1);
        tree(pA, pB, limit - 1);
    }
    else
    {
        sketch.DrawLine({ pB.x,pB.y }, { pA.x,pA.y });
        sketch.DrawLine({ pA.x,pA.y }, { pC.x,pC.y });
        sketch.DrawLine({ pC.x,pC.y }, { pB.x,pB.y });
    }
    branchAngleA += my_random(-0.02f, 0.02f);
    branchAngleB += my_random(-0.02f, 0.02f);
    trunkRatio += my_random(-0.02f, 0.02f);
}

float Demo::my_random(float min, float max)
{
    return min + CS230::random()*(max - min);
}
