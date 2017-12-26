using typename SwizzleHelper<T>::UXY;
using typename SwizzleHelper<T>::UXZ;
using typename SwizzleHelper<T>::UXW;
using typename SwizzleHelper<T>::UYZ;
using typename SwizzleHelper<T>::UYW;
using typename SwizzleHelper<T>::UZW;
using typename SwizzleHelper<T>::UXYZ;
using typename SwizzleHelper<T>::UXYZW;
using typename SwizzleHelper<T>::SX;
using typename SwizzleHelper<T>::SY;
using typename SwizzleHelper<T>::SZ;
using typename SwizzleHelper<T>::SW;
using typename SwizzleHelper<T>::P1;
using typename SwizzleHelper<T>::P2;
using typename SwizzleHelper<T>::P3;


//template<int N>
//using Offset = typename SwizzleHelper<T>:: template Offset<N>;

template<typename A, typename B = void, typename C = void, typename D = void>
using Swizzle2 = Swizzle2T<T, A, B, C, D>;
template<typename A, typename B = void, typename C = void, typename D = void>
using Swizzle3 = Swizzle3T<T, A, B, C, D>;
template<typename A, typename B = void, typename C = void, typename D = void>
using Swizzle4 = Swizzle4T<T, A, B, C, D>;
