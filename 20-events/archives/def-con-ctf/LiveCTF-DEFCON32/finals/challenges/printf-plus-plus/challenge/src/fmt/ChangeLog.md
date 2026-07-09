# 10.2.1 - 2024-01-03

-   Fixed ABI compatibility with earlier 10.x versions
    (https://github.com/fmtlib/fmt/pull/3786). Thanks @saraedum.

# 10.2.0 - 2024-01-01

-   Added support for the `%j` specifier (the number of days) for
    `std::chrono::duration` (https://github.com/fmtlib/fmt/issues/3643,
    mt/pull/3732). Thanks @intelfx.

-   Added support for the chrono suffix for days and changed
    the suffix for minutes from "m" to the correct "min"
    (https://github.com/fmtlib/fmt/issues/3662,
    mt/pull/3664).
    For example ([godbolt](https://godbolt.org/z/9KhMnq9ba)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      fmt::print("{}\n", std::chrono::days(42)); // prints "42d"
    }
    ```

    Thanks @Richardk2n.

-   Fixed an overflow in `std::chrono::time_point` formatting with large dates
    (https://github.com/fmtlib/fmt/issues/3725,
    mt/pull/3727). Thanks @cschreib.

-   Added a formatter for `std::source_location`
    (https://github.com/fmtlib/fmt/pull/3730).
    For example ([godbolt](https://godbolt.org/z/YajfKjhhr)):

    ```c++
    #include <source_location>
    #include <fmt/std.h>

    int main() {
      fmt::print("{}\n", std::source_location::current());
    }
    ```

    prints

    ```
    /app/example.cpp:5:51: int main()
    ```

    Thanks @felix642.

-   Added a formatter for `std::bitset`
    (https://github.com/fmtlib/fmt/pull/3660).
    For example ([godbolt](https://godbolt.org/z/bdEaGeYxe)):

    ```c++
    #include <bitset>
    #include <fmt/std.h>

    int main() {
      fmt::print("{}\n", std::bitset<6>(42)); // prints "101010"
    }
    ```

    Thanks @muggenhor.

-   Added an experimental `nested_formatter` that provides an easy way of
    applying a formatter to one or more subobjects while automatically handling
    width, fill and alignment. For example:

    ```c++
    #include <fmt/format.h>

    struct point {
      double x, y;
    };

    template <>
    struct fmt::formatter<point> : nested_formatter<double> {
      auto format(point p, format_context& ctx) const {
        return write_padded(ctx, [=](auto out) {
          return format_to(out, "({}, {})", nested(p.x), nested(p.y));
        });
      }
    };

    int main() {
      fmt::print("[{:>20.2f}]", point{1, 2});
    }
    ```

    prints

    ```
    [          (1.00, 2.00)]
    ```

-   Added the generic representation (`g`) to `std::filesystem::path`
    (https://github.com/fmtlib/fmt/issues/3715,
    mt/pull/3729). For example:

    ```c++
    #include <filesystem>
    #include <fmt/std.h>

    int main() {
      fmt::print("{:g}\n", std::filesystem::path("C:\\foo"));
    }
    ```

    prints `"C:/foo"` on Windows.

    Thanks @js324.

-   Made `format_as` work with references
    (https://github.com/fmtlib/fmt/pull/3739). Thanks @tchaikov.

-   Fixed formatting of invalid UTF-8 with precision
    (https://github.com/fmtlib/fmt/issues/3284).

-   Fixed an inconsistency between `fmt::to_string` and `fmt::format`
    (https://github.com/fmtlib/fmt/issues/3684).

-   Disallowed unsafe uses of `fmt::styled`
    (https://github.com/fmtlib/fmt/issues/3625):

    ```c++
    auto s = fmt::styled(std::string("dangle"), fmt::emphasis::bold);
    fmt::print("{}\n", s); // compile error
    ```

    Pass `fmt::styled(...)` as a parameter instead.

-   Added a null check when formatting a C string with the `s` specifier
    (https://github.com/fmtlib/fmt/issues/3706).

-   Disallowed the `c` specifier for `bool`
    (https://github.com/fmtlib/fmt/issues/3726,
    mt/pull/3734). Thanks @js324.

-   Made the default formatting unlocalized in `fmt::ostream_formatter` for
    consistency with the rest of the library
    (https://github.com/fmtlib/fmt/issues/3460).

-   Fixed localized formatting in bases other than decimal
    (https://github.com/fmtlib/fmt/issues/3693,
    mt/pull/3750). Thanks @js324.

-   Fixed a performance regression in experimental `fmt::ostream::print`
    (https://github.com/fmtlib/fmt/issues/3674).

-   Added synchronization with the underlying output stream when writing to
    the Windows console
    (https://github.com/fmtlib/fmt/pull/3668,
    mt/issues/3688,
    mt/pull/3689).
    Thanks @Roman-Koshelev and @dimztimz.

-   Changed to only export `format_error` when {fmt} is built as a shared
    library (https://github.com/fmtlib/fmt/issues/3626,
    mt/pull/3627). Thanks @phprus.

-   Made `fmt::streamed` `constexpr`.
    (https://github.com/fmtlib/fmt/pull/3650). Thanks @muggenhor.

-   Enabled `consteval` on older versions of MSVC
    (https://github.com/fmtlib/fmt/pull/3757). Thanks @phprus.

-   Added an option to build without `wchar_t` support on Windows
    (https://github.com/fmtlib/fmt/issues/3631,
    mt/pull/3636). Thanks @glebm.

-   Improved build and CI configuration
    (https://github.com/fmtlib/fmt/pull/3679,
    mt/issues/3701,
    mt/pull/3702,
    mt/pull/3749).
    Thanks @jcar87, @pklima and @tchaikov.

-   Fixed various warnings, compilation and test issues
    (https://github.com/fmtlib/fmt/issues/3607,
    mt/pull/3610,
    mt/pull/3624,
    mt/pull/3630,
    mt/pull/3634,
    mt/pull/3638,
    mt/issues/3645,
    mt/issues/3646,
    mt/pull/3647,
    mt/pull/3652,
    mt/issues/3654,
    mt/pull/3663,
    mt/issues/3670,
    mt/pull/3680,
    mt/issues/3694,
    mt/pull/3695,
    mt/pull/3699,
    mt/issues/3705,
    mt/issues/3710,
    mt/issues/3712,
    mt/pull/3713,
    mt/issues/3714,
    mt/pull/3716,
    mt/pull/3723,
    mt/issues/3738,
    mt/issues/3740,
    mt/pull/3741,
    mt/pull/3743,
    mt/issues/3745,
    mt/pull/3747,
    mt/pull/3748,
    mt/pull/3751,
    mt/pull/3754,
    mt/pull/3755,
    mt/issues/3760,
    mt/pull/3762,
    mt/issues/3763,
    mt/pull/3764,
    mt/issues/3774,
    mt/pull/3779).
    Thanks @danakj, @vinayyadav3016, @cyyever, @phprus, @qimiko, @saschasc,
    @gsjaardema, @lazka, @Zhaojun-Liu, @carlsmedstad, @hotwatermorning,
    @cptFracassa, @kuguma, @PeterJohnson, @H1X4Dev, @asantoni, @eltociear,
    @msimberg, @tchaikov, @waywardmonkeys.

-   Improved documentation and README
    (https://github.com/fmtlib/fmt/issues/2086,
    mt/issues/3637,
    mt/pull/3642,
    mt/pull/3653,
    mt/pull/3655,
    mt/pull/3661,
    mt/issues/3673,
    mt/pull/3677,
    mt/pull/3737,
    mt/issues/3742,
    mt/pull/3744).
    Thanks @idzm, @perlun, @joycebrum, @fennewald, @reinhardt1053, @GeorgeLS.

-   Updated CI dependencies
    (https://github.com/fmtlib/fmt/pull/3615,
    mt/pull/3622,
    mt/pull/3623,
    mt/pull/3666,
    mt/pull/3696,
    mt/pull/3697,
    mt/pull/3759,
    mt/pull/3782).

# 10.1.1 - 2023-08-28

-   Added formatters for `std::atomic` and `atomic_flag`
    (https://github.com/fmtlib/fmt/pull/3574,
    mt/pull/3594).
    Thanks @wangzw and @AlexGuteniev.
-   Fixed an error about partial specialization of `formatter<string>`
    after instantiation when compiled with gcc and C++20
    (https://github.com/fmtlib/fmt/issues/3584).
-   Fixed compilation as a C++20 module with gcc and clang
    (https://github.com/fmtlib/fmt/issues/3587,
    mt/pull/3597,
    mt/pull/3605).
    Thanks @MathewBensonCode.
-   Made `fmt::to_string` work with types that have `format_as`
    overloads (https://github.com/fmtlib/fmt/pull/3575). Thanks @phprus.
-   Made `formatted_size` work with integral format specifiers at
    compile time (https://github.com/fmtlib/fmt/pull/3591).
    Thanks @elbeno.
-   Fixed a warning about the `no_unique_address` attribute on clang-cl
    (https://github.com/fmtlib/fmt/pull/3599). Thanks @lukester1975.
-   Improved compatibility with the legacy GBK encoding
    (https://github.com/fmtlib/fmt/issues/3598,
    mt/pull/3599). Thanks @YuHuanTin.
-   Added OpenSSF Scorecard analysis
    (https://github.com/fmtlib/fmt/issues/3530,
    mt/pull/3571). Thanks @joycebrum.
-   Updated CI dependencies
    (https://github.com/fmtlib/fmt/pull/3591,
    mt/pull/3592,
    mt/pull/3593,
    mt/pull/3602).

# 10.1.0 - 2023-08-12

-   Optimized format string compilation resulting in up to 40% speed up
    in compiled `format_to` and \~4x speed up in compiled `format_to_n`
    on a concatenation benchmark
    (https://github.com/fmtlib/fmt/issues/3133,
    mt/issues/3484).

    {fmt} 10.0:

        ---------------------------------------------------------
        Benchmark               Time             CPU   Iterations
        ---------------------------------------------------------
        BM_format_to         78.9 ns         78.9 ns      8881746
        BM_format_to_n        568 ns          568 ns      1232089

    {fmt} 10.1:

        ---------------------------------------------------------
        Benchmark               Time             CPU   Iterations
        ---------------------------------------------------------
        BM_format_to         54.9 ns         54.9 ns     12727944
        BM_format_to_n        133 ns          133 ns      5257795

-   Optimized storage of an empty allocator in `basic_memory_buffer`
    (https://github.com/fmtlib/fmt/pull/3485). Thanks @Minty-Meeo.

-   Added formatters for proxy references to elements of
    `std::vector<bool>` and `std::bitset<N>`
    (https://github.com/fmtlib/fmt/issues/3567,
    mt/pull/3570). For example
    ([godbolt](https://godbolt.org/z/zYb79Pvn8)):

    ```c++
    #include <vector>
    #include <fmt/std.h>

    int main() {
      auto v = std::vector<bool>{true};
      fmt::print("{}", v[0]);
    }
    ```

    Thanks @phprus and @felix642.

-   Fixed an ambiguous formatter specialization for containers that look
    like container adaptors such as `boost::flat_set`
    (https://github.com/fmtlib/fmt/issues/3556,
    mt/pull/3561). Thanks @5chmidti.

-   Fixed compilation when formatting durations not convertible from
    `std::chrono::seconds`
    (https://github.com/fmtlib/fmt/pull/3430). Thanks @patlkli.

-   Made the `formatter` specialization for `char*` const-correct
    (https://github.com/fmtlib/fmt/pull/3432). Thanks @timsong-cpp.

-   Made `{}` and `{:}` handled consistently during compile-time checks
    (https://github.com/fmtlib/fmt/issues/3526).

-   Disallowed passing temporaries to `make_format_args` to improve API
    safety by preventing dangling references.

-   Improved the compile-time error for unformattable types
    (https://github.com/fmtlib/fmt/pull/3478). Thanks @BRevzin.

-   Improved the floating-point formatter
    (https://github.com/fmtlib/fmt/pull/3448,
    mt/pull/3450).
    Thanks @florimond-collette.

-   Fixed handling of precision for `long double` larger than 64 bits.
    (https://github.com/fmtlib/fmt/issues/3539,
    mt/issues/3564).

-   Made floating-point and chrono tests less platform-dependent
    (https://github.com/fmtlib/fmt/issues/3337,
    mt/issues/3433,
    mt/pull/3434). Thanks @phprus.

-   Removed the remnants of the Grisu floating-point formatter that has
    been replaced by Dragonbox in earlier versions.

-   Added `throw_format_error` to the public API
    (https://github.com/fmtlib/fmt/pull/3551). Thanks @mjerabek.

-   Made `FMT_THROW` assert even if assertions are disabled when
    compiling with exceptions disabled
    (https://github.com/fmtlib/fmt/issues/3418,
    mt/pull/3439). Thanks @BRevzin.

-   Made `format_as` and `std::filesystem::path` formatter work with
    exotic code unit types.
    (https://github.com/fmtlib/fmt/pull/3457,
    mt/pull/3476). Thanks @gix and @hmbj.

-   Added support for the `?` format specifier to
    `std::filesystem::path` and made the default unescaped for
    consistency with strings.

-   Deprecated the wide stream overload of `printf`.

-   Removed unused `basic_printf_parse_context`.

-   Improved RTTI detection used when formatting exceptions
    (https://github.com/fmtlib/fmt/pull/3468). Thanks @danakj.

-   Improved compatibility with VxWorks7
    (https://github.com/fmtlib/fmt/pull/3467). Thanks @wenshan1.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/3174,
    mt/issues/3423,
    mt/pull/3454,
    mt/issues/3458,
    mt/pull/3461,
    mt/issues/3487,
    mt/pull/3515).
    Thanks @zencatalyst, @rlalik and @mikecrowe.

-   Improved build and CI configurations
    (https://github.com/fmtlib/fmt/issues/3449,
    mt/pull/3451,
    mt/pull/3452,
    mt/pull/3453,
    mt/pull/3459,
    mt/issues/3481,
    mt/pull/3486,
    mt/issues/3489,
    mt/pull/3496,
    mt/issues/3517,
    mt/pull/3523,
    mt/pull/3563).
    Thanks @joycebrum, @glebm, @phprus, @petrmanek, @setoye and @abouvier.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/3408,
    mt/issues/3424,
    mt/issues/3444,
    mt/pull/3446,
    mt/pull/3475,
    mt/pull/3482,
    mt/issues/3492,
    mt/pull/3493,
    mt/pull/3508,
    mt/issues/3509,
    mt/issues/3533,
    mt/pull/3542,
    mt/issues/3543,
    mt/issues/3540,
    mt/pull/3544,
    mt/issues/3548,
    mt/pull/3549,
    mt/pull/3550,
    mt/pull/3552).
    Thanks @adesitter, @hmbj, @Minty-Meeo, @phprus, @TobiSchluter,
    @kieranclancy, @alexeedm, @jurihock, @Ozomahtli and @razaqq.

# 10.0.0 - 2023-05-09

-   Replaced Grisu with a new floating-point formatting algorithm for
    given precision (https://github.com/fmtlib/fmt/issues/3262,
    mt/issues/2750,
    mt/pull/3269,
    mt/pull/3276). The new algorithm
    is based on Dragonbox already used for the shortest representation
    and gives substantial performance improvement:

    ![](https://user-images.githubusercontent.com/33922675/211956670-84891a09-6867-47d9-82fc-3230da7abe0f.png)

    -   Red: new algorithm
    -   Green: new algorithm with `FMT_USE_FULL_CACHE_DRAGONBOX` defined
        to 1
    -   Blue: old algorithm

    Thanks @jk-jeon.

-   Replaced `snprintf`-based hex float formatter with an internal
    implementation (https://github.com/fmtlib/fmt/pull/3179,
    mt/pull/3203). This removes the
    last usage of `s(n)printf` in {fmt}. Thanks @phprus.

-   Fixed alignment of floating-point numbers with localization
    (https://github.com/fmtlib/fmt/issues/3263,
    mt/pull/3272). Thanks @ShawnZhong.

-   Made handling of `#` consistent with `std::format`.

-   Improved C++20 module support
    (https://github.com/fmtlib/fmt/pull/3134,
    mt/pull/3254,
    mt/pull/3386,
    mt/pull/3387,
    mt/pull/3388,
    mt/pull/3392,
    mt/pull/3397,
    mt/pull/3399,
    mt/pull/3400).
    Thanks @laitingsheng, @Orvid and @DanielaE.
    
-   Switched to the modules CMake library
    which allows building {fmt} as a C++20 module with clang:

        CXX=clang++ cmake -DFMT_MODULE=ON .
        make

-   Made `format_as` work with any user-defined type and not just enums.
    For example ([godbolt](https://godbolt.org/z/b7rqhq5Kh)):

    ```c++
    #include <fmt/format.h>

    struct floaty_mc_floatface {
      double value;
    };

    auto format_as(floaty_mc_floatface f) { return f.value; }

    int main() {
      fmt::print("{:8}\n", floaty_mc_floatface{0.42}); // prints "    0.42"
    }
    ```

-   Removed deprecated implicit conversions for enums and conversions to
    primitive types for compatibility with `std::format` and to prevent
    potential ODR violations. Use `format_as` instead.

-   Added support for fill, align and width to the time point formatter
    (https://github.com/fmtlib/fmt/issues/3237,
    mt/pull/3260,
    mt/pull/3275). For example
    ([godbolt](https://godbolt.org/z/rKP6MGz6c)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      // prints "    2023"
      fmt::print("{:>8%Y}\n", std::chrono::system_clock::now());
    }
    ```

    Thanks @ShawnZhong.

-   Implemented formatting of subseconds
    (https://github.com/fmtlib/fmt/issues/2207,
    mt/issues/3117,
    mt/pull/3115,
    mt/pull/3143,
    mt/pull/3144,
    mt/pull/3349). For example
    ([godbolt](https://godbolt.org/z/45738oGEo)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      // prints 01.234567
      fmt::print("{:%S}\n", std::chrono::microseconds(1234567));
    }
    ```

    Thanks @patrickroocks @phprus and @BRevzin.

-   Added precision support to `%S`
    (https://github.com/fmtlib/fmt/pull/3148). Thanks @SappyJoy

-   Added support for `std::utc_time`
    (https://github.com/fmtlib/fmt/issues/3098,
    mt/pull/3110). Thanks @patrickroocks.

-   Switched formatting of `std::chrono::system_clock` from local time
    to UTC for compatibility with the standard
    (https://github.com/fmtlib/fmt/issues/3199,
    mt/pull/3230). Thanks @ned14.

-   Added support for `%Ez` and `%Oz` to chrono formatters.
    (https://github.com/fmtlib/fmt/issues/3220,
    mt/pull/3222). Thanks @phprus.

-   Improved validation of format specifiers for `std::chrono::duration`
    (https://github.com/fmtlib/fmt/issues/3219,
    mt/pull/3232). Thanks @ShawnZhong.

-   Fixed formatting of time points before the epoch
    (https://github.com/fmtlib/fmt/issues/3117,
    mt/pull/3261). For example
    ([godbolt](https://godbolt.org/z/f7bcznb3W)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      auto t = std::chrono::system_clock::from_time_t(0) -
               std::chrono::milliseconds(250);
      fmt::print("{:%S}\n", t); // prints 59.750000000
    }
    ```

    Thanks @ShawnZhong.

-   Experimental: implemented glibc extension for padding seconds,
    minutes and hours
    (https://github.com/fmtlib/fmt/issues/2959,
    mt/pull/3271). Thanks @ShawnZhong.

-   Added a formatter for `std::exception`
    (https://github.com/fmtlib/fmt/issues/2977,
    mt/issues/3012,
    mt/pull/3062,
    mt/pull/3076,
    mt/pull/3119). For example
    ([godbolt](https://godbolt.org/z/8xoWGs9e4)):

    ```c++
    #include <fmt/std.h>
    #include <vector>

    int main() {
      try {
        std::vector<bool>().at(0);
      } catch(const std::exception& e) {
        fmt::print("{}", e);
      }
    }
    ```

    prints:

        vector<bool>::_M_range_check: __n (which is 0) >= this->size() (which is 0)

    on libstdc++. Thanks @zach2good and @phprus.

-   Moved `std::error_code` formatter from `fmt/os.h` to `fmt/std.h`.
    (https://github.com/fmtlib/fmt/pull/3125). Thanks @phprus.

-   Added formatters for standard container adapters:
    `std::priority_queue`, `std::queue` and `std::stack`
    (https://github.com/fmtlib/fmt/issues/3215,
    mt/pull/3279). For example
    ([godbolt](https://godbolt.org/z/74h1xY9qK)):

    ```c++
    #include <fmt/ranges.h>
    #include <stack>
    #include <vector>

    int main() {
      auto s = std::stack<bool, std::vector<bool>>();
      for (auto b: {true, false, true}) s.push(b);
      fmt::print("{}\n", s); // prints [true, false, true]
    }
    ```

    Thanks @ShawnZhong.

-   Added a formatter for `std::optional` to `fmt/std.h`
    (https://github.com/fmtlib/fmt/issues/1367,
    mt/pull/3303).
    Thanks @tom-huntington.

-   Fixed formatting of valueless by exception variants
    (https://github.com/fmtlib/fmt/pull/3347). Thanks @TheOmegaCarrot.

-   Made `fmt::ptr` accept `unique_ptr` with a custom deleter
    (https://github.com/fmtlib/fmt/pull/3177). Thanks @hmbj.

-   Fixed formatting of noncopyable ranges and nested ranges of chars
    (https://github.com/fmtlib/fmt/pull/3158
    mt/issues/3286,
    mt/pull/3290). Thanks @BRevzin.

-   Fixed issues with formatting of paths and ranges of paths
    (https://github.com/fmtlib/fmt/issues/3319,
    mt/pull/3321
    mt/issues/3322). Thanks @phprus.

-   Improved handling of invalid Unicode in paths.

-   Enabled compile-time checks on Apple clang 14 and later
    (https://github.com/fmtlib/fmt/pull/3331). Thanks @cloyce.

-   Improved compile-time checks of named arguments
    (https://github.com/fmtlib/fmt/issues/3105,
    mt/pull/3214). Thanks @rbrich.

-   Fixed formatting when both alignment and `0` are given
    (https://github.com/fmtlib/fmt/issues/3236,
    mt/pull/3248). Thanks @ShawnZhong.

-   Improved Unicode support in the experimental file API on Windows
    (https://github.com/fmtlib/fmt/issues/3234,
    mt/pull/3293). Thanks @Fros1er.

-   Unified UTF transcoding
    (https://github.com/fmtlib/fmt/pull/3416). Thanks @phprus.

-   Added support for UTF-8 digit separators via an experimental locale
    facet (https://github.com/fmtlib/fmt/issues/1861). For
    example ([godbolt](https://godbolt.org/z/f7bcznb3W)):

    ```c++
    auto loc = std::locale(
      std::locale(), new fmt::format_facet<std::locale>("’"));
    auto s = fmt::format(loc, "{:L}", 1000);
    ```

    where `’` is U+2019 used as a digit separator in the de_CH locale.

-   Added an overload of `formatted_size` that takes a locale
    (https://github.com/fmtlib/fmt/issues/3084,
    mt/pull/3087). Thanks @gerboengels.

-   Removed the deprecated `FMT_DEPRECATED_OSTREAM`.

-   Fixed a UB when using a null `std::string_view` with
    `fmt::to_string` or format string compilation
    (https://github.com/fmtlib/fmt/issues/3241,
    mt/pull/3244). Thanks @phprus.

-   Added `starts_with` to the fallback `string_view` implementation
    (https://github.com/fmtlib/fmt/pull/3080). Thanks @phprus.

-   Added `fmt::basic_format_string::get()` for compatibility with
    `basic_format_string`
    (https://github.com/fmtlib/fmt/pull/3111). Thanks @huangqinjin.

-   Added `println` for compatibility with C++23
    (https://github.com/fmtlib/fmt/pull/3267). Thanks @ShawnZhong.

-   Renamed the `FMT_EXPORT` macro for shared library usage to
    `FMT_LIB_EXPORT`.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/3108,
    mt/issues/3169,
    mt/pull/3243).
    mt/pull/3404).
    Thanks @Cleroth and @Vertexwahn.

-   Improved build configuration and tests
    (https://github.com/fmtlib/fmt/pull/3118,
    mt/pull/3120,
    mt/pull/3188,
    mt/issues/3189,
    mt/pull/3198,
    mt/pull/3205,
    mt/pull/3207,
    mt/pull/3210,
    mt/pull/3240,
    mt/pull/3256,
    mt/pull/3264,
    mt/issues/3299,
    mt/pull/3302,
    mt/pull/3312,
    mt/issues/3317,
    mt/pull/3328,
    mt/pull/3333,
    mt/pull/3369,
    mt/issues/3373,
    mt/pull/3395,
    mt/pull/3406,
    mt/pull/3411).
    Thanks @dimztimz, @phprus, @DavidKorczynski, @ChrisThrasher,
    @FrancoisCarouge, @kennyweiss, @luzpaz, @codeinred, @Mixaill, @joycebrum,
    @kevinhwang and @Vertexwahn.

-   Fixed a regression in handling empty format specifiers after a colon
    (`{:}`) (https://github.com/fmtlib/fmt/pull/3086). Thanks @oxidase.

-   Worked around a broken implementation of
    `std::is_constant_evaluated` in some versions of libstdc++ on clang
    (https://github.com/fmtlib/fmt/issues/3247,
    mt/pull/3281). Thanks @phprus.

-   Fixed formatting of volatile variables
    (https://github.com/fmtlib/fmt/pull/3068).

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/3057,
    mt/pull/3066,
    mt/pull/3072,
    mt/pull/3082,
    mt/pull/3091,
    mt/issues/3092,
    mt/pull/3093,
    mt/pull/3095,
    mt/issues/3096,
    mt/pull/3097,
    mt/issues/3128,
    mt/pull/3129,
    mt/pull/3137,
    mt/pull/3139,
    mt/issues/3140,
    mt/pull/3142,
    mt/issues/3149,
    mt/pull/3150,
    mt/issues/3154,
    mt/issues/3163,
    mt/issues/3178,
    mt/pull/3184,
    mt/pull/3196,
    mt/issues/3204,
    mt/pull/3206,
    mt/pull/3208,
    mt/issues/3213,
    mt/pull/3216,
    mt/issues/3224,
    mt/issues/3226,
    mt/issues/3228,
    mt/pull/3229,
    mt/pull/3259,
    mt/issues/3274,
    mt/issues/3287,
    mt/pull/3288,
    mt/issues/3292,
    mt/pull/3295,
    mt/pull/3296,
    mt/issues/3298,
    mt/issues/3325,
    mt/pull/3326,
    mt/issues/3334,
    mt/issues/3342,
    mt/pull/3343,
    mt/issues/3351,
    mt/pull/3352,
    mt/pull/3362,
    mt/issues/3365,
    mt/pull/3366,
    mt/pull/3374,
    mt/issues/3377,
    mt/pull/3378,
    mt/issues/3381,
    mt/pull/3398,
    mt/pull/3413,
    mt/issues/3415).
    Thanks @phprus, @gsjaardema, @NewbieOrange, @EngineLessCC, @asmaloney,
    @HazardyKnusperkeks, @sergiud, @Youw, @thesmurph, @czudziakm,
    @Roman-Koshelev, @chronoxor, @ShawnZhong, @russelltg, @glebm, @tmartin-gh,
    @Zhaojun-Liu, @louiswins and @mogemimi.

# 9.1.0 - 2022-08-27

-   `fmt::formatted_size` now works at compile time
    (https://github.com/fmtlib/fmt/pull/3026). For example
    ([godbolt](https://godbolt.org/z/1MW5rMdf8)):

    ```c++
    #include <fmt/compile.h>

    int main() {
      using namespace fmt::literals;
      constexpr size_t n = fmt::formatted_size("{}"_cf, 42);
      fmt::print("{}\n", n); // prints 2
    }
    ```

    Thanks @marksantaniello.

-   Fixed handling of invalid UTF-8
    (https://github.com/fmtlib/fmt/pull/3038,
    mt/pull/3044,
    mt/pull/3056).
    Thanks @phprus and @skeeto.

-   Improved Unicode support in `ostream` overloads of `print`
    (https://github.com/fmtlib/fmt/pull/2994,
    mt/pull/3001,
    mt/pull/3025). Thanks @dimztimz.

-   Fixed handling of the sign specifier in localized formatting on
    systems with 32-bit `wchar_t`
    (https://github.com/fmtlib/fmt/issues/3041).

-   Added support for wide streams to `fmt::streamed`
    (https://github.com/fmtlib/fmt/pull/2994). Thanks @phprus.

-   Added the `n` specifier that disables the output of delimiters when
    formatting ranges (https://github.com/fmtlib/fmt/pull/2981,
    mt/pull/2983). For example
    ([godbolt](https://godbolt.org/z/roKqGdj8c)):

    ```c++
    #include <fmt/ranges.h>
    #include <vector>

    int main() {
      auto v = std::vector{1, 2, 3};
      fmt::print("{:n}\n", v); // prints 1, 2, 3
    }
    ```

    Thanks @BRevzin.

-   Worked around problematic `std::string_view` constructors introduced
    in C++23 (https://github.com/fmtlib/fmt/issues/3030,
    mt/issues/3050). Thanks @strega-nil-ms.

-   Improve handling (exclusion) of recursive ranges
    (https://github.com/fmtlib/fmt/issues/2968,
    mt/pull/2974). Thanks @Dani-Hub.

-   Improved error reporting in format string compilation
    (https://github.com/fmtlib/fmt/issues/3055).

-   Improved the implementation of
    Dragonbox, the algorithm
    used for the default floating-point formatting
    (https://github.com/fmtlib/fmt/pull/2984). Thanks @jk-jeon.

-   Fixed issues with floating-point formatting on exotic platforms.

-   Improved the implementation of chrono formatting
    (https://github.com/fmtlib/fmt/pull/3010). Thanks @phprus.

-   Improved documentation
    (https://github.com/fmtlib/fmt/pull/2966,
    mt/pull/3009,
    mt/issues/3020,
    mt/pull/3037).
    Thanks @mwinterb, @jcelerier and @remiburtin.

-   Improved build configuration
    (https://github.com/fmtlib/fmt/pull/2991,
    mt/pull/2995,
    mt/issues/3004,
    mt/pull/3007,
    mt/pull/3040).
    Thanks @dimztimz and @hwhsu1231.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/2969,
    mt/pull/2971,
    mt/issues/2975,
    mt/pull/2982,
    mt/pull/2985,
    mt/issues/2988,
    mt/issues/2989,
    mt/issues/3000,
    mt/issues/3006,
    mt/issues/3014,
    mt/issues/3015,
    mt/pull/3021,
    mt/issues/3023,
    mt/pull/3024,
    mt/pull/3029,
    mt/pull/3043,
    mt/issues/3052,
    mt/pull/3053,
    mt/pull/3054).
    Thanks @h-friederich, @dimztimz, @olupton, @bernhardmgruber and @phprus.

# 9.0.0 - 2022-07-04

-   Switched to the internal floating point formatter for all decimal
    presentation formats. In particular this results in consistent
    rounding on all platforms and removing the `s[n]printf` fallback for
    decimal FP formatting.

-   Compile-time floating point formatting no longer requires the
    header-only mode. For example
    ([godbolt](https://godbolt.org/z/G37PTeG3b)):

    ```c++
    #include <array>
    #include <fmt/compile.h>

    consteval auto compile_time_dtoa(double value) -> std::array<char, 10> {
      auto result = std::array<char, 10>();
      fmt::format_to(result.data(), FMT_COMPILE("{}"), value);
      return result;
    }

    constexpr auto answer = compile_time_dtoa(0.42);
    ```

    works with the default settings.

-   Improved the implementation of
    Dragonbox, the algorithm
    used for the default floating-point formatting
    (https://github.com/fmtlib/fmt/pull/2713,
    mt/pull/2750). Thanks @jk-jeon.

-   Made `fmt::to_string` work with `__float128`. This uses the internal
    FP formatter and works even on system without `__float128` support
    in `[s]printf`.

-   Disabled automatic `std::ostream` insertion operator (`operator<<`)
    discovery when `fmt/ostream.h` is included to prevent ODR
    violations. You can get the old behavior by defining
    `FMT_DEPRECATED_OSTREAM` but this will be removed in the next major
    release. Use `fmt::streamed` or `fmt::ostream_formatter` to enable
    formatting via `std::ostream` instead.

-   Added `fmt::ostream_formatter` that can be used to write `formatter`
    specializations that perform formatting via `std::ostream`. For
    example ([godbolt](https://godbolt.org/z/5sEc5qMsf)):

    ```c++
    #include <fmt/ostream.h>

    struct date {
      int year, month, day;

      friend std::ostream& operator<<(std::ostream& os, const date& d) {
        return os << d.year << '-' << d.month << '-' << d.day;
      }
    };

    template <> struct fmt::formatter<date> : ostream_formatter {};

    std::string s = fmt::format("The date is {}", date{2012, 12, 9});
    // s == "The date is 2012-12-9"
    ```

-   Added the `fmt::streamed` function that takes an object and formats
    it via `std::ostream`. For example
    ([godbolt](https://godbolt.org/z/5G3346G1f)):

    ```c++
    #include <thread>
    #include <fmt/ostream.h>

    int main() {
      fmt::print("Current thread id: {}\n",
                 fmt::streamed(std::this_thread::get_id()));
    }
    ```

    Note that `fmt/std.h` provides a `formatter` specialization for
    `std::thread::id` so you don\'t need to format it via
    `std::ostream`.

-   Deprecated implicit conversions of unscoped enums to integers for
    consistency with scoped enums.

-   Added an argument-dependent lookup based `format_as` extension API
    to simplify formatting of enums.

-   Added experimental `std::variant` formatting support
    (https://github.com/fmtlib/fmt/pull/2941). For example
    ([godbolt](https://godbolt.org/z/KG9z6cq68)):

    ```c++
    #include <variant>
    #include <fmt/std.h>

    int main() {
      auto v = std::variant<int, std::string>(42);
      fmt::print("{}\n", v);
    }
    ```

    prints:

        variant(42)

    Thanks @jehelset.

-   Added experimental `std::filesystem::path` formatting support
    (https://github.com/fmtlib/fmt/issues/2865,
    mt/pull/2902,
    mt/issues/2917,
    mt/pull/2918). For example
    ([godbolt](https://godbolt.org/z/o44dMexEb)):

    ```c++
    #include <filesystem>
    #include <fmt/std.h>

    int main() {
      fmt::print("There is no place like {}.", std::filesystem::path("/home"));
    }
    ```

    prints:

        There is no place like "/home".

    Thanks @phprus.

-   Added a `std::thread::id` formatter to `fmt/std.h`. For example
    ([godbolt](https://godbolt.org/z/j1azbYf3E)):

    ```c++
    #include <thread>
    #include <fmt/std.h>

    int main() {
      fmt::print("Current thread id: {}\n", std::this_thread::get_id());
    }
    ```

-   Added `fmt::styled` that applies a text style to an individual
    argument (https://github.com/fmtlib/fmt/pull/2793). For
    example ([godbolt](https://godbolt.org/z/vWGW7v5M6)):

    ```c++
    #include <fmt/chrono.h>
    #include <fmt/color.h>

    int main() {
      auto now = std::chrono::system_clock::now();
      fmt::print(
        "[{}] {}: {}\n",
        fmt::styled(now, fmt::emphasis::bold),
        fmt::styled("error", fg(fmt::color::red)),
        "something went wrong");
    }
    ```

    prints

    ![](https://user-images.githubusercontent.com/576385/175071215-12809244-dab0-4005-96d8-7cd911c964d5.png)

    Thanks @rbrugo.

-   Made `fmt::print` overload for text styles correctly handle UTF-8
    (https://github.com/fmtlib/fmt/issues/2681,
    mt/pull/2701). Thanks @AlexGuteniev.

-   Fixed Unicode handling when writing to an ostream.

-   Added support for nested specifiers to range formatting
    (https://github.com/fmtlib/fmt/pull/2673). For example
    ([godbolt](https://godbolt.org/z/xd3Gj38cf)):

    ```c++
    #include <vector>
    #include <fmt/ranges.h>

    int main() {
      fmt::print("{::#x}\n", std::vector{10, 20, 30});
    }
    ```

    prints `[0xa, 0x14, 0x1e]`.

    Thanks @BRevzin.

-   Implemented escaping of wide strings in ranges
    (https://github.com/fmtlib/fmt/pull/2904). Thanks @phprus.

-   Added support for ranges with `begin` / `end` found via the
    argument-dependent lookup
    (https://github.com/fmtlib/fmt/pull/2807). Thanks @rbrugo.

-   Fixed formatting of certain kinds of ranges of ranges
    (https://github.com/fmtlib/fmt/pull/2787). Thanks @BRevzin.

-   Fixed handling of maps with element types other than `std::pair`
    (https://github.com/fmtlib/fmt/pull/2944). Thanks @BrukerJWD.

-   Made tuple formatter enabled only if elements are formattable
    (https://github.com/fmtlib/fmt/issues/2939,
    mt/pull/2940). Thanks @jehelset.

-   Made `fmt::join` compatible with format string compilation
    (https://github.com/fmtlib/fmt/issues/2719,
    mt/pull/2720). Thanks @phprus.

-   Made compile-time checks work with named arguments of custom types
    and `std::ostream` `print` overloads
    (https://github.com/fmtlib/fmt/issues/2816,
    mt/issues/2817,
    mt/pull/2819). Thanks @timsong-cpp.

-   Removed `make_args_checked` because it is no longer needed for
    compile-time checks
    (https://github.com/fmtlib/fmt/pull/2760). Thanks @phprus.

-   Removed the following deprecated APIs: `_format`, `arg_join`, the
    `format_to` overload that takes a memory buffer, `[v]fprintf` that
    takes an `ostream`.

-   Removed the deprecated implicit conversion of `[const] signed char*`
    and `[const] unsigned char*` to C strings.

-   Removed the deprecated `fmt/locale.h`.

-   Replaced the deprecated `fileno()` with `descriptor()` in
    `buffered_file`.

-   Moved `to_string_view` to the `detail` namespace since it\'s an
    implementation detail.

-   Made access mode of a created file consistent with `fopen` by
    setting `S_IWGRP` and `S_IWOTH`
    (https://github.com/fmtlib/fmt/pull/2733). Thanks @arogge.

-   Removed a redundant buffer resize when formatting to `std::ostream`
    (https://github.com/fmtlib/fmt/issues/2842,
    mt/pull/2843). Thanks @jcelerier.

-   Made precision computation for strings consistent with width
    (https://github.com/fmtlib/fmt/issues/2888).

-   Fixed handling of locale separators in floating point formatting
    (https://github.com/fmtlib/fmt/issues/2830).

-   Made sign specifiers work with `__int128_t`
    (https://github.com/fmtlib/fmt/issues/2773).

-   Improved support for systems such as CHERI with extra data stored in
    pointers (https://github.com/fmtlib/fmt/pull/2932).
    Thanks @davidchisnall.

-   Improved documentation
    (https://github.com/fmtlib/fmt/pull/2706,
    mt/pull/2712,
    mt/pull/2789,
    mt/pull/2803,
    mt/pull/2805,
    mt/pull/2815,
    mt/pull/2924).
    Thanks @BRevzin, @Pokechu22, @setoye, @rtobar, @rbrugo, @anoonD and
    @leha-bot.

-   Improved build configuration
    (https://github.com/fmtlib/fmt/pull/2766,
    mt/pull/2772,
    mt/pull/2836,
    mt/pull/2852,
    mt/pull/2907,
    mt/pull/2913,
    mt/pull/2914).
    Thanks @kambala-decapitator, @mattiasljungstrom, @kieselnb, @nathannaveen
    and @Vertexwahn.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/2408,
    mt/issues/2507,
    mt/issues/2697,
    mt/issues/2715,
    mt/issues/2717,
    mt/pull/2722,
    mt/pull/2724,
    mt/pull/2725,
    mt/issues/2726,
    mt/pull/2728,
    mt/pull/2732,
    mt/issues/2738,
    mt/pull/2742,
    mt/issues/2744,
    mt/issues/2745,
    mt/issues/2746,
    mt/issues/2754,
    mt/pull/2755,
    mt/issues/2757,
    mt/pull/2758,
    mt/issues/2761,
    mt/pull/2762,
    mt/issues/2763,
    mt/pull/2765,
    mt/issues/2769,
    mt/pull/2770,
    mt/issues/2771,
    mt/issues/2777,
    mt/pull/2779,
    mt/pull/2782,
    mt/pull/2783,
    mt/issues/2794,
    mt/issues/2796,
    mt/pull/2797,
    mt/pull/2801,
    mt/pull/2802,
    mt/issues/2808,
    mt/issues/2818,
    mt/pull/2819,
    mt/issues/2829,
    mt/issues/2835,
    mt/issues/2848,
    mt/issues/2860,
    mt/pull/2861,
    mt/pull/2882,
    mt/issues/2886,
    mt/issues/2891,
    mt/pull/2892,
    mt/issues/2895,
    mt/issues/2896,
    mt/pull/2903,
    mt/issues/2906,
    mt/issues/2908,
    mt/pull/2909,
    mt/issues/2920,
    mt/pull/2922,
    mt/pull/2927,
    mt/pull/2929,
    mt/issues/2936,
    mt/pull/2937,
    mt/pull/2938,
    mt/pull/2951,
    mt/issues/2954,
    mt/pull/2957,
    mt/issues/2958,
    mt/pull/2960).
    Thanks @matrackif @Tobi823, @ivan-volnov, @VasiliPupkin256,
    @federico-busato, @barcharcraz, @jk-jeon, @HazardyKnusperkeks, @dalboris,
    @seanm, @gsjaardema, @timsong-cpp, @seanm, @frithrah, @chronoxor, @Agga,
    @madmaxoft, @JurajX, @phprus and @Dani-Hub.

# 8.1.1 - 2022-01-06

-   Restored ABI compatibility with version 8.0.x
    (https://github.com/fmtlib/fmt/issues/2695,
    mt/pull/2696). Thanks @saraedum.
-   Fixed chrono formatting on big endian systems
    (https://github.com/fmtlib/fmt/issues/2698,
    mt/pull/2699).
    Thanks @phprus and @xvitaly.
-   Fixed a linkage error with mingw
    (https://github.com/fmtlib/fmt/issues/2691,
    mt/pull/2692). Thanks @rbberger.

# 8.1.0 - 2022-01-02

-   Optimized chrono formatting
    (https://github.com/fmtlib/fmt/pull/2500,
    mt/pull/2537,
    mt/issues/2541,
    mt/pull/2544,
    mt/pull/2550,
    mt/pull/2551,
    mt/pull/2576,
    mt/issues/2577,
    mt/pull/2586,
    mt/pull/2591,
    mt/pull/2594,
    mt/pull/2602,
    mt/pull/2617,
    mt/issues/2628,
    mt/pull/2633,
    mt/issues/2670,
    mt/pull/2671).

    Processing of some specifiers such as `%z` and `%Y` is now up to
    10-20 times faster, for example on GCC 11 with libstdc++:

        ----------------------------------------------------------------------------
        Benchmark                                  Before             After
        ----------------------------------------------------------------------------
        FMTFormatter_z                             261 ns             26.3 ns
        FMTFormatterCompile_z                      246 ns             11.6 ns
        FMTFormatter_Y                             263 ns             26.1 ns
        FMTFormatterCompile_Y                      244 ns             10.5 ns
        ----------------------------------------------------------------------------

    Thanks @phprus and @toughengineer.

-   Implemented subsecond formatting for chrono durations
    (https://github.com/fmtlib/fmt/pull/2623). For example
    ([godbolt](https://godbolt.org/z/es7vWTETe)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      fmt::print("{:%S}", std::chrono::milliseconds(1234));
    }
    ```

    prints \"01.234\".

    Thanks @matrackif.

-   Fixed handling of precision 0 when formatting chrono durations
    (https://github.com/fmtlib/fmt/issues/2587,
    mt/pull/2588). Thanks @lukester1975.

-   Fixed an overflow on invalid inputs in the `tm` formatter
    (https://github.com/fmtlib/fmt/pull/2564). Thanks @phprus.

-   Added `fmt::group_digits` that formats integers with a non-localized
    digit separator (comma) for groups of three digits. For example
    ([godbolt](https://godbolt.org/z/TxGxG9Poq)):

    ```c++
    #include <fmt/format.h>

    int main() {
      fmt::print("{} dollars", fmt::group_digits(1000000));
    }
    ```

    prints \"1,000,000 dollars\".

-   Added support for faint, conceal, reverse and blink text styles
    (https://github.com/fmtlib/fmt/pull/2394):

    <https://user-images.githubusercontent.com/576385/147710227-c68f5317-f8fa-42c3-9123-7c4ba3c398cb.mp4>

    Thanks @benit8 and @data-man.

-   Added experimental support for compile-time floating point
    formatting (https://github.com/fmtlib/fmt/pull/2426,
    mt/pull/2470). It is currently
    limited to the header-only mode. Thanks @alexezeder.

-   Added UDL-based named argument support to compile-time format string
    checks (https://github.com/fmtlib/fmt/issues/2640,
    mt/pull/2649). For example
    ([godbolt](https://godbolt.org/z/ohGbbvonv)):

    ```c++
    #include <fmt/format.h>

    int main() {
      using namespace fmt::literals;
      fmt::print("{answer:s}", "answer"_a=42);
    }
    ```

    gives a compile-time error on compilers with C++20 `consteval` and
    non-type template parameter support (gcc 10+) because `s` is not a
    valid format specifier for an integer.

    Thanks @alexezeder.

-   Implemented escaping of string range elements. For example
    ([godbolt](https://godbolt.org/z/rKvM1vKf3)):

    ```c++
    #include <fmt/ranges.h>
    #include <vector>

    int main() {
      fmt::print("{}", std::vector<std::string>{"\naan"});
    }
    ```

    is now printed as:

        ["\naan"]

    instead of:

        ["
        aan"]

-   Added an experimental `?` specifier for escaping strings.
    (https://github.com/fmtlib/fmt/pull/2674). Thanks @BRevzin.

-   Switched to JSON-like representation of maps and sets for
    consistency with Python\'s `str.format`. For example
    ([godbolt](https://godbolt.org/z/seKjoY9W5)):

    ```c++
    #include <fmt/ranges.h>
    #include <map>

    int main() {
      fmt::print("{}", std::map<std::string, int>{{"answer", 42}});
    }
    ```

    is now printed as:

        {"answer": 42}

-   Extended `fmt::join` to support C++20-only ranges
    (https://github.com/fmtlib/fmt/pull/2549). Thanks @BRevzin.

-   Optimized handling of non-const-iterable ranges and implemented
    initial support for non-const-formattable types.

-   Disabled implicit conversions of scoped enums to integers that was
    accidentally introduced in earlier versions
    (https://github.com/fmtlib/fmt/pull/1841).

-   Deprecated implicit conversion of `[const] signed char*` and
    `[const] unsigned char*` to C strings.

-   Deprecated `_format`, a legacy UDL-based format API
    (https://github.com/fmtlib/fmt/pull/2646). Thanks @alexezeder.

-   Marked `format`, `formatted_size` and `to_string` as `[[nodiscard]]`
    (https://github.com/fmtlib/fmt/pull/2612). @0x8000-0000.

-   Added missing diagnostic when trying to format function and member
    pointers as well as objects convertible to pointers which is
    explicitly disallowed
    (https://github.com/fmtlib/fmt/issues/2598,
    mt/pull/2609,
    mt/pull/2610). Thanks @AlexGuteniev.

-   Optimized writing to a contiguous buffer with `format_to_n`
    (https://github.com/fmtlib/fmt/pull/2489). Thanks @Roman-Koshelev.

-   Optimized writing to non-`char` buffers
    (https://github.com/fmtlib/fmt/pull/2477). Thanks @Roman-Koshelev.

-   Decimal point is now localized when using the `L` specifier.

-   Improved floating point formatter implementation
    (https://github.com/fmtlib/fmt/pull/2498,
    mt/pull/2499). Thanks @Roman-Koshelev.

-   Fixed handling of very large precision in fixed format
    (https://github.com/fmtlib/fmt/pull/2616).

-   Made a table of cached powers used in FP formatting static
    (https://github.com/fmtlib/fmt/pull/2509). Thanks @jk-jeon.

-   Resolved a lookup ambiguity with C++20 format-related functions due
    to ADL (https://github.com/fmtlib/fmt/issues/2639,
    mt/pull/2641). Thanks @mkurdej.

-   Removed unnecessary inline namespace qualification
    (https://github.com/fmtlib/fmt/issues/2642,
    mt/pull/2643). Thanks @mkurdej.

-   Implemented argument forwarding in `format_to_n`
    (https://github.com/fmtlib/fmt/issues/2462,
    mt/pull/2463). Thanks @owent.

-   Fixed handling of implicit conversions in `fmt::to_string` and
    format string compilation
    (https://github.com/fmtlib/fmt/issues/2565).

-   Changed the default access mode of files created by
    `fmt::output_file` to `-rw-r--r--` for consistency with `fopen`
    (https://github.com/fmtlib/fmt/issues/2530).

-   Make `fmt::ostream::flush` public
    (https://github.com/fmtlib/fmt/issues/2435).

-   Improved C++14/17 attribute detection
    (https://github.com/fmtlib/fmt/pull/2615). Thanks @AlexGuteniev.

-   Improved `consteval` detection for MSVC
    (https://github.com/fmtlib/fmt/pull/2559). Thanks @DanielaE.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/2406,
    mt/pull/2446,
    mt/issues/2493,
    mt/issues/2513,
    mt/pull/2515,
    mt/issues/2522,
    mt/pull/2562,
    mt/pull/2575,
    mt/pull/2606,
    mt/pull/2620,
    mt/issues/2676).
    Thanks @sobolevn, @UnePierre, @zhsj, @phprus, @ericcurtin and @Lounarok.

-   Improved fuzzers and added a fuzzer for chrono timepoint formatting
    (https://github.com/fmtlib/fmt/pull/2461,
    mt/pull/2469). @pauldreik,

-   Added the `FMT_SYSTEM_HEADERS` CMake option setting which marks
    {fmt}\'s headers as system. It can be used to suppress warnings
    (https://github.com/fmtlib/fmt/issues/2644,
    mt/pull/2651). Thanks @alexezeder.

-   Added the Bazel build system support
    (https://github.com/fmtlib/fmt/pull/2505,
    mt/pull/2516). Thanks @Vertexwahn.

-   Improved build configuration and tests
    (https://github.com/fmtlib/fmt/issues/2437,
    mt/pull/2558,
    mt/pull/2648,
    mt/pull/2650,
    mt/pull/2663,
    mt/pull/2677).
    Thanks @DanielaE, @alexezeder and @phprus.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/2353,
    mt/pull/2356,
    mt/pull/2399,
    mt/issues/2408,
    mt/pull/2414,
    mt/pull/2427,
    mt/pull/2432,
    mt/pull/2442,
    mt/pull/2434,
    mt/issues/2439,
    mt/pull/2447,
    mt/pull/2450,
    mt/issues/2455,
    mt/issues/2465,
    mt/issues/2472,
    mt/issues/2474,
    mt/pull/2476,
    mt/issues/2478,
    mt/issues/2479,
    mt/issues/2481,
    mt/pull/2482,
    mt/pull/2483,
    mt/issues/2490,
    mt/pull/2491,
    mt/pull/2510,
    mt/pull/2518,
    mt/issues/2528,
    mt/pull/2529,
    mt/pull/2539,
    mt/issues/2540,
    mt/pull/2545,
    mt/pull/2555,
    mt/issues/2557,
    mt/issues/2570,
    mt/pull/2573,
    mt/pull/2582,
    mt/issues/2605,
    mt/pull/2611,
    mt/pull/2647,
    mt/issues/2627,
    mt/pull/2630,
    mt/issues/2635,
    mt/issues/2638,
    mt/issues/2653,
    mt/issues/2654,
    mt/issues/2661,
    mt/pull/2664,
    mt/pull/2684).
    Thanks @DanielaE, @mwinterb, @cdacamar, @TrebledJ, @bodomartin, @cquammen,
    @white238, @mmarkeloff, @palacaze, @jcelerier, @mborn-adi, @BrukerJWD,
    @spyridon97, @phprus, @oliverlee, @joshessman-llnl, @akohlmey, @timkalu,
    @olupton, @Acretock, @alexezeder, @andrewcorrigan, @lucpelletier and
    @HazardyKnusperkeks.

# 8.0.1 - 2021-07-02

-   Fixed the version number in the inline namespace
    (https://github.com/fmtlib/fmt/issues/2374).
-   Added a missing presentation type check for `std::string`
    (https://github.com/fmtlib/fmt/issues/2402).
-   Fixed a linkage error when mixing code built with clang and gcc
    (https://github.com/fmtlib/fmt/issues/2377).
-   Fixed documentation issues
    (https://github.com/fmtlib/fmt/pull/2396,
    mt/issues/2403,
    mt/issues/2406). Thanks @mkurdej.
-   Removed dead code in FP formatter (
    mt/pull/2398). Thanks @javierhonduco.
-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/2351,
    mt/issues/2359,
    mt/pull/2365,
    mt/issues/2368,
    mt/pull/2370,
    mt/pull/2376,
    mt/pull/2381,
    mt/pull/2382,
    mt/issues/2386,
    mt/pull/2389,
    mt/pull/2395,
    mt/pull/2397,
    mt/issues/2400,
    mt/issues/2401,
    mt/pull/2407).
    Thanks @zx2c4, @AidanSun05, @mattiasljungstrom, @joemmett, @erengy,
    @patlkli, @gsjaardema and @phprus.

# 8.0.0 - 2021-06-21

-   Enabled compile-time format string checks by default. For example
    ([godbolt](https://godbolt.org/z/sMxcohGjz)):

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{:d}", "I am not a number");
    }
    ```

    gives a compile-time error on compilers with C++20 `consteval`
    support (gcc 10+, clang 11+) because `d` is not a valid format
    specifier for a string.

    To pass a runtime string wrap it in `fmt::runtime`:

    ```c++
    fmt::print(fmt::runtime("{:d}"), "I am not a number");
    ```

-   Added compile-time formatting
    (https://github.com/fmtlib/fmt/pull/2019,
    mt/pull/2044,
    mt/pull/2056,
    mt/pull/2072,
    mt/pull/2075,
    mt/issues/2078,
    mt/pull/2129,
    mt/pull/2326). For example
    ([godbolt](https://godbolt.org/z/Mxx9d89jM)):

    ```c++
    #include <fmt/compile.h>

    consteval auto compile_time_itoa(int value) -> std::array<char, 10> {
      auto result = std::array<char, 10>();
      fmt::format_to(result.data(), FMT_COMPILE("{}"), value);
      return result;
    }

    constexpr auto answer = compile_time_itoa(42);
    ```

    Most of the formatting functionality is available at compile time
    with a notable exception of floating-point numbers and pointers.
    Thanks @alexezeder.

-   Optimized handling of format specifiers during format string
    compilation. For example, hexadecimal formatting (`"{:x}"`) is now
    3-7x faster than before when using `format_to` with format string
    compilation and a stack-allocated buffer
    (https://github.com/fmtlib/fmt/issues/1944).

    Before (7.1.3):

        ----------------------------------------------------------------------------
        Benchmark                                  Time             CPU   Iterations
        ----------------------------------------------------------------------------
        FMTCompileOld/0                         15.5 ns         15.5 ns     43302898
        FMTCompileOld/42                        16.6 ns         16.6 ns     43278267
        FMTCompileOld/273123                    18.7 ns         18.6 ns     37035861
        FMTCompileOld/9223372036854775807       19.4 ns         19.4 ns     35243000
        ----------------------------------------------------------------------------

    After (8.x):

        ----------------------------------------------------------------------------
        Benchmark                                  Time             CPU   Iterations
        ----------------------------------------------------------------------------
        FMTCompileNew/0                         1.99 ns         1.99 ns    360523686
        FMTCompileNew/42                        2.33 ns         2.33 ns    279865664
        FMTCompileNew/273123                    3.72 ns         3.71 ns    190230315
        FMTCompileNew/9223372036854775807       5.28 ns         5.26 ns    130711631
        ----------------------------------------------------------------------------

    It is even faster than `std::to_chars` from libc++ compiled with
    clang on macOS:

        ----------------------------------------------------------------------------
        Benchmark                                  Time             CPU   Iterations
        ----------------------------------------------------------------------------
        ToChars/0                               4.42 ns         4.41 ns    160196630
        ToChars/42                              5.00 ns         4.98 ns    140735201
        ToChars/273123                          7.26 ns         7.24 ns     95784130
        ToChars/9223372036854775807             8.77 ns         8.75 ns     75872534
        ----------------------------------------------------------------------------

    In other cases, especially involving `std::string` construction, the
    speed up is usually lower because handling format specifiers takes a
    smaller fraction of the total time.

-   Added the `_cf` user-defined literal to represent a compiled format
    string. It can be used instead of the `FMT_COMPILE` macro
    (https://github.com/fmtlib/fmt/pull/2043,
    mt/pull/2242):

    ```c++
    #include <fmt/compile.h>

    using namespace fmt::literals;
    auto s = fmt::format(FMT_COMPILE("{}"), 42); // 🙁 not modern
    auto s = fmt::format("{}"_cf, 42);           // 🙂 modern as hell
    ```

    It requires compiler support for class types in non-type template
    parameters (a C++20 feature) which is available in GCC 9.3+.
    Thanks @alexezeder.

-   Format string compilation now requires `format` functions of
    `formatter` specializations for user-defined types to be `const`:

    ```c++
    template <> struct fmt::formatter<my_type>: formatter<string_view> {
      template <typename FormatContext>
      auto format(my_type obj, FormatContext& ctx) const {  // Note const here.
        // ...
      }
    };
    ```

-   Added UDL-based named argument support to format string compilation
    (https://github.com/fmtlib/fmt/pull/2243,
    mt/pull/2281). For example:

    ```c++
    #include <fmt/compile.h>

    using namespace fmt::literals;
    auto s = fmt::format(FMT_COMPILE("{answer}"), "answer"_a = 42);
    ```

    Here the argument named \"answer\" is resolved at compile time with
    no runtime overhead. Thanks @alexezeder.

-   Added format string compilation support to `fmt::print`
    (https://github.com/fmtlib/fmt/issues/2280,
    mt/pull/2304). Thanks @alexezeder.

-   Added initial support for compiling {fmt} as a C++20 module
    (https://github.com/fmtlib/fmt/pull/2235,
    mt/pull/2240,
    mt/pull/2260,
    mt/pull/2282,
    mt/pull/2283,
    mt/pull/2288,
    mt/pull/2298,
    mt/pull/2306,
    mt/pull/2307,
    mt/pull/2309,
    mt/pull/2318,
    mt/pull/2324,
    mt/pull/2332,
    mt/pull/2340). Thanks @DanielaE.

-   Made symbols private by default reducing shared library size
    (https://github.com/fmtlib/fmt/pull/2301). For example
    there was a \~15% reported reduction on one platform. Thanks @sergiud.

-   Optimized includes making the result of preprocessing `fmt/format.h`
    \~20% smaller with libstdc++/C++20 and slightly improving build
    times (https://github.com/fmtlib/fmt/issues/1998).

-   Added support of ranges with non-const `begin` / `end`
    (https://github.com/fmtlib/fmt/pull/1953). Thanks @kitegi.

-   Added support of `std::byte` and other formattable types to
    `fmt::join` (https://github.com/fmtlib/fmt/issues/1981,
    mt/issues/2040,
    mt/pull/2050,
    mt/issues/2262). For example:

    ```c++
    #include <fmt/format.h>
    #include <cstddef>
    #include <vector>

    int main() {
      auto bytes = std::vector{std::byte(4), std::byte(2)};
      fmt::print("{}", fmt::join(bytes, ""));
    }
    ```

    prints \"42\".

    Thanks @kamibo.

-   Implemented the default format for `std::chrono::system_clock`
    (https://github.com/fmtlib/fmt/issues/2319,
    mt/pull/2345). For example:

    ```c++
    #include <fmt/chrono.h>

    int main() {
      fmt::print("{}", std::chrono::system_clock::now());
    }
    ```

    prints \"2021-06-18 15:22:00\" (the output depends on the current
    date and time). Thanks @sunmy2019.

-   Made more chrono specifiers locale independent by default. Use the
    `'L'` specifier to get localized formatting. For example:

    ```c++
    #include <fmt/chrono.h>

    int main() {
      std::locale::global(std::locale("ru_RU.UTF-8"));
      auto monday = std::chrono::weekday(1);
      fmt::print("{}\n", monday);   // prints "Mon"
      fmt::print("{:L}\n", monday); // prints "пн"
    }
    ```

-   Improved locale handling in chrono formatting
    (https://github.com/fmtlib/fmt/issues/2337,
    mt/pull/2349,
    mt/pull/2350). Thanks @phprus.

-   Deprecated `fmt/locale.h` moving the formatting functions that take
    a locale to `fmt/format.h` (`char`) and `fmt/xchar` (other
    overloads). This doesn\'t introduce a dependency on `<locale>` so
    there is virtually no compile time effect.

-   Deprecated an undocumented `format_to` overload that takes
    `basic_memory_buffer`.

-   Made parameter order in `vformat_to` consistent with `format_to`
    (https://github.com/fmtlib/fmt/issues/2327).

-   Added support for time points with arbitrary durations
    (https://github.com/fmtlib/fmt/issues/2208). For example:

    ```c++
    #include <fmt/chrono.h>

    int main() {
      using tp = std::chrono::time_point<
        std::chrono::system_clock, std::chrono::seconds>;
      fmt::print("{:%S}", tp(std::chrono::seconds(42)));
    }
    ```

    prints \"42\".

-   Formatting floating-point numbers no longer produces trailing zeros
    by default for consistency with `std::format`. For example:

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{0:.3}", 1.1);
    }
    ```

    prints \"1.1\". Use the `'#'` specifier to keep trailing zeros.

-   Dropped a limit on the number of elements in a range and replaced
    `{}` with `[]` as range delimiters for consistency with Python\'s
    `str.format`.

-   The `'L'` specifier for locale-specific numeric formatting can now
    be combined with presentation specifiers as in `std::format`. For
    example:

    ```c++
    #include <fmt/core.h>
    #include <locale>

    int main() {
      std::locale::global(std::locale("fr_FR.UTF-8"));
      fmt::print("{0:.2Lf}", 0.42);
    }
    ```

    prints \"0,42\". The deprecated `'n'` specifier has been removed.

-   Made the `0` specifier ignored for infinity and NaN
    (https://github.com/fmtlib/fmt/issues/2305,
    mt/pull/2310). Thanks @Liedtke.

-   Made the hexfloat formatting use the right alignment by default
    (https://github.com/fmtlib/fmt/issues/2308,
    mt/pull/2317). Thanks @Liedtke.

-   Removed the deprecated numeric alignment (`'='`). Use the `'0'`
    specifier instead.

-   Removed the deprecated `fmt/posix.h` header that has been replaced
    with `fmt/os.h`.

-   Removed the deprecated `format_to_n_context`, `format_to_n_args` and
    `make_format_to_n_args`. They have been replaced with
    `format_context`, `` format_args` and ``make_format_args\`\`
    respectively.

-   Moved `wchar_t`-specific functions and types to `fmt/xchar.h`. You
    can define `FMT_DEPRECATED_INCLUDE_XCHAR` to automatically include
    `fmt/xchar.h` from `fmt/format.h` but this will be disabled in the
    next major release.

-   Fixed handling of the `'+'` specifier in localized formatting
    (https://github.com/fmtlib/fmt/issues/2133).

-   Added support for the `'s'` format specifier that gives textual
    representation of `bool`
    (https://github.com/fmtlib/fmt/issues/2094,
    mt/pull/2109). For example:

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{:s}", true);
    }
    ```

    prints \"true\". Thanks @powercoderlol.

-   Made `fmt::ptr` work with function pointers
    (https://github.com/fmtlib/fmt/pull/2131). For example:

    ```c++
    #include <fmt/format.h>

    int main() {
      fmt::print("My main: {}\n", fmt::ptr(main));
    }
    ```

    Thanks @mikecrowe.

-   The undocumented support for specializing `formatter` for pointer
    types has been removed.

-   Fixed `fmt::formatted_size` with format string compilation
    (https://github.com/fmtlib/fmt/pull/2141,
    mt/pull/2161). Thanks @alexezeder.

-   Fixed handling of empty format strings during format string
    compilation (https://github.com/fmtlib/fmt/issues/2042):

    ```c++
    auto s = fmt::format(FMT_COMPILE(""));
    ```

    Thanks @alexezeder.

-   Fixed handling of enums in `fmt::to_string`
    (https://github.com/fmtlib/fmt/issues/2036).

-   Improved width computation
    (https://github.com/fmtlib/fmt/issues/2033,
    mt/issues/2091). For example:

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{:-<10}{}\n", "你好", "世界");
      fmt::print("{:-<10}{}\n", "hello", "world");
    }
    ```

    prints

    ![](https://user-images.githubusercontent.com/576385/119840373-cea3ca80-beb9-11eb-91e0-54266c48e181.png)

    on a modern terminal.

-   The experimental fast output stream (`fmt::ostream`) is now
    truncated by default for consistency with `fopen`
    (https://github.com/fmtlib/fmt/issues/2018). For example:

    ```c++
    #include <fmt/os.h>

    int main() {
      fmt::ostream out1 = fmt::output_file("guide");
      out1.print("Zaphod");
      out1.close();
      fmt::ostream out2 = fmt::output_file("guide");
      out2.print("Ford");
    }
    ```

    writes \"Ford\" to the file \"guide\". To preserve the old file
    content if any pass `fmt::file::WRONLY | fmt::file::CREATE` flags to
    `fmt::output_file`.

-   Fixed moving of `fmt::ostream` that holds buffered data
    (https://github.com/fmtlib/fmt/issues/2197,
    mt/pull/2198). Thanks @vtta.

-   Replaced the `fmt::system_error` exception with a function of the
    same name that constructs `std::system_error`
    (https://github.com/fmtlib/fmt/issues/2266).

-   Replaced the `fmt::windows_error` exception with a function of the
    same name that constructs `std::system_error` with the category
    returned by `fmt::system_category()`
    (https://github.com/fmtlib/fmt/issues/2274,
    mt/pull/2275). The latter is
    similar to `std::sytem_category` but correctly handles UTF-8.
    Thanks @phprus.

-   Replaced `fmt::error_code` with `std::error_code` and made it
    formattable (https://github.com/fmtlib/fmt/issues/2269,
    mt/pull/2270,
    mt/pull/2273). Thanks @phprus.

-   Added speech synthesis support
    (https://github.com/fmtlib/fmt/pull/2206).

-   Made `format_to` work with a memory buffer that has a custom
    allocator (https://github.com/fmtlib/fmt/pull/2300).
    Thanks @voxmea.

-   Added `Allocator::max_size` support to `basic_memory_buffer`.
    (https://github.com/fmtlib/fmt/pull/1960). Thanks @phprus.

-   Added wide string support to `fmt::join`
    (https://github.com/fmtlib/fmt/pull/2236). Thanks @crbrz.

-   Made iterators passed to `formatter` specializations via a format
    context satisfy C++20 `std::output_iterator` requirements
    (https://github.com/fmtlib/fmt/issues/2156,
    mt/pull/2158,
    mt/issues/2195,
    mt/pull/2204). Thanks @randomnetcat.

-   Optimized the `printf` implementation
    (https://github.com/fmtlib/fmt/pull/1982,
    mt/pull/1984,
    mt/pull/2016,
    mt/pull/2164).
    Thanks @rimathia and @moiwi.

-   Improved detection of `constexpr` `char_traits`
    (https://github.com/fmtlib/fmt/pull/2246,
    mt/pull/2257). Thanks @phprus.

-   Fixed writing to `stdout` when it is redirected to `NUL` on Windows
    (https://github.com/fmtlib/fmt/issues/2080).

-   Fixed exception propagation from iterators
    (https://github.com/fmtlib/fmt/issues/2097).

-   Improved `strftime` error handling
    (https://github.com/fmtlib/fmt/issues/2238,
    mt/pull/2244). Thanks @yumeyao.

-   Stopped using deprecated GCC UDL template extension.

-   Added `fmt/args.h` to the install target
    (https://github.com/fmtlib/fmt/issues/2096).

-   Error messages are now passed to assert when exceptions are disabled
    (https://github.com/fmtlib/fmt/pull/2145). Thanks @NobodyXu.

-   Added the `FMT_MASTER_PROJECT` CMake option to control build and
    install targets when {fmt} is included via `add_subdirectory`
    (https://github.com/fmtlib/fmt/issues/2098,
    mt/pull/2100).
    Thanks @randomizedthinking.

-   Improved build configuration
    (https://github.com/fmtlib/fmt/pull/2026,
    mt/pull/2122).
    Thanks @luncliff and @ibaned.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/1947,
    mt/pull/1959,
    mt/pull/1963,
    mt/pull/1965,
    mt/issues/1966,
    mt/pull/1974,
    mt/pull/1975,
    mt/pull/1990,
    mt/issues/2000,
    mt/pull/2001,
    mt/issues/2002,
    mt/issues/2004,
    mt/pull/2006,
    mt/pull/2009,
    mt/pull/2010,
    mt/issues/2038,
    mt/issues/2039,
    mt/issues/2047,
    mt/pull/2053,
    mt/issues/2059,
    mt/pull/2065,
    mt/pull/2067,
    mt/pull/2068,
    mt/pull/2073,
    mt/issues/2103,
    mt/issues/2105,
    mt/pull/2106,
    mt/pull/2107,
    mt/issues/2116,
    mt/pull/2117,
    mt/issues/2118,
    mt/pull/2119,
    mt/issues/2127,
    mt/pull/2128,
    mt/issues/2140,
    mt/issues/2142,
    mt/pull/2143,
    mt/pull/2144,
    mt/issues/2147,
    mt/issues/2148,
    mt/issues/2149,
    mt/pull/2152,
    mt/pull/2160,
    mt/issues/2170,
    mt/issues/2175,
    mt/issues/2176,
    mt/pull/2177,
    mt/issues/2178,
    mt/pull/2179,
    mt/issues/2180,
    mt/issues/2181,
    mt/pull/2183,
    mt/issues/2184,
    mt/issues/2185,
    mt/pull/2186,
    mt/pull/2187,
    mt/pull/2190,
    mt/pull/2192,
    mt/pull/2194,
    mt/pull/2205,
    mt/issues/2210,
    mt/pull/2211,
    mt/pull/2215,
    mt/pull/2216,
    mt/pull/2218,
    mt/pull/2220,
    mt/issues/2228,
    mt/pull/2229,
    mt/pull/2230,
    mt/issues/2233,
    mt/pull/2239,
    mt/issues/2248,
    mt/issues/2252,
    mt/pull/2253,
    mt/pull/2255,
    mt/issues/2261,
    mt/issues/2278,
    mt/issues/2284,
    mt/pull/2287,
    mt/pull/2289,
    mt/pull/2290,
    mt/pull/2293,
    mt/issues/2295,
    mt/pull/2296,
    mt/pull/2297,
    mt/issues/2311,
    mt/pull/2313,
    mt/pull/2315,
    mt/issues/2320,
    mt/pull/2321,
    mt/pull/2323,
    mt/issues/2328,
    mt/pull/2329,
    mt/pull/2333,
    mt/pull/2338,
    mt/pull/2341).
    Thanks @darklukee, @fagg, @killerbot242, @jgopel, @yeswalrus, @Finkman,
    @HazardyKnusperkeks, @dkavolis, @concatime, @chronoxor, @summivox, @yNeo,
    @Apache-HB, @alexezeder, @toojays, @Brainy0207, @vadz, @imsherlock, @phprus,
    @white238, @yafshar, @BillyDonahue, @jstaahl, @denchat, @DanielaE,
    @ilyakurdyukov, @ilmai, @JessyDL, @sergiud, @mwinterb, @sven-herrmann,
    @jmelas, @twoixter, @crbrz and @upsj.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/1986,
    mt/pull/2051,
    mt/issues/2057,
    mt/pull/2081,
    mt/issues/2084,
    mt/pull/2312).
    Thanks @imba-tjd, @0x416c69 and @mordante.

-   Continuous integration and test improvements
    (https://github.com/fmtlib/fmt/issues/1969,
    mt/pull/1991,
    mt/pull/2020,
    mt/pull/2110,
    mt/pull/2114,
    mt/issues/2196,
    mt/pull/2217,
    mt/pull/2247,
    mt/pull/2256,
    mt/pull/2336,
    mt/pull/2346).
    Thanks @jgopel, @alexezeder and @DanielaE.

# 7.1.3 - 2020-11-24

-   Fixed handling of buffer boundaries in `format_to_n`
    (https://github.com/fmtlib/fmt/issues/1996,
    mt/issues/2029).
-   Fixed linkage errors when linking with a shared library
    (https://github.com/fmtlib/fmt/issues/2011).
-   Reintroduced ostream support to range formatters
    (https://github.com/fmtlib/fmt/issues/2014).
-   Worked around an issue with mixing std versions in gcc
    (https://github.com/fmtlib/fmt/issues/2017).

# 7.1.2 - 2020-11-04

-   Fixed floating point formatting with large precision
    (https://github.com/fmtlib/fmt/issues/1976).

# 7.1.1 - 2020-11-01

-   Fixed ABI compatibility with 7.0.x
    (https://github.com/fmtlib/fmt/issues/1961).
-   Added the `FMT_ARM_ABI_COMPATIBILITY` macro to work around ABI
    incompatibility between GCC and Clang on ARM
    (https://github.com/fmtlib/fmt/issues/1919).
-   Worked around a SFINAE bug in GCC 8
    (https://github.com/fmtlib/fmt/issues/1957).
-   Fixed linkage errors when building with GCC\'s LTO
    (https://github.com/fmtlib/fmt/issues/1955).
-   Fixed a compilation error when building without `__builtin_clz` or
    equivalent (https://github.com/fmtlib/fmt/pull/1968).
    Thanks @tohammer.
-   Fixed a sign conversion warning
    (https://github.com/fmtlib/fmt/pull/1964). Thanks @OptoCloud.

# 7.1.0 - 2020-10-25

-   Switched from
    [Grisu3](https://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf)
    to Dragonbox for the default
    floating-point formatting which gives the shortest decimal
    representation with round-trip guarantee and correct rounding
    (https://github.com/fmtlib/fmt/pull/1882,
    mt/pull/1887,
    mt/pull/1894). This makes {fmt}
    up to 20-30x faster than common implementations of
    `std::ostringstream` and `sprintf` on
    dtoa-benchmark and
    faster than double-conversion and Ryū:

    ![](https://user-images.githubusercontent.com/576385/95684665-11719600-0ba8-11eb-8e5b-972ff4e49428.png)

    It is possible to get even better performance at the cost of larger
    binary size by compiling with the `FMT_USE_FULL_CACHE_DRAGONBOX`
    macro set to 1.

    Thanks @jk-jeon.

-   Added an experimental unsynchronized file output API which, together
    with [format string
    compilation](https://fmt.dev/latest/api.html#compile-api), can give
    [5-9 times speed up compared to
    fprintf](https://www.zverovich.net/2020/08/04/optimal-file-buffer-size.html)
    on common platforms ([godbolt](https://godbolt.org/z/nsTcG8)):

    ```c++
    #include <fmt/os.h>

    int main() {
      auto f = fmt::output_file("guide");
      f.print("The answer is {}.", 42);
    }
    ```

-   Added a formatter for `std::chrono::time_point<system_clock>`
    (https://github.com/fmtlib/fmt/issues/1819,
    mt/pull/1837). For example
    ([godbolt](https://godbolt.org/z/c4M6fh)):

    ```c++
    #include <fmt/chrono.h>

    int main() {
      auto now = std::chrono::system_clock::now();
      fmt::print("The time is {:%H:%M:%S}.\n", now);
    }
    ```

    Thanks @adamburgess.

-   Added support for ranges with non-const `begin`/`end` to `fmt::join`
    (https://github.com/fmtlib/fmt/issues/1784,
    mt/pull/1786). For example
    ([godbolt](https://godbolt.org/z/jP63Tv)):

    ```c++
    #include <fmt/ranges.h>
    #include <range/v3/view/filter.hpp>

    int main() {
      using std::literals::string_literals::operator""s;
      auto strs = std::array{"a"s, "bb"s, "ccc"s};
      auto range = strs | ranges::views::filter(
        [] (const std::string &x) { return x.size() != 2; }
      );
      fmt::print("{}\n", fmt::join(range, ""));
    }
    ```

    prints \"accc\".

    Thanks @tonyelewis.

-   Added a `memory_buffer::append` overload that takes a range
    (https://github.com/fmtlib/fmt/pull/1806). Thanks @BRevzin.

-   Improved handling of single code units in `FMT_COMPILE`. For
    example:

    ```c++
    #include <fmt/compile.h>

    char* f(char* buf) {
      return fmt::format_to(buf, FMT_COMPILE("x{}"), 42);
    }
    ```

    compiles to just ([godbolt](https://godbolt.org/z/5vncz3)):

    ```asm
    _Z1fPc:
      movb $120, (%rdi)
      xorl %edx, %edx
      cmpl $42, _ZN3fmt2v76detail10basic_dataIvE23zero_or_powers_of_10_32E+8(%rip)
      movl $3, %eax
      seta %dl
      subl %edx, %eax
      movzwl _ZN3fmt2v76detail10basic_dataIvE6digitsE+84(%rip), %edx
      cltq
      addq %rdi, %rax
      movw %dx, -2(%rax)
      ret
    ```

    Here a single `mov` instruction writes `'x'` (`$120`) to the output
    buffer.

-   Added dynamic width support to format string compilation
    (https://github.com/fmtlib/fmt/issues/1809).

-   Improved error reporting for unformattable types: now you\'ll get
    the type name directly in the error message instead of the note:

    ```c++
    #include <fmt/core.h>

    struct how_about_no {};

    int main() {
      fmt::print("{}", how_about_no());
    }
    ```

    Error ([godbolt](https://godbolt.org/z/GoxM4e)):

    `fmt/core.h:1438:3: error: static_assert failed due to requirement 'fmt::v7::formattable<how_about_no>()' "Cannot format an argument. To make type T formattable provide a formatter<T> specialization: https://fmt.dev/latest/api.html#udt" ...`

-   Added the
    [make_args_checked](https://fmt.dev/7.1.0/api.html#argument-lists)
    function template that allows you to write formatting functions with
    compile-time format string checks and avoid binary code bloat
    ([godbolt](https://godbolt.org/z/PEf9qr)):

    ```c++
    void vlog(const char* file, int line, fmt::string_view format,
              fmt::format_args args) {
      fmt::print("{}: {}: ", file, line);
      fmt::vprint(format, args);
    }

    template <typename S, typename... Args>
    void log(const char* file, int line, const S& format, Args&&... args) {
      vlog(file, line, format,
          fmt::make_args_checked<Args...>(format, args...));
    }

    #define MY_LOG(format, ...) \
      log(__FILE__, __LINE__, FMT_STRING(format), __VA_ARGS__)

    MY_LOG("invalid squishiness: {}", 42);
    ```

-   Replaced `snprintf` fallback with a faster internal IEEE 754 `float`
    and `double` formatter for arbitrary precision. For example
    ([godbolt](https://godbolt.org/z/dPhWvj)):

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{:.500}\n", 4.9406564584124654E-324);
    }
    ```

    prints

    `4.9406564584124654417656879286822137236505980261432476442558568250067550727020875186529983636163599237979656469544571773092665671035593979639877479601078187812630071319031140452784581716784898210368871863605699873072305000638740915356498438731247339727316961514003171538539807412623856559117102665855668676818703956031062493194527159149245532930545654440112748012970999954193198940908041656332452475714786901472678015935523861155013480352649347201937902681071074917033322268447533357208324319360923829e-324`.

-   Made `format_to_n` and `formatted_size` part of the [core
    API](https://fmt.dev/latest/api.html#core-api)
    ([godbolt](https://godbolt.org/z/sPjY1K)):

    ```c++
    #include <fmt/core.h>

    int main() {
      char buffer[10];
      auto result = fmt::format_to_n(buffer, sizeof(buffer), "{}", 42);
    }
    ```

-   Added `fmt::format_to_n` overload with format string compilation
    (https://github.com/fmtlib/fmt/issues/1764,
    mt/pull/1767,
    mt/pull/1869). For example
    ([godbolt](https://godbolt.org/z/93h86q)):

    ```c++
    #include <fmt/compile.h>

    int main() {
      char buffer[8];
      fmt::format_to_n(buffer, sizeof(buffer), FMT_COMPILE("{}"), 42);
    }
    ```

    Thanks @Kurkin and @alexezeder.

-   Added `fmt::format_to` overload that take `text_style`
    (https://github.com/fmtlib/fmt/issues/1593,
    mt/issues/1842,
    mt/pull/1843). For example
    ([godbolt](https://godbolt.org/z/91153r)):

    ```c++
    #include <fmt/color.h>

    int main() {
      std::string out;
      fmt::format_to(std::back_inserter(out),
                     fmt::emphasis::bold | fg(fmt::color::red),
                     "The answer is {}.", 42);
    }
    ```

    Thanks @Naios.

-   Made the `'#'` specifier emit trailing zeros in addition to the
    decimal point (https://github.com/fmtlib/fmt/issues/1797).
    For example ([godbolt](https://godbolt.org/z/bhdcW9)):

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("{:#.2g}", 0.5);
    }
    ```

    prints `0.50`.

-   Changed the default floating point format to not include `.0` for
    consistency with `std::format` and `std::to_chars`
    (https://github.com/fmtlib/fmt/issues/1893,
    mt/issues/1943). It is possible
    to get the decimal point and trailing zero with the `#` specifier.

-   Fixed an issue with floating-point formatting that could result in
    addition of a non-significant trailing zero in rare cases e.g.
    `1.00e-34` instead of `1.0e-34`
    (https://github.com/fmtlib/fmt/issues/1873,
    mt/issues/1917).

-   Made `fmt::to_string` fallback on `ostream` insertion operator if
    the `formatter` specialization is not provided
    (https://github.com/fmtlib/fmt/issues/1815,
    mt/pull/1829). Thanks @alexezeder.

-   Added support for the append mode to the experimental file API and
    improved `fcntl.h` detection.
    (https://github.com/fmtlib/fmt/pull/1847,
    mt/pull/1848). Thanks @t-wiser.

-   Fixed handling of types that have both an implicit conversion
    operator and an overloaded `ostream` insertion operator
    (https://github.com/fmtlib/fmt/issues/1766).

-   Fixed a slicing issue in an internal iterator type
    (https://github.com/fmtlib/fmt/pull/1822). Thanks @BRevzin.

-   Fixed an issue in locale-specific integer formatting
    (https://github.com/fmtlib/fmt/issues/1927).

-   Fixed handling of exotic code unit types
    (https://github.com/fmtlib/fmt/issues/1870,
    mt/issues/1932).

-   Improved `FMT_ALWAYS_INLINE`
    (https://github.com/fmtlib/fmt/pull/1878). Thanks @jk-jeon.

-   Removed dependency on `windows.h`
    (https://github.com/fmtlib/fmt/pull/1900). Thanks @bernd5.

-   Optimized counting of decimal digits on MSVC
    (https://github.com/fmtlib/fmt/pull/1890). Thanks @mwinterb.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/1772,
    mt/pull/1775,
    mt/pull/1792,
    mt/pull/1838,
    mt/pull/1888,
    mt/pull/1918,
    mt/pull/1939).
    Thanks @leolchat, @pepsiman, @Klaim, @ravijanjam, @francesco-st and @udnaan.

-   Added the `FMT_REDUCE_INT_INSTANTIATIONS` CMake option that reduces
    the binary code size at the cost of some integer formatting
    performance. This can be useful for extremely memory-constrained
    embedded systems
    (https://github.com/fmtlib/fmt/issues/1778,
    mt/pull/1781). Thanks @kammce.

-   Added the `FMT_USE_INLINE_NAMESPACES` macro to control usage of
    inline namespaces
    (https://github.com/fmtlib/fmt/pull/1945). Thanks @darklukee.

-   Improved build configuration
    (https://github.com/fmtlib/fmt/pull/1760,
    mt/pull/1770,
    mt/issues/1779,
    mt/pull/1783,
    mt/pull/1823).
    Thanks @dvetutnev, @xvitaly, @tambry, @medithe and @martinwuehrer.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/1790,
    mt/pull/1802,
    mt/pull/1808,
    mt/issues/1810,
    mt/issues/1811,
    mt/pull/1812,
    mt/pull/1814,
    mt/pull/1816,
    mt/pull/1817,
    mt/pull/1818,
    mt/issues/1825,
    mt/pull/1836,
    mt/pull/1855,
    mt/pull/1856,
    mt/pull/1860,
    mt/pull/1877,
    mt/pull/1879,
    mt/pull/1880,
    mt/issues/1896,
    mt/pull/1897,
    mt/pull/1898,
    mt/issues/1904,
    mt/pull/1908,
    mt/issues/1911,
    mt/issues/1912,
    mt/issues/1928,
    mt/pull/1929,
    mt/issues/1935,
    mt/pull/1937,
    mt/pull/1942,
    mt/issues/1949).
    Thanks @TheQwertiest, @medithe, @martinwuehrer, @n16h7hunt3r, @Othereum,
    @gsjaardema, @AlexanderLanin, @gcerretani, @chronoxor, @noizefloor,
    @akohlmey, @jk-jeon, @rimathia, @rglarix, @moiwi, @heckad, @MarcDirven.
    @BartSiwek and @darklukee.

# 7.0.3 - 2020-08-06

-   Worked around broken `numeric_limits` for 128-bit integers
    (https://github.com/fmtlib/fmt/issues/1787).
-   Added error reporting on missing named arguments
    (https://github.com/fmtlib/fmt/issues/1796).
-   Stopped using 128-bit integers with clang-cl
    (https://github.com/fmtlib/fmt/pull/1800). Thanks @Kingcom.
-   Fixed issues in locale-specific integer formatting
    (https://github.com/fmtlib/fmt/issues/1782,
    mt/issues/1801).

# 7.0.2 - 2020-07-29

-   Worked around broken `numeric_limits` for 128-bit integers
    (https://github.com/fmtlib/fmt/issues/1725).
-   Fixed compatibility with CMake 3.4
    (https://github.com/fmtlib/fmt/issues/1779).
-   Fixed handling of digit separators in locale-specific formatting
    (https://github.com/fmtlib/fmt/issues/1782).

# 7.0.1 - 2020-07-07

-   Updated the inline version namespace name.
-   Worked around a gcc bug in mangling of alias templates
    (https://github.com/fmtlib/fmt/issues/1753).
-   Fixed a linkage error on Windows
    (https://github.com/fmtlib/fmt/issues/1757). Thanks @Kurkin.
-   Fixed minor issues with the documentation.

# 7.0.0 - 2020-07-05

-   Reduced the library size. For example, on macOS a stripped test
    binary statically linked with {fmt} [shrank from \~368k to less than
    100k](http://www.zverovich.net/2020/05/21/reducing-library-size.html).

-   Added a simpler and more efficient [format string compilation
    API](https://fmt.dev/7.0.0/api.html#compile-api):

    ```c++
    #include <fmt/compile.h>

    // Converts 42 into std::string using the most efficient method and no
    // runtime format string processing.
    std::string s = fmt::format(FMT_COMPILE("{}"), 42);
    ```

    The old `fmt::compile` API is now deprecated.

-   Optimized integer formatting: `format_to` with format string
    compilation and a stack-allocated buffer is now [faster than
    to_chars on both libc++ and
    libstdc++](http://www.zverovich.net/2020/06/13/fast-int-to-string-revisited.html).

-   Optimized handling of small format strings. For example,

    ```c++
    fmt::format("Result: {}: ({},{},{},{})", str1, str2, str3, str4, str5)
    ```

    is now \~40% faster
    (https://github.com/fmtlib/fmt/issues/1685).

-   Applied extern templates to improve compile times when using the
    core API and `fmt/format.h`
    (https://github.com/fmtlib/fmt/issues/1452). For example,
    on macOS with clang the compile time of a test translation unit
    dropped from 2.3s to 0.3s with `-O2` and from 0.6s to 0.3s with the
    default settings (`-O0`).

    Before (`-O2`):

        % time c++ -c test.cc -I include -std=c++17 -O2
        c++ -c test.cc -I include -std=c++17 -O2  2.22s user 0.08s system 99% cpu 2.311 total

    After (`-O2`):

        % time c++ -c test.cc -I include -std=c++17 -O2
        c++ -c test.cc -I include -std=c++17 -O2  0.26s user 0.04s system 98% cpu 0.303 total

    Before (default):

        % time c++ -c test.cc -I include -std=c++17
        c++ -c test.cc -I include -std=c++17  0.53s user 0.06s system 98% cpu 0.601 total

    After (default):

        % time c++ -c test.cc -I include -std=c++17
        c++ -c test.cc -I include -std=c++17  0.24s user 0.06s system 98% cpu 0.301 total

    It is still recommended to use `fmt/core.h` instead of
    `fmt/format.h` but the compile time difference is now smaller.
    Thanks @alex3d for the suggestion.

-   Named arguments are now stored on stack (no dynamic memory
    allocations) and the compiled code is more compact and efficient.
    For example

    ```c++
    #include <fmt/core.h>

    int main() {
      fmt::print("The answer is {answer}\n", fmt::arg("answer", 42));
    }
    ```

    compiles to just ([godbolt](https://godbolt.org/z/NcfEp_))

    ```asm
    .LC0:
            .string "answer"
    .LC1:
            .string "The answer is {answer}\n"
    main:
            sub     rsp, 56
            mov     edi, OFFSET FLAT:.LC1
            mov     esi, 23
            movabs  rdx, 4611686018427387905
            lea     rax, [rsp+32]
            lea     rcx, [rsp+16]
            mov     QWORD PTR [rsp+8], 1
            mov     QWORD PTR [rsp], rax
            mov     DWORD PTR [rsp+16], 42
            mov     QWORD PTR [rsp+32], OFFSET FLAT:.LC0
            mov     DWORD PTR [rsp+40], 0
            call    fmt::v6::vprint(fmt::v6::basic_string_view<char>,
                                    fmt::v6::format_args)
            xor     eax, eax
            add     rsp, 56
            ret

        .L.str.1:
                .asciz  "answer"
    ```

-   Implemented compile-time checks for dynamic width and precision
    (https://github.com/fmtlib/fmt/issues/1614):

    ```c++
    #include <fmt/format.h>

    int main() {
      fmt::print(FMT_STRING("{0:{1}}"), 42);
    }
    ```

    now gives a compilation error because argument 1 doesn\'t exist:

        In file included from test.cc:1:
        include/fmt/format.h:2726:27: error: constexpr variable 'invalid_format' must be
        initialized by a constant expression
          FMT_CONSTEXPR_DECL bool invalid_format =
                                  ^
        ...
        include/fmt/core.h:569:26: note: in call to
        '&checker(s, {}).context_->on_error(&"argument not found"[0])'
            if (id >= num_args_) on_error("argument not found");
                                ^

-   Added sentinel support to `fmt::join`
    (https://github.com/fmtlib/fmt/pull/1689)

    ```c++
    struct zstring_sentinel {};
    bool operator==(const char* p, zstring_sentinel) { return *p == '\0'; }
    bool operator!=(const char* p, zstring_sentinel) { return *p != '\0'; }

    struct zstring {
      const char* p;
      const char* begin() const { return p; }
      zstring_sentinel end() const { return {}; }
    };

    auto s = fmt::format("{}", fmt::join(zstring{"hello"}, "_"));
    // s == "h_e_l_l_o"
    ```

    Thanks @BRevzin.

-   Added support for named arguments, `clear` and `reserve` to
    `dynamic_format_arg_store`
    (https://github.com/fmtlib/fmt/issues/1655,
    mt/pull/1663,
    mt/pull/1674,
    mt/pull/1677). Thanks @vsolontsov-ll.

-   Added support for the `'c'` format specifier to integral types for
    compatibility with `std::format`
    (https://github.com/fmtlib/fmt/issues/1652).

-   Replaced the `'n'` format specifier with `'L'` for compatibility
    with `std::format`
    (https://github.com/fmtlib/fmt/issues/1624). The `'n'`
    specifier can be enabled via the `FMT_DEPRECATED_N_SPECIFIER` macro.

-   The `'='` format specifier is now disabled by default for
    compatibility with `std::format`. It can be enabled via the
    `FMT_DEPRECATED_NUMERIC_ALIGN` macro.

-   Removed the following deprecated APIs:

    -   `FMT_STRING_ALIAS` and `fmt` macros - replaced by `FMT_STRING`
    -   `fmt::basic_string_view::char_type` - replaced by
        `fmt::basic_string_view::value_type`
    -   `convert_to_int`
    -   `format_arg_store::types`
    -   `*parse_context` - replaced by `*format_parse_context`
    -   `FMT_DEPRECATED_INCLUDE_OS`
    -   `FMT_DEPRECATED_PERCENT` - incompatible with `std::format`
    -   `*writer` - replaced by compiled format API

-   Renamed the `internal` namespace to `detail`
    (https://github.com/fmtlib/fmt/issues/1538). The former is
    still provided as an alias if the `FMT_USE_INTERNAL` macro is
    defined.

-   Improved compatibility between `fmt::printf` with the standard specs
    (https://github.com/fmtlib/fmt/issues/1595,
    mt/pull/1682,
    mt/pull/1683,
    mt/pull/1687,
    mt/pull/1699). Thanks @rimathia.

-   Fixed handling of `operator<<` overloads that use `copyfmt`
    (https://github.com/fmtlib/fmt/issues/1666).

-   Added the `FMT_OS` CMake option to control inclusion of OS-specific
    APIs in the fmt target. This can be useful for embedded platforms
    (https://github.com/fmtlib/fmt/issues/1654,
    mt/pull/1656). Thanks @kwesolowski.

-   Replaced `FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION` with the
    `FMT_FUZZ` macro to prevent interfering with fuzzing of projects
    using {fmt} (https://github.com/fmtlib/fmt/pull/1650).
    Thanks @asraa.

-   Fixed compatibility with emscripten
    (https://github.com/fmtlib/fmt/issues/1636,
    mt/pull/1637). Thanks @ArthurSonzogni.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/704,
    mt/pull/1643,
    mt/pull/1660,
    mt/pull/1681,
    mt/pull/1691,
    mt/pull/1706,
    mt/pull/1714,
    mt/pull/1721,
    mt/pull/1739,
    mt/pull/1740,
    mt/pull/1741,
    mt/pull/1751).
    Thanks @senior7515, @lsr0, @puetzk, @fpelliccioni, Alexey Kuzmenko, @jelly,
    @claremacrae, @jiapengwen, @gsjaardema and @alexey-milovidov.

-   Implemented various build configuration fixes and improvements
    (https://github.com/fmtlib/fmt/pull/1603,
    mt/pull/1657,
    mt/pull/1702,
    mt/pull/1728).
    Thanks @scramsby, @jtojnar, @orivej and @flagarde.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/1616,
    mt/issues/1620,
    mt/issues/1622,
    mt/issues/1625,
    mt/pull/1627,
    mt/issues/1628,
    mt/pull/1629,
    mt/issues/1631,
    mt/pull/1633,
    mt/pull/1649,
    mt/issues/1658,
    mt/pull/1661,
    mt/pull/1667,
    mt/issues/1668,
    mt/pull/1669,
    mt/issues/1692,
    mt/pull/1696,
    mt/pull/1697,
    mt/issues/1707,
    mt/pull/1712,
    mt/pull/1716,
    mt/pull/1722,
    mt/issues/1724,
    mt/pull/1729,
    mt/pull/1738,
    mt/issues/1742,
    mt/issues/1743,
    mt/pull/1744,
    mt/issues/1747,
    mt/pull/1750).
    Thanks @gsjaardema, @gabime, @johnor, @Kurkin, @invexed, @peterbell10,
    @daixtrose, @petrutlucian94, @Neargye, @ambitslix, @gabime, @erthink,
    @tohammer and @0x8000-0000.

# 6.2.1 - 2020-05-09

-   Fixed ostream support in `sprintf`
    (https://github.com/fmtlib/fmt/issues/1631).
-   Fixed type detection when using implicit conversion to `string_view`
    and ostream `operator<<` inconsistently
    (https://github.com/fmtlib/fmt/issues/1662).

# 6.2.0 - 2020-04-05

-   Improved error reporting when trying to format an object of a
    non-formattable type:

    ```c++
    fmt::format("{}", S());
    ```

    now gives:

        include/fmt/core.h:1015:5: error: static_assert failed due to requirement
        'formattable' "Cannot format argument. To make type T formattable provide a
        formatter<T> specialization:
        https://fmt.dev/latest/api.html#formatting-user-defined-types"
            static_assert(
            ^
        ...
        note: in instantiation of function template specialization
        'fmt::v6::format<char [3], S, char>' requested here
          fmt::format("{}", S());
               ^

    if `S` is not formattable.

-   Reduced the library size by \~10%.

-   Always print decimal point if `#` is specified
    (https://github.com/fmtlib/fmt/issues/1476,
    mt/issues/1498):

    ```c++
    fmt::print("{:#.0f}", 42.0);
    ```

    now prints `42.`

-   Implemented the `'L'` specifier for locale-specific numeric
    formatting to improve compatibility with `std::format`. The `'n'`
    specifier is now deprecated and will be removed in the next major
    release.

-   Moved OS-specific APIs such as `windows_error` from `fmt/format.h`
    to `fmt/os.h`. You can define `FMT_DEPRECATED_INCLUDE_OS` to
    automatically include `fmt/os.h` from `fmt/format.h` for
    compatibility but this will be disabled in the next major release.

-   Added precision overflow detection in floating-point formatting.

-   Implemented detection of invalid use of `fmt::arg`.

-   Used `type_identity` to block unnecessary template argument
    deduction. Thanks Tim Song.

-   Improved UTF-8 handling
    (https://github.com/fmtlib/fmt/issues/1109):

    ```c++
    fmt::print("┌{0:─^{2}}┐\n"
               "│{1: ^{2}}│\n"
               "└{0:─^{2}}┘\n", "", "Привет, мир!", 20);
    ```

    now prints:

        ┌────────────────────┐
        │    Привет, мир!    │
        └────────────────────┘

    on systems that support Unicode.

-   Added experimental dynamic argument storage
    (https://github.com/fmtlib/fmt/issues/1170,
    mt/pull/1584):

    ```c++
    fmt::dynamic_format_arg_store<fmt::format_context> store;
    store.push_back("answer");
    store.push_back(42);
    fmt::vprint("The {} is {}.\n", store);
    ```

    prints:

        The answer is 42.

    Thanks @vsolontsov-ll.

-   Made `fmt::join` accept `initializer_list`
    (https://github.com/fmtlib/fmt/pull/1591). Thanks @Rapotkinnik.

-   Fixed handling of empty tuples
    (https://github.com/fmtlib/fmt/issues/1588).

-   Fixed handling of output iterators in `format_to_n`
    (https://github.com/fmtlib/fmt/issues/1506).

-   Fixed formatting of `std::chrono::duration` types to wide output
    (https://github.com/fmtlib/fmt/pull/1533). Thanks @zeffy.

-   Added const `begin` and `end` overload to buffers
    (https://github.com/fmtlib/fmt/pull/1553). Thanks @dominicpoeschko.

-   Added the ability to disable floating-point formatting via
    `FMT_USE_FLOAT`, `FMT_USE_DOUBLE` and `FMT_USE_LONG_DOUBLE` macros
    for extremely memory-constrained embedded system
    (https://github.com/fmtlib/fmt/pull/1590). Thanks @albaguirre.

-   Made `FMT_STRING` work with `constexpr` `string_view`
    (https://github.com/fmtlib/fmt/pull/1589). Thanks @scramsby.

-   Implemented a minor optimization in the format string parser
    (https://github.com/fmtlib/fmt/pull/1560). Thanks @IkarusDeveloper.

-   Improved attribute detection
    (https://github.com/fmtlib/fmt/pull/1469,
    mt/pull/1475,
    mt/pull/1576).
    Thanks @federico-busato, @chronoxor and @refnum.

-   Improved documentation
    (https://github.com/fmtlib/fmt/pull/1481,
    mt/pull/1523).
    Thanks @JackBoosY and @imba-tjd.

-   Fixed symbol visibility on Linux when compiling with
    `-fvisibility=hidden`
    (https://github.com/fmtlib/fmt/pull/1535). Thanks @milianw.

-   Implemented various build configuration fixes and improvements
    (https://github.com/fmtlib/fmt/issues/1264,
    mt/issues/1460,
    mt/pull/1534,
    mt/issues/1536,
    mt/issues/1545,
    mt/pull/1546,
    mt/issues/1566,
    mt/pull/1582,
    mt/issues/1597,
    mt/pull/1598).
    Thanks @ambitslix, @jwillikers and @stac47.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/1433,
    mt/issues/1461,
    mt/pull/1470,
    mt/pull/1480,
    mt/pull/1485,
    mt/pull/1492,
    mt/issues/1493,
    mt/issues/1504,
    mt/pull/1505,
    mt/pull/1512,
    mt/issues/1515,
    mt/pull/1516,
    mt/pull/1518,
    mt/pull/1519,
    mt/pull/1520,
    mt/pull/1521,
    mt/pull/1522,
    mt/issues/1524,
    mt/pull/1530,
    mt/issues/1531,
    mt/pull/1532,
    mt/issues/1539,
    mt/issues/1547,
    mt/issues/1548,
    mt/pull/1554,
    mt/issues/1567,
    mt/pull/1568,
    mt/pull/1569,
    mt/pull/1571,
    mt/pull/1573,
    mt/pull/1575,
    mt/pull/1581,
    mt/issues/1583,
    mt/issues/1586,
    mt/issues/1587,
    mt/issues/1594,
    mt/pull/1596,
    mt/issues/1604,
    mt/pull/1606,
    mt/issues/1607,
    mt/issues/1609).
    Thanks @marti4d, @iPherian, @parkertomatoes, @gsjaardema, @chronoxor,
    @DanielaE, @torsten48, @tohammer, @lefticus, @ryusakki, @adnsv, @fghzxm,
    @refnum, @pramodk, @Spirrwell and @scramsby.

# 6.1.2 - 2019-12-11

-   Fixed ABI compatibility with `libfmt.so.6.0.0`
    (https://github.com/fmtlib/fmt/issues/1471).
-   Fixed handling types convertible to `std::string_view`
    (https://github.com/fmtlib/fmt/pull/1451). Thanks @denizevrenci.
-   Made CUDA test an opt-in enabled via the `FMT_CUDA_TEST` CMake
    option.
-   Fixed sign conversion warnings
    (https://github.com/fmtlib/fmt/pull/1440). Thanks @0x8000-0000.

# 6.1.1 - 2019-12-04

-   Fixed shared library build on Windows
    (https://github.com/fmtlib/fmt/pull/1443,
    mt/issues/1445,
    mt/pull/1446,
    mt/issues/1450).
    Thanks @egorpugin and @bbolli.
-   Added a missing decimal point in exponent notation with trailing
    zeros.
-   Removed deprecated `format_arg_store::TYPES`.

# 6.1.0 - 2019-12-01

-   {fmt} now formats IEEE 754 `float` and `double` using the shortest
    decimal representation with correct rounding by default:

    ```c++
    #include <cmath>
    #include <fmt/core.h>

    int main() {
      fmt::print("{}", M_PI);
    }
    ```

    prints `3.141592653589793`.

-   Made the fast binary to decimal floating-point formatter the
    default, simplified it and improved performance. {fmt} is now 15
    times faster than libc++\'s `std::ostringstream`, 11 times faster
    than `printf` and 10% faster than double-conversion on
    dtoa-benchmark:

    | Function      | Time (ns) | Speedup |
    | ------------- | --------: | ------: |
    | ostringstream | 1,346.30  | 1.00x   |
    | ostrstream    | 1,195.74  | 1.13x   |
    | sprintf       | 995.08    | 1.35x   |
    | doubleconv    | 99.10     | 13.59x  |
    | fmt           | 88.34     | 15.24x  |

    ![](https://user-images.githubusercontent.com/576385/69767160-cdaca400-112f-11ea-9fc5-347c9f83caad.png)

-   {fmt} no longer converts `float` arguments to `double`. In
    particular this improves the default (shortest) representation of
    floats and makes `fmt::format` consistent with `std::format` specs
    (https://github.com/fmtlib/fmt/issues/1336,
    mt/issues/1353,
    mt/pull/1360,
    mt/pull/1361):

    ```c++
    fmt::print("{}", 0.1f);
    ```

    prints `0.1` instead of `0.10000000149011612`.

    Thanks @orivej.

-   Made floating-point formatting output consistent with
    `printf`/iostreams
    (https://github.com/fmtlib/fmt/issues/1376,
    mt/issues/1417).

-   Added support for 128-bit integers
    (https://github.com/fmtlib/fmt/pull/1287):

    ```c++
    fmt::print("{}", std::numeric_limits<__int128_t>::max());
    ```

    prints `170141183460469231731687303715884105727`.

    Thanks @denizevrenci.

-   The overload of `print` that takes `text_style` is now atomic, i.e.
    the output from different threads doesn\'t interleave
    (https://github.com/fmtlib/fmt/pull/1351). Thanks @tankiJong.

-   Made compile time in the header-only mode \~20% faster by reducing
    the number of template instantiations. `wchar_t` overload of
    `vprint` was moved from `fmt/core.h` to `fmt/format.h`.

-   Added an overload of `fmt::join` that works with tuples
    (https://github.com/fmtlib/fmt/issues/1322,
    mt/pull/1330):

    ```c++
    #include <tuple>
    #include <fmt/ranges.h>

    int main() {
      std::tuple<char, int, float> t{'a', 1, 2.0f};
      fmt::print("{}", t);
    }
    ```

    prints `('a', 1, 2.0)`.

    Thanks @jeremyong.

-   Changed formatting of octal zero with prefix from \"00\" to \"0\":

    ```c++
    fmt::print("{:#o}", 0);
    ```

    prints `0`.

-   The locale is now passed to ostream insertion (`<<`) operators
    (https://github.com/fmtlib/fmt/pull/1406):

    ```c++
    #include <fmt/locale.h>
    #include <fmt/ostream.h>

    struct S {
      double value;
    };

    std::ostream& operator<<(std::ostream& os, S s) {
      return os << s.value;
    }

    int main() {
      auto s = fmt::format(std::locale("fr_FR.UTF-8"), "{}", S{0.42});
      // s == "0,42"
    }
    ```

    Thanks @dlaugt.

-   Locale-specific number formatting now uses grouping
    (https://github.com/fmtlib/fmt/issues/1393,
    mt/pull/1394). Thanks @skrdaniel.

-   Fixed handling of types with deleted implicit rvalue conversion to
    `const char**` (https://github.com/fmtlib/fmt/issues/1421):

    ```c++
    struct mystring {
      operator const char*() const&;
      operator const char*() &;
      operator const char*() const&& = delete;
      operator const char*() && = delete;
    };
    mystring str;
    fmt::print("{}", str); // now compiles
    ```

-   Enums are now mapped to correct underlying types instead of `int`
    (https://github.com/fmtlib/fmt/pull/1286). Thanks @agmt.

-   Enum classes are no longer implicitly converted to `int`
    (https://github.com/fmtlib/fmt/issues/1424).

-   Added `basic_format_parse_context` for consistency with C++20
    `std::format` and deprecated `basic_parse_context`.

-   Fixed handling of UTF-8 in precision
    (https://github.com/fmtlib/fmt/issues/1389,
    mt/pull/1390). Thanks @tajtiattila.

-   {fmt} can now be installed on Linux, macOS and Windows with
    [Conda](https://docs.conda.io/en/latest/) using its
    [conda-forge](https://conda-forge.org)
    package
    (https://github.com/fmtlib/fmt/pull/1410):

        conda install -c conda-forge fmt

    Thanks @tdegeus.

-   Added a CUDA test (https://github.com/fmtlib/fmt/pull/1285,
    mt/pull/1317).
    Thanks @luncliff and @risa2000.

-   Improved documentation
    (https://github.com/fmtlib/fmt/pull/1276,
    mt/issues/1291,
    mt/issues/1296,
    mt/pull/1315,
    mt/pull/1332,
    mt/pull/1337,
    mt/issues/1395
    mt/pull/1418).
    Thanks @waywardmonkeys, @pauldreik and @jackoalan.

-   Various code improvements
    (https://github.com/fmtlib/fmt/pull/1358,
    mt/pull/1407).
    Thanks @orivej and @dpacbach.

-   Fixed compile-time format string checks for user-defined types
    (https://github.com/fmtlib/fmt/issues/1292).

-   Worked around a false positive in `unsigned-integer-overflow` sanitizer
    (https://github.com/fmtlib/fmt/issues/1377).

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/issues/1273,
    mt/pull/1278,
    mt/pull/1280,
    mt/issues/1281,
    mt/issues/1288,
    mt/pull/1290,
    mt/pull/1301,
    mt/issues/1305,
    mt/issues/1306,
    mt/issues/1309,
    mt/pull/1312,
    mt/issues/1313,
    mt/issues/1316,
    mt/issues/1319,
    mt/pull/1320,
    mt/pull/1326,
    mt/pull/1328,
    mt/issues/1344,
    mt/pull/1345,
    mt/pull/1347,
    mt/pull/1349,
    mt/issues/1354,
    mt/issues/1362,
    mt/issues/1366,
    mt/pull/1364,
    mt/pull/1370,
    mt/pull/1371,
    mt/issues/1385,
    mt/issues/1388,
    mt/pull/1397,
    mt/pull/1414,
    mt/pull/1416,
    mt/issues/1422
    mt/pull/1427,
    mt/issues/1431,
    mt/pull/1433).
    Thanks @hhb, @gsjaardema, @gabime, @neheb, @vedranmiletic, @dkavolis,
    @mwinterb, @orivej, @denizevrenci, @leonklingele, @chronoxor, @kent-tri,
    @0x8000-0000 and @marti4d.

# 6.0.0 - 2019-08-26

-   Switched to the [MIT license](
    mt/blob/5a4b24613ba16cc689977c3b5bd8274a3ba1dd1f/LICENSE.rst)
    with an optional exception that allows distributing binary code
    without attribution.

-   Floating-point formatting is now locale-independent by default:

    ```c++
    #include <locale>
    #include <fmt/core.h>

    int main() {
      std::locale::global(std::locale("ru_RU.UTF-8"));
      fmt::print("value = {}", 4.2);
    }
    ```

    prints \"value = 4.2\" regardless of the locale.

    For locale-specific formatting use the `n` specifier:

    ```c++
    std::locale::global(std::locale("ru_RU.UTF-8"));
    fmt::print("value = {:n}", 4.2);
    ```

    prints \"value = 4,2\".

-   Added an experimental Grisu floating-point formatting algorithm
    implementation (disabled by default). To enable it compile with the
    `FMT_USE_GRISU` macro defined to 1:

    ```c++
    #define FMT_USE_GRISU 1
    #include <fmt/format.h>

    auto s = fmt::format("{}", 4.2); // formats 4.2 using Grisu
    ```

    With Grisu enabled, {fmt} is 13x faster than `std::ostringstream`
    (libc++) and 10x faster than `sprintf` on
    dtoa-benchmark ([full
    results](https://fmt.dev/unknown_mac64_clang10.0.html)):

    ![](https://user-images.githubusercontent.com/576385/54883977-9fe8c000-4e28-11e9-8bde-272d122e7c52.jpg)

-   Separated formatting and parsing contexts for consistency with
    [C++20 std::format](http://eel.is/c++draft/format), removing the
    undocumented `basic_format_context::parse_context()` function.

-   Added oss-fuzz support
    (https://github.com/fmtlib/fmt/pull/1199). Thanks @pauldreik.

-   `formatter` specializations now always take precedence over
    `operator<<` (https://github.com/fmtlib/fmt/issues/952):

    ```c++
    #include <iostream>
    #include <fmt/ostream.h>

    struct S {};

    std::ostream& operator<<(std::ostream& os, S) {
      return os << 1;
    }

    template <>
    struct fmt::formatter<S> : fmt::formatter<int> {
      auto format(S, format_context& ctx) {
        return formatter<int>::format(2, ctx);
      }
    };

    int main() {
      std::cout << S() << "\n"; // prints 1 using operator<<
      fmt::print("{}\n", S());  // prints 2 using formatter
    }
    ```

-   Introduced the experimental `fmt::compile` function that does format
    string compilation
    (https://github.com/fmtlib/fmt/issues/618,
    mt/issues/1169,
    mt/pull/1171):

    ```c++
    #include <fmt/compile.h>

    auto f = fmt::compile<int>("{}");
    std::string s = fmt::format(f, 42); // can be called multiple times to
                                        // format different values
    // s == "42"
    ```

    It moves the cost of parsing a format string outside of the format
    function which can be beneficial when identically formatting many
    objects of the same types. Thanks @stryku.

-   Added experimental `%` format specifier that formats floating-point
    values as percentages
    (https://github.com/fmtlib/fmt/pull/1060,
    mt/pull/1069,
    mt/pull/1071):

    ```c++
    auto s = fmt::format("{:.1%}", 0.42); // s == "42.0%"
    ```

    Thanks @gawain-bolton.

-   Implemented precision for floating-point durations
    (https://github.com/fmtlib/fmt/issues/1004,
    mt/pull/1012):

    ```c++
    auto s = fmt::format("{:.1}", std::chrono::duration<double>(1.234));
    // s == 1.2s
    ```

    Thanks @DanielaE.

-   Implemented `chrono` format specifiers `%Q` and `%q` that give the
    value and the unit respectively
    (https://github.com/fmtlib/fmt/pull/1019):

    ```c++
    auto value = fmt::format("{:%Q}", 42s); // value == "42"
    auto unit  = fmt::format("{:%q}", 42s); // unit == "s"
    ```

    Thanks @DanielaE.

-   Fixed handling of dynamic width in chrono formatter:

    ```c++
    auto s = fmt::format("{0:{1}%H:%M:%S}", std::chrono::seconds(12345), 12);
    //                        ^ width argument index                     ^ width
    // s == "03:25:45    "
    ```

    Thanks Howard Hinnant.

-   Removed deprecated `fmt/time.h`. Use `fmt/chrono.h` instead.

-   Added `fmt::format` and `fmt::vformat` overloads that take
    `text_style` (https://github.com/fmtlib/fmt/issues/993,
    mt/pull/994):

    ```c++
    #include <fmt/color.h>

    std::string message = fmt::format(fmt::emphasis::bold | fg(fmt::color::red),
                                      "The answer is {}.", 42);
    ```

    Thanks @Naios.

-   Removed the deprecated color API (`print_colored`). Use the new API,
    namely `print` overloads that take `text_style` instead.

-   Made `std::unique_ptr` and `std::shared_ptr` formattable as pointers
    via `fmt::ptr` (https://github.com/fmtlib/fmt/pull/1121):

    ```c++
    std::unique_ptr<int> p = ...;
    fmt::print("{}", fmt::ptr(p)); // prints p as a pointer
    ```

    Thanks @sighingnow.

-   Made `print` and `vprint` report I/O errors
    (https://github.com/fmtlib/fmt/issues/1098,
    mt/pull/1099). Thanks @BillyDonahue.

-   Marked deprecated APIs with the `[[deprecated]]` attribute and
    removed internal uses of deprecated APIs
    (https://github.com/fmtlib/fmt/pull/1022). Thanks @eliaskosunen.

-   Modernized the codebase using more C++11 features and removing
    workarounds. Most importantly, `buffer_context` is now an alias
    template, so use `buffer_context<T>` instead of
    `buffer_context<T>::type`. These features require GCC 4.8 or later.

-   `formatter` specializations now always take precedence over implicit
    conversions to `int` and the undocumented `convert_to_int` trait is
    now deprecated.

-   Moved the undocumented `basic_writer`, `writer`, and `wwriter` types
    to the `internal` namespace.

-   Removed deprecated `basic_format_context::begin()`. Use `out()`
    instead.

-   Disallowed passing the result of `join` as an lvalue to prevent
    misuse.

-   Refactored the undocumented structs that represent parsed format
    specifiers to simplify the API and allow multibyte fill.

-   Moved SFINAE to template parameters to reduce symbol sizes.

-   Switched to `fputws` for writing wide strings so that it\'s no
    longer required to call `_setmode` on Windows
    (https://github.com/fmtlib/fmt/issues/1229,
    mt/pull/1243). Thanks @jackoalan.

-   Improved literal-based API
    (https://github.com/fmtlib/fmt/pull/1254). Thanks @sylveon.

-   Added support for exotic platforms without `uintptr_t` such as IBM i
    (AS/400) which has 128-bit pointers and only 64-bit integers
    (https://github.com/fmtlib/fmt/issues/1059).

-   Added [Sublime Text syntax highlighting config](
    mt/blob/master/support/C%2B%2B.sublime-syntax)
    (https://github.com/fmtlib/fmt/issues/1037). Thanks @Kronuz.

-   Added the `FMT_ENFORCE_COMPILE_STRING` macro to enforce the use of
    compile-time format strings
    (https://github.com/fmtlib/fmt/pull/1231). Thanks @jackoalan.

-   Stopped setting `CMAKE_BUILD_TYPE` if {fmt} is a subproject
    (https://github.com/fmtlib/fmt/issues/1081).

-   Various build improvements
    (https://github.com/fmtlib/fmt/pull/1039,
    mt/pull/1078,
    mt/pull/1091,
    mt/pull/1103,
    mt/pull/1177).
    Thanks @luncliff, @jasonszang, @olafhering, @Lecetem and @pauldreik.

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/1049,
    mt/pull/1051,
    mt/pull/1083,
    mt/pull/1113,
    mt/pull/1114,
    mt/issues/1146,
    mt/issues/1180,
    mt/pull/1250,
    mt/pull/1252,
    mt/pull/1265).
    Thanks @mikelui, @foonathan, @BillyDonahue, @jwakely, @kaisbe and
    @sdebionne.

-   Fixed ambiguous formatter specialization in `fmt/ranges.h`
    (https://github.com/fmtlib/fmt/issues/1123).

-   Fixed formatting of a non-empty `std::filesystem::path` which is an
    infinitely deep range of its components
    (https://github.com/fmtlib/fmt/issues/1268).

-   Fixed handling of general output iterators when formatting
    characters (https://github.com/fmtlib/fmt/issues/1056,
    mt/pull/1058). Thanks @abolz.

-   Fixed handling of output iterators in `formatter` specialization for
    ranges (https://github.com/fmtlib/fmt/issues/1064).

-   Fixed handling of exotic character types
    (https://github.com/fmtlib/fmt/issues/1188).

-   Made chrono formatting work with exceptions disabled
    (https://github.com/fmtlib/fmt/issues/1062).

-   Fixed DLL visibility issues
    (https://github.com/fmtlib/fmt/pull/1134,
    mt/pull/1147). Thanks @denchat.

-   Disabled the use of UDL template extension on GCC 9
    (https://github.com/fmtlib/fmt/issues/1148).

-   Removed misplaced `format` compile-time checks from `printf`
    (https://github.com/fmtlib/fmt/issues/1173).

-   Fixed issues in the experimental floating-point formatter
    (https://github.com/fmtlib/fmt/issues/1072,
    mt/issues/1129,
    mt/issues/1153,
    mt/pull/1155,
    mt/issues/1210,
    mt/issues/1222). Thanks @alabuzhev.

-   Fixed bugs discovered by fuzzing or during fuzzing integration
    (https://github.com/fmtlib/fmt/issues/1124,
    mt/issues/1127,
    mt/issues/1132,
    mt/pull/1135,
    mt/issues/1136,
    mt/issues/1141,
    mt/issues/1142,
    mt/issues/1178,
    mt/issues/1179,
    mt/issues/1194). Thanks @pauldreik.

-   Fixed building tests on FreeBSD and Hurd
    (https://github.com/fmtlib/fmt/issues/1043). Thanks @jackyf.

-   Fixed various warnings and compilation issues
    (https://github.com/fmtlib/fmt/pull/998,
    mt/pull/1006,
    mt/issues/1008,
    mt/issues/1011,
    mt/issues/1025,
    mt/pull/1027,
    mt/pull/1028,
    mt/pull/1029,
    mt/pull/1030,
    mt/pull/1031,
    mt/pull/1054,
    mt/issues/1063,
    mt/pull/1068,
    mt/pull/1074,
    mt/pull/1075,
    mt/pull/1079,
    mt/pull/1086,
    mt/issues/1088,
    mt/pull/1089,
    mt/pull/1094,
    mt/issues/1101,
    mt/pull/1102,
    mt/issues/1105,
    mt/pull/1107,
    mt/issues/1115,
    mt/issues/1117,
    mt/issues/1118,
    mt/issues/1120,
    mt/issues/1123,
    mt/pull/1139,
    mt/issues/1140,
    mt/issues/1143,
    mt/pull/1144,
    mt/pull/1150,
    mt/pull/1151,
    mt/issues/1152,
    mt/issues/1154,
    mt/issues/1156,
    mt/pull/1159,
    mt/issues/1175,
    mt/issues/1181,
    mt/issues/1186,
    mt/pull/1187,
    mt/pull/1191,
    mt/issues/1197,
    mt/issues/1200,
    mt/issues/1203,
    mt/issues/1205,
    mt/pull/1206,
    mt/issues/1213,
    mt/issues/1214,
    mt/pull/1217,
    mt/issues/1228,
    mt/pull/1230,
    mt/issues/1232,
    mt/pull/1235,
    mt/pull/1236,
    mt/issues/1240).
    Thanks @DanielaE, @mwinterb, @eliaskosunen, @morinmorin, @ricco19,
    @waywardmonkeys, @chronoxor, @remyabel, @pauldreik, @gsjaardema, @rcane,
    @mocabe, @denchat, @cjdb, @HazardyKnusperkeks, @vedranmiletic, @jackoalan,
    @DaanDeMeyer and @starkmapper.

# 5.3.0 - 2018-12-28

-   Introduced experimental chrono formatting support:

    ```c++
    #include <fmt/chrono.h>

    int main() {
      using namespace std::literals::chrono_literals;
      fmt::print("Default format: {} {}\n", 42s, 100ms);
      fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
    }
    ```

    prints:

        Default format: 42s 100ms
        strftime-like format: 03:15:30

-   Added experimental support for emphasis (bold, italic, underline,
    strikethrough), colored output to a file stream, and improved
    colored formatting API
    (https://github.com/fmtlib/fmt/pull/961,
    mt/pull/967,
    mt/pull/973):

    ```c++
    #include <fmt/color.h>

    int main() {
      print(fg(fmt::color::crimson) | fmt::emphasis::bold,
            "Hello, {}!\n", "world");
      print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
            fmt::emphasis::underline, "Hello, {}!\n", "мир");
      print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
            "Hello, {}!\n", "世界");
    }
    ```

    prints the following on modern terminals with RGB color support:

    ![](https://user-images.githubusercontent.com/576385/50405788-b66e7500-076e-11e9-9592-7324d1f951d8.png)

    Thanks @Rakete1111.

-   Added support for 4-bit terminal colors
    (https://github.com/fmtlib/fmt/issues/968,
    mt/pull/974)

    ```c++
    #include <fmt/color.h>

    int main() {
      print(fg(fmt::terminal_color::red), "stop\n");
    }
    ```

    Note that these colors vary by terminal:

    ![](https://user-images.githubusercontent.com/576385/50405925-dbfc7e00-0770-11e9-9b85-333fab0af9ac.png)

    Thanks @Rakete1111.

-   Parameterized formatting functions on the type of the format string
    (https://github.com/fmtlib/fmt/issues/880,
    mt/pull/881,
    mt/pull/883,
    mt/pull/885,
    mt/pull/897,
    mt/issues/920). Any object of
    type `S` that has an overloaded `to_string_view(const S&)` returning
    `fmt::string_view` can be used as a format string:

    ```c++
    namespace my_ns {
    inline string_view to_string_view(const my_string& s) {
      return {s.data(), s.length()};
    }
    }

    std::string message = fmt::format(my_string("The answer is {}."), 42);
    ```

    Thanks @DanielaE.

-   Made `std::string_view` work as a format string
    (https://github.com/fmtlib/fmt/pull/898):

    ```c++
    auto message = fmt::format(std::string_view("The answer is {}."), 42);
    ```

    Thanks @DanielaE.

-   Added wide string support to compile-time format string checks
    (https://github.com/fmtlib/fmt/pull/924):

    ```c++
    print(fmt(L"{:f}"), 42); // compile-time error: invalid type specifier
    ```

    Thanks @XZiar.

-   Made colored print functions work with wide strings
    (https://github.com/fmtlib/fmt/pull/867):

    ```c++
    #include <fmt/color.h>

    int main() {
      print(fg(fmt::color::red), L"{}\n", 42);
    }
    ```

    Thanks @DanielaE.

-   Introduced experimental Unicode support
    (https://github.com/fmtlib/fmt/issues/628,
    mt/pull/891):

    ```c++
    using namespace fmt::literals;
    auto s = fmt::format("{:*^5}"_u, "🤡"_u); // s == "**🤡**"_u
    ```

-   Improved locale support:

    ```c++
    #include <fmt/locale.h>

    struct numpunct : std::numpunct<char> {
     protected:
      char do_thousands_sep() const override { return '~'; }
    };

    std::locale loc;
    auto s = fmt::format(std::locale(loc, new numpunct()), "{:n}", 1234567);
    // s == "1~234~567"
    ```

-   Constrained formatting functions on proper iterator types
    (https://github.com/fmtlib/fmt/pull/921). Thanks @DanielaE.

-   Added `make_printf_args` and `make_wprintf_args` functions
    (https://github.com/fmtlib/fmt/pull/934). Thanks @tnovotny.

-   Deprecated `fmt::visit`, `parse_context`, and `wparse_context`. Use
    `fmt::visit_format_arg`, `format_parse_context`, and
    `wformat_parse_context` instead.

-   Removed undocumented `basic_fixed_buffer` which has been superseded
    by the iterator-based API
    (https://github.com/fmtlib/fmt/issues/873,
    mt/pull/902). Thanks @superfunc.

-   Disallowed repeated leading zeros in an argument ID:

    ```c++
    fmt::print("{000}", 42); // error
    ```

-   Reintroduced support for gcc 4.4.

-   Fixed compilation on platforms with exotic `double`
    (https://github.com/fmtlib/fmt/issues/878).

-   Improved documentation
    (https://github.com/fmtlib/fmt/issues/164,
    mt/issues/877,
    mt/pull/901,
    mt/pull/906,
    mt/pull/979).
    Thanks @kookjr, @DarkDimius and @HecticSerenity.

-   Added pkgconfig support which makes it easier to consume the library
    from meson and other build systems
    (https://github.com/fmtlib/fmt/pull/916). Thanks @colemickens.

-   Various build improvements
    (https://github.com/fmtlib/fmt/pull/909,
    mt/pull/926,
    mt/pull/937,
    mt/pull/953,
    mt/pull/959).
    Thanks @tchaikov, @luncliff, @AndreasSchoenle, @hotwatermorning and @Zefz.

-   Improved `string_view` construction performance
    (https://github.com/fmtlib/fmt/pull/914). Thanks @gabime.

-   Fixed non-matching char types
    (https://github.com/fmtlib/fmt/pull/895). Thanks @DanielaE.

-   Fixed `format_to_n` with `std::back_insert_iterator`
    (https://github.com/fmtlib/fmt/pull/913). Thanks @DanielaE.

-   Fixed locale-dependent formatting
    (https://github.com/fmtlib/fmt/issues/905).

-   Fixed various compiler warnings and errors
    (https://github.com/fmtlib/fmt/pull/882,
    mt/pull/886,
    mt/pull/933,
    mt/pull/941,
    mt/issues/931,
    mt/pull/943,
    mt/pull/954,
    mt/pull/956,
    mt/pull/962,
    mt/issues/965,
    mt/issues/977,
    mt/pull/983,
    mt/pull/989).
    Thanks @Luthaf, @stevenhoving, @christinaa, @lgritz, @DanielaE,
    @0x8000-0000 and @liuping1997.

# 5.2.1 - 2018-09-21

-   Fixed `visit` lookup issues on gcc 7 & 8
    (https://github.com/fmtlib/fmt/pull/870). Thanks @medithe.
-   Fixed linkage errors on older gcc.
-   Prevented `fmt/range.h` from specializing `fmt::basic_string_view`
    (https://github.com/fmtlib/fmt/issues/865,
    mt/pull/868). Thanks @hhggit.
-   Improved error message when formatting unknown types
    (https://github.com/fmtlib/fmt/pull/872). Thanks @foonathan.
-   Disabled templated user-defined literals when compiled under nvcc
    (https://github.com/fmtlib/fmt/pull/875). Thanks @CandyGumdrop.
-   Fixed `format_to` formatting to `wmemory_buffer`
    (https://github.com/fmtlib/fmt/issues/874).

# 5.2.0 - 2018-09-13

-   Optimized format string parsing and argument processing which
    resulted in up to 5x speed up on long format strings and significant
    performance boost on various benchmarks. For example, version 5.2 is
    2.22x faster than 5.1 on decimal integer formatting with `format_to`
    (macOS, clang-902.0.39.2):

    | Method                     | Time, s         | Speedup |
    | -------------------------- | --------------: | ------: |
    | fmt::format 5.1            | 0.58            |         |
    | fmt::format 5.2            | 0.35            |   1.66x |
    | fmt::format_to 5.1         | 0.51            |         |
    | fmt::format_to 5.2         | 0.23            |   2.22x |
    | sprintf                    | 0.71            |         |
    | std::to_string             | 1.01            |         |
    | std::stringstream          | 1.73            |         |

-   Changed the `fmt` macro from opt-out to opt-in to prevent name
    collisions. To enable it define the `FMT_STRING_ALIAS` macro to 1
    before including `fmt/format.h`:

    ```c++
    #define FMT_STRING_ALIAS 1
    #include <fmt/format.h>
    std::string answer = format(fmt("{}"), 42);
    ```

-   Added compile-time format string checks to `format_to` overload that
    takes `fmt::memory_buffer`
    (https://github.com/fmtlib/fmt/issues/783):

    ```c++
    fmt::memory_buffer buf;
    // Compile-time error: invalid type specifier.
    fmt::format_to(buf, fmt("{:d}"), "foo");
    ```

-   Moved experimental color support to `fmt/color.h` and enabled the
    new API by default. The old API can be enabled by defining the
    `FMT_DEPRECATED_COLORS` macro.

-   Added formatting support for types explicitly convertible to
    `fmt::string_view`:

    ```c++
    struct foo {
      explicit operator fmt::string_view() const { return "foo"; }
    };
    auto s = format("{}", foo());
    ```

    In particular, this makes formatting function work with
    `folly::StringPiece`.

-   Implemented preliminary support for `char*_t` by replacing the
    `format` function overloads with a single function template
    parameterized on the string type.

-   Added support for dynamic argument lists
    (https://github.com/fmtlib/fmt/issues/814,
    mt/pull/819). Thanks @MikePopoloski.

-   Reduced executable size overhead for embedded targets using newlib
    nano by making locale dependency optional
    (https://github.com/fmtlib/fmt/pull/839). Thanks @teajay-fr.

-   Keep `noexcept` specifier when exceptions are disabled
    (https://github.com/fmtlib/fmt/issues/801,
    mt/pull/810). Thanks @qis.

-   Fixed formatting of user-defined types providing `operator<<` with
    `format_to_n` (https://github.com/fmtlib/fmt/pull/806).
    Thanks @mkurdej.

-   Fixed dynamic linkage of new symbols
    (https://github.com/fmtlib/fmt/issues/808).

-   Fixed global initialization issue
    (https://github.com/fmtlib/fmt/issues/807):

    ```c++
    // This works on compilers with constexpr support.
    static const std::string answer = fmt::format("{}", 42);
    ```

-   Fixed various compiler warnings and errors
    (https://github.com/fmtlib/fmt/pull/804,
    mt/issues/809,
    mt/pull/811,
    mt/issues/822,
    mt/pull/827,
    mt/issues/830,
    mt/pull/838,
    mt/issues/843,
    mt/pull/844,
    mt/issues/851,
    mt/pull/852,
    mt/pull/854).
    Thanks @henryiii, @medithe, and @eliasdaler.

# 5.1.0 - 2018-07-05

-   Added experimental support for RGB color output enabled with the
    `FMT_EXTENDED_COLORS` macro:

    ```c++
    #define FMT_EXTENDED_COLORS
    #define FMT_HEADER_ONLY // or compile fmt with FMT_EXTENDED_COLORS defined
    #include <fmt/format.h>

    fmt::print(fmt::color::steel_blue, "Some beautiful text");
    ```

    The old API (the `print_colored` and `vprint_colored` functions and
    the `color` enum) is now deprecated.
    (https://github.com/fmtlib/fmt/issues/762
    mt/pull/767). thanks @Remotion.

-   Added quotes to strings in ranges and tuples
    (https://github.com/fmtlib/fmt/pull/766). Thanks @Remotion.

-   Made `format_to` work with `basic_memory_buffer`
    (https://github.com/fmtlib/fmt/issues/776).

-   Added `vformat_to_n` and `wchar_t` overload of `format_to_n`
    (https://github.com/fmtlib/fmt/issues/764,
    mt/issues/769).

-   Made `is_range` and `is_tuple_like` part of public (experimental)
    API to allow specialization for user-defined types
    (https://github.com/fmtlib/fmt/issues/751,
    mt/pull/759). Thanks @drrlvn.

-   Added more compilers to continuous integration and increased
    `FMT_PEDANTIC` warning levels
    (https://github.com/fmtlib/fmt/pull/736). Thanks @eliaskosunen.

-   Fixed compilation with MSVC 2013.

-   Fixed handling of user-defined types in `format_to`
    (https://github.com/fmtlib/fmt/issues/793).

-   Forced linking of inline `vformat` functions into the library
    (https://github.com/fmtlib/fmt/issues/795).

-   Fixed incorrect call to on_align in `'{:}='`
    (https://github.com/fmtlib/fmt/issues/750).

-   Fixed floating-point formatting to a non-back_insert_iterator with
    sign & numeric alignment specified
    (https://github.com/fmtlib/fmt/issues/756).

-   Fixed formatting to an array with `format_to_n`
    (https://github.com/fmtlib/fmt/issues/778).

-   Fixed formatting of more than 15 named arguments
    (https://github.com/fmtlib/fmt/issues/754).

-   Fixed handling of compile-time strings when including
    `fmt/ostream.h`. (https://github.com/fmtlib/fmt/issues/768).

-   Fixed various compiler warnings and errors
    (https://github.com/fmtlib/fmt/issues/742,
    mt/issues/748,
    mt/issues/752,
    mt/issues/770,
    mt/pull/775,
    mt/issues/779,
    mt/pull/780,
    mt/pull/790,
    mt/pull/792,
    mt/pull/800).
    Thanks @Remotion, @gabime, @foonathan, @Dark-Passenger and @0x8000-0000.

# 5.0.0 - 2018-05-21

-   Added a requirement for partial C++11 support, most importantly
    variadic templates and type traits, and dropped `FMT_VARIADIC_*`
    emulation macros. Variadic templates are available since GCC 4.4,
    Clang 2.9 and MSVC 18.0 (2013). For older compilers use {fmt}
    version 4.x
    which continues to be maintained and works with C++98 compilers.

-   Renamed symbols to follow standard C++ naming conventions and
    proposed a subset of the library for standardization in [P0645R2
    Text Formatting](https://wg21.link/P0645).

-   Implemented `constexpr` parsing of format strings and [compile-time
    format string
    checks](https://fmt.dev/latest/api.html#compile-time-format-string-checks).
    For example

    ```c++
    #include <fmt/format.h>

    std::string s = format(fmt("{:d}"), "foo");
    ```

    gives a compile-time error because `d` is an invalid specifier for
    strings ([godbolt](https://godbolt.org/g/rnCy9Q)):

        ...
        <source>:4:19: note: in instantiation of function template specialization 'fmt::v5::format<S, char [4]>' requested here
          std::string s = format(fmt("{:d}"), "foo");
                          ^
        format.h:1337:13: note: non-constexpr function 'on_error' cannot be used in a constant expression
            handler.on_error("invalid type specifier");

    Compile-time checks require relaxed `constexpr` (C++14 feature)
    support. If the latter is not available, checks will be performed at
    runtime.

-   Separated format string parsing and formatting in the extension API
    to enable compile-time format string processing. For example

    ```c++
    struct Answer {};

    namespace fmt {
    template <>
    struct formatter<Answer> {
      constexpr auto parse(parse_context& ctx) {
        auto it = ctx.begin();
        spec = *it;
        if (spec != 'd' && spec != 's')
          throw format_error("invalid specifier");
        return ++it;
      }

      template <typename FormatContext>
      auto format(Answer, FormatContext& ctx) {
        return spec == 's' ?
          format_to(ctx.begin(), "{}", "fourty-two") :
          format_to(ctx.begin(), "{}", 42);
      }

      char spec = 0;
    };
    }

    std::string s = format(fmt("{:x}"), Answer());
    ```

    gives a compile-time error due to invalid format specifier
    ([godbolt](https://godbolt.org/g/2jQ1Dv)):

        ...
        <source>:12:45: error: expression '<throw-expression>' is not a constant expression
               throw format_error("invalid specifier");

-   Added [iterator
    support](https://fmt.dev/latest/api.html#output-iterator-support):

    ```c++
    #include <vector>
    #include <fmt/format.h>

    std::vector<char> out;
    fmt::format_to(std::back_inserter(out), "{}", 42);
    ```

-   Added the
    [format_to_n](https://fmt.dev/latest/api.html#_CPPv2N3fmt11format_to_nE8OutputItNSt6size_tE11string_viewDpRK4Args)
    function that restricts the output to the specified number of
    characters (https://github.com/fmtlib/fmt/issues/298):

    ```c++
    char out[4];
    fmt::format_to_n(out, sizeof(out), "{}", 12345);
    // out == "1234" (without terminating '\0')
    ```

-   Added the [formatted_size](
    https://fmt.dev/latest/api.html#_CPPv2N3fmt14formatted_sizeE11string_viewDpRK4Args)
    function for computing the output size:

    ```c++
    #include <fmt/format.h>

    auto size = fmt::formatted_size("{}", 12345); // size == 5
    ```

-   Improved compile times by reducing dependencies on standard headers
    and providing a lightweight [core
    API](https://fmt.dev/latest/api.html#core-api):

    ```c++
    #include <fmt/core.h>

    fmt::print("The answer is {}.", 42);
    ```

    See Compile time and code
    bloat.

-   Added the [make_format_args](
    https://fmt.dev/latest/api.html#_CPPv2N3fmt16make_format_argsEDpRK4Args)
    function for capturing formatting arguments:

    ```c++
    // Prints formatted error message.
    void vreport_error(const char *format, fmt::format_args args) {
      fmt::print("Error: ");
      fmt::vprint(format, args);
    }
    template <typename... Args>
    void report_error(const char *format, const Args & ... args) {
      vreport_error(format, fmt::make_format_args(args...));
    }
    ```

-   Added the `make_printf_args` function for capturing `printf`
    arguments (https://github.com/fmtlib/fmt/issues/687,
    mt/pull/694). Thanks @Kronuz.

-   Added prefix `v` to non-variadic functions taking `format_args` to
    distinguish them from variadic ones:

    ```c++
    std::string vformat(string_view format_str, format_args args);

    template <typename... Args>
    std::string format(string_view format_str, const Args & ... args);
    ```

-   Added experimental support for formatting ranges, containers and
    tuple-like types in `fmt/ranges.h`
    (https://github.com/fmtlib/fmt/pull/735):

    ```c++
    #include <fmt/ranges.h>

    std::vector<int> v = {1, 2, 3};
    fmt::print("{}", v); // prints {1, 2, 3}
    ```

    Thanks @Remotion.

-   Implemented `wchar_t` date and time formatting
    (https://github.com/fmtlib/fmt/pull/712):

    ```c++
    #include <fmt/time.h>

    std::time_t t = std::time(nullptr);
    auto s = fmt::format(L"The date is {:%Y-%m-%d}.", *std::localtime(&t));
    ```

    Thanks @DanielaE.

-   Provided more wide string overloads
    (https://github.com/fmtlib/fmt/pull/724). Thanks @DanielaE.

-   Switched from a custom null-terminated string view class to
    `string_view` in the format API and provided `fmt::string_view`
    which implements a subset of `std::string_view` API for pre-C++17
    systems.

-   Added support for `std::experimental::string_view`
    (https://github.com/fmtlib/fmt/pull/607):

    ```c++
    #include <fmt/core.h>
    #include <experimental/string_view>

    fmt::print("{}", std::experimental::string_view("foo"));
    ```

    Thanks @virgiliofornazin.

-   Allowed mixing named and automatic arguments:

    ```c++
    fmt::format("{} {two}", 1, fmt::arg("two", 2));
    ```

-   Removed the write API in favor of the [format
    API](https://fmt.dev/latest/api.html#format-api) with compile-time
    handling of format strings.

-   Disallowed formatting of multibyte strings into a wide character
    target (https://github.com/fmtlib/fmt/pull/606).

-   Improved documentation
    (https://github.com/fmtlib/fmt/pull/515,
    mt/issues/614,
    mt/pull/617,
    mt/pull/661,
    mt/pull/680).
    Thanks @ibell, @mihaitodor and @johnthagen.

-   Implemented more efficient handling of large number of format
    arguments.

-   Introduced an inline namespace for symbol versioning.

-   Added debug postfix `d` to the `fmt` library name
    (https://github.com/fmtlib/fmt/issues/636).

-   Removed unnecessary `fmt/` prefix in includes
    (https://github.com/fmtlib/fmt/pull/397). Thanks @chronoxor.

-   Moved `fmt/*.h` to `include/fmt/*.h` to prevent irrelevant files and
    directories appearing on the include search paths when fmt is used
    as a subproject and moved source files to the `src` directory.

-   Added qmake project file `support/fmt.pro`
    (https://github.com/fmtlib/fmt/pull/641). Thanks @cowo78.

-   Added Gradle build file `support/build.gradle`
    (https://github.com/fmtlib/fmt/pull/649). Thanks @luncliff.

-   Removed `FMT_CPPFORMAT` CMake option.

-   Fixed a name conflict with the macro `CHAR_WIDTH` in glibc
    (https://github.com/fmtlib/fmt/pull/616). Thanks @aroig.

-   Fixed handling of nested braces in `fmt::join`
    (https://github.com/fmtlib/fmt/issues/638).

-   Added `SOURCELINK_SUFFIX` for compatibility with Sphinx 1.5
    (https://github.com/fmtlib/fmt/pull/497). Thanks @ginggs.

-   Added a missing `inline` in the header-only mode
    (https://github.com/fmtlib/fmt/pull/626). Thanks @aroig.

-   Fixed various compiler warnings
    (https://github.com/fmtlib/fmt/pull/640,
    mt/pull/656,
    mt/pull/679,
    mt/pull/681,
    mt/pull/705,
    mt/issues/715,
    mt/pull/717,
    mt/pull/720,
    mt/pull/723,
    mt/pull/726,
    mt/pull/730,
    mt/pull/739).
    Thanks @peterbell10, @LarsGullik, @foonathan, @eliaskosunen,
    @christianparpart, @DanielaE and @mwinterb.

-   Worked around an MSVC bug and fixed several warnings
    (https://github.com/fmtlib/fmt/pull/653). Thanks @alabuzhev.

-   Worked around GCC bug 67371
    (https://github.com/fmtlib/fmt/issues/682).

-   Fixed compilation with `-fno-exceptions`
    (https://github.com/fmtlib/fmt/pull/655). Thanks @chenxiaolong.

-   Made `constexpr remove_prefix` gcc version check tighter
    (https://github.com/fmtlib/fmt/issues/648).

-   Renamed internal type enum constants to prevent collision with
    poorly written C libraries
    (https://github.com/fmtlib/fmt/issues/644).

-   Added detection of `wostream operator<<`
    (https://github.com/fmtlib/fmt/issues/650).

-   Fixed compilation on OpenBSD
    (https://github.com/fmtlib/fmt/pull/660). Thanks @hubslave.

-   Fixed compilation on FreeBSD 12
    (https://github.com/fmtlib/fmt/pull/732). Thanks @dankm.

-   Fixed compilation when there is a mismatch between `-std` options
    between the library and user code
    (https://github.com/fmtlib/fmt/issues/664).

-   Fixed compilation with GCC 7 and `-std=c++11`
    (https://github.com/fmtlib/fmt/issues/734).

-   Improved generated binary code on GCC 7 and older
    (https://github.com/fmtlib/fmt/issues/668).

-   Fixed handling of numeric alignment with no width
    (https://github.com/fmtlib/fmt/issues/675).

-   Fixed handling of empty strings in UTF8/16 converters
    (https://github.com/fmtlib/fmt/pull/676). Thanks @vgalka-sl.

-   Fixed formatting of an empty `string_view`
    (https://github.com/fmtlib/fmt/issues/689).

-   Fixed detection of `string_view` on libc++
    (https://github.com/fmtlib/fmt/issues/686).

-   Fixed DLL issues (https://github.com/fmtlib/fmt/pull/696).
    Thanks @sebkoenig.

-   Fixed compile checks for mixing narrow and wide strings
    (https://github.com/fmtlib/fmt/issues/690).

-   Disabled unsafe implicit conversion to `std::string`
    (https://github.com/fmtlib/fmt/issues/729).

-   Fixed handling of reused format specs (as in `fmt::join`) for
    pointers (https://github.com/fmtlib/fmt/pull/725). Thanks @mwinterb.

-   Fixed installation of `fmt/ranges.h`
    (https://github.com/fmtlib/fmt/pull/738). Thanks @sv1990.

# 4.1.0 - 2017-12-20

-   Added `fmt::to_wstring()` in addition to `fmt::to_string()`
    (https://github.com/fmtlib/fmt/pull/559). Thanks @alabuzhev.
-   Added support for C++17 `std::string_view`
    (https://github.com/fmtlib/fmt/pull/571 and
    mt/pull/578).
    Thanks @thelostt and @mwinterb.
-   Enabled stream exceptions to catch errors
    (https://github.com/fmtlib/fmt/issues/581). Thanks @crusader-mike.
-   Allowed formatting of class hierarchies with `fmt::format_arg()`
    (https://github.com/fmtlib/fmt/pull/547). Thanks @rollbear.
-   Removed limitations on character types
    (https://github.com/fmtlib/fmt/pull/563). Thanks @Yelnats321.
-   Conditionally enabled use of `std::allocator_traits`
    (https://github.com/fmtlib/fmt/pull/583). Thanks @mwinterb.
-   Added support for `const` variadic member function emulation with
    `FMT_VARIADIC_CONST`
    (https://github.com/fmtlib/fmt/pull/591). Thanks @ludekvodicka.
-   Various bugfixes: bad overflow check, unsupported implicit type
    conversion when determining formatting function, test segfaults
    (https://github.com/fmtlib/fmt/issues/551), ill-formed
    macros (https://github.com/fmtlib/fmt/pull/542) and
    ambiguous overloads
    (https://github.com/fmtlib/fmt/issues/580). Thanks @xylosper.
-   Prevented warnings on MSVC
    (https://github.com/fmtlib/fmt/pull/605,
    mt/pull/602, and
    mt/pull/545), clang
    (https://github.com/fmtlib/fmt/pull/582), GCC
    (https://github.com/fmtlib/fmt/issues/573), various
    conversion warnings (https://github.com/fmtlib/fmt/pull/609,
    mt/pull/567,
    mt/pull/553 and
    mt/pull/553), and added
    `override` and `[[noreturn]]`
    (https://github.com/fmtlib/fmt/pull/549 and
    mt/issues/555).
    Thanks @alabuzhev, @virgiliofornazin, @alexanderbock, @yumetodo, @VaderY,
    @jpcima, @thelostt and @Manu343726.
-   Improved CMake: Used `GNUInstallDirs` to set installation location
    (https://github.com/fmtlib/fmt/pull/610) and fixed warnings
    (https://github.com/fmtlib/fmt/pull/536 and
    mt/pull/556).
    Thanks @mikecrowe, @evgen231 and @henryiii.

# 4.0.0 - 2017-06-27

-   Removed old compatibility headers `cppformat/*.h` and CMake options
    (https://github.com/fmtlib/fmt/pull/527). Thanks @maddinat0r.

-   Added `string.h` containing `fmt::to_string()` as alternative to
    `std::to_string()` as well as other string writer functionality
    (https://github.com/fmtlib/fmt/issues/326 and
    mt/pull/441):

    ```c++
    #include "fmt/string.h"

    std::string answer = fmt::to_string(42);
    ```

    Thanks @glebov-andrey.

-   Moved `fmt::printf()` to new `printf.h` header and allowed `%s` as
    generic specifier (https://github.com/fmtlib/fmt/pull/453),
    made `%.f` more conformant to regular `printf()`
    (https://github.com/fmtlib/fmt/pull/490), added custom
    writer support (https://github.com/fmtlib/fmt/issues/476)
    and implemented missing custom argument formatting
    (https://github.com/fmtlib/fmt/pull/339 and
    mt/pull/340):

    ```c++
    #include "fmt/printf.h"

    // %s format specifier can be used with any argument type.
    fmt::printf("%s", 42);
    ```

    Thanks @mojoBrendan, @manylegged and @spacemoose.
    See also mt/issues/360,
    mt/issues/335 and
    mt/issues/331.

-   Added `container.h` containing a `BasicContainerWriter` to write to
    containers like `std::vector`
    (https://github.com/fmtlib/fmt/pull/450). Thanks @polyvertex.

-   Added `fmt::join()` function that takes a range and formats its
    elements separated by a given string
    (https://github.com/fmtlib/fmt/pull/466):

    ```c++
    #include "fmt/format.h"

    std::vector<double> v = {1.2, 3.4, 5.6};
    // Prints "(+01.20, +03.40, +05.60)".
    fmt::print("({:+06.2f})", fmt::join(v.begin(), v.end(), ", "));
    ```

    Thanks @olivier80.

-   Added support for custom formatting specifications to simplify
    customization of built-in formatting
    (https://github.com/fmtlib/fmt/pull/444). Thanks @polyvertex.
    See also mt/issues/439.

-   Added `fmt::format_system_error()` for error code formatting
    (https://github.com/fmtlib/fmt/issues/323 and
    mt/pull/526). Thanks @maddinat0r.

-   Added thread-safe `fmt::localtime()` and `fmt::gmtime()` as
    replacement for the standard version to `time.h`
    (https://github.com/fmtlib/fmt/pull/396). Thanks @codicodi.

-   Internal improvements to `NamedArg` and `ArgLists`
    (https://github.com/fmtlib/fmt/pull/389 and
    mt/pull/390). Thanks @chronoxor.

-   Fixed crash due to bug in `FormatBuf`
    (https://github.com/fmtlib/fmt/pull/493). Thanks @effzeh. See also
    mt/issues/480 and
    mt/issues/491.

-   Fixed handling of wide strings in `fmt::StringWriter`.

-   Improved compiler error messages
    (https://github.com/fmtlib/fmt/issues/357).

-   Fixed various warnings and issues with various compilers
    (https://github.com/fmtlib/fmt/pull/494,
    mt/pull/499,
    mt/pull/483,
    mt/pull/485,
    mt/pull/482,
    mt/pull/475,
    mt/pull/473 and
    mt/pull/414).
    Thanks @chronoxor, @zhaohuaxishi, @pkestene, @dschmidt and @0x414c.

-   Improved CMake: targets are now namespaced
    (https://github.com/fmtlib/fmt/pull/511 and
    mt/pull/513), supported
    header-only `printf.h`
    (https://github.com/fmtlib/fmt/pull/354), fixed issue with
    minimal supported library subset
    (https://github.com/fmtlib/fmt/issues/418,
    mt/pull/419 and
    mt/pull/420).
    Thanks @bjoernthiel, @niosHD, @LogicalKnight and @alabuzhev.

-   Improved documentation (https://github.com/fmtlib/fmt/pull/393).
    Thanks @pwm1234.

# 3.0.2 - 2017-06-14

-   Added `FMT_VERSION` macro
    (https://github.com/fmtlib/fmt/issues/411).
-   Used `FMT_NULL` instead of literal `0`
    (https://github.com/fmtlib/fmt/pull/409). Thanks @alabuzhev.
-   Added extern templates for `format_float`
    (https://github.com/fmtlib/fmt/issues/413).
-   Fixed implicit conversion issue
    (https://github.com/fmtlib/fmt/issues/507).
-   Fixed signbit detection
    (https://github.com/fmtlib/fmt/issues/423).
-   Fixed naming collision
    (https://github.com/fmtlib/fmt/issues/425).
-   Fixed missing intrinsic for C++/CLI
    (https://github.com/fmtlib/fmt/pull/457). Thanks @calumr.
-   Fixed Android detection
    (https://github.com/fmtlib/fmt/pull/458). Thanks @Gachapen.
-   Use lean `windows.h` if not in header-only mode
    (https://github.com/fmtlib/fmt/pull/503). Thanks @Quentin01.
-   Fixed issue with CMake exporting C++11 flag
    (https://github.com/fmtlib/fmt/pull/455). Thanks @EricWF.
-   Fixed issue with nvcc and MSVC compiler bug and MinGW
    (https://github.com/fmtlib/fmt/issues/505).
-   Fixed DLL issues (https://github.com/fmtlib/fmt/pull/469 and
    mt/pull/502).
    Thanks @richardeakin and @AndreasSchoenle.
-   Fixed test compilation under FreeBSD
    (https://github.com/fmtlib/fmt/issues/433).
-   Fixed various warnings
    (https://github.com/fmtlib/fmt/pull/403,
    mt/pull/410 and
    mt/pull/510).
    Thanks @Lecetem, @chenhayat and @trozen.
-   Worked around a broken `__builtin_clz` in clang with MS codegen
    (https://github.com/fmtlib/fmt/issues/519).
-   Removed redundant include
    (https://github.com/fmtlib/fmt/issues/479).
-   Fixed documentation issues.

# 3.0.1 - 2016-11-01

-   Fixed handling of thousands separator
    (https://github.com/fmtlib/fmt/issues/353).
-   Fixed handling of `unsigned char` strings
    (https://github.com/fmtlib/fmt/issues/373).
-   Corrected buffer growth when formatting time
    (https://github.com/fmtlib/fmt/issues/367).
-   Removed warnings under MSVC and clang
    (https://github.com/fmtlib/fmt/issues/318,
    mt/issues/250, also merged
    mt/pull/385 and
    mt/pull/361).
    Thanks @jcelerier and @nmoehrle.
-   Fixed compilation issues under Android
    (https://github.com/fmtlib/fmt/pull/327,
    mt/issues/345 and
    mt/pull/381), FreeBSD
    (https://github.com/fmtlib/fmt/pull/358), Cygwin
    (https://github.com/fmtlib/fmt/issues/388), MinGW
    (https://github.com/fmtlib/fmt/issues/355) as well as other
    issues (https://github.com/fmtlib/fmt/issues/350,
    mt/issues/355,
    mt/pull/348,
    mt/pull/402,
    mt/pull/405).
    Thanks @dpantele, @hghwng, @arvedarved, @LogicalKnight and @JanHellwig.
-   Fixed some documentation issues and extended specification
    (https://github.com/fmtlib/fmt/issues/320,
    mt/pull/333,
    mt/issues/347,
    mt/pull/362). Thanks @smellman.

# 3.0.0 - 2016-05-07

-   The project has been renamed from C++ Format (cppformat) to fmt for
    consistency with the used namespace and macro prefix
    (https://github.com/fmtlib/fmt/issues/307). Library headers
    are now located in the `fmt` directory:

    ```c++
    #include "fmt/format.h"
    ```

    Including `format.h` from the `cppformat` directory is deprecated
    but works via a proxy header which will be removed in the next major
    version.

    The documentation is now available at <https://fmt.dev>.

-   Added support for
    [strftime](http://en.cppreference.com/w/cpp/chrono/c/strftime)-like
    [date and time
    formatting](https://fmt.dev/3.0.0/api.html#date-and-time-formatting)
    (https://github.com/fmtlib/fmt/issues/283):

    ```c++
    #include "fmt/time.h"

    std::time_t t = std::time(nullptr);
    // Prints "The date is 2016-04-29." (with the current date)
    fmt::print("The date is {:%Y-%m-%d}.", *std::localtime(&t));
    ```

-   `std::ostream` support including formatting of user-defined types
    that provide overloaded `operator<<` has been moved to
    `fmt/ostream.h`:

    ```c++
    #include "fmt/ostream.h"

    class Date {
      int year_, month_, day_;
    public:
      Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

      friend std::ostream &operator<<(std::ostream &os, const Date &d) {
        return os << d.year_ << '-' << d.month_ << '-' << d.day_;
      }
    };

    std::string s = fmt::format("The date is {}", Date(2012, 12, 9));
    // s == "The date is 2012-12-9"
    ```

-   Added support for [custom argument
    formatters](https://fmt.dev/3.0.0/api.html#argument-formatters)
    (https://github.com/fmtlib/fmt/issues/235).

-   Added support for locale-specific integer formatting with the `n`
    specifier (https://github.com/fmtlib/fmt/issues/305):

    ```c++
    std::setlocale(LC_ALL, "en_US.utf8");
    fmt::print("cppformat: {:n}\n", 1234567); // prints 1,234,567
    ```

-   Sign is now preserved when formatting an integer with an incorrect
    `printf` format specifier
    (https://github.com/fmtlib/fmt/issues/265):

    ```c++
    fmt::printf("%lld", -42); // prints -42
    ```

    Note that it would be an undefined behavior in `std::printf`.

-   Length modifiers such as `ll` are now optional in printf formatting
    functions and the correct type is determined automatically
    (https://github.com/fmtlib/fmt/issues/255):

    ```c++
    fmt::printf("%d", std::numeric_limits<long long>::max());
    ```

    Note that it would be an undefined behavior in `std::printf`.

-   Added initial support for custom formatters
    (https://github.com/fmtlib/fmt/issues/231).

-   Fixed detection of user-defined literal support on Intel C++
    compiler (https://github.com/fmtlib/fmt/issues/311,
    mt/pull/312).
    Thanks @dean0x7d and @speth.

-   Reduced compile time
    (https://github.com/fmtlib/fmt/pull/243,
    mt/pull/249,
    mt/issues/317):

    ![](https://cloud.githubusercontent.com/assets/4831417/11614060/b9e826d2-9c36-11e5-8666-d4131bf503ef.png)

    ![](https://cloud.githubusercontent.com/assets/4831417/11614080/6ac903cc-9c37-11e5-8165-26df6efae364.png)

    Thanks @dean0x7d.

-   Compile test fixes (https://github.com/fmtlib/fmt/pull/313).
    Thanks @dean0x7d.

-   Documentation fixes (https://github.com/fmtlib/fmt/pull/239,
    mt/issues/248,
    mt/issues/252,
    mt/pull/258,
    mt/issues/260,
    mt/issues/301,
    mt/pull/309).
    Thanks @ReadmeCritic @Gachapen and @jwilk.

-   Fixed compiler and sanitizer warnings
    (https://github.com/fmtlib/fmt/issues/244,
    mt/pull/256,
    mt/pull/259,
    mt/issues/263,
    mt/issues/274,
    mt/pull/277,
    mt/pull/286,
    mt/issues/291,
    mt/issues/296,
    mt/issues/308).
    Thanks @mwinterb, @pweiskircher and @Naios.

-   Improved compatibility with Windows Store apps
    (https://github.com/fmtlib/fmt/issues/280,
    mt/pull/285) Thanks @mwinterb.

-   Added tests of compatibility with older C++ standards
    (https://github.com/fmtlib/fmt/pull/273). Thanks @niosHD.

-   Fixed Android build
    (https://github.com/fmtlib/fmt/pull/271). Thanks @newnon.

-   Changed `ArgMap` to be backed by a vector instead of a map.
    (https://github.com/fmtlib/fmt/issues/261,
    mt/pull/262). Thanks @mwinterb.

-   Added `fprintf` overload that writes to a `std::ostream`
    (https://github.com/fmtlib/fmt/pull/251).
    Thanks @nickhutchinson.

-   Export symbols when building a Windows DLL
    (https://github.com/fmtlib/fmt/pull/245).
    Thanks @macdems.

-   Fixed compilation on Cygwin
    (https://github.com/fmtlib/fmt/issues/304).

-   Implemented a workaround for a bug in Apple LLVM version 4.2 of
    clang (https://github.com/fmtlib/fmt/issues/276).

-   Implemented a workaround for Google Test bug
    oogletest/issues/705 on gcc 6
    (https://github.com/fmtlib/fmt/issues/268). Thanks @octoploid.

-   Removed Biicode support because the latter has been discontinued.

# 2.1.1 - 2016-04-11

-   The install location for generated CMake files is now configurable
    via the `FMT_CMAKE_DIR` CMake variable
    (https://github.com/fmtlib/fmt/pull/299). Thanks @niosHD.
-   Documentation fixes
    (https://github.com/fmtlib/fmt/issues/252).

# 2.1.0 - 2016-03-21

-   Project layout and build system improvements
    (https://github.com/fmtlib/fmt/pull/267):

    -   The code have been moved to the `cppformat` directory. Including
        `format.h` from the top-level directory is deprecated but works
        via a proxy header which will be removed in the next major
        version.
    -   C++ Format CMake targets now have proper interface definitions.
    -   Installed version of the library now supports the header-only
        configuration.
    -   Targets `doc`, `install`, and `test` are now disabled if C++
        Format is included as a CMake subproject. They can be enabled by
        setting `FMT_DOC`, `FMT_INSTALL`, and `FMT_TEST` in the parent
        project.

    Thanks @niosHD.

# 2.0.1 - 2016-03-13

-   Improved CMake find and package support
    (https://github.com/fmtlib/fmt/issues/264). Thanks @niosHD.
-   Fix compile error with Android NDK and mingw32
    (https://github.com/fmtlib/fmt/issues/241). Thanks @Gachapen.
-   Documentation fixes
    (https://github.com/fmtlib/fmt/issues/248,
    mt/issues/260).

# 2.0.0 - 2015-12-01

## General

-   \[Breaking\] Named arguments
    (https://github.com/fmtlib/fmt/pull/169,
    mt/pull/173,
    mt/pull/174):

    ```c++
    fmt::print("The answer is {answer}.", fmt::arg("answer", 42));
    ```

    Thanks @jamboree.

-   \[Experimental\] User-defined literals for format and named
    arguments (https://github.com/fmtlib/fmt/pull/204,
    mt/pull/206,
    mt/pull/207):

    ```c++
    using namespace fmt::literals;
    fmt::print("The answer is {answer}.", "answer"_a=42);
    ```

    Thanks @dean0x7d.

-   \[Breaking\] Formatting of more than 16 arguments is now supported
    when using variadic templates
    (https://github.com/fmtlib/fmt/issues/141). Thanks @Shauren.

-   Runtime width specification
    (https://github.com/fmtlib/fmt/pull/168):

    ```c++
    fmt::format("{0:{1}}", 42, 5); // gives "   42"
    ```

    Thanks @jamboree.

-   \[Breaking\] Enums are now formatted with an overloaded
    `std::ostream` insertion operator (`operator<<`) if available
    (https://github.com/fmtlib/fmt/issues/232).

-   \[Breaking\] Changed default `bool` format to textual, \"true\" or
    \"false\" (https://github.com/fmtlib/fmt/issues/170):

    ```c++
    fmt::print("{}", true); // prints "true"
    ```

    To print `bool` as a number use numeric format specifier such as
    `d`:

    ```c++
    fmt::print("{:d}", true); // prints "1"
    ```

-   `fmt::printf` and `fmt::sprintf` now support formatting of `bool`
    with the `%s` specifier giving textual output, \"true\" or \"false\"
    (https://github.com/fmtlib/fmt/pull/223):

    ```c++
    fmt::printf("%s", true); // prints "true"
    ```

    Thanks @LarsGullik.

-   \[Breaking\] `signed char` and `unsigned char` are now formatted as
    integers by default
    (https://github.com/fmtlib/fmt/pull/217).

-   \[Breaking\] Pointers to C strings can now be formatted with the `p`
    specifier (https://github.com/fmtlib/fmt/pull/223):

    ```c++
    fmt::print("{:p}", "test"); // prints pointer value
    ```

    Thanks @LarsGullik.

-   \[Breaking\] `fmt::printf` and `fmt::sprintf` now print null
    pointers as `(nil)` and null strings as `(null)` for consistency
    with glibc (https://github.com/fmtlib/fmt/pull/226).
    Thanks @LarsGullik.

-   \[Breaking\] `fmt::(s)printf` now supports formatting of objects of
    user-defined types that provide an overloaded `std::ostream`
    insertion operator (`operator<<`)
    (https://github.com/fmtlib/fmt/issues/201):

    ```c++
    fmt::printf("The date is %s", Date(2012, 12, 9));
    ```

-   \[Breaking\] The `Buffer` template is now part of the public API and
    can be used to implement custom memory buffers
    (https://github.com/fmtlib/fmt/issues/140). Thanks @polyvertex.

-   \[Breaking\] Improved compatibility between `BasicStringRef` and
    [std::experimental::basic_string_view](
    http://en.cppreference.com/w/cpp/experimental/basic_string_view)
    (https://github.com/fmtlib/fmt/issues/100,
    mt/issues/159,
    mt/issues/183):

    -   Comparison operators now compare string content, not pointers
    -   `BasicStringRef::c_str` replaced by `BasicStringRef::data`
    -   `BasicStringRef` is no longer assumed to be null-terminated

    References to null-terminated strings are now represented by a new
    class, `BasicCStringRef`.

-   Dependency on pthreads introduced by Google Test is now optional
    (https://github.com/fmtlib/fmt/issues/185).

-   New CMake options `FMT_DOC`, `FMT_INSTALL` and `FMT_TEST` to control
    generation of `doc`, `install` and `test` targets respectively, on
    by default (https://github.com/fmtlib/fmt/issues/197,
    mt/issues/198,
    mt/issues/200). Thanks @maddinat0r.

-   `noexcept` is now used when compiling with MSVC2015
    (https://github.com/fmtlib/fmt/pull/215). Thanks @dmkrepo.

-   Added an option to disable use of `windows.h` when
    `FMT_USE_WINDOWS_H` is defined as 0 before including `format.h`
    (https://github.com/fmtlib/fmt/issues/171). Thanks @alfps.

-   \[Breaking\] `windows.h` is now included with `NOMINMAX` unless
    `FMT_WIN_MINMAX` is defined. This is done to prevent breaking code
    using `std::min` and `std::max` and only affects the header-only
    configuration (https://github.com/fmtlib/fmt/issues/152,
    mt/pull/153,
    mt/pull/154). Thanks @DevO2012.

-   Improved support for custom character types
    (https://github.com/fmtlib/fmt/issues/171). Thanks @alfps.

-   Added an option to disable use of IOStreams when `FMT_USE_IOSTREAMS`
    is defined as 0 before including `format.h`
    (https://github.com/fmtlib/fmt/issues/205,
    mt/pull/208). Thanks @JodiTheTigger.

-   Improved detection of `isnan`, `isinf` and `signbit`.

## Optimization

-   Made formatting of user-defined types more efficient with a custom
    stream buffer (https://github.com/fmtlib/fmt/issues/92,
    mt/pull/230). Thanks @NotImplemented.
-   Further improved performance of `fmt::Writer` on integer formatting
    and fixed a minor regression. Now it is \~7% faster than
    `karma::generate` on Karma\'s benchmark
    (https://github.com/fmtlib/fmt/issues/186).
-   \[Breaking\] Reduced compiled code
    size
    (https://github.com/fmtlib/fmt/issues/143,
    mt/pull/149).

## Distribution

-   \[Breaking\] Headers are now installed in
    `${CMAKE_INSTALL_PREFIX}/include/cppformat`
    (https://github.com/fmtlib/fmt/issues/178). Thanks @jackyf.

-   \[Breaking\] Changed the library name from `format` to `cppformat`
    for consistency with the project name and to avoid potential
    conflicts (https://github.com/fmtlib/fmt/issues/178).
    Thanks @jackyf.

-   C++ Format is now available in [Debian](https://www.debian.org/)
    GNU/Linux
    ([stretch](https://packages.debian.org/source/stretch/cppformat),
    [sid](https://packages.debian.org/source/sid/cppformat)) and derived
    distributions such as
    [Ubuntu](https://launchpad.net/ubuntu/+source/cppformat) 15.10 and
    later (https://github.com/fmtlib/fmt/issues/155):

        $ sudo apt-get install libcppformat1-dev

    Thanks @jackyf.

-   [Packages for Fedora and
    RHEL](https://admin.fedoraproject.org/pkgdb/package/cppformat/) are
    now available. Thanks Dave Johansen.

-   C++ Format can now be installed via [Homebrew](http://brew.sh/) on
    OS X (https://github.com/fmtlib/fmt/issues/157):

        $ brew install cppformat

    Thanks @ortho and Anatoliy Bulukin.

## Documentation

-   Migrated from ReadTheDocs to GitHub Pages for better responsiveness
    and reliability (https://github.com/fmtlib/fmt/issues/128).
    New documentation address is <http://cppformat.github.io/>.
-   Added [Building thedocumentation](
    https://fmt.dev/2.0.0/usage.html#building-the-documentation)
    section to the documentation.
-   Documentation build script is now compatible with Python 3 and newer
    pip versions. (https://github.com/fmtlib/fmt/pull/189,
    mt/issues/209).
    Thanks @JodiTheTigger and @xentec.
-   Documentation fixes and improvements
    (https://github.com/fmtlib/fmt/issues/36,
    mt/issues/75,
    mt/issues/125,
    mt/pull/160,
    mt/pull/161,
    mt/issues/162,
    mt/issues/165,
    mt/issues/210). 
    Thanks @syohex.
-   Fixed out-of-tree documentation build
    (https://github.com/fmtlib/fmt/issues/177). Thanks @jackyf.

## Fixes

-   Fixed `initializer_list` detection
    (https://github.com/fmtlib/fmt/issues/136). Thanks @Gachapen.

-   \[Breaking\] Fixed formatting of enums with numeric format
    specifiers in `fmt::(s)printf`
    (https://github.com/fmtlib/fmt/issues/131,
    mt/issues/139):

    ```c++
    enum { ANSWER = 42 };
    fmt::printf("%d", ANSWER);
    ```

    Thanks @Naios.

-   Improved compatibility with old versions of MinGW
    (https://github.com/fmtlib/fmt/issues/129,
    mt/pull/130,
    mt/issues/132). Thanks @cstamford.

-   Fixed a compile error on MSVC with disabled exceptions
    (https://github.com/fmtlib/fmt/issues/144).

-   Added a workaround for broken implementation of variadic templates
    in MSVC2012 (https://github.com/fmtlib/fmt/issues/148).

-   Placed the anonymous namespace within `fmt` namespace for the
    header-only configuration (https://github.com/fmtlib/fmt/issues/171).
    Thanks @alfps.

-   Fixed issues reported by Coverity Scan
    (https://github.com/fmtlib/fmt/issues/187,
    mt/issues/192).

-   Implemented a workaround for a name lookup bug in MSVC2010
    (https://github.com/fmtlib/fmt/issues/188).

-   Fixed compiler warnings
    (https://github.com/fmtlib/fmt/issues/95,
    mt/issues/96,
    mt/pull/114,
    mt/issues/135,
    mt/issues/142,
    mt/issues/145,
    mt/issues/146,
    mt/issues/158,
    mt/issues/163,
    mt/issues/175,
    mt/issues/190,
    mt/pull/191,
    mt/issues/194,
    mt/pull/196,
    mt/issues/216,
    mt/pull/218,
    mt/pull/220,
    mt/pull/229,
    mt/issues/233,
    mt/issues/234,
    mt/pull/236,
    mt/issues/281,
    mt/issues/289).
    Thanks @seanmiddleditch, @dixlorenz, @CarterLi, @Naios, @fmatthew5876,
    @LevskiWeng, @rpopescu, @gabime, @cubicool, @jkflying, @LogicalKnight,
    @inguin and @Jopie64.

-   Fixed portability issues (mostly causing test failures) on ARM,
    ppc64, ppc64le, s390x and SunOS 5.11 i386
    (https://github.com/fmtlib/fmt/issues/138,
    mt/issues/179,
    mt/issues/180,
    mt/issues/202,
    mt/issues/225, [Red Hat Bugzilla
    Bug 1260297](https://bugzilla.redhat.com/show_bug.cgi?id=1260297)).
    Thanks @Naios, @jackyf and Dave Johansen.

-   Fixed a name conflict with macro `free` defined in `crtdbg.h` when
    `_CRTDBG_MAP_ALLOC` is set (https://github.com/fmtlib/fmt/issues/211).

-   Fixed shared library build on OS X
    (https://github.com/fmtlib/fmt/pull/212). Thanks @dean0x7d.

-   Fixed an overload conflict on MSVC when `/Zc:wchar_t-` option is
    specified (https://github.com/fmtlib/fmt/pull/214).
    Thanks @slavanap.

-   Improved compatibility with MSVC 2008
    (https://github.com/fmtlib/fmt/pull/236). Thanks @Jopie64.

-   Improved compatibility with bcc32
    (https://github.com/fmtlib/fmt/issues/227).

-   Fixed `static_assert` detection on Clang
    (https://github.com/fmtlib/fmt/pull/228). Thanks @dean0x7d.

# 1.1.0 - 2015-03-06

-   Added `BasicArrayWriter`, a class template that provides operations
    for formatting and writing data into a fixed-size array
    (https://github.com/fmtlib/fmt/issues/105 and
    mt/issues/122):

    ```c++
    char buffer[100];
    fmt::ArrayWriter w(buffer);
    w.write("The answer is {}", 42);
    ```

-   Added [0 A.D.](http://play0ad.com/) and [PenUltima Online
    (POL)](http://www.polserver.com/) to the list of notable projects
    using C++ Format.

-   C++ Format now uses MSVC intrinsics for better formatting performance
    (https://github.com/fmtlib/fmt/pull/115,
    mt/pull/116,
    mt/pull/118 and
    mt/pull/121). Previously these
    optimizations where only used on GCC and Clang.
    Thanks @CarterLi and @objectx.

-   CMake install target
    (https://github.com/fmtlib/fmt/pull/119). Thanks @TrentHouliston.

    You can now install C++ Format with `make install` command.

-   Improved [Biicode](http://www.biicode.com/) support
    (https://github.com/fmtlib/fmt/pull/98 and
    mt/pull/104).
    Thanks @MariadeAnton and @franramirez688.

-   Improved support for building with [Android NDK](
    https://developer.android.com/tools/sdk/ndk/index.html)
    (https://github.com/fmtlib/fmt/pull/107). Thanks @newnon.

    The android-ndk-example
    repository provides and example of using C++ Format with Android NDK:

    ![](https://raw.githubusercontent.com/fmtlib/android-ndk-example/master/screenshot.png)

-   Improved documentation of `SystemError` and `WindowsError`
    (https://github.com/fmtlib/fmt/issues/54).

-   Various code improvements
    (https://github.com/fmtlib/fmt/pull/110,
    mt/pull/111
    mt/pull/112). Thanks @CarterLi.

-   Improved compile-time errors when formatting wide into narrow
    strings (https://github.com/fmtlib/fmt/issues/117).

-   Fixed `BasicWriter::write` without formatting arguments when C++11
    support is disabled
    (https://github.com/fmtlib/fmt/issues/109).

-   Fixed header-only build on OS X with GCC 4.9
    (https://github.com/fmtlib/fmt/issues/124).

-   Fixed packaging issues (https://github.com/fmtlib/fmt/issues/94).

-   Added changelog
    (https://github.com/fmtlib/fmt/issues/103).

# 1.0.0 - 2015-02-05

-   Add support for a header-only configuration when `FMT_HEADER_ONLY`
    is defined before including `format.h`:

    ```c++
    #define FMT_HEADER_ONLY
    #include "format.h"
    ```

-   Compute string length in the constructor of `BasicStringRef` instead
    of the `size` method
    (https://github.com/fmtlib/fmt/issues/79). This eliminates
    size computation for string literals on reasonable optimizing
    compilers.

-   Fix formatting of types with overloaded `operator <<` for
    `std::wostream` (https://github.com/fmtlib/fmt/issues/86):

    ```c++
    fmt::format(L"The date is {0}", Date(2012, 12, 9));
    ```

-   Fix linkage of tests on Arch Linux
    (https://github.com/fmtlib/fmt/issues/89).

-   Allow precision specifier for non-float arguments
    (https://github.com/fmtlib/fmt/issues/90):

    ```c++
    fmt::print("{:.3}\n", "Carpet"); // prints "Car"
    ```

-   Fix build on Android NDK (https://github.com/fmtlib/fmt/issues/93).

-   Improvements to documentation build procedure.

-   Remove `FMT_SHARED` CMake variable in favor of standard [BUILD_SHARED_LIBS](
    http://www.cmake.org/cmake/help/v3.0/variable/BUILD_SHARED_LIBS.html).

-   Fix error handling in `fmt::fprintf`.

-   Fix a number of warnings.

# 0.12.0 - 2014-10-25

-   \[Breaking\] Improved separation between formatting and buffer
    management. `Writer` is now a base class that cannot be instantiated
    directly. The new `MemoryWriter` class implements the default buffer
    management with small allocations done on stack. So `fmt::Writer`
    should be replaced with `fmt::MemoryWriter` in variable
    declarations.

    Old code:

    ```c++
    fmt::Writer w;
    ```

    New code:

    ```c++
    fmt::MemoryWriter w;
    ```

    If you pass `fmt::Writer` by reference, you can continue to do so:

    ```c++
    void f(fmt::Writer &w);
    ```

    This doesn\'t affect the formatting API.

-   Support for custom memory allocators
    (https://github.com/fmtlib/fmt/issues/69)

-   Formatting functions now accept [signed char]{.title-ref} and
    [unsigned char]{.title-ref} strings as arguments
    (https://github.com/fmtlib/fmt/issues/73):

    ```c++
    auto s = format("GLSL version: {}", glGetString(GL_VERSION));
    ```

-   Reduced code bloat. According to the new benchmark
    results,
    cppformat is close to `printf` and by the order of magnitude better
    than Boost Format in terms of compiled code size.

-   Improved appearance of the documentation on mobile by using the
    [Sphinx Bootstrap
    theme](http://ryan-roemer.github.io/sphinx-bootstrap-theme/):

    | Old | New |
    | --- | --- |
    | ![](https://cloud.githubusercontent.com/assets/576385/4792130/cd256436-5de3-11e4-9a62-c077d0c2b003.png) | ![](https://cloud.githubusercontent.com/assets/576385/4792131/cd29896c-5de3-11e4-8f59-cac952942bf0.png) |

# 0.11.0 - 2014-08-21

-   Safe printf implementation with a POSIX extension for positional
    arguments:

    ```c++
    fmt::printf("Elapsed time: %.2f seconds", 1.23);
    fmt::printf("%1$s, %3$d %2$s", weekday, month, day);
    ```

-   Arguments of `char` type can now be formatted as integers (Issue
    mt/issues/55):

    ```c++
    fmt::format("0x{0:02X}", 'a');
    ```

-   Deprecated parts of the API removed.

-   The library is now built and tested on MinGW with Appveyor in
    addition to existing test platforms Linux/GCC, OS X/Clang,
    Windows/MSVC.

# 0.10.0 - 2014-07-01

**Improved API**

-   All formatting methods are now implemented as variadic functions
    instead of using `operator<<` for feeding arbitrary arguments into a
    temporary formatter object. This works both with C++11 where
    variadic templates are used and with older standards where variadic
    functions are emulated by providing lightweight wrapper functions
    defined with the `FMT_VARIADIC` macro. You can use this macro for
    defining your own portable variadic functions:

    ```c++
    void report_error(const char *format, const fmt::ArgList &args) {
      fmt::print("Error: {}");
      fmt::print(format, args);
    }
    FMT_VARIADIC(void, report_error, const char *)

    report_error("file not found: {}", path);
    ```

    Apart from a more natural syntax, this also improves performance as
    there is no need to construct temporary formatter objects and
    control arguments\' lifetimes. Because the wrapper functions are
    very lightweight, this doesn\'t cause code bloat even in pre-C++11
    mode.

-   Simplified common case of formatting an `std::string`. Now it
    requires a single function call:

    ```c++
    std::string s = format("The answer is {}.", 42);
    ```

    Previously it required 2 function calls:

    ```c++
    std::string s = str(Format("The answer is {}.") << 42);
    ```

    Instead of unsafe `c_str` function, `fmt::Writer` should be used
    directly to bypass creation of `std::string`:

    ```c++
    fmt::Writer w;
    w.write("The answer is {}.", 42);
    w.c_str();  // returns a C string
    ```

    This doesn\'t do dynamic memory allocation for small strings and is
    less error prone as the lifetime of the string is the same as for
    `std::string::c_str` which is well understood (hopefully).

-   Improved consistency in naming functions that are a part of the
    public API. Now all public functions are lowercase following the
    standard library conventions. Previously it was a combination of
    lowercase and CapitalizedWords. Issue
    mt/issues/50.

-   Old functions are marked as deprecated and will be removed in the
    next release.

**Other Changes**

-   Experimental support for printf format specifications (work in
    progress):

    ```c++
    fmt::printf("The answer is %d.", 42);
    std::string s = fmt::sprintf("Look, a %s!", "string");
    ```

-   Support for hexadecimal floating point format specifiers `a` and
    `A`:

    ```c++
    print("{:a}", -42.0); // Prints -0x1.5p+5
    print("{:A}", -42.0); // Prints -0X1.5P+5
    ```

-   CMake option `FMT_SHARED` that specifies whether to build format as
    a shared library (off by default).

# 0.9.0 - 2014-05-13

-   More efficient implementation of variadic formatting functions.

-   `Writer::Format` now has a variadic overload:

    ```c++
    Writer out;
    out.Format("Look, I'm {}!", "variadic");
    ```

-   For efficiency and consistency with other overloads, variadic
    overload of the `Format` function now returns `Writer` instead of
    `std::string`. Use the `str` function to convert it to
    `std::string`:

    ```c++
    std::string s = str(Format("Look, I'm {}!", "variadic"));
    ```

-   Replaced formatter actions with output sinks: `NoAction` -\>
    `NullSink`, `Write` -\> `FileSink`, `ColorWriter` -\>
    `ANSITerminalSink`. This improves naming consistency and shouldn\'t
    affect client code unless these classes are used directly which
    should be rarely needed.

-   Added `ThrowSystemError` function that formats a message and throws
    `SystemError` containing the formatted message and system-specific
    error description. For example, the following code

    ```c++
    FILE *f = fopen(filename, "r");
    if (!f)
      ThrowSystemError(errno, "Failed to open file '{}'") << filename;
    ```

    will throw `SystemError` exception with description \"Failed to open
    file \'\<filename\>\': No such file or directory\" if file doesn\'t
    exist.

-   Support for AppVeyor continuous integration platform.

-   `Format` now throws `SystemError` in case of I/O errors.

-   Improve test infrastructure. Print functions are now tested by
    redirecting the output to a pipe.

# 0.8.0 - 2014-04-14

-   Initial release
