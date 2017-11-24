template<typename A, typename B = NULL0, typename C = NULL1>
using Swizzle2 = Swizzle2T<T, A, B, C>;

using XX = Swizzle2<UXY>;
using XY = Swizzle2<SX, SY>;
using YY = Swizzle2<Offset<1>, UXY>;
using YX = Swizzle2<SY, SX>;