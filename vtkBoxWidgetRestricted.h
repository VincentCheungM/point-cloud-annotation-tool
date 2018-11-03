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
#ifndef VTKBOXWIDGETRESTRICTED_H
#define VTKBOXWIDGETRESTRICTED_H

#include <vtkBoxWidget.h>
#include <vtkTransform.h>


/**
 * @brief The vtkBoxWidgetRestricted class
 * vtkBoxWidgetRestricted restricts the rotation with Z axis
 *
 *
 */

class vtkBoxWidgetRestricted : public vtkBoxWidget {
   public:
    static vtkBoxWidgetRestricted *New();

    vtkTypeMacro(vtkBoxWidgetRestricted, vtkBoxWidget);

    virtual void Rotate(int X, int Y, double *p1, double *p2, double *vpn);
};
#endif
