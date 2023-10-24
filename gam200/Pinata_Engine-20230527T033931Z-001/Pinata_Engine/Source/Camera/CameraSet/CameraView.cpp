/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include "CameraView.hpp"

// For RightHanded_OriginCenter
// You want to map (-w/2, w/2) to (-1,1) and (-h/2,h/2) to (-1,1)
//           (w/2,h/2)                (1,1)
//      +--------+             +--------+
//      |        |             |        |
//      | cam    |     --->    | ndc    |
//      +--------+             +--------+
// (-w/2,-h/2)              (-1,-1)
//

// For RightHanded_OriginBottomLeft
// You want to map (0, w) to (-1,1) and (0,h) to (-1,1)
//             (w,h)                  (1,1)
//      +--------+             +--------+
//      |        |             |        |
//      | cam    |     --->    | ndc    |
//      +--------+             +--------+
//    (0,0)                 (-1,-1)
//

// For LeftHanded_OriginTopLeft
// You want to map (0, w) to (-1,1) and (0,h) to (1,-1)
//    (0,0)                 (-1,1)
//      +--------+             +--------+
//      |        |             |        |
//      | cam    |     --->    | ndc    |
//      +--------+             +--------+
//             (w,h)                  (1,-1)
//



Matrix3<float> MatrixBuild(CameraView *view, Vector2<float> pixel_size)
{
    switch (view->GetFrameOfReference())
    {
    case(CameraView::FrameOfReference::RightHanded_OriginCenter):
        return Matrix3<float>{
            2 / pixel_size.x*view->GetZoom(), 0, 0,
                0, 2 / pixel_size.y*view->GetZoom(), 0,
                0, 0, 1

        };
    case(CameraView::FrameOfReference::RightHanded_OriginBottomLeft):
        return Matrix3<float>{
            2 / pixel_size.x*view->GetZoom(), 0, 0,
                0, 2 / pixel_size.y*view->GetZoom(), 0,
                -1, -1, 1
        };
    case(CameraView::FrameOfReference::LeftHanded_OriginTopLeft):
        return Matrix3<float>(
            2 / pixel_size.x*view->GetZoom(), 0, 0,
            0, -2 / pixel_size.y*view->GetZoom(), 0,
            -1, 1, 1
            );
    default:
        return Matrix3<float>{
            1, 0, 0,
                0, 1, 0,
                0, 0, 1
        };
    }
}

void CameraView::SetViewSize(Vector2<float> pixel_size) noexcept
{
    displaySize.x = pixel_size.x;
    displaySize.y = pixel_size.y;
    cameraToNDC = MatrixBuild(this, displaySize);
}

void CameraView::SetViewSize(int new_pixel_width, int new_pixel_height) noexcept
{
    displaySize.x = static_cast<float>(new_pixel_width);
    displaySize.y = static_cast<float>(new_pixel_height);
    cameraToNDC = MatrixBuild(this, displaySize);
}

void CameraView::SetZoom(float new_zoom) noexcept
{
    zoom = new_zoom;
    cameraToNDC = MatrixBuild(this, displaySize);
}

void CameraView::SetFrameOfReference(FrameOfReference frame_of_reference) noexcept
{
    frameOfReference = frame_of_reference;
    cameraToNDC = MatrixBuild(this, displaySize);
}

