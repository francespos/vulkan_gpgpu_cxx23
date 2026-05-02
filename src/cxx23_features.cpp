#include <expected>
#include <string>
#include <print>
#include <mdspan>
#include <utility>
#include <string_view>

std::expected<int, std::string> safe_division(int x, int y) {
    if (y == 0) {
        return std::unexpected("division for zero");
    }

    return x / y;
}

void print_expected_val(std::expected<int, std::string> val) {
    if (val) {
        std::println("Result = {}", *val);
    } else {
        std::println("Error: {}", val.error());
    }
}

void print_matrix(std::mdspan<int, std::dextents<std::size_t, 2>> matrix) {
    for (size_t i = 0; i < matrix.extent(0); ++i) {
        for (size_t j = 0; j < matrix.extent(1); ++j) {
            std::print("{}    ", matrix[i, j]);
        }
        std::print("\n");
    }
}

class Person {
public:
    explicit Person(std::string_view name, std::string_view surname)
        : name_(name), surname_(surname) {}

    template<typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }

    template<typename Self>
    auto&& surname(this Self&& self) {
        return std::forward<Self>(self).surname_;
    }
private:
    std::string name_;
    std::string surname_;
};

int main() {
    std::println("Computing 3 divided by 1 ...");
    auto res1 = safe_division(3, 1);
    print_expected_val(res1);
    std::print("\n");

    std::println("Computing 3 divided by 0 ... ");
    auto res2 = safe_division(3, 0);
    print_expected_val(res2);
    std::print("\n");

    // matrix = [1, 2, 3; 4, 5, 6]
    int matrix_data[] = {1, 2, 3, 4, 5, 6};
    auto matrix = std::mdspan(matrix_data, 2, 3);
    std::println("matrix(1, 1) = {}", matrix[1, 1]);
    std::print("\n");

    std::println("Printing matrix entries:");
    print_matrix(matrix);
    std::print("\n");

    Person person1("Mario", "Rossi");
    std::println("person1 is {} {}", person1.name(), person1.surname());

    const Person person2("Luca", "Bianchi");
    std::println("person2 is {} {}", person2.name(), person2.surname());
}