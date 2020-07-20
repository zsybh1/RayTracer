#include <cfloat>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

#include <camera.h>
#include <hitable.h>
#include <hitable/hitlist.h>
#include <hitable/sphere.h>
#include <material.h>
#include <material/lambertian.h>
#include <material/metal.h>
#include <material/transparency.h>
#include <random.h>

vec3 get_color(const ray &r, const HitableList &world, int depth) {
    HitResult res;
    if (world.hit(r, 0.001f, 10000.0f, res)) {
        ray next;
        vec3 attenuation;
        res.mateial->scatter(r, res, attenuation, next);
        if (depth > 0) {
            return attenuation * get_color(next, world, depth - 1);
        } else {
            return vec3(0.0f);
        }
    }
    float t = 0.5f * unit(r.direction()).y() + 0.5f;
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    clock_t starttime = clock();

    char str[50];
    time_t now = time(NULL);
    strftime(str, 50, "%y%m%d%H%M%S", localtime(&now));
    std::string path(str);
    path = "image/raytracing-" + path + ".ppm";
    std::ofstream out(path);
    if (!out) {
        system("md image");
        std::ofstream out(path);
    }

    constexpr int random_count = 100;

    constexpr int scale = 2;
    constexpr int width = 192 * scale;
    constexpr int height = 108 * scale;
    out << "P3\n" << width << " " << height << "\n255\n";

    Camera camera(vec3(0.0f, 1.0f, 5.0f), vec3(0.0f, 1.0f, 0.0f),
                  vec3(0.0f, 1.0f, 0.0f), 45.0f, (float)width / height, 0.0f);

    HitableList world;
    // for (int i = -11; i <= 11; ++i) {
    //     for (int j = -11; j <= 11; ++j) {
    //         vec3 pos =
    //             vec3(i + 0.8 * getrand(seed), 0.2, j + 0.8 * getrand(seed));
    //         float p = getrand(seed);
    //         if (p < 0.8f) {
    //             world.add(
    //                 new Sphere(pos, 0.2f,
    //                            new Lambertian(vec3(getrand(seed), getrand(seed),
    //                                                getrand(seed)))));
    //         } else if (p < 0.95f) {
    //             world.add(new Sphere(
    //                 pos, 0.2f,
    //                 new Metal(vec3(getrand(seed), getrand(seed), getrand(seed)),
    //                           getrand(seed) * getrand(seed))));
    //         } else {
    //             world.add(new Sphere(
    //                 pos, 0.2f,
    //                 new Transparency(getrand(seed),
    //                                  vec3(0.8f + 0.2f * getrand(seed),
    //                                       0.8f + 0.2f * getrand(seed),
    //                                       0.8f + 0.2f * getrand(seed)))));
    //         }
    //     }
    // }
    world.add(new Sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
                         new Lambertian(vec3(0.4f, 0.4f, 0.4f))));
    world.add(new Sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f,
                         new Lambertian(vec3(1.0f, 0.5f, 0.3f))));
    world.add(new Sphere(vec3(2.0f, 1.0f, 0.0f), 1.0f,
                         new Metal(vec3(0.8f, 0.9f, 1.0f), 0.5f)));
    world.add(
         new Sphere(vec3(-2.0f, 1.0f, 0.0f), 1.0f, new Transparency(1.5f)));

    clock_t lasttime = clock();
    int lastProgress = 0;
    std::cout << "0.0%..";
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(1);
    for (int j = height - 1; j >= 0; --j) {
        clock_t nowtime = clock();
        if (((nowtime - lasttime) / CLOCKS_PER_SEC) >= 1) {
            int nowProgress = int(float(height - j) / float(height) * 1000.0f);
            if (nowProgress > lastProgress) {
                if (nowProgress < 1000)
                    std::cout << nowProgress / 10.0f << "%..";
                lastProgress = nowProgress;
                lasttime = nowtime;
            }
        }
        for (int i = 0; i < width; ++i) {
            vec3 color(0.0f);
            for (int k = 0; k < random_count; ++k) {
                float u = float(i + getrand(seed)) / width;
                float v = float(j + getrand(seed)) / height;
                ray r = camera.get_ray(u, v);
                color += get_color(r, world, 50);
            }
            color /= random_count;
            color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            int R = int(255.99 * color.r());
            int G = int(255.99 * color.g());
            int B = int(255.99 * color.b());
            out << R << " " << G << " " << B << std::endl;
        }
    }

    clock_t endtime = clock();
    std::cout << "100%\nDone in ";
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(3) << float(endtime - starttime) / CLOCKS_PER_SEC;
    std::cout << "s. Save as " << path << ".\n";
}
