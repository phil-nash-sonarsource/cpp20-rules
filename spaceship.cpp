#include <compare>
#include <string>

namespace spaceship {
    enum class Provenance {
        African, European
    };

namespace s6230 {

    // * Use =default (6230)
    //   https://rules.sonarsource.com/cpp/RSPEC-6230

    class Swallow {
        Provenance provenance = Provenance::European;
        int weight = 0;
    public:
        bool operator==( Swallow const& other ) const {
            return provenance == other.provenance && weight == other.weight;
        }
    };

    void test() {
        Swallow a, b;
        bool x = a == b;
        // x = a < b;
        // x = a > b;
    }
}

namespace s6187 {

    // * 6187 : Operator spaceship "<=>" should be used to define comparable types

    class Swallow {
        Provenance provenance = Provenance::African;
        int weight = 0;
    public:
        bool operator<( Swallow const& other ) const {
            return provenance < other.provenance || (provenance == other.provenance && weight < other.weight);
        }
        bool operator==( Swallow const& other ) const {
            return provenance == other.provenance && weight == other.weight;
        }
    };

    void test() {
        Swallow a, b;
        bool x = a < b;
        x = a == b;
        // x = a > b;
    }
}
namespace s6186 {

    // * 6186 : Redundant comparison operators should not be defined

    class Swallow {
        Provenance provenance = Provenance::European;
        int weight = 0;
    public:
        auto operator<=>( const Swallow& ) const = default;

        bool operator<( Swallow const& other ) const {
            return provenance < other.provenance || (provenance == other.provenance && weight < other.weight);
        }
        bool operator==( Swallow const& other ) const {
            return provenance == other.provenance && weight == other.weight;
        }
    };

    void test() {
        Swallow a, b;
        bool x = a < b;
        x = a == b;
        x = a > b;
    }
}

namespace cpp20 {
    class Swallow {
        Provenance provenance = Provenance::European;
        int weight = 0;
    public:
        auto operator<=>( const Swallow& ) const = default;
    };

    void test() {
        Swallow a, b;
        bool x = a < b;
        x = a == b;
        x = a > b;
    }
}
} // spaceship
