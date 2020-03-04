//
// Created by LEI XU on 3/3/20.
//

#ifndef PATHTRACER_LIGHT_H
#define PATHTRACER_LIGHT_H

#include "Vectors.h"
#include "Intersection.h"
#include "Scene.h"

namespace hikari{
    class Light{
    public:
        virtual ~Light();

        Light(int nSamples = 1);
        virtual Vector3 Sample_Li(const Intersection &ref, const Vector2 &u, Vector3 *wi, float *pdf) const =0;
        virtual Vector3 Power() const = 0;
        virtual double Pdf_Li(const Intersection &ref, const Vector3 &wi) const = 0;
        virtual Vector3 Sample_Le(const Vector2 &u1, const Vector2 &u2, float time,
                                   Ray *ray, Vector3 *nLight, float *pdfPos,
                                  float *pdfDir) const = 0;
        virtual void Pdf_Le(const Ray &ray, const Vector3 &nLight, float *pdfPos,
                            float *pdfDir) const = 0;

        const int nSamples;
    };

    class AreaLight: public Light {
    public:
        AreaLight(int nSamples);
        virtual Vector3 L(const Intersection &intr, const Vector3 &w) const = 0;
    };

    class VisibilityTester{
    public:
        VisibilityTester(){}
        VisibilityTester(const Intersection &p0, const Intersection &p1)
        :p0(p0), p1(p1){}
        const Intersection &P0() const {return p0;}
        const Intersection &P1() const {return p1;}
        bool Unoccluded(const Scene &scene) const ;

    private:
        Intersection p0, p1;
    };

}
#endif //PATHTRACER_LIGHT_H