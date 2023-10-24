/*
junseok.yang
shaderslab
cs230
spring 2019
Demo.cpp
*/
#include "Demo.hpp"
#include <CS230/graphics/GL.hpp>
#include <CS230/graphics/Mesh.hpp>
#include <CS230/math/angles.hpp>
#include <fstream>

const std::filesystem::path vertex_shader_filepath("assets/explore.vert");
const std::filesystem::path fragment_shader_filepath("assets/explore.frag");

std::string get_file_contents(const std::filesystem::path& textfile_path);

bool Demo::StartUpWasSuccessful()
{
    using namespace CS230;

    GL::set_line_width(3.0f);

    if (const bool loaded = shader.LoadFromSource(get_file_contents(vertex_shader_filepath),
        get_file_contents(fragment_shader_filepath));
        !loaded)
    {
        return false;
    }
    material.shader = &shader;
    material.color4fUniforms["color"] = to_color4f(Color4ub{ 165 });

    material.matrix3Uniforms["to_ndc"] = MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material.floatUniforms["seconds"] = 0.0f;
    const auto layout = { VertexLayoutDescription::Position2WithFloats };
    Mesh mesh;
    mesh.SetPointListType(PointListPattern::LineStrip);
    float angle = 0;
    constexpr float circle_length = 10.0f;
    while (angle < TWO_PI*circle_length)
    {

        float x = angle * (cos(angle));
        float y = angle * (sin(angle));


        mesh.AddPoint({ x,y });
        angle += 0.001f;
    }

    mesh.AddColor({ 0, 0, 255 });

    shape.InitializeWithMeshAndLayout(mesh, layout);

    return true;
}

bool Demo::ShouldClose() const { return isDone; }

void Demo::Update(float delta_time_seconds)
{
    // ++frameCount;
    seconds += delta_time_seconds;
    //material.floatUniforms["time"] = seconds;
    material.floatUniforms["mouse_x"] = float(mouseX);
    material.floatUniforms["mouse_y"] = float(mouseY);
}

void Demo::Draw()
{
    CS230::GL::begin_drawing();

    CS230::GL::draw(shape, material);

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
    CS230::GL::set_display_area(width, height);
    material.matrix3Uniforms["to_ndc"] = CS230::MATRIX3::build_scale(2.0f / width, 2.0f / height);
}

void Demo::HandleKeyReleased(CS230::KeyboardButton keyboard_button)
{
    if (keyboard_button == CS230::KeyboardButton::R)
    {
        shader.LoadFromSource(get_file_contents(vertex_shader_filepath), get_file_contents(fragment_shader_filepath));
    }
}

std::string get_file_contents(const std::filesystem::path& textfile_path)
{
    std::ifstream in(textfile_path, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(unsigned(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    return {};
}
