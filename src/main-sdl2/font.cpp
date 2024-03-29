#include "autoconf.h"
#ifdef USE_SDL2

#include <optional>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <fontconfig/fontconfig.h>

#include <SDL_ttf.h>

#include "main-sdl2/font.hpp"
#include "main-sdl2/prelude.hpp"
#include "main-sdl2/system.hpp"

namespace {

class FontConfigPattern : private boost::noncopyable {
private:
    FcPattern *pat_;

public:
    explicit FontConfigPattern(FcPattern *const pat)
        : pat_(pat)
    {
    }

    ~FontConfigPattern() { FcPatternDestroy(pat_); }

    [[nodiscard]] FcPattern *get() const { return pat_; }
};

class FontConfig : private boost::noncopyable {
public:
    FontConfig()
    {
        if (FcInit() != FcTrue)
            PANIC("FcInit() failed");
    }

    ~FontConfig() { FcFini(); }

    [[nodiscard]] std::optional<std::string> query_path(const std::string &name) const
    {
        (void)this;

        auto *const pat_raw = FcNameParse(reinterpret_cast<const FcChar8 *>(name.data()));
        if (!pat_raw)
            return std::nullopt;
        FontConfigPattern pat(pat_raw);

        if (FcConfigSubstitute(nullptr, pat.get(), FcMatchPattern) != FcTrue)
            return std::nullopt;
        FcDefaultSubstitute(pat.get());

        FcResult result;
        auto *const match_raw = FcFontMatch(nullptr, pat.get(), &result);
        if (!match_raw)
            return std::nullopt;
        FontConfigPattern match(match_raw);

        auto *const s = FcPatternFormat(match.get(), reinterpret_cast<const FcChar8 *>("%{file}"));
        if (!s)
            return std::nullopt;
        std::string path(reinterpret_cast<char *>(s));
        FcStrFree(s);

        return path;
    }
};

} // anonymous namespace

void Font::drop()
{
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

Font::Font(const std::string &path, const int pt)
    : path_(path)
    , pt_(pt)
    , font_(TTF_OpenFont(path.c_str(), pt))
{
    constexpr char CHARS_ASCII[] = R"( !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~)";

    if (!font_)
        PANIC("TTF_OpenFont() failed");

    // 半角文字の幅を得る (等幅フォントを仮定)
    if (TTF_SizeUTF8(font_, "X", &w_, nullptr) != 0)
        PANIC("TTF_SizeUTF8() failed");

    // 文字の高さの最大値を得る。
    // TTF_FontHeight() は最大値より小さい値を返すことがあるため、
    // TTF_SizeUTF8() に全ての ASCII 文字からなる文字列を渡す方法をとる。
    // 非 ASCII 文字については全て調べるのが非現実的なので妥協する。
    if (TTF_SizeUTF8(font_, CHARS_ASCII, nullptr, &h_) != 0)
        PANIC("TTF_SizeUTF8() failed");
}

Font::Font(Font &&other) noexcept
    : path_(std::move(other.path_))
    , pt_(other.pt_)
    , font_(std::exchange(other.font_, nullptr))
    , w_(other.w_)
    , h_(other.h_)
{
}

Font &Font::operator=(Font &&rhs) noexcept
{
    drop();
    path_ = std::move(rhs.path_);
    pt_ = rhs.pt_;
    font_ = std::exchange(rhs.font_, nullptr);
    w_ = rhs.w_;
    h_ = rhs.h_;
    return *this;
}

Font::~Font() { drop(); }

const std::string &Font::path() const { return path_; }
int Font::pt() const { return pt_; }

int Font::w() const { return w_; }
int Font::h() const { return h_; }

int Font::x2c(const int x) const { return x / w_; }
int Font::y2r(const int y) const { return y / h_; }

int Font::c2x(const int c) const { return w_ * c; }
int Font::r2y(const int r) const { return h_ * r; }

std::pair<int, int> Font::xy2cr(const int x, const int y) const { return { x2c(x), y2r(y) }; }

std::pair<int, int> Font::xy2cr(const std::pair<int, int> &xy) const { return xy2cr(xy.first, xy.second); }

std::pair<int, int> Font::cr2xy(const int c, const int r) const { return { c2x(c), r2y(r) }; }

std::pair<int, int> Font::cr2xy(const std::pair<int, int> &cr) const { return cr2xy(cr.first, cr.second); }

Rect Font::calc_rect(const int c, const int r, const int ncol, const int nrow) const
{
    const auto [x, y] = cr2xy(c, r);
    const auto [w, h] = cr2xy(ncol, nrow);
    return Rect(x, y, w, h);
}

Surface Font::render(const std::string &text, Color fg, Color bg) const
{
    auto *const surf = TTF_RenderUTF8_Shaded(font_, text.c_str(), fg.to_sdl_color(), bg.to_sdl_color());
    if (!surf)
        PANIC("TTF_RenderUTF8_Shaded() failed");
    return Surface(surf);
}

std::optional<std::string> get_font_path(const std::string &name)
{
    static const FontConfig fontconfig;
    return fontconfig.query_path(name);
}

#endif // USE_SDL2
