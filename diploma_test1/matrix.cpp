#include "matrix.h"

namespace Util
{

template class Matrix<int, 2, 2>;
template class Matrix<int, 3, 3>;
template class Matrix<float, 2, 2>;
template class Matrix<float, 3, 3>;

template class Matrix<int, 2, 3>;
template class Matrix<int, 3, 4>;
template class Matrix<float, 2, 3>;
template class Matrix<float, 3, 4>;

}
