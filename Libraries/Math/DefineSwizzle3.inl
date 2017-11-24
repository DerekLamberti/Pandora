template<typename A, typename B = NULL0, typename C = NULL1>
using Swizzle3 = Swizzle3T<T, A, B, C>;

using XXX = Swizzle3<UXYZ>;
using XXY = Swizzle3<UXY, SZ>;
using XXZ = Swizzle3<UXY, Offset<1>, SZ>;
using XYX = Swizzle3<UXZ, SY>;
using XYY = Swizzle3<SX, UYZ>;
using XYZ = Swizzle3<SX, SY, SZ>;
using XZX = Swizzle3<UXZ, Offset<1>, SY>;
using XZY = Swizzle3<SX, SZ, SY>;
using XZZ = Swizzle3<SX, Offset<1>, UYZ>;

using YXX = Swizzle3<UYZ, SX>;
using YXY = Swizzle3<SY, UXZ>;
using YXZ = Swizzle3<SY, SX, SZ>;
using YYX = Swizzle3<SZ, UXY>;
using YYY = Swizzle3<Offset<1>, UXYZ>;
using YYZ = Swizzle3<Offset<1>, UXY, SZ>;
using YZX = Swizzle3<SZ, SX, SY>;
using YZY = Swizzle3<Offset<1>, UXZ, SY>;
using YZZ = Swizzle3<Offset<1>, SX, UYZ>;

using ZXX = Swizzle3<UYZ, Offset<1>, SX>;
using ZXY = Swizzle3<SY, SZ, SX>;
using ZXZ = Swizzle3<SY, Offset<1>, UXZ>;
using ZYX = Swizzle3<SZ, SY, SX>;
using ZYY = Swizzle3<Offset<1>, UYZ, SX>;
using ZYZ = Swizzle3<Offset<1>, SY, UXZ>;
using ZZX = Swizzle3<SZ, Offset<1>, UXY>;
using ZZY = Swizzle3<Offset<1>, SZ, UXY>;
using ZZZ = Swizzle3<Offset<2>, UXYZ>;
