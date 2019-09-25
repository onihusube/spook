#include "doctest/doctest.h"

#include <array>
#include <complex>

#include "spook.hpp"

namespace spook_test::dft_test {

    TEST_CASE("fft4 test") {
        {
            //1Hzのcos波
            constexpr std::array<double, 4> data = {1.0, 0.0, -1.0, 0.0};

            //周波数分解能は1Hz、r[0]は直流成分
            constexpr auto r = spook::fft_4(data);

            CHECK_EQ(std::complex<double>{0.0, 0.0}, r[0]);
            CHECK_EQ(std::complex<double>{2.0, 0.0}, r[1]);
            CHECK_EQ(std::complex<double>{0.0, 0.0}, r[2]);
            CHECK_EQ(std::complex<double>{2.0, 0.0}, r[3]);
        }
        {
            //cos(θ)+0.5sin(θ)+0.5)
            constexpr std::array<double, 4> data = {1.5, 1.0, -0.5, 0.0};

            //周波数分解能は1Hz、r[0]は直流成分
            constexpr auto r = spook::fft_4(data);

            CHECK_EQ(std::complex<double>{2.0, 0.0} , r[0]);
            CHECK_EQ(std::complex<double>{2.0, -1.0}, r[1]);
            CHECK_EQ(std::complex<double>{0.0, 0.0} , r[2]);
            CHECK_EQ(std::complex<double>{2.0, 1.0} , r[3]);
        }
    }
}