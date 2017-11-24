using XZ = Swizzle2<SX, Offset<1>, SY>;
using YZ = Swizzle2<Offset<1>, SX, SY>;
using ZX = Swizzle2<SY, Offset<1>, SX>;
using ZY = Swizzle2<Offset<1>, SY, SX>;
using ZZ = Swizzle2<Offset<2>, UXY>;