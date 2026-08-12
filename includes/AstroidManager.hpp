//
// Created by HardcoreAxolotl on 10/08/2026.
//

#ifndef ASTROIDS_ASTROIDMANAGER_HPP
#define ASTROIDS_ASTROIDMANAGER_HPP

#include <array>

class Sprite;

class Player;

class Astroid;

class AstroidManager {
    friend class BigAstroid;
    friend class SmallAstroid;

    static Sprite big_astroid;
    static Sprite small_astroid;
public:
    inline static std::array<Astroid*, 100> astroids{nullptr};
    inline static unsigned short astroid_count = 0;
    static void clean_up(size_t index);
    AstroidManager() = default;
    AstroidManager(Sprite *big_astroid, Sprite *small_astroid);

    void SpawnBigAstroid(Player *player);
    void SpawnSmallAstroid(Player *player);
    void UpdateAstroids(float delta_time);
    void RenderAstroids(SDL_Renderer *renderer, bool debug);
};


#endif //ASTROIDS_ASTROIDMANAGER_HPP