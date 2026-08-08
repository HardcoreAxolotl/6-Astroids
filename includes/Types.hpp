#pragma once

namespace types {
    struct vec2 {
        float x;
        float y;

        void operator=(vec2 *other) {
            this->x = other->x;
            this->y = other->y;
        }
        void operator+(vec2 *other) {
            this->x += other->x;
            this->y += other->y;
        }
        void operator-(vec2 *other) {
            this->x -= other->x;
            this->y -= other->y;
        }
    };
}