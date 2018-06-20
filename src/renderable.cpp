#include <functional>

#include "renderable.hpp"

ogld::renderable::operator std::reference_wrapper<renderable const>() const {
    return std::cref(*this);
}
