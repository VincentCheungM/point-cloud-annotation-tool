/*
* MIT License
* 
* Copyright (c) 2018 Vincent Cheung
* Copyright (c) 2018 Fancy Zhang
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include <vtkPoints.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "vtkBoxWidgetRestricted.h"

// vtkStandardNewMacro (vtkBoxWidgetRestricted){}

vtkBoxWidgetRestricted *vtkBoxWidgetRestricted::New() {
    return new vtkBoxWidgetRestricted;
}

void vtkBoxWidgetRestricted::Rotate(int X, int Y, double *p1, double *p2,
                                    double *vpn) {
    double *pts =
        static_cast<vtkDoubleArray *>(this->Points->GetData())->GetPointer(0);
    double *center = static_cast<vtkDoubleArray *>(this->Points->GetData())
                         ->GetPointer(3 * 14);
    double v[3];  // vector of motion
    //        double axis[3]; //axis of rotation
    double theta;  // rotation angle
    int i;

    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    v[2] = p2[2] - p1[2];

    // Create axis of rotation and angle of rotation
    // compute the vector which perpendicular to Z axis in current view
    double z[3] = {0, 0, 1};  // restrict to Z rotation
    double m[3];
    vtkMath::Cross(z, vpn, m);
    if (vtkMath::Normalize(m) == 0.0 || vtkMath::Normalize(v) == 0.0) {
        return;
    }
    // alpha is the angle between the motion vector and vector m
    double cos_alpha = vtkMath::Dot(m, v);
    //    std::cout<<cos_alpha<<endl;
    int *size = this->CurrentRenderer->GetSize();
    double l2 = (X - this->Interactor->GetLastEventPosition()[0]) *
                    (X - this->Interactor->GetLastEventPosition()[0]) +
                (Y - this->Interactor->GetLastEventPosition()[1]) *
                    (Y - this->Interactor->GetLastEventPosition()[1]);
    theta =
        360.0 * cos_alpha * sqrt(l2 / (size[0] * size[0] + size[1] * size[1]));

    // Manipulate the transform to reflect the rotation
    this->Transform->Identity();
    this->Transform->Translate(center[0], center[1], center[2]);
    this->Transform->RotateZ(theta);
    this->Transform->Translate(-center[0], -center[1], -center[2]);

    // Set the corners
    vtkPoints *newPts = vtkPoints::New(VTK_DOUBLE);
    this->Transform->TransformPoints(this->Points, newPts);

    for (i = 0; i < 8; i++, pts += 3) {
        this->Points->SetPoint(i, newPts->GetPoint(i));
    }

    newPts->Delete();
    this->PositionHandles();
}
