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
#include <vtkBoxWidget.h>
#include <vtkTransform.h>

#include "vtkBoxWidgetCallback.h"
#include "Annotation.h"

vtkBoxWidgetCallback0 *vtkBoxWidgetCallback0::New() {
    return new vtkBoxWidgetCallback0;
}

void vtkBoxWidgetCallback0::Execute(vtkObject *caller, unsigned long, void *) {
    // Here we use the vtkBoxWidget to transform the underlying coneActor
    // (by manipulating its transformation matrix).
    vtkSmartPointer<vtkTransform> t = vtkSmartPointer<vtkTransform>::New();
    vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget *>(caller);

    widget->GetTransform(t);
    if (anno) {
        // widget->GetProp3D()->SetUserTransform(t);
        anno->applyTransform(t);
    }
}

void vtkBoxWidgetCallback0::setAnno(Annotation *value) { anno = value; }

vtkBoxWidgetCallback1 *vtkBoxWidgetCallback1::New() {
    return new vtkBoxWidgetCallback1;
}

void vtkBoxWidgetCallback1::Execute(vtkObject *caller, unsigned long, void *) {
    if (anno) {
        anno->adjustToAnchor();
    }
}

void vtkBoxWidgetCallback1::setAnno(Annotation *value) { anno = value; }
