# Box2D sources
INCLUDEPATH += $$PWD
SOURCES = \
        $$PWD/Collision/*.cpp \
        $$PWD/Collision/Shapes/*.cpp \
        $$PWD/Common/*.cpp \
        $$PWD/Dynamics/*.cpp \
        $$PWD/Dynamics/Contacts/*.cpp \
        $$PWD/Dynamics/Joints/*.cpp \
        $$PWD/Rope/*.cpp

HEADERS = \
	$$PWD/Box2D.h \
        $$PWD/Collision/*.h \
        $$PWD/Collision/Shapes/*.h \
        $$PWD/Common/*.h \
        $$PWD/Dynamics/*.h \
        $$PWD/Dynamics/Contacts/*.h \
        $$PWD/Dynamics/Joints/*.h \
        $$PWD/Rope/*.h

