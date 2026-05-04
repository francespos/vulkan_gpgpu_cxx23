#include <array>
#include <expected>
#include <mdspan>
#include <print>
#include <string>
#include <string_view>
#include <utility>

namespace cxx23 {

auto divide(int x, int y) -> std::expected<int, const char*> {
    if (y == 0) {
        return std::unexpected("division for zero");
    }

    return x / y;
}

class Player {
public:
    explicit Player(std::string_view name, unsigned short age) : name_(name), age_(age) {}

    [[nodiscard]] const char* name() const {
        return name_.c_str();
    }

    [[nodiscard]] unsigned short age() const {
        return age_;
    }

    template <typename Self>
    auto&& score(this Self&& self) {
        return std::forward<Self>(self).score_;
    }

private:
    std::string name_;
    unsigned short age_;
    int score_ = 0;
};

} // namespace cxx23

int main() {
    auto print = [](std::expected<int, const char*> expected) {
        if (expected) {
            std::println("{}", *expected);
        } else {
            std::println(stderr, "Error: {}.", expected.error());
        }
    };

    std::println("Computing 3 divided by 1 ...");
    auto expected1 = cxx23::divide(3, 1);
    print(expected1);
    std::println();

    std::println("Computing 3 divided by 0 ...");
    auto expected2 = cxx23::divide(3, 0);
    print(expected2);
    std::println();

    std::array<int, 6> arr{1, 2, 3, 4, 5, 6};
    auto matrix = std::mdspan(arr.data(), 2, 3);
    std::println("matrix[1, 1] = {}", matrix[1, 1]);
    std::println();

    cxx23::Player player1("Mario", 52);
    player1.score() = 40;
    std::println("player1's score is {}", player1.score());

    const cxx23::Player player2("Luca", 17);
    std::println("player2's score is {}", player2.score());
}