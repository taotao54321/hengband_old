#pragma once

#include <cstddef>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <SDL.h>

#include "main-sdl2/prelude.hpp"

class Color {
private:
    SDL_Color color_;

public:
    Color(u8 r, u8 g, u8 b, u8 a);

    static Color from_sdl_color(SDL_Color color);

    [[nodiscard]] u8 r() const;
    [[nodiscard]] u8 g() const;
    [[nodiscard]] u8 b() const;
    [[nodiscard]] u8 a() const;

    [[nodiscard]] SDL_Color to_sdl_color() const;
};

class Rect {
private:
    int x_;
    int y_;
    int w_;
    int h_;

public:
    Rect(int x, int y, int w, int h);

    static Rect from_sdl_rect(const SDL_Rect &rect);

    [[nodiscard]] int x() const;
    [[nodiscard]] int y() const;
    [[nodiscard]] int w() const;
    [[nodiscard]] int h() const;

    [[nodiscard]] int right() const;
    [[nodiscard]] int bottom() const;

    [[nodiscard]] std::pair<int, int> pos() const;
    [[nodiscard]] std::pair<int, int> size() const;

    [[nodiscard]] bool contains(int x, int y) const;

    [[nodiscard]] SDL_Rect to_sdl_rect() const;
};

class System : private boost::noncopyable {
public:
    System();

    ~System();
};

class Window : private boost::noncopyable {
private:
    SDL_Window *win_;

    void drop();

public:
    explicit Window(SDL_Window *win);

    static Window create(const std::string &title, int x, int y, int w, int h, u32 flags);

    // movable
    Window(Window &&other) noexcept;
    Window &operator=(Window &&rhs) noexcept;

    ~Window();

    [[nodiscard]] SDL_Window *get() const;
};

class Renderer : private boost::noncopyable {
private:
    SDL_Renderer *ren_;

    void drop();

public:
    explicit Renderer(SDL_Renderer *ren);

    static Renderer with_window(SDL_Window *win);

    // movable
    Renderer(Renderer &&other) noexcept;
    Renderer &operator=(Renderer &&rhs) noexcept;

    ~Renderer();

    [[nodiscard]] SDL_Renderer *get() const;
};

class Surface;

class Texture : private boost::noncopyable {
private:
    SDL_Texture *tex_;

    void drop();

public:
    explicit Texture(SDL_Texture *tex);

    // ターゲットテクスチャを作る。
    static Texture create_target(SDL_Renderer *ren, int w, int h);

    static Texture from_surface(SDL_Renderer *ren, SDL_Surface *surf);

    // movable
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&rhs) noexcept;

    ~Texture();

    [[nodiscard]] SDL_Texture *get() const;
};

class Surface : private boost::noncopyable {
private:
    SDL_Surface *surf_;

    void drop();

public:
    explicit Surface(SDL_Surface *surf);

    // サイズ (w,h) の RGBA サーフェスを作る。
    static Surface create(int w, int h);

    // サイズ (w,h) かつ color で塗りつぶされた RGBA サーフェスを作る。
    static Surface create(int w, int h, Color color);

    // サイズ (w,h) に tile を敷き詰めた RGBA サーフェスを作る。
    static Surface create_tiled(SDL_Surface *tile, int w, int h);

    // メモリ上の画像ファイルからサーフェスを作る。
    static Surface from_bytes(const u8 *buf, std::size_t len);

    // movable
    Surface(Surface &&other) noexcept;
    Surface &operator=(Surface &&rhs) noexcept;

    ~Surface();

    [[nodiscard]] SDL_Surface *get() const;

    [[nodiscard]] u32 map_color(Color color) const;

    [[nodiscard]] Texture to_texture(SDL_Renderer *ren) const;
};
