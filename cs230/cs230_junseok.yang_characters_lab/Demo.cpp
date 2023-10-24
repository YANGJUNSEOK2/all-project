/*
junseok.yang
texture_lap
cs230
spring 2019
Demo.cpp
*/
#include "Demo.hpp"
#include <CS230/graphics/GL.hpp>
#include <CS230/graphics/Mesh.hpp>
#include <CS230/graphics/StockShaders.hpp>


bool Demo::StartUpWasSuccessful()
{

    using namespace CS230;
    sketch.SetupSketch(width, height);
    sketch.SetFrameOfReference(CS230::CameraView::LeftHanded_OriginTopLeft);
    texture.LoadFromPNG("korean_2_0.png");
    textureuniform.texture = &texture;
    material.textureUniforms["texture_to_sample"] = textureuniform;
    material.matrix3Uniforms[SHADER::Uniform_ToNDC] = MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material.shader = &SHADER::textured();
    material.color4fUniforms["color"] = to_color4f(Color4ub{ 255 });
    texture2.LoadFromPNG("English_0.png");
    textureuniform2.texture = &texture2;
    material2.textureUniforms["texture_to_sample"] = textureuniform2;
    material2.matrix3Uniforms[SHADER::Uniform_ToNDC] = MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material2.shader = &SHADER::textured();
    material2.color4fUniforms["color"] = to_color4f(Color4ub{ 255 });

    Mesh Kr_name;
    Kr_name.SetPointListType(PointListPattern::Triangles);
    Kr_name.AddPoint({ -350, -100 });
    Kr_name.AddPoint({ -350, 0 });
    Kr_name.AddPoint({ -250, -100 });
    Kr_name.AddPoint({ -250, -100 });
    Kr_name.AddPoint({ -350, 0 });
    Kr_name.AddPoint({ -250, 0 });

    Kr_name.AddTextureCoordinate({ 0.0898f, 0.1054f });
    Kr_name.AddTextureCoordinate({ 0.0898f, 0.0f });
    Kr_name.AddTextureCoordinate({ 0.1953125f, 0.1054f });
    Kr_name.AddTextureCoordinate({ 0.1953125f, 0.1054f });
    Kr_name.AddTextureCoordinate({ 0.0898f, 0.f });
    Kr_name.AddTextureCoordinate({ 0.1953125f, 0.f });

    Kr_name.AddPoint({ -240, -100 });
    Kr_name.AddPoint({ -240, 0 });
    Kr_name.AddPoint({ -140, -100 });
    Kr_name.AddPoint({ -140, -100 });
    Kr_name.AddPoint({ -240, 0 });
    Kr_name.AddPoint({ -140, 0 });

    Kr_name.AddTextureCoordinate({ 0.1953125f, 0.1015f });
    Kr_name.AddTextureCoordinate({ 0.1953125f, 0.f });
    Kr_name.AddTextureCoordinate({ 0.3046875f, 0.1015f });
    Kr_name.AddTextureCoordinate({ 0.3046875f, 0.1015f });
    Kr_name.AddTextureCoordinate({ 0.1953125f, 0 });
    Kr_name.AddTextureCoordinate({ 0.3046875f, 0 });

    Kr_name.AddPoint({ -130, -100 });
    Kr_name.AddPoint({ -130, 0 });
    Kr_name.AddPoint({ -30, -100 });
    Kr_name.AddPoint({ -30, -100 });
    Kr_name.AddPoint({ -130, 0 });
    Kr_name.AddPoint({ -30, 0 });

    Kr_name.AddTextureCoordinate({ 0, 0.109f });
    Kr_name.AddTextureCoordinate({ 0, 0 });
    Kr_name.AddTextureCoordinate({ 0.0898f, 0.109f });
    Kr_name.AddTextureCoordinate({ 0.0898f, 0.109f });
    Kr_name.AddTextureCoordinate({ 0, 0 });
    Kr_name.AddTextureCoordinate({ 0.0898f, 0 });

    Mesh En_name;
    En_name.SetPointListType(PointListPattern::Triangles);
    En_name.AddPoint({ 100, -100 });
    En_name.AddPoint({ 100, -0 });
    En_name.AddPoint({ 150, -100 });
    En_name.AddPoint({ 150, -100 });
    En_name.AddPoint({ 100, 0 });
    En_name.AddPoint({ 150, 0 });

    En_name.AddTextureCoordinate({ 0.0625f, 0.089f });
    En_name.AddTextureCoordinate({ 0.0625f, 0 });
    En_name.AddTextureCoordinate({ 0.125f, 0.089f });
    En_name.AddTextureCoordinate({ 0.125f, 0.089f });
    En_name.AddTextureCoordinate({ 0.0625f, 0 });
    En_name.AddTextureCoordinate({ 0.125f, 0 });

    En_name.AddPoint({ 160, -100 });
    En_name.AddPoint({ 160, -0 });
    En_name.AddPoint({ 210, -100 });
    En_name.AddPoint({ 210, -100 });
    En_name.AddPoint({ 160, 0 });
    En_name.AddPoint({ 210, 0 });

    En_name.AddTextureCoordinate({ 0.135f, 0.089f });
    En_name.AddTextureCoordinate({ 0.135f, 0 });
    En_name.AddTextureCoordinate({ 0.1857f, 0.089f });
    En_name.AddTextureCoordinate({ 0.1857f, 0.089f });
    En_name.AddTextureCoordinate({ 0.135f, 0 });
    En_name.AddTextureCoordinate({ 0.1857f, 0 });

    En_name.AddPoint({ 220, -100 });
    En_name.AddPoint({ 220, -0 });
    En_name.AddPoint({ 270, -100 });
    En_name.AddPoint({ 270, -100 });
    En_name.AddPoint({ 220, 0 });
    En_name.AddPoint({ 270, 0 });

    En_name.AddTextureCoordinate({ 0.f, 0.089f });
    En_name.AddTextureCoordinate({ 0.f, 0.f });
    En_name.AddTextureCoordinate({ 0.0625f, 0.0898f });
    En_name.AddTextureCoordinate({ 0.0625f, 0.0898f });
    En_name.AddTextureCoordinate({ 0, 0 });
    En_name.AddTextureCoordinate({ 0.0625f, 0 });

    shape.InitializeWithMeshAndLayout(
        Kr_name, SHADER::textured_vertex_layout());
    shape2.InitializeWithMeshAndLayout(
        En_name, SHADER::textured_vertex_layout());

    return true;
}

bool Demo::ShouldClose() const { return isDone; }

void Demo::Update(float delta_time_seconds)
{
    seconds += delta_time_seconds;
}

void Demo::Draw()
{
    CS230::GL::begin_drawing();

    CS230::GL::draw(shape, material);
    CS230::GL::draw(shape2, material2);

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
}
