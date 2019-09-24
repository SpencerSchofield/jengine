#ifndef JENGINE_DEFINE_H
#define JENGINE_DEFINE_H

#ifdef JENGINE_DEBUG
#define UNIMPLEMENTED [[maybe_unused]]
#define UNSURE
#else
#define UNIMPLEMENTED
#define  UNSURE static_assert(false, "functionality has not yet been tested");
#endif

#endif // JENGINE_DEFINE_H
