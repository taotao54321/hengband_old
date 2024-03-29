#pragma once

#include <array>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#include "main-sdl2/font.hpp"
#include "main-sdl2/prelude.hpp"
#include "main-sdl2/system.hpp"

class GameWindow;

class GameWindowDesc {
private:
    std::string title_;
    int x_;
    int y_;
    int w_;
    int h_;
    std::string font_path_;
    int font_pt_;
    bool visible_;

public:
    GameWindowDesc();

    [[nodiscard]] const std::string &title() const;
    GameWindowDesc &title(std::string title);

    [[nodiscard]] int x() const;
    GameWindowDesc &x(int x);

    [[nodiscard]] int y() const;
    GameWindowDesc &y(int y);

    [[nodiscard]] int w() const;
    GameWindowDesc &w(int w);

    [[nodiscard]] int h() const;
    GameWindowDesc &h(int h);

    [[nodiscard]] const std::string &font_path() const;
    GameWindowDesc &font_path(std::string path);

    [[nodiscard]] int font_pt() const;
    GameWindowDesc &font_pt(int pt);

    [[nodiscard]] bool visible() const;
    GameWindowDesc &visible(bool visible);

    [[nodiscard]] GameWindow build(bool is_main) const;
};

// TODO: UI周り、もうちょいマシな設計がある気はする

struct PresentParam {
    // 各ウィンドウの可視状態
    std::array<bool, 8> visibles;

    bool bgm_enabled;
    bool se_enabled;

    // 対象端末のテキスト選択状態 (c,r,ncol,nrow)
    std::optional<std::tuple<int, int, int, int>> selection;
};

struct TermCell {
    int col;
    int row;
};

struct WindowButton {
    int idx;
};

struct BgmButton {
};

struct SeButton {
};

struct NullElement {
};

using UiElement = std::variant<TermCell, WindowButton, BgmButton, SeButton, NullElement>;

struct ButtonVisual {
    Rect rect;
    Texture tex;

    ButtonVisual(Rect rect, Texture tex);
};

class GameWindow {
private:
    bool is_main_;
    Font font_;
    Window win_;
    Renderer ren_;
    std::pair<int, int> ncnr_; // 端末画面サイズ (ncol,nrow)
    Texture tex_term_; // 端末画面テクスチャ
    Texture tex_ascii_; // ASCII 文字テクスチャキャッシュ (描画高速化用)
    Texture tex_wall_; // 壁画像テクスチャ
    std::vector<ButtonVisual> buttons_window_;
    std::optional<ButtonVisual> button_bgm_;
    std::optional<ButtonVisual> button_se_;

    // サイズ ncnr_ の端末画面テクスチャを作る。
    [[nodiscard]] Texture init_tex_term() const;

    // ASCII 文字テクスチャキャッシュを作る。
    [[nodiscard]] Texture init_tex_ascii() const;

    // 壁画像テクスチャを作る。
    [[nodiscard]] Texture init_tex_wall() const;

    void update_button_rects();

    [[nodiscard]] std::vector<ButtonVisual> init_buttons_window() const;
    [[nodiscard]] std::optional<ButtonVisual> init_button_bgm() const;
    [[nodiscard]] std::optional<ButtonVisual> init_button_se() const;

    GameWindow(bool is_main, Font font, Window win);

    // ウィンドウの4辺の枠幅を得る。top, left, bottom, right の順。
    [[nodiscard]] std::tuple<int, int, int, int> borders_size() const;

    // ウィンドウ位置を得る。
    [[nodiscard]] std::pair<int, int> pos() const;

    // 現在のクライアント領域サイズを得る。
    [[nodiscard]] std::pair<int, int> client_area_size() const;

    // 端末画面サイズ (ncol,nrow) を実現する最低限のクライアント領域サイズを得る。
    [[nodiscard]] std::pair<int, int> client_area_size_for(int ncol, int nrow) const;

    // ウィンドウサイズを (w,h) にしたときの端末画面サイズ (ncol,nrow) を得る。
    [[nodiscard]] std::pair<int, int> term_size_for(int w, int h) const;
    [[nodiscard]] std::pair<int, int> term_size_for(const std::pair<int, int> &wh) const;

    // ウィンドウ上の端末画面領域の矩形を得る。
    [[nodiscard]] Rect term_area_rect() const;

    void draw_button(const ButtonVisual &button, bool enabled) const;

    friend class GameWindowDesc;

public:
    // noncopyable
    GameWindow(const GameWindow &) = delete;
    GameWindow &operator=(const GameWindow &) = delete;

    // movable
    GameWindow(GameWindow &&other) noexcept = default;
    GameWindow &operator=(GameWindow &&rhs) noexcept = default;

    [[nodiscard]] u32 id() const;

    [[nodiscard]] bool is_visible() const;
    void set_visible(bool visible) const;
    void toggle_visible() const;

    void raise() const;

    // 現在の端末画面サイズ (ncol,nrow) を得る。
    [[nodiscard]] std::pair<int, int> term_size() const;

    // 端末画面全体をクリアする。
    void term_clear() const;

    // 端末画面の矩形範囲 (c,r,ncol,nrow) を色 color で塗りつぶす。
    void term_fill_rect(int c, int r, int ncol, int nrow, Color color) const;

    // 端末画面の文字座標 (c,r) に UTF-8 文字列 text を色 (fg,bg) で描画する。
    //
    // XXX:
    //   事前に term_fill_rect() で対象範囲をクリアしておかないと画面にゴミが残
    //   ることがある。等幅フォントであっても文字ごとに高さが異なるのが原因。
    //   文字幅計算の都合上、このクリア処理は呼び出し側に任せている。
    //   (とはいえ EUC-JP でもバイト数と文字幅は厳密には一致しないが)
    void term_draw_text(int c, int r, const std::string &text, Color color) const;

    // 端末画面の文字座標 (c,r) に壁画像を色 color で描画する。
    void term_draw_wall(int c, int r, Color color) const;

    // バッファに描画した内容を画面に反映する。
    void present(const PresentParam &param) const;

    // ピクセル座標 (x,y) 上の UI 要素を得る。
    [[nodiscard]] UiElement ui_element_at(int x, int y) const;

    // ウィンドウリサイズ時に呼ばれる。新たな端末画面サイズ (ncol,nrow) を返す。
    std::pair<int, int> on_size_change(int w, int h);

    [[nodiscard]] GameWindowDesc desc() const;
};
