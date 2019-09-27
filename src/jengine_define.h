#ifndef JENGINE_DEFINE_H
#define JENGINE_DEFINE_H

#ifdef JENGINE_DEBUG
#define UNIMPLEMENTED [[maybe_unused]]
#define UNSURE
#else
#define UNIMPLEMENTED
#define  UNSURE static_assert(false, "functionality has not yet been tested");
#endif


#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#ifdef __GNUC__

#else
#define __PRETTY_FUNCTION__ __func__
#endif
#endif

#endif // JENGINE_DEFINE_H
