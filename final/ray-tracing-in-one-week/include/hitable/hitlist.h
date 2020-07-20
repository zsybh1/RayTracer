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

    void add(Hitable *p) {
        list.push_back(p);
    }
};

bool HitableList::hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
    HitResult rec;
    bool isHitSth = false;
    float tcloset = tmax;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i]->hit(r, tmin, tcloset, rec)) {
            isHitSth = true;
            tcloset = rec.t;
            hitResult = rec;
        }
    }
    return isHitSth;
}

#endif 