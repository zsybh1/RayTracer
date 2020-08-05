#ifndef HITLIST_H_
#define HITLIST_H_

#include <hitable.h>
#include <vector>

class HitableList : public Hitable{
public:
    std::vector<Hitable *> list;

    HitableList() {}
    HitableList(std::vector<Hitable *> l) : list(l) {}
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const;

    void add(Hitable *p) {
        list.push_back(p);
    }
};

bool HitableList::hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
    HitResult rec;
    bool isHitSth = false;
    float tcloset = tmax;
    for (auto i: list) {
        if (i->hit(r, tmin, tcloset, rec)) {
            isHitSth = true;
            tcloset = rec.t;
            hitResult = rec;
        }
    }
    return isHitSth;
}

bool HitableList::bounding_box(float t0, float t1, AABB &box) const {
    if(list.size() == 0) return false;
    AABB tmp;
    bool first = list[0]->bounding_box(t0, t1, tmp);
    if (!first) {
        return false;
    }
    else {
        box = tmp;
    }
    for (int i = 1; i < list.size(); ++i) {
        if (list[i]->bounding_box(t0, t1, tmp)) {
            box = surrounding_box(box, tmp);
        }
        else {
            return false;
        }
    }
    return true;
}

#endif 