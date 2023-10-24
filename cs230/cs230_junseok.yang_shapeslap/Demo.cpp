/*
junseok.yang
shape_lap
cs230
spring 2019
Demo.cpp
*/
#include "Demo.hpp"
#include <CS230/graphics/GL.hpp>
#include <CS230/graphics/Mesh.hpp>
#include <CS230/math/angles.hpp>
#include <fstream>

const std::filesystem::path vertex2_shader_filepath("assets/explore_animal.vert");
const std::filesystem::path fragment2_shader_filepath("assets/explore_animal.frag");
const std::filesystem::path vertex_shader_filepath("assets/updown.vert");
const std::filesystem::path fragment_shader_filepath("assets/updown.frag");

std::string get_file_contents(const std::filesystem::path& textfile_path);

bool Demo::StartUpWasSuccessful()
{
    using namespace CS230;

    GL::set_line_width(3.0f);

    if (const bool loaded = shader_name.LoadFromSource(get_file_contents(vertex_shader_filepath),
                                                  get_file_contents(fragment_shader_filepath));
        !loaded)
    {
        return false;
    }
    if (const bool loaded = shader_animal.LoadFromSource(get_file_contents(vertex2_shader_filepath),
        get_file_contents(fragment2_shader_filepath));
        !loaded)
    {
        return false;
    }

    material_name.shader = &shader_name;
    material_name.matrix3Uniforms["to_ndc"] = MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material_name.floatUniforms["seconds"] = 0.0f;
    material_animal.shader = &shader_animal;
    material_animal.matrix3Uniforms["to_ndc"] = MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material_animal.floatUniforms["seconds"] = 0.0f;
    const auto layout = { 
        VertexLayoutDescription::Position2WithFloats
    };
    const auto layout2 = {
        VertexLayoutDescription::Position2WithFloats,
        VertexLayoutDescription::Color4WithUnsignedBytes
    };
    const auto layout3 = {
        VertexLayoutDescription::Position2WithFloats,
        VertexLayoutDescription::Color4WithUnsignedBytes,
        VertexLayoutDescription::TextureCoordinates2WithFloats
    };

    Mesh backGround_Mesh;
    backGround_Mesh.SetPointListType(PointListPattern::TriangleFan);
    backGround_Mesh.AddPoint({ -2000,1000 });
    backGround_Mesh.AddPoint({ 2000,1000 });
    backGround_Mesh.AddPoint({ 2000,-1000 });
    backGround_Mesh.AddPoint({ -2000,-1000 });
    backGround_Mesh.AddColor(Color4ub{ 200,125,0 });
     backGround.InitializeWithMeshAndLayout(backGround_Mesh, layout2);

    Mesh name_Mesh;
    name_Mesh.SetPointListType(PointListPattern::TriangleFan);
       name_Mesh.AddPoint({ -260,110 });
    name_Mesh.AddPoint({ -150,110 });
    name_Mesh.AddPoint({ -150,100 });
    name_Mesh.AddPoint({ -260,100 });
    name_Mesh.AddColor(Color4ub{ 255,0,0 });
    name.InitializeWithMeshAndLayout(name_Mesh, layout2);

    Mesh name_Mesh2;
    name_Mesh2.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh2.AddPoint({ -205,110 });
    name_Mesh2.AddPoint({ -195,105 });
    name_Mesh2.AddPoint({ -230,30 });
    name_Mesh2.AddPoint({ -240,35 });
    name_Mesh2.AddColor(Color4ub{ 255,0,0 });
    name2.InitializeWithMeshAndLayout(name_Mesh2, layout2);

    Mesh name_Mesh3;
    name_Mesh3.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh3.AddPoint({ -205,110 });
    name_Mesh3.AddPoint({ -215,105 });
    name_Mesh3.AddPoint({ -180,30 });
    name_Mesh3.AddPoint({ -170,35 });
    name_Mesh3.AddColor({ 255,0,0 });
    name3.InitializeWithMeshAndLayout(name_Mesh3, layout2);

    Mesh name_Mesh4;
    name_Mesh4.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh4.AddPoint({ -260,20 });
    name_Mesh4.AddPoint({ -150,20 });
    name_Mesh4.AddPoint({ -150,10 });
    name_Mesh4.AddPoint({ -260,10 });
    name_Mesh4.AddColor({ 0,0,255 });
    name4.InitializeWithMeshAndLayout(name_Mesh4, layout2);

    Mesh name_Mesh5;
    name_Mesh5.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh5.AddPoint({ -215,20 });
    name_Mesh5.AddPoint({ -195,20 });
    name_Mesh5.AddPoint({ -195,-10 });
    name_Mesh5.AddPoint({ -215,-10 });
    name_Mesh5.AddColor({ 0,0,255 });
    name5.InitializeWithMeshAndLayout(name_Mesh5, layout2);

    Mesh name_Mesh6;
    name_Mesh6.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh6.AddPoint({ -260,-20 });
    name_Mesh6.AddPoint({ -150,-20 });
    name_Mesh6.AddPoint({ -150,-30 });
    name_Mesh6.AddPoint({ -260,-30 });
    name_Mesh6.AddColor({ 255,0,255 });
    name6.InitializeWithMeshAndLayout(name_Mesh6, layout2);

    Mesh name_Mesh7;
    name_Mesh7.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh7.AddPoint({ -260,0 });
    name_Mesh7.AddPoint({ -240,0 });
    name_Mesh7.AddPoint({ -240,-30 });
    name_Mesh7.AddPoint({ -260,-30 });
    name_Mesh7.AddColor({ 255,0,255 });
    name7.InitializeWithMeshAndLayout(name_Mesh7, layout2);

    Mesh name_Mesh8;
    name_Mesh8.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh8.AddPoint({ 185,110 });
    name_Mesh8.AddPoint({ 175,105 });
    name_Mesh8.AddPoint({ 210,30 });
    name_Mesh8.AddPoint({ 220,35 });
    name_Mesh8.AddColor({ 0,255,0 });
    name8.InitializeWithMeshAndLayout(name_Mesh8, layout2);

    Mesh name_Mesh9;
    name_Mesh9.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh9.AddPoint({ 175,110 });
    name_Mesh9.AddPoint({ 185,105 });
    name_Mesh9.AddPoint({ 150,30 });
    name_Mesh9.AddPoint({ 140,35 });
    name_Mesh9.AddColor({ 0,255,0 });
    name9.InitializeWithMeshAndLayout(name_Mesh9, layout2);

    Mesh name_Mesh10;
    name_Mesh10.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh10.AddPoint({ 210,70 });
    name_Mesh10.AddPoint({ 240,70 });
    name_Mesh10.AddPoint({ 240,80 });
    name_Mesh10.AddPoint({ 210,80 });
    name_Mesh10.AddColor({ 150,50,100 });
    name10.InitializeWithMeshAndLayout(name_Mesh10, layout2);

    Mesh name_Mesh11;
    name_Mesh11.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh11.AddPoint({ 240,30 });
    name_Mesh11.AddPoint({ 250,30 });
    name_Mesh11.AddPoint({ 250,110 });
    name_Mesh11.AddPoint({ 240,110 });
    name_Mesh11.AddColor({ 150,50,100 });
    name11.InitializeWithMeshAndLayout(name_Mesh11, layout2);

    Mesh name_Mesh12;
    name_Mesh12.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh12.AddPoint({ 140,10 });
    name_Mesh12.AddPoint({ 240,10 });
    name_Mesh12.AddPoint({ 240,0 });
    name_Mesh12.AddPoint({ 140,0 });
    name_Mesh12.AddColor({ 0,255,255 });
    name12.InitializeWithMeshAndLayout(name_Mesh12, layout2);

    Mesh name_Mesh13;
    name_Mesh13.SetPointListType(PointListPattern::TriangleFan);
    name_Mesh13.AddPoint({ 250,10 });
    name_Mesh13.AddPoint({ 240,10 });
    name_Mesh13.AddPoint({ 240,-30 });
    name_Mesh13.AddPoint({ 250,-30 });
    name_Mesh13.AddColor({ 0,255,255 });
    name13.InitializeWithMeshAndLayout(name_Mesh13, layout2);

    Mesh mesh;
    mesh.SetPointListType(PointListPattern::TriangleFan);
    float angle = 0;
    constexpr float circle_length = 100.0f;
    while (angle < TWO_PI)
    {

        float x =  (cos(angle))*circle_length;
        float y =    (sin(angle))*circle_length;

        mesh.AddPoint({ x,y });
        angle += 0.001f;
    }
    mesh.AddColor(Color4ub{ 0,150,150 });
    shape.InitializeWithMeshAndLayout(mesh, layout2);
    
    Mesh mesh2;
    mesh2.SetPointListType(PointListPattern::TriangleFan);
    float angle2 = 0;
    constexpr float circle2_length = 5.0f;
    while (angle2 < TWO_PI)
    {
        
        float x = (cos(angle2))*circle2_length+60;
        float y = (sin(angle2))*circle2_length+30;

        mesh2.AddPoint({ x,y });
        angle2 += 0.001f;
    }
    mesh2.AddColor(Color4ub{ 0 });
    mesh2.AddTextureCoordinate({ -40,20 });
    shape2.InitializeWithMeshAndLayout(mesh2, layout3);
    
    Mesh mesh3;
    mesh3.SetPointListType(PointListPattern::TriangleFan);
    float angle3 = 0;
    constexpr float circle3_length = 5.0f;
    while (angle3 < TWO_PI)
    {

        float x = (cos(angle3))*circle3_length - 60;
        float y = (sin(angle3))*circle3_length + 30;


        mesh3.AddPoint({ x,y });
        angle3 += 0.001f;
    }
    mesh3.AddColor(Color4ub{ 0 });
    mesh3.AddTextureCoordinate({ 40,20 });
    shape3.InitializeWithMeshAndLayout(mesh3, layout3);
    
    Mesh mesh4;
    mesh4.SetPointListType(PointListPattern::TriangleFan);
    mesh4.AddPoint({ 0, -5 });
    float angle4 = 0;
    constexpr float circle4_length = 15.0f;
    while (angle4 < TWO_PI)
    {

        float x = (cos(angle4))*circle4_length;
        float y = (sin(angle4))*circle4_length-5;

        mesh4.AddPoint({ x,y });
        angle4 += 0.001f;
    }
    mesh4.AddColor(Color4ub{ 0});
     shape4.InitializeWithMeshAndLayout(mesh4, layout2);

    Mesh mesh5;
    mesh5.SetPointListType(PointListPattern::TriangleFan);
    mesh5.AddPoint({ 0, -5 });
    float angle5 = 0;
    constexpr float circle5_length = 25.0f;
    while (angle5 < TWO_PI)
    {

        float x = (cos(angle5))*circle5_length - 25;
        float y = (sin(angle5))*circle5_length - 30;

        mesh5.AddPoint({ x,y });
        angle5 += 0.001f;
    }
    mesh5.AddColor(Color4ub{ 255 });
    shape5.InitializeWithMeshAndLayout(mesh5, layout2);

    Mesh mesh6;
    mesh6.SetPointListType(PointListPattern::TriangleFan);
    float angle6 = 0;
    constexpr float circle6_length = 25.0f;
    while (angle6 < TWO_PI)
    {

        float x = (cos(angle6))*circle6_length + 25;
        float y = (sin(angle6))*circle6_length - 30;

        mesh6.AddPoint({ x,y });
        angle6 += 0.001f;
    }
    mesh6.AddColor(Color4ub{ 255 });
    shape6.InitializeWithMeshAndLayout(mesh6, layout2);

    Mesh mesh7;
    mesh7.SetPointListType(PointListPattern::Lines);
    mesh7.AddPoint({ -70,-10 });
    mesh7.AddPoint({ -40,-20 });
    mesh7.AddColor(Color4ub{ 0 });
    shape7.InitializeWithMeshAndLayout(mesh7, layout2);

    Mesh mesh8;
    mesh8.SetPointListType(PointListPattern::Lines);
    mesh8.AddPoint({ -70,-30 });
    mesh8.AddPoint({ -40,-30 });
    mesh8.AddColor(Color4ub{ 0 });
    shape8.InitializeWithMeshAndLayout(mesh8, layout2);
    
    Mesh mesh9;
    mesh9.SetPointListType(PointListPattern::Lines);
    mesh9.AddPoint({ -70,-50 });
    mesh9.AddPoint({ -40,-40 });
    mesh9.AddColor(Color4ub{ 0 });
    shape9.InitializeWithMeshAndLayout(mesh9, layout2);
    
    Mesh mesh10;
    mesh10.SetPointListType(PointListPattern::Lines);
    mesh10.AddPoint({ 70,-10 });
    mesh10.AddPoint({ 40,-20 });
    mesh10.AddColor(Color4ub{ 0 });
    shape10.InitializeWithMeshAndLayout(mesh10, layout2);
    
    Mesh mesh11;
    mesh11.SetPointListType(PointListPattern::Lines);
    mesh11.AddPoint({ 70,-30 });
    mesh11.AddPoint({ 40,-30 });
    mesh11.AddColor(Color4ub{ 0 });
    shape11.InitializeWithMeshAndLayout(mesh11, layout2);
    
    Mesh mesh12;
    mesh12.SetPointListType(PointListPattern::Lines);
    mesh12.AddPoint({ 70,-50 });
    mesh12.AddPoint({ 40,-40 });
    mesh12.AddColor(Color4ub{ 0 });
    shape12.InitializeWithMeshAndLayout(mesh12, layout2);
    
    Mesh mesh13;
    mesh13.SetPointListType(PointListPattern::TriangleFan);
    mesh13.AddPoint({ 0, -5 });
    float angle13 = 0;
    constexpr float circle13_length = 100.0f;
    while (angle13 < TWO_PI)
    {

        float x = (cos(angle13))*circle13_length;
        float y = (sin(angle13))*circle13_length - 175;

        mesh13.AddPoint({ x,y });
        angle13 += 0.001f;
    }
    mesh13.AddColor(Color4ub{ 0,150,150 });
    shape13.InitializeWithMeshAndLayout(mesh13, layout2);

    Mesh mesh14;
    mesh14.SetPointListType(PointListPattern::TriangleFan);
    mesh14.AddPoint({ 0, -170 });
    float angle14 = 0;
    constexpr float circle14_length = 50.0f;
    while (angle14 < TWO_PI)
    {

        float x = (cos(angle14))*circle14_length;
        float y = (sin(angle14))*circle14_length - 170;

        mesh14.AddPoint({ x,y });
        
        angle14 += 0.001f;
    }
    mesh14.AddColor(Color4ub{ 255 });
    shape14.InitializeWithMeshAndLayout(mesh14, layout2);

    return true;
}

bool Demo::ShouldClose() const { return isDone; }

void Demo::Update(float delta_time_seconds)
{
    ++frameCount;
    seconds += delta_time_seconds;
    material_name.floatUniforms["time"] = seconds;
    material_animal.floatUniforms["time"] = seconds;
}

void Demo::Draw()
{
    CS230::GL::begin_drawing();

    CS230::GL::draw(name, material_name);
    CS230::GL::draw(name2, material_name);
    CS230::GL::draw(name3, material_name);
    CS230::GL::draw(name4, material_name);
    CS230::GL::draw(name5, material_name);
    CS230::GL::draw(name6, material_name);
    CS230::GL::draw(name7, material_name);
    CS230::GL::draw(name8, material_name);
    CS230::GL::draw(name9, material_name);
    CS230::GL::draw(name10, material_name);
    CS230::GL::draw(name11, material_name);
    CS230::GL::draw(name12, material_name);
    CS230::GL::draw(name13, material_name);
    
    CS230::GL::draw(shape12, material_animal);
    CS230::GL::draw(shape11, material_animal);
    CS230::GL::draw(shape10, material_animal);
    CS230::GL::draw(shape9, material_animal);
    CS230::GL::draw(shape8, material_animal);
    CS230::GL::draw(shape7, material_animal);
    CS230::GL::draw(shape4, material_animal);
    CS230::GL::draw(shape5, material_animal);
    CS230::GL::draw(shape6, material_animal);
    CS230::GL::draw(shape2, material_animal);
    CS230::GL::draw(shape3, material_animal);
    CS230::GL::draw(shape, material_animal);
    CS230::GL::draw(shape14, material_animal);
    CS230::GL::draw(shape13, material_animal);

    CS230::GL::draw(backGround, material_name);
    
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
    width  = size.width;
    height = size.height;
    CS230::GL::set_display_area(width, height);
    material_name.matrix3Uniforms["to_ndc"] = CS230::MATRIX3::build_scale(2.0f / width, 2.0f / height);
    material_animal.matrix3Uniforms["to_ndc"] = CS230::MATRIX3::build_scale(2.0f / width, 2.0f / height);
}

void Demo::HandleKeyReleased(CS230::KeyboardButton keyboard_button)
{
    if (keyboard_button == CS230::KeyboardButton::R)
    {
        shader_name.LoadFromSource(get_file_contents(vertex_shader_filepath), get_file_contents(fragment_shader_filepath));
        shader_animal.LoadFromSource(get_file_contents(vertex2_shader_filepath), get_file_contents(fragment2_shader_filepath));
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
