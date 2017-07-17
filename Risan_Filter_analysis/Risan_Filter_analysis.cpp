#include<iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <complex>

class x{
public:
    x(std::vector<std::pair<double, double> > _f){
        f = std::vector<std::pair<double, double> >(_f);
    }
    x(int delay){
        f.push_back(std::make_pair(delay, 1));
    }
    x operator+(x x_){
        std::vector<std::pair<double, double> > tmp;
        auto _v = std::vector<std::pair<double, double> >(x_.f);
        _v.insert(_v.end(), this->f.begin(), this->f.end());
        std::sort(_v.begin(), _v.end());
        std::vector<std::pair<double, double> > ret;
        double _sum = 0;
        for(int i = 0;i < _v.size(); i++){
            _sum += _v[i].second;
            if(i == _v.size() - 1 || _v[i].first != _v[i + 1].first){
                ret.push_back(std::make_pair(_v[i].first, _sum));
                _sum = 0;
            }
        }
        return ret;
    }
    std::vector<std::pair<double, double> > get() const{
        return f;
    }
    void set(std::vector<std::pair<double, double> > _f){
        f = std::vector<std::pair<double, double> >(_f);
    }
private:
    std::vector<std::pair<double, double> > f;
};
x operator*(double a, x x_){
    auto p_x_ = x_.get();
    for(int i = 0;i < p_x_.size(); i++){
        p_x_[i].second *= a;
    }
    return x(p_x_);
}
//領域は-0.5 <= f <= 0.5 //the function(filter)'s domain of definition is from -5 to 5.
std::function<double(double)> abs_impulse_response(x func){
    auto ret = [=](double f) -> double{
        std::complex<double> H(0, 0);
        auto j = std::complex<double>(0,1);
        for(int i = 0; i < func.get().capacity(); i++){
            H += func.get()[i].second * std::exp(j * 2.0 * M_PI * func.get()[i].first*f);
        }
        return std::abs(H);
    };
    return ret;
}
int main(void){

    //引数は遅れ要素でもともとnが表現されているものとする //the argments means delay. The argment is k when x(n - k).
    auto f = 0.5 * x(-1) + 0.5 * x(0);

    auto absH = abs_impulse_response(f);
    for(int i = 0;i < 101; i++)
        std::cout << 0.01 * (double)i - (double)0.5 << " " << absH(0.01 * (double)i - (double)0.5) << std::endl;

    return 0;
}