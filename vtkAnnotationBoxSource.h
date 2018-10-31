#ifndef VTKANNOTATIONBOXSOURCE_H
#define VTKANNOTATIONBOXSOURCE_H

#include "vtkFiltersSourcesModule.h"  // For export macro
#include "vtkPolyDataAlgorithm.h"


class vtkAnnotationBoxSource : public vtkPolyDataAlgorithm {
   public:
    static vtkAnnotationBoxSource *New();
    vtkTypeMacro(vtkAnnotationBoxSource, vtkPolyDataAlgorithm);

   protected:
    vtkAnnotationBoxSource();
    ~vtkAnnotationBoxSource();
    int RequestData(vtkInformation *, vtkInformationVector **,
                    vtkInformationVector *);

   private:
    vtkAnnotationBoxSource(const vtkAnnotationBoxSource &);
    void operator=(const vtkAnnotationBoxSource &);
};

#endif
