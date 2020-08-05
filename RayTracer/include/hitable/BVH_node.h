#ifndef BVH_NODE_H_
#define BVH_NODE_H_

#include <hitable.h>
#include <vector>
#include <random.h>
#include <algorithm>

template<int axis>
bool AABB_compare(const Hitable *a, const Hitable *b) {
    AABB box_left, box_right;
    if (!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right)) {
        std::cout << "No bounding_box\n";
    }
    return box_left.min[axis] < box_right.min[axis];
}

class BVH_node : public Hitable {
public:
    Hitable *left;
    Hitable *right;
    AABB box;

    BVH_node() {}
    BVH_node(std::vector<Hitable *> &list, int start, int end, float t0, float t1);
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &b) const {
        b = box;
        return true;
    }
};

bool BVH_node::hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
    if (box.hit(r, tmin, tmax)) {
        HitResult left_res, right_res;
        bool hit_left = left->hit(r, tmin, tmax, left_res);
        bool hit_right = right->hit(r, tmin, tmax, right_res);
        if (hit_right && hit_left) {
            hitResult = left_res.t < right_res.t? left_res: right_res; 
        }
        else if (hit_right) {
            hitResult = right_res;
        }
        else if (hit_left){
            hitResult = left_res;
        }
        else {
            return false;
        }
        return true;
    }
    return false;
}

BVH_node::BVH_node(std::vector<Hitable *> &list, int start, int end, float t0, float t1) {
    int size = end - start;
    if (size == 1) {
        left = right = list[start];
    }
    else if (size == 2) {
        left = list[start];
        right = list[start + 1];
    }
    else {
        int axis = 3 * getrand(seed);
        switch(axis) {
            case 0: std::sort(&list[start], &list[end], AABB_compare<0>); break;
            case 1: std::sort(&list[start], &list[end], AABB_compare<1>); break;
            case 2: std::sort(&list[start], &list[end], AABB_compare<2>); break;
        }
        left = new BVH_node(list, start, start + size / 2, t0, t1);
        right = new BVH_node(list, start + size / 2, end, t0, t1);
    }
    AABB box_left, box_right;
    if (!left->bounding_box(t0, t1, box_left) || !right->bounding_box(t0, t1, box_right)) {
        std::cout << "No bounding_box\n";
    }
    box = surrounding_box(box_left, box_right);
}

#endif