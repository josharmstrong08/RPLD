#ifndef RPLDCOMMUNICATIONS_GLOBAL_H
#define RPLDCOMMUNICATIONS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RPLDCOMMUNICATIONS_LIBRARY)
#  define RPLDCOMMUNICATIONSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RPLDCOMMUNICATIONSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RPLDCOMMUNICATIONS_GLOBAL_H
