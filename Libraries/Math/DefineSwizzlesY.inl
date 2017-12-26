using XY = Swizzle2<SX, SY>;
using YX = Swizzle2<SY, SX>;
using YY = Swizzle2<P1, UXY>;

using XXY = Swizzle3<UXY, SZ>;
using XYX = Swizzle3<UXZ, SY>;
using XYY = Swizzle3<SX, UYZ>;
using YXX = Swizzle3<UYZ, SX>;
using YXY = Swizzle3<SY, UXZ>;
using YYX = Swizzle3<SZ, UXY>;
using YYY = Swizzle3<P1, UXYZ>;

using XXXY = Swizzle4<UXYZ, SW>;
using XXYX = Swizzle4<UXYW, SZ>;
using XXYY = Swizzle4<UXY, UZW>;
using XYXX = Swizzle4<UXZW, SY>;
using XYXY = Swizzle4<UXZ, UYW>;
using XYYX = Swizzle4<UXW, UYZ>;
using XYYY = Swizzle4<SX, UYZW>;

using YXXX = Swizzle4<UYZW, SX>;
using YXXY = Swizzle4<UYZ, UXW>;
using YXYX = Swizzle4<UYW, UXZ>;
using YXYY = Swizzle4<SY, UXZW>;
using YYXX = Swizzle4<UZW, UXY>;
using YYXY = Swizzle4<SZ, UXYW>;
using YYYX = Swizzle4<SW, UXYZ>;
using YYYY = Swizzle4<P1, UXYZW>;
