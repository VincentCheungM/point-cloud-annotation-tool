#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <vtkSmartPointer.h>

#include "common.h"

class vtkAnnotationBoxSource;
class vtkBoxWidgetRestricted;
class vtkBoxWidgetCallback0;
class vtkBoxWidgetCallback1;

struct BoxLabel {
    BoxLabel() {
        type = "unknown";
        this->detail.center_x = this->detail.center_y = this->detail.center_z =
            0;
        this->detail.yaw = 2;
        this->detail.length = this->detail.width = this->detail.height = 1;
    }
    BoxLabel(const double p1[3], const double p2[3],
             std::string type_ = "unknown") {
        type = type_;
        this->detail.center_x = (p1[0] + p2[0]) / 2;
        this->detail.center_y = (p1[1] + p2[1]) / 2;
        this->detail.center_z = (p1[2] + p2[2]) / 2;
        this->detail.yaw = 0;
        this->detail.length = p2[0] - p1[0];
        this->detail.width = p2[1] - p1[1];
        this->detail.height = p2[2] - p1[2];
    }
    std::string type;
    union {
        double data[7];
        struct {
            double center_x;
            double center_y;
            double center_z;
            double length;
            double width;
            double height;
            double yaw;
        } detail;
    };

    std::string toString() {
        char buffer[200];
        sprintf(buffer, "%s %.3lf %.3lf %.3lf %.3lf %.3f %.3lf %.3lf",
                type.c_str(), data[0], data[1], data[2], data[3], data[4],
                data[5], data[6]);
        return std::string(buffer);
        ;
    }
};

class Annotation {
   public:
    /**
     * @brief Annotation  construct from boxlabel which load from label file
     * @param label
     * @param visible_
     * @param lock_
     */
    Annotation(const BoxLabel &label, bool visible_ = true, bool lock_ = false);

    /**
     * @brief Annotation construct from part of cloud points
     * @param cloud
     * @param slice
     * @param type_
     * @param ground_z The ground plane `Z` value.
     */
    Annotation(const PointCloudTPtr cloud, std::vector<int> &slice,
               std::string type_, double ground_z);

    ~Annotation();

    /**
     * @brief getBoxLabel get boxLabel from annotaion tranformation
     * @return
     */
    BoxLabel getBoxLabel();

    /**
     * @brief apply transform to annotation
     * @param t
     */
    void applyTransform(vtkSmartPointer<vtkTransform> t);

    /**
     * @brief enter picked state, show boxwidget which allow to adjust
     * annotation
     * @param interactor
     */
    void picked(vtkRenderWindowInteractor *interactor);

    /**
     * @brief disable boxWidget
     */
    void unpicked();

    /**
     * @brief keep current orientation, re-compute the center and scale
     * to make annotation fit to selected point well enough
     */
    void adjustToAnchor();

    /**
     * @brief change the type of annotation, and color too
     * @param value
     */
    void setType(const std::string value);
    vtkSmartPointer<vtkActor> getActor() const;
    std::string getType() const;

   protected:
    void initial();

    /**
     * @brief color the annotation with given color
     * @param color_index
     * if color_index>=0,refer to @ref pcl::GlasbeyLUT
     * otherwise use color already mapped by type
     */
    void colorAnnotation(int color_index = -1);

    /**
     * @brief copy selected points as anchor to current annotation
     * @param cloud
     * @param slice
     */
    void setAnchorPoint(const PointCloudTPtr cloud,
                        const std::vector<int> &slice);

    /**
     * @brief computeScaleAndCenterShift
     * @param o direction
     * @param scs ["scale", "center shift"]
     * @return scale
     */
    double computeScaleAndCenterShift(double o[3], double scs[2]);

   private:
    std::string type;
    vtkSmartPointer<vtkAnnotationBoxSource> source;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkTransform> transform;

    vtkSmartPointer<vtkBoxWidgetRestricted> boxWidget;
    vtkSmartPointer<vtkBoxWidgetCallback0> boxWidgetCallback0;
    vtkSmartPointer<vtkBoxWidgetCallback1> boxWidgetCallback1;

    std::vector<double *> anchorPoints;
    double center[3];

    // NOTE not used
    bool visible;
    bool lock;

   public:
    /**
     * @brief get types vector pointer
     * @return
     */
    static std::vector<std::string> *getTypes();

    /**
     * @brief getTypeIndex  auto add to vector map if has not
     * @param type_
     * @return
     */
    static int getTypeIndex(std::string type_);

    /**
     * @brief getColor map type to color in pcl::GlasbeyLUT
     * @param type_
     * @return
     */
    static pcl::RGB getColor(std::string type_);

    /**
     * @brief computeOBB compute max,min [x,y,z] aligned to xyz axis
     * @param cloud
     * @param slice
     * @param p1 min [x,y,z]
     * @param p2 max [x,y,z]
     * @param ground_z The ground plane `Z` value
     */
    static void computeOBB(const PointCloudTPtr cloud, std::vector<int> &slice,
                           double p1[3], double p2[3], double ground_z);

   private:
    /**
     * @brief types all annotation type here
     */
    static std::vector<std::string> *types;
};

class Annotaions {
   public:
    /**
     * @brief from annotatin box actor to find annotation itself
     * @param actor
     * @return
     */
    Annotation *getAnnotation(vtkActor *actor);

    void push_back(Annotation *anno);
    void remove(Annotation *anno);
    void clear();
    int getSize();

    /**
     * @brief load annotations from file
     * @param filename
     */
    void loadAnnotations(std::string filename);

    /**
     * @brief save annotations to file
     * @param filename
     */
    void saveAnnotations(std::string filename);

    std::vector<Annotation *> &getAnnotations();

   protected:
    /**
     * @brief keep all annotation from current cloud
     */
    std::vector<Annotation *> annotations;
};

#endif  // Annotaions_H
