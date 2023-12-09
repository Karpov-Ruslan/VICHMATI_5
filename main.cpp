#include <iostream>
#include <vector>
#include <cmath>

using LD = long double;
using p_vector = std::vector<std::pair<LD, LD>>;

class MathIntegr {
public:
    explicit MathIntegr(const p_vector& data) : data(data) {};

    LD TrapMethodStep(bool uUseAccurateMethod) const {
        LD ret = 0.0L;
        const size_t size = data.size();

        if (!uUseAccurateMethod) {
            for (size_t i = 1; i < size - 1; i += 2) {
                ret += (data[i - 1].second + data[i + 1].second)*(data[i + 1].first - data[i - 1].first)/2.0L;
            }
            if (size%2 == 0) {
                ret += (data[size - 1].second + data[size - 2].second)*(data[size - 1].first - data[size - 2].first)/2.0L;
            }
        }
        else {
            for (size_t i = 0; i < size - 1; i++) {
                ret += (data[i].second + data[i + 1].second)*(data[i + 1].first - data[i].first)/2.0L;
            }
        }

        return ret;
    }

    LD Richard() const {
        LD accurate_val = TrapMethodStep(true);
        LD no_accurate_val = TrapMethodStep(false);
        return accurate_val + (accurate_val - no_accurate_val)/3.0L;
    }

    LD Simpson() const {
        LD ret = 0.0L;
        for (size_t k = 0, end = data.size()/2; k < end; k++) {
            ret += (data[2*k].second + 4.0L*data[2*k + 1].second + data[2*k+2].second)*(data[2*k+2].first - data[2*k].first)/6.0L;
        }
        return ret;
    }
private:
    p_vector data;
};

int main() {
    p_vector data = {{0.0L, 1.0L}};
    for (LD x = 0.25L; x <=2.1L; x += 0.25L) {
        data.push_back(std::make_pair(x, std::sin(x)/x));
    }

    MathIntegr mathIntegr(data);

    std::cout << "Method of trapezoid (less accurate): " << mathIntegr.TrapMethodStep(false) << std::endl;
    std::cout << "Method of trapezoid (more accurate): " << mathIntegr.TrapMethodStep(true) << std::endl;
    std::cout << "Method of Richardson: " << mathIntegr.Richard() << std::endl;
    std::cout << "Method of Simpson: " << mathIntegr.Simpson() << std::endl;
    std::cout << "The real value: 1.6054129768" << std::endl;
}
