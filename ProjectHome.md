This project aims to port the Nintendo 64 graphics plugin glN64 to OpenGL ES 2.0 supporting devices (OMAP3, etc). Since most OGLES2 devices are constrained platforms, Performance will be a high priority.

Much of the core gln64 rendering has been rewritten to use native OpenGL ES 2.0, It emulates combiners with shaders and uses vertex arrays.

In its current state (14/12/09) it renders most games glN64 supports. Potentially it has greater compatibility (ie it supports PRIM\_LOD combiners, etc).