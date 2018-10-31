#ifndef VTKBOXWIDGETCALLBACK_H
#define VTKBOXWIDGETCALLBACK_H

#include <vtkCommand.h>
#include "common.h"

class Annotation;

class vtkBoxWidgetCallback0 : public vtkCommand {
   public:
    static vtkBoxWidgetCallback0 *New();
    virtual void Execute(vtkObject *caller, unsigned long, void *);

    /**
     * @brief setAnno set the current annotation in which theb actor is picked
     * @param value
     */
    void setAnno(Annotation *value);

   private:
    Annotation *anno;
};

class vtkBoxWidgetCallback1 : public vtkCommand {
   public:
    static vtkBoxWidgetCallback1 *New();
    virtual void Execute(vtkObject *caller, unsigned long, void *);

    /**
     * @brief setAnno set the current annotation in which the actor is picked
     * @param value
     */
    void setAnno(Annotation *value);

   private:
    Annotation *anno;
};

#endif
