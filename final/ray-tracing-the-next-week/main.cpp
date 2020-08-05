#include <header.h>

constexpr int thnum = 4;
constexpr int ray_per_pixel = 10000;
constexpr int random_count = ray_per_pixel / thnum;

constexpr int scale = 3;
constexpr int width = 108 * scale;
constexpr int height = 108 * scale;

float time0 = 0.0f;
float time1 = 0.1f;

Camera camera(vec3(256, 256, 1130), vec3(256),
                vec3(0.0f, 1.0f, 0.0f), 45.0f, (float)width / height, 0.0f, time0, time1);

vec3 get_color(const ray &r, const HitableList &world, int depth) {
    HitResult res;
    if (world.hit(r, 0.001f, 10000.0f, res)) {
        ray next;
        vec3 attenuation;
        vec3 light = res.mateial->emit(res.u, res.v);
        if (depth > 0 && res.mateial->scatter(r, res, attenuation, next)) {
            return light + attenuation * get_color(next, world, depth - 1);
        } else {
            return light;
        }
    }
    return vec3(0.0f);
}

void calculate(HitableList &list, Image &image) {
    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            vec3 color(0.0f);
            for (int k = 0; k < random_count; ++k) {
                float u = float(i + getrand(seed)) / width;
                float v = float(j + getrand(seed)) / height;
                ray r = camera.get_ray(u, v);
                color += get_color(r, list, 50);
            }
            color /= random_count;
            color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            image.putRGB(i, height - 1 - j, color);
        }
    }
}


int main() {
    clock_t starttime = clock();

    char str[50];
    time_t now = time(NULL);
    strftime(str, 50, "%y%m%d%H%M%S", localtime(&now));
    std::string path(str);
    path = "image/raytracing-" + path + ".bmp";
    system("if not exist image md image");

    Material *white = new Lambertian(new Pure_color(vec3(0.75f)));
    Material *red = new Lambertian(new Pure_color(vec3(0.6f, 0.05f, 0.05f)));
    Material *green = new Lambertian(new Pure_color(vec3(0.05f, 0.6f, 0.05f)));
    Material *light = new Diffuse_light(new Pure_color(vec3(5.0f)));
    HitableList section;
    //section.add(new xz_rect(0, 0, 512, 512, 0, white));
    // section.add(new xy_rect(0, 0, 512, 512, 0, white));
    // section.add(new Filp_normal(new xz_rect(0, 0, 512, 512, 512, white)));
    // section.add(new yz_rect(0, 0, 512, 512, 0, green));
    // section.add(new Filp_normal(new yz_rect(0, 0, 512, 512, 512, red)));

    section.add(new Filp_normal(new xz_rect(128, 128, 384, 384, 511, light)));
    section.add(new xz_rect(-2048, -2048, 2560, 2560, 128, white));
    
    Hitable *boundary = new Sphere(vec3(256), 128, new Transparency(1.5));
    section.add(boundary);
    section.add(new constant_medium(boundary, 0.2, new Pure_color(vec3(0.2f, 0.4f, 0.9f))));
    // section.add(new Translate(new Rotate_y(new Cube(vec3(0), vec3(128, 192, 256), white), -30.0f), vec3(132, 0, 128)));

    BVH_node *Tree = new BVH_node(section.list, 0, section.list.size(), time0, time1);
    HitableList list;
    list.add(Tree);

    Image image[thnum];
    std::vector<std::thread> threads;
    for (int i = 1; i < thnum; ++i) {
        image[i] = Image(width, height, 3);
        threads.emplace_back(calculate, std::ref(list), std::ref(image[i]));
    }
    image[0] = Image(width, height, 3);
    
    clock_t lasttime = clock();
    int lastProgress = 0;
    std::cout << "0.0%..";
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(1);
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
                color += get_color(r, list, 50);
            }
            color /= random_count;
            color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            image[0].putRGB(i, height - 1 - j, color);
        }
    }

    for (auto i = threads.begin(); i != threads.end(); ++i) {
        i->join();
    }

    Image result(width, height, 3);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            vec3 color = vec3(0);
            for (int k = 0; k < thnum; ++k) {
                color += image[k].getRGB(i, j);
            }
            color /= thnum;
            result.putRGB(i, j, color);
        }
    }

    result.save(path.c_str());

    clock_t endtime = clock();
    std::cout << "100%\nDone in ";
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3)
              << float(endtime - starttime) / CLOCKS_PER_SEC;
    std::cout << "s. Save as " << path << ".\n";
}
